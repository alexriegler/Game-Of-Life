#pragma once

#include <iostream>

struct Coordinates {
    constexpr auto operator<=>(const Coordinates&) const = default;

    // Used for debugging purposes
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coords)
    {
        os << '(' << coords.row << ", " << coords.col << ')';
        return os;
    }

    int row{};
    int col{};
};
