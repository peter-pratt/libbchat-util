#pragma once

#include <bchat/config.hpp>
#include <bchat/config/base.hpp>
#include <bchat/bchat_protocol.hpp>

namespace bchat::config {

/// keys used currently or in the past (so that we don't reuse):
///
/// s + bchat pro data
///   |
///   +-- p + proof
///   |     |
///   |     +-- @ - version
///   |     +-- e - expiry unix timestamp (in milliseconds)
///   |     +-- g - gen_index_hash
///   |     +-- s - proof signature, signed by the BChat Pro Backend's ed25519 key
///   |
///   +-- r - rotating ed25519 seed (32b)
class ProConfig {
  public:
    /// Rotating private key for the public key specified in the proof. On the wire we store the
    /// seed. At runtime we derive the full key for convenience.
    cleared_uc64 rotating_privkey;

    /// A cryptographic proof for entitling an Ed25519 key to BChat Pro
    ProProof proof;

    bool load(const dict& root);

    bool operator==(const ProConfig& other) const {
        return rotating_privkey == other.rotating_privkey && proof == other.proof;
    }
};
};  // namespace bchat::config
