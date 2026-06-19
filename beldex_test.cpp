#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "session/network/bchat_network.h"
#include "session/network/bchat_network_types.h"

// Global state for callback
static volatile int nodes_received = -1;
static network_service_node received_nodes[10];

void on_status_change(CONNECTION_STATUS status, void* ctx) {
    const char* s =
        status == CONNECTION_STATUS_UNKNOWN      ? "UNKNOWN"      :
        status == CONNECTION_STATUS_CONNECTING   ? "CONNECTING"   :
        status == CONNECTION_STATUS_CONNECTED    ? "CONNECTED"    :
        status == CONNECTION_STATUS_DISCONNECTED ? "DISCONNECTED" : "?";
    printf("[STATUS] %s\n", s);
    fflush(stdout);
}

void on_nodes_received(network_service_node* nodes, size_t count, void* ctx) {
    printf("\n[CALLBACK] Received %zu nodes from Beldex network!\n", count);

    size_t print_count = count;
    for (size_t i = 0; i < print_count; i++) {
        printf("  Node %zu:\n", i + 1);
        printf("    IP:      %u.%u.%u.%u\n", nodes[i].ip[0], nodes[i].ip[1], nodes[i].ip[2], nodes[i].ip[3]);
        printf("    HTTPS port: %u  OMQ port: %u\n", nodes[i].https_port, nodes[i].omq_port);
        printf("    Pubkey:  %s\n", nodes[i].ed25519_pubkey_hex);
        printf("    Version: %u.%u.%u\n",
            nodes[i].version[0],
            nodes[i].version[1],
            nodes[i].version[2]);
    }
    if (count > 5)
        printf("  ... and %zu more nodes\n", count - 5);

    nodes_received = (int)count;
    fflush(stdout);
}

int main() {
    printf("=== Beldex Network Deep Connectivity Test ===\n\n");
    fflush(stdout);

    session_network_config config = session_network_config_default();
    config.netid     = SESSION_NETWORK_MAINNET;
    config.router    = SESSION_NETWORK_ROUTER_ONION_REQUESTS;
    config.transport = SESSION_NETWORK_TRANSPORT_QUIC;
    config.cache_dir = "/tmp/beldex_test_cache";
    config.increase_no_file_limit = true;

    char error[256] = {0};
    network_object* network = NULL;

    printf("[1] Initializing network...\n");
    fflush(stdout);

    bool ok = session_network_init(&network, &config, error);
    if (!ok || !network) {
        printf("[FAIL] Init failed: %s\n", error);
        return 1;
    }
    printf("[OK] Initialized\n\n");

    session_network_set_status_changed_callback(network, on_status_change, NULL);

    // Wait for CONNECTED
    printf("[2] Waiting for connection (15s max)...\n");
    fflush(stdout);
    int connected = 0;
    for (int i = 0; i < 15; i++) {
        sleep(1);
        CONNECTION_STATUS s = session_network_get_status(network);
        if (s == CONNECTION_STATUS_CONNECTED) {
            connected = 1;
            printf("[OK] Connected at %ds\n\n", i + 1);
            fflush(stdout);
            break;
        }
        printf("  [%2ds] waiting...\n", i + 1);
        fflush(stdout);
    }

    if (!connected) {
        printf("[FAIL] Could not connect\n");
        session_network_free(network);
        return 1;
    }

    // Fetch 5 random nodes from the Beldex masternode pool
    printf("[3] Fetching 5 random masternodes from Beldex network...\n");
    fflush(stdout);

    session_network_get_random_nodes(network, 10, on_nodes_received, NULL);

    // Wait up to 15 seconds for callback
    for (int i = 0; i < 15; i++) {
        sleep(1);
        if (nodes_received >= 0) break;
        printf("  [%2ds] waiting for node data...\n", i + 1);
        fflush(stdout);
    }

    if (nodes_received < 0) {
        printf("\n[FAIL] No nodes received within 15 seconds\n");
        session_network_free(network);
        return 1;
    }

    printf("\n=== RESULT ===\n");
    printf("  Connected to Beldex network:  YES\n");
    printf("  Masternodes fetched:          %d\n", nodes_received);
    printf("  Time offset retrieved:        %s\n",
        session_network_has_retrieved_time_offset(network) ? "YES" : "NO");
    printf("  Hardfork:                     %u\n", session_network_hardfork(network));
    printf("  Softfork:                     %u\n", session_network_softfork(network));
    printf("\n[PASS] libsession-util is fully working with the Beldex network!\n");
    fflush(stdout);

    session_network_suspend(network);
    session_network_free(network);
    return 0;
}