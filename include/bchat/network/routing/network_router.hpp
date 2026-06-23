#pragma once

#include "bchat/network/transport/network_transport.hpp"

namespace bchat::network {

class IRouter {
  public:
    std::function<void()> on_status_changed;

    virtual ~IRouter() = default;

    virtual void suspend() = 0;
    virtual void resume(bool automatically_reconnect = true) = 0;
    virtual void close_connections() = 0;
    virtual void clear_cache() = 0;

    virtual ConnectionStatus get_status() const = 0;
    virtual std::vector<PathInfo> get_active_paths() { return {}; };
    virtual std::vector<master_node> get_all_used_nodes() { return {}; };
    virtual void send_request(Request request, network_response_callback_t callback) = 0;
    virtual void upload(UploadRequest request) = 0;
    virtual void download(DownloadRequest request) = 0;
};

}  // namespace bchat::network