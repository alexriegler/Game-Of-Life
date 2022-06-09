// GameOfLife.cpp : Defines the entry point for the application.
//

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>

// GameState
template <int rows, int cols>
struct GameState {
    friend constexpr auto operator==(const GameState& lhs, const GameState& rhs) {
        return lhs.grid == rhs.grid;
    }

    std::array<bool, rows* cols> grid{};
};

template <template <int, int> typename T, int rows, int cols>
constexpr auto Rows(const T<rows, cols>&) {
    return rows;
}

template <template <int, int> typename T, int rows, int cols>
constexpr auto Cols(const T<rows, cols>&) {
    return cols;
}

// NextCell
template <GameState game_state, int row, int col>
struct NextCell {
    static constexpr auto value = game_state.grid[row * Rows(game_state) + col] ? false : true;
};

// Variable template
template <GameState game_state, int row, int col>
inline constexpr auto NextCell_v = NextCell<game_state, row, col>::value;

// Next state
template <GameState game_state, int steps>
struct NextState {
    static constexpr auto value = GameState<Rows(game_state), Cols(game_state)>{ NextCell_v<game_state, 0, 0> };
};

template <GameState game_state>
struct NextState<game_state, 0> {
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
        static constexpr auto final_state = NextState_v<initial_state, 0>;
        REQUIRE(initial_state == final_state);
    }
}

TEST_CASE("Default game state") {
    static constexpr GameState<3, 3> state{};
    constexpr auto is_false = [](bool b) { return !b; };
    REQUIRE(std::ranges::all_of(state.grid, is_false));
}

TEST_CASE("Set game state") {
    static constinit GameState<3, 3> state{};
    std::ranges::fill(state.grid, true);
    constexpr auto is_true = [](bool b) { return b; };
    REQUIRE(std::ranges::all_of(state.grid, is_true));
}

TEST_CASE("3x3, 1 alive, 1 step") {
    static constexpr GameState<3, 3> initial_state{
        true, false, false,
        false, false, false,
        false, false, false,
    };
    static constexpr GameState<3, 3> expected_state{
        false, false, false,
        false, false, false,
        false, false, false,
    };
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
