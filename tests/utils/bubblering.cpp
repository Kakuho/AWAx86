#include <catch2/catch_test_macros.hpp>
#include <string>
#include <cstdint>
#include <cassert>
#include <iostream>

#include "utils/bubblering.hpp"
#include "tokens.hpp"

TEST_CASE( "bubble ring cache", "[bubble_cache]" ){
  using namespace Awax86;
  SECTION("push"){
    BubbleRing<3> cache;
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    cache.Push({BubbleType::Single, std::uint8_t{13}});
    REQUIRE(cache.AllSingles());
  }

  SECTION("push updates index"){
    BubbleRing<3> cache;
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 0);
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 1);
    cache.Push({BubbleType::Single, std::uint8_t{13}});
    REQUIRE(cache.GetIndex() == 2);
  }

  SECTION("index"){
    // top is at index 0
    BubbleRing<3> cache;
    REQUIRE(cache.GetIndex() == 0);
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 0);
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 1);
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 2);
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    REQUIRE(cache.GetIndex() == 0);
  }

  SECTION("operator[]"){
    // top is at index 0
    BubbleRing<3> cache;
    cache.Push({BubbleType::Single, std::uint8_t{10}});
    cache.Push({BubbleType::Single, std::uint8_t{2}});
    cache.Push({BubbleType::Single, std::uint8_t{43}});
    REQUIRE(cache[0] == 10);
    REQUIRE(cache[1] == 2);
    REQUIRE(cache[2] == 43);
  }

}
