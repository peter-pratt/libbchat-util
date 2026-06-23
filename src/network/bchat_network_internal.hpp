#pragma once

#include "bchat/network/bchat_network_types.h"
#include "bchat/network/bchat_network_types.hpp"

namespace bchat::network::detail {
bchat_request_params* convert_cpp_request_to_c(const bchat::network::Request& req);
}