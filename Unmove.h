#pragma once 

#include "CastlingRights.h"
#include "Square.h"
#include "Pieces.h"

struct Unmove {
    // Used to represent the information needed to unmake a move. 
    Pieces captured_piece {Pieces::NOPIECE};
    Square captured_square {-1};
    unsigned char halfmove_clock {0};
    unsigned short fullmove_num {0};
    CastlingRights castling_rights;
    Square en_passant_square {-1};
};