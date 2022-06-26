#pragma once

#include <array>

template <int rows, int cols>
struct GameState {
    constexpr bool operator==(const GameState&) const = default;

    std::array<bool, rows* cols> grid{};
};

// TODO: Make this a template
template <template <int, int> typename T, int rows, int cols>
constexpr auto Rows(const T<rows, cols>&) {
    return rows;
}

// TODO: Make this a template
template <template <int, int> typename T, int rows, int cols>
constexpr auto Cols(const T<rows, cols>&) {
    return cols;
}
