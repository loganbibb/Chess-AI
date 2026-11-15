#include "Move.h"
#include "evaluation.h"

bool Move::operator<(const Move& other) const {
        /* For use in priority queue. Sort by promotions, then captures, then all other moves. 
         * IMPORTANT: This function is intended to be called by std::priority_queue inside the 
         * generate_(piece)_moves() functions, therefore it is assumed the Move has NOT been 
         * applied to the position. This is important for detecting captures. 
         * Scoring is done using MVV-LVA ranking. The piece values themselves are just the 
         * average of the middlegame and endgame values from evaluation.h. A fairly quick and 
         * dirty score. 
         */

        int from_idx = std::abs((int)(from_square));
        int to_idx = std::abs((int)(to_square));
        int from_idx_other = std::abs((int)(other.from_square));
        int to_idx_other = std::abs((int)(other.to_square));
        float MVV = eval::middlegame::piece_values[to_idx] + eval::endgame::piece_values[to_idx];
        float LVA = eval::middlegame::piece_values[from_idx] + eval::endgame::piece_values[from_idx];
        float MVV_other = eval::middlegame::piece_values[to_idx_other] + eval::endgame::piece_values[to_idx_other];
        float LVA_other = eval::middlegame::piece_values[from_idx_other] + eval::endgame::piece_values[from_idx_other];
        return (MVV - LVA) < (MVV_other - LVA_other);
    }