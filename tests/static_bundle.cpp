// This file isn't designed to do anything useful, but just to test that we can compile and link
// against the combined static bundle (when using cmake ... -DSTATIC_BUILD=ON)

#include <random>
#include <bchat/config/groups/keys.hpp>

int main() {
    if (std::mt19937_64{}() == 123) {
        auto& k = *reinterpret_cast<bchat::config::groups::Keys*>(12345);
        k.encrypt_message(std::span<const unsigned char>{});
    }
}
