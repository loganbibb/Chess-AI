#include "Pieces.h"
#include "Square.h"

#pragma once 

struct Move {
    // Used to represent a move from one square to another. 
    Square from_square = 0; // 0-63, where 0 is a1 and 63 is h8
    Square to_square = 0; // 0-63, where 0 is a1 and 63 is h8

    bool is_check = false;
    bool is_castle = false; 
    bool is_promotion = false;
    bool is_en_passant = false;

    Pieces promotion_piece = Pieces::NOPIECE; // only used if is_promotion is true
};
