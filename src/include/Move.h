#pragma once 

#include <string> 
#include <queue>

#include "Piece.h"
#include "Square.h"

struct Move {
    // Used to represent a move from one square to another. 
    Square from_square = 0; // 0-63, where 0 is a1 and 63 is h8
    Square to_square = 0; // 0-63, where 0 is a1 and 63 is h8
    
    bool is_castle = false; 
    bool is_promotion = false;
    bool is_en_passant = false;
    int score{INT32_MIN};

    Piece promotion_piece = Piece::NOPIECE; // only used if is_promotion is true
    bool operator<(const Move& other) const;
};

using MoveList = std::priority_queue<Move, std::vector<Move>, std::less<Move>>;
