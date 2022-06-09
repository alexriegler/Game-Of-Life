// GameOfLife.cpp : Defines the entry point for the application.
//

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>

template <int rows, int cols>
struct GameState {
    friend constexpr auto operator==(const GameState& lhs, const GameState& rhs) {
        return lhs.grid == rhs.grid;
    }

    std::array<bool, rows* cols> grid{};
};

template <GameState game_state, int steps>
struct NextState {
    static constexpr auto value = game_state;
};

// Variable template
template <GameState game_state, int steps>
inline constexpr auto NextState_v = NextState<game_state, steps>::value;

TEST_CASE("Game state generated") {
    static constexpr GameState<3, 3> initial_state{};

    SECTION("Standard") {
        static constexpr auto final_state = NextState<initial_state, 0>::value;
        REQUIRE(initial_state == final_state);
    }

    SECTION("Variable template") {
        static constexpr auto finalState = NextState_v<initial_state, 0>;
        REQUIRE(initial_state == finalState);
    }
}

TEST_CASE("Default game state") {
    static constexpr GameState<3, 3> state{};
    constexpr auto is_false = [](bool b) { return !b; };
    REQUIRE(std::ranges::all_of(state.grid, is_false));
}
