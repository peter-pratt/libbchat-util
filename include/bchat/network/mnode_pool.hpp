#pragma once

#include <chrono>
#include <filesystem>
#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "bchat/network/key_types.hpp"
#include "bchat/network/network_config.hpp"
#include "bchat/network/master_node.hpp"
#include "swarm.hpp"

namespace bchat::network {

namespace config {
    struct MnodePool {
        std::optional<std::filesystem::path> cache_directory;
        std::optional<std::filesystem::path> fallback_mnode_pool_path;
        std::chrono::minutes cache_expiration;
        std::chrono::milliseconds cache_min_lifetime;
        bool enforce_subnet_diversity;
        network::opt::retry_delay retry_delay;

        opt::netid::Target netid;
        std::vector<master_node> seed_nodes;

        size_t cache_min_size;
        size_t cache_min_swarm_size;
        uint8_t cache_num_nodes_to_use_for_refresh;
        uint8_t cache_min_num_refresh_presence_to_include_node;
        uint16_t cache_node_strike_threshold;
    };
}  // namespace config

class empty_file_exception : public std::runtime_error {
  public:
    empty_file_exception() : std::runtime_error{"Empty file"} {}
};

class MnodePool : public std::enable_shared_from_this<MnodePool> {
  public:
    using network_fetcher_t = std::function<void(Request, network_response_callback_t)>;
    using fetcher_connectivity_check_t = std::function<bool()>;

    MnodePool(
            config::MnodePool config,
            std::shared_ptr<oxen::quic::Loop> loop,
            std::shared_ptr<oxen::quic::Loop> disk_loop,
            network_fetcher_t direct_fetcher);
    ~MnodePool() = default;

    void suspend();
    void resume();

    // Sets the network fetcher which should be used once the mnode cache exists
    void set_routed_fetcher(
            network_fetcher_t routed_fetcher, fetcher_connectivity_check_t connectivity_check);

    // Returns the number of nodes currently in the pool
    size_t size();

    // Forcibly clears the cache from memory and disk
    void clear_cache();

    // Records that a specific node has failed a request
    virtual void record_node_failure(const master_node& node, bool permanent = false);
    virtual void record_node_failure(const ed25519_pubkey& key, bool permanent = false);
    uint16_t node_strike_count(const master_node& node);
    uint16_t node_strike_count(const ed25519_pubkey& key);
    void clear_node_strikes();

    // Checks if the pool is empty or stale and triggers a refresh if needed
    virtual void refresh_if_needed(
            const std::vector<master_node>& in_use_nodes,
            std::function<void()> on_refresh_complete = nullptr);

    virtual void get_swarm(
            bchat::network::x25519_pubkey swarm_pubkey,
            bool ignore_strike_count,
            std::function<void(swarm::swarm_id_t, std::vector<master_node>)> callback);

    virtual std::vector<master_node> get_unused_nodes(
            size_t count, const std::vector<master_node>& exclude = {});

  private:
    friend class TestMnodePool;

    bool _suspended = false;
    config::MnodePool _config;
    std::shared_ptr<oxen::quic::Loop> _loop;
    std::shared_ptr<oxen::quic::Loop> _disk_loop;
    network_fetcher_t _direct_fetcher;
    std::optional<network_fetcher_t> _routed_fetcher;
    std::optional<fetcher_connectivity_check_t> _routed_fetcher_connectivity_check;

    // Data
    std::vector<master_node> _mnode_cache;
    std::vector<std::pair<swarm::swarm_id_t, std::vector<master_node>>> _all_swarms;
    std::unordered_map<x25519_pubkey, std::pair<swarm::swarm_id_t, std::vector<master_node>>>
            _swarm_cache;
    std::map<ed25519_pubkey, std::vector<std::chrono::sys_seconds>> _mnode_strikes;
    bool _strikes_flush_scheduled = false;

    // Disk I/O
    std::filesystem::path _mnode_cache_file_path;
    std::filesystem::path _strikes_file_path;

    // Refresh logic
    std::chrono::system_clock::time_point _last_mnode_cache_update;
    std::optional<std::string> _current_mnode_cache_refresh_id;
    int _mnode_cache_refresh_failure_count = 0;
    std::vector<master_node> _refresh_candidate_nodes;
    std::vector<std::vector<std::byte>> _mnode_refresh_results;
    std::vector<std::function<void()>> _after_mnode_cache_refresh;

    // Disk I/O functions
    void _load_from_disk();
    static void _clear_disk_cache(const std::filesystem::path& path);
    static void _perform_cache_write(
            const std::filesystem::path& path, const std::vector<master_node>& cache);
    static void _perform_strikes_write(
            const std::filesystem::path& path,
            const std::map<ed25519_pubkey, std::vector<std::chrono::sys_seconds>>& strikes);

    // Refresh functions
    void _refresh_mnode_cache(std::optional<std::string> request_id = std::nullopt);
    void _launch_next_refresh_request(
            const std::string& request_id,
            const uint8_t index,
            const bool refreshing_from_seed_nodes,
            const bool use_direct_fetcher,
            const uint8_t total_requests);
    void _retry_refresh_request(
            const std::string& request_id,
            const uint8_t index,
            const bool refreshing_from_seed_nodes,
            const bool use_direct_fetcher,
            const uint8_t total_requests);
    void _on_refresh_complete(
            std::string refresh_id,
            std::vector<std::vector<std::byte>> raw_results,
            const bool refreshing_from_seed_nodes,
            const bool use_direct_fetcher,
            const uint8_t total_requests);
    void _update_cache(std::string refresh_id, std::vector<master_node> nodes);
};

}  // namespace bchat::network
