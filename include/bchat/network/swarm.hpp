#pragma once

#include "bchat/network/key_types.hpp"

namespace bchat::network {
struct master_node;
}  // namespace bchat::network

namespace bchat::network::swarm {

using swarm_id_t = uint64_t;
constexpr swarm_id_t INVALID_SWARM_ID = std::numeric_limits<uint64_t>::max();

swarm_id_t pubkey_to_swarm_space(const bchat::network::x25519_pubkey& pk);
std::vector<std::pair<swarm_id_t, std::vector<master_node>>> generate_swarms(
        const std::vector<master_node> nodes);
std::pair<swarm_id_t, std::vector<master_node>> get_swarm(
        const bchat::network::x25519_pubkey swarm_pubkey,
        const std::vector<std::pair<swarm_id_t, std::vector<master_node>>> all_swarms);

}  // namespace bchat::network::swarm
