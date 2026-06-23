#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#include "../export.h"
#include "bchat/network/master_node.h"

typedef enum CONNECTION_STATUS {
    CONNECTION_STATUS_UNKNOWN,
    CONNECTION_STATUS_CONNECTING,
    CONNECTION_STATUS_CONNECTED,
    CONNECTION_STATUS_DISCONNECTED,
} CONNECTION_STATUS;

typedef enum {
    BCHAT_NETWORK_REQUEST_CATEGORY_STANDARD,
    BCHAT_NETWORK_REQUEST_CATEGORY_STANDARD_SMALL,
    BCHAT_NETWORK_REQUEST_CATEGORY_FILE,
    BCHAT_NETWORK_REQUEST_CATEGORY_FILE_SMALL,
} BCHAT_NETWORK_REQUEST_CATEGORY;

typedef enum {
    BCHAT_NETWORK_PATH_CATEGORY_STANDARD,
    BCHAT_NETWORK_PATH_CATEGORY_FILE,
} BCHAT_NETWORK_PATH_CATEGORY;

typedef struct network_server_destination {
    const char* method;
    const char* protocol;
    const char* host;
    uint16_t port;
    const char* x25519_pubkey_hex;
    const char* const* headers_kv_pairs;
    size_t headers_kv_pairs_len;
} network_server_destination;

typedef struct {
    char ed25519_pubkey_hex[65];  // The 64-byte ed25519 pubkey in hex + null terminator.
    uint8_t ip[4];
    uint16_t port;
} bchat_remote_address;

typedef struct {
    // Only ONE of these pointers should be set, the other should be left null
    const network_master_node* mnode_dest;
    const network_server_destination* server_dest;
    const bchat_remote_address* remote_addr_dest;

    const char* endpoint;
    const unsigned char* body;
    size_t body_size;

    BCHAT_NETWORK_REQUEST_CATEGORY category;
    uint64_t request_timeout_ms;
    uint64_t overall_timeout_ms;  // Use 0 for no overall timeout

    const char* upload_file_name;  // Optional name for file uploads, null terminated

    const char* request_id;  // Optional id for the request to trace through logs, null terminated

} bchat_request_params;

typedef struct {
    BCHAT_NETWORK_PATH_CATEGORY category;
} bchat_onion_path_metadata;

typedef struct {
    char destination_pubkey[65];         // The 64-byte ed25519 pubkey in hex + null terminator.
    char destination_master_node_address[65];  // The 64-byte .mnode address + null terminator.
} belnet_router_tunnel_metadata;

typedef struct {
    const network_master_node* nodes;
    size_t nodes_count;

    // Only ONE of these pointers should be set, the other should be left null
    const bchat_onion_path_metadata* onion_metadata;
    const belnet_router_tunnel_metadata* belnet_router_metadata;

} bchat_path_info;

#ifdef __cplusplus
}
#endif
