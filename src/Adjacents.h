#pragma once

#include "Coordinates.h"
#include "GameState.h"

#include <array>

using AdjacentCoords = std::array<Coordinates, 8>;

template<GameState game_state, int row>
struct RowWrap {
    static constexpr auto value =
        row >= 0 ?
            ( row < Rows(game_state) ?
                row
                : 0 )
            : Rows(game_state) - 1;
};

template <GameState game_state, int row>
inline constexpr auto RowWrap_v = RowWrap<game_state, row>::value;

template<GameState game_state, Coordinates coords>
struct TopLeft {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row - 1>,
        coords.col - 1
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto TopLeft_v = TopLeft<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct TopMiddle {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row - 1>,
        coords.col
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto TopMiddle_v = TopMiddle<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct TopRight {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row - 1>,
        coords.col + 1
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto TopRight_v = TopRight<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct BottomLeft {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row + 1>,
        coords.col - 1
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto BottomLeft_v = BottomLeft<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct BottomMiddle {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row + 1>,
        coords.col
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto BottomMiddle_v = BottomMiddle<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct BottomRight {
    static constexpr auto value = Coordinates{
        RowWrap_v<game_state, coords.row + 1>,
        coords.col + 1
    };
};

template <GameState game_state, Coordinates coords>
inline constexpr auto BottomRight_v = BottomRight<game_state, coords>::value;

template<GameState game_state, Coordinates coords>
struct Adjacents {
    static constexpr auto value = AdjacentCoords{ {
        TopLeft_v<game_state, coords>, TopMiddle_v<game_state, coords>, TopRight_v<game_state, coords>,
        { coords.row, coords.col - 1 },   /*{ coords.row, coords.col },   */{ coords.row, coords.col + 1 },
        BottomLeft_v<game_state, coords>, BottomMiddle_v<game_state, coords>, BottomRight_v<game_state, coords>,
    } };
};

// Variable helper template
template <GameState game_state, Coordinates coords>
inline constexpr auto Adjacents_v = Adjacents<game_state, coords>::value;
