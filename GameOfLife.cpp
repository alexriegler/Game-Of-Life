// GameOfLife.cpp : Defines the entry point for the application.
//

#include <catch2/catch_test_macros.hpp>

#include <array>

template <int rows, int cols>
struct GameState {
    friend constexpr auto operator==(const GameState& lhs, const GameState& rhs) {
        return lhs.grid == rhs.grid;
    }

    std::array<bool, rows* cols> grid{};
};

template <GameState gameState, int steps>
struct NextState {
    static constexpr auto value = gameState;
};

TEST_CASE("Game state generated") {
    constexpr GameState<3, 3> initialState{
        true, false, false,
        false, false, false,
        false, false, false,
    };

    static constexpr auto finalState = NextState<initialState, 0>::value;

    REQUIRE(initialState == finalState);
}
