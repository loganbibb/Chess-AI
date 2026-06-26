#pragma once 

#include <vector>

namespace offsets {
    // knight move offsets
    static const std::vector<std::pair<int, int>> knight_move_offsets = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };
    // bishop move offsets
    static const std::vector<std::pair<int, int>> bishop_move_offsets = {
        {1, 1}, {1, -1}, {-1, -1}, {-1, 1}
    };
    // rook move offsets
    static const std::vector<std::pair<int, int>> rook_move_offsets = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };
    // king move offsets
    static const std::vector<std::pair<int, int>> king_move_offsets = {
        {1, 1}, {1, 0}, {1, -1}, 
        {0, -1}, {-1, -1}, {-1, 0}, 
        {-1, 1}, {0, 1}
    };
}