#include <catch2/catch_test_macros.hpp>

#include "bchat/random.h"
#include "bchat/random.hpp"
#include "utils.hpp"

TEST_CASE("Random generation", "[random][random]") {
    auto rand1 = bchat::random::random(10);
    auto rand2 = bchat::random::random(10);
    auto rand3 = bchat::random::random(20);

    CHECK(rand1.size() == 10);
    CHECK(rand2.size() == 10);
    CHECK(rand3.size() == 20);
    CHECK(rand1 != rand2);
}
