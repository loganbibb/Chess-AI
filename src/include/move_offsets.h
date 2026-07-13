#pragma once 

#include <array>

namespace offsets {
    // knight move offsets
    inline constexpr std::array<std::pair<int, int>, 8> knight_move_offsets = {{
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    }};
    // bishop move offsets
    inline constexpr std::array<std::pair<int, int>, 4> bishop_move_offsets = {{
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
    }};
    // rook move offsets
    inline constexpr std::array<std::pair<int, int>, 4> rook_move_offsets = {{
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    }};
    // king move offsets
    inline constexpr std::array<std::pair<int, int>, 8> king_move_offsets = {{
        {1, 1}, {1, 0}, {1, -1}, 
        {0, -1}, {-1, -1}, {-1, 0}, 
        {-1, 1}, {0, 1}
    }};
}