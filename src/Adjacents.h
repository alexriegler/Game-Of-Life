#pragma once

#include "Coordinates.h"
#include "GameState.h"

#include <array>

// TODO: Member template function could be useful? Then I wouldn't need to
//       explicitly pass game state to everything.

/// <summary>
/// An alias representing a collection of coordinates adjacent to a cell.
/// 
/// In the following diagram, the 'A's represent the adjacent cells and the
/// 'C' represents the center cell:
/// 
///     A A A
///     A C A
///     A A A
/// 
/// </summary>
using AdjacentCoords = std::array<Coordinates, 8>;

/// <summary>
/// Metafunction for mapping a row to the coordinate system of the GameState.
/// 
/// Mapping:
/// The table below describes the mapping from an input row, x, to the output row, y.
/// The variable N is the number of rows in the GameState.
/// 
///    +--------------------------+
///    |         x        |   y   |
///    |--------------------------|
///    |       x < 0      | N - 1 |
///    |  0 <= x <= N - 1 |   x   |
///    |       x >= N     |   0   |
///    +--------------------------+
/// </summary>
/// <typeparam name="game_state">The game state associated with the row</typeparam>
/// <typeparam name="row">The row to remap</typeparam>
template<GameState game_state, int row>
struct RowWrap {
    static constexpr auto value =
        row >= 0 ?
            ( row < Rows(game_state) ?
                row
                : 0 )
            : Rows(game_state) - 1;
};

/// <summary>
/// Variable helper template for wrapping a row.
/// </summary>
/// <typeparam name="game_state">The game state associated with the row</typeparam>
/// <typeparam name="row">The row to wrap</typeparam>
template <GameState game_state, int row>
inline constexpr auto RowWrap_v = RowWrap<game_state, row>::value;

/// <summary>
/// Metafunction for getting the coordinates of the adjacent cell that is
/// northwest of the cell at the specified coordinates.
/// </summary>
/// <typeparam name="game_state">The game state associated with the coordinates</typeparam>
/// <typeparam name="coords">The coordinates of the center cell relative to the northwest adjacent cell</typeparam>
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
