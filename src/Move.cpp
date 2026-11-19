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

        return score < other.score;
    }