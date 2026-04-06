#include "Pieces.h"

struct Move {
    // Used to represent a move from one square to another. 
    char from_file = 0;
    char from_rank = 0;
    char to_file = 0;
    char to_rank = 0;

    bool is_check = false;
    bool is_castle = false; 
    bool is_promotion = false;
    bool is_en_passant = false;

    Pieces promotion_piece = Pieces::NOPIECE; // only used if is_promotion is true
};
