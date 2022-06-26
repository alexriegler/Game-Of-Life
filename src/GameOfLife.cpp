#include "GameOfLife.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

namespace ranges = std::ranges;

TEST_CASE("Game state generated") {
    static constexpr GameState<3, 3> initial_state{};

    SECTION("Standard") {
        static constexpr auto final_state = NextState<initial_state, 0>::value;
        REQUIRE(initial_state == final_state);
    }

    SECTION("Variable template") {
        static constexpr auto final_state = NextState_v<initial_state, 0>;
        REQUIRE(initial_state == final_state);
    }
}

TEST_CASE("Default game state") {
    static constexpr GameState<3, 3> state{};
    constexpr auto is_false = [](bool b) { return !b; };
    REQUIRE(ranges::all_of(state.grid, is_false));
}

TEST_CASE("Set game state") {
    static constinit GameState<3, 3> state{};
    ranges::fill(state.grid, true);
    constexpr auto is_true = [](bool b) { return b; };
    REQUIRE(ranges::all_of(state.grid, is_true));
}

TEST_CASE("3x3, 1 alive, 1 step") {
    static constexpr GameState<3, 3> initial_state{
        true, false, false,
        false, false, false,
        false, false, false,
    };
    static constexpr GameState<3, 3> expected_state{};
    static constexpr auto actual_state = NextState_v<initial_state, 1>;

    REQUIRE(expected_state == actual_state);
}

TEST_CASE("4x4, 1 alive, 1 step") {
    static constexpr GameState<4, 4> initial_state{
        true, false, false, false,
        false, false, false, false,
        false, false, false, false
    };
    static constexpr GameState<4, 4> expected_state{};
    static constexpr auto actual_state = NextState_v<initial_state, 1>;
    REQUIRE(expected_state == actual_state);
}

//TEST_CASE("5x5, 3 alive (Blinker)") {
//    static constexpr GameState<5, 5> initial_state{
//        false, false, false, false, false,
//        false, true,  true,  true,  false,
//        false, false, false, false, false,
//    };
//    SECTION("One step") {
//        static constexpr GameState<5, 5> expected_state{
//            false, false, true, false, false,
//            false, false, true, false, false,
//            false, false, true, false, false,
//        };
//        static constexpr auto actual_state = NextState_v<initial_state, 1>;
//        REQUIRE(expected_state == actual_state);
//    }
//    SECTION("Two step") {
//        static constexpr GameState<5, 5> expected_state{
//            false, false, false, false, false,
//            false, true,  true,  true,  false,
//            false, false, false, false, false,
//        };
//        static constexpr auto actual_state = NextState_v<initial_state, 2>;
//        REQUIRE(expected_state == actual_state);
//    }
//}

TEST_CASE("Get adjacent neighbors") {
    static constexpr GameState<3, 3> state{};

    SECTION("(1, 1)") {
        static constexpr auto center = Coordinates{ 1, 1 };
        static constinit auto expected_coords = AdjacentCoords{ {
            { 0, 0 }, { 0, 1 }, { 0, 2 },
            { 1, 0 }, /*{1, 1}*/{ 1, 2 },
            { 2, 0 }, { 2, 1 }, { 2, 2 }
        }};
        static constinit auto actual_coords = Adjacents_v<state, center>;

        ranges::sort(expected_coords);
        ranges::sort(actual_coords);
        REQUIRE(expected_coords == actual_coords);
    }
    SECTION("(0, 1) [wraparound north]") {
        static constexpr auto center = Coordinates{ 0, 1 };
        static constinit auto expected_coords = AdjacentCoords{ {
            { 2, 0 }, { 2, 1 }, { 2, 2 },
            { 0, 0 }, /*{0, 1}*/{ 0, 2 },
            { 1, 0 }, { 1, 1 }, { 1, 2 }
        } };
        static constinit auto actual_coords = Adjacents_v<state, center>;

        ranges::sort(expected_coords);
        ranges::sort(actual_coords);
        REQUIRE(expected_coords == actual_coords);
    }
}
