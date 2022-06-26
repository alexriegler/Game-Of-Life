#pragma once

#include "Coordinates.h"
#include "GameState.h"

/// <summary>
/// Metafunction for generating the next state of a cell.
/// </summary>
/// <typeparam name="game_state">The game state associated with the cell</typeparam>
/// <typeparam name="coords">The coordinates of the cell</typeparam>
template <GameState game_state, Coordinates coords>
struct NextCell {
    static constexpr auto value = game_state.grid[coords.row * Rows(game_state) + coords.col] ? false : true;
};

// Variable template

/// <summary>
/// Variable helper template.
/// </summary>
/// <typeparam name="game_state">The game state associated with the cell</typeparam>
/// <typeparam name="coords">The coordinates of the cell</typeparam>
template <GameState game_state, Coordinates coords>
inline constexpr auto NextCell_v = NextCell<game_state, coords>::value;

/// <summary>
/// Metafunction for generating the state of the game after N steps.
/// </summary>
/// <typeparam name="game_state">The initial game state</typeparam>
/// <typeparam name="steps">The number of generations to step</typeparam>
template <GameState game_state, int steps>
struct NextState {
    static constexpr auto value = GameState<Rows(game_state), Cols(game_state)>{ NextCell_v < game_state, Coordinates{0, 0} > };
};

/// <summary>
/// Template specialization for zero steps.
/// 
/// The next state after zero steps is the same as the input state.
/// </summary>
/// <typeparam name="game_state">The initial game state</typeparam>
template <GameState game_state>
struct NextState<game_state, 0> {
    static constexpr auto value = game_state;
};

/// <summary>
/// Variable helper template.
/// </summary>
/// <typeparam name="game_state">The initial game state</typeparam>
/// <typeparam name="steps">The number of generations to step</typeparam>
template <GameState game_state, int steps>
inline constexpr auto NextState_v = NextState<game_state, steps>::value;
