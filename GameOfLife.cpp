// GameOfLife.cpp : Defines the entry point for the application.
//

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>

// Coordinates
struct Coordinates {
    constexpr bool operator==(const Coordinates&) const = default;

    int row{};
    int col{};
};

// GameState
template <int rows, int cols>
struct GameState {
    constexpr bool operator==(const GameState&) const = default;

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
template <GameState game_state, Coordinates coords>
struct NextCell {
    static constexpr auto value = game_state.grid[coords.row * Rows(game_state) + coords.col] ? false : true;
};

// Variable template
template <GameState game_state, Coordinates coords>
inline constexpr auto NextCell_v = NextCell<game_state, coords>::value;

// Next state
template <GameState game_state, int steps>
struct NextState {
    static constexpr auto value = GameState<Rows(game_state), Cols(game_state)>{ NextCell_v < game_state, Coordinates{0, 0} > };
};

template <GameState game_state>
struct NextState<game_state, 0> {
    static constexpr auto value = game_state;
};

// Variable template
template <GameState game_state, int steps>
inline constexpr auto NextState_v = NextState<game_state, steps>::value;

// Adjacents
template<GameState game_state, Coordinates coords>
struct Adjacents {
    static constexpr auto value = std::array<Coordinates, 8>{ {
        { coords.row - 1, coords.col - 1 }, { coords.row - 1, coords.col }, { coords.row - 1, coords.col + 1 },
        { coords.row, coords.col - 1 },   /*{ coords.row, coords.col },   */{ coords.row, coords.col + 1 },
        { coords.row + 1, coords.col - 1 }, { coords.row + 1, coords.col }, { coords.row + 1, coords.col + 1 },
        }};
};

// Variable helper template
template <GameState game_state, Coordinates coords>
inline constexpr auto Adjacents_v = Adjacents<game_state, coords>::value;

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
    static constexpr auto expected_coords = std::array<Coordinates, 8>{ {
        { 0, 0 }, { 0, 1 }, { 0, 2 },
        { 1, 0 }, /*{1, 1}*/{ 1, 2 },
        { 2, 0 }, { 2, 1 }, { 2, 2 }
        }};
    static constexpr auto actual_coords = Adjacents_v < state, Coordinates{ 1, 1 } > ;
    REQUIRE(expected_coords == actual_coords);
}
