#pragma once 

#include <stdint.h>

#include "CastlingRights.h"
#include "Square.h"
#include "Pieces.h"

struct Unmove {
    // Used to represent the information needed to unmake a move. 
    Pieces captured_piece {Pieces::NOPIECE};
    Square captured_square {-1};
    uint8_t halfmove_clock {0};  // Tracks number of halfmoves since last capture or pawn move for 50-move rule
    uint16_t fullmove_num {0};  // Tracks the full move number (both black and white), never resets
    CastlingRights castling_rights;
    Square en_passant_square {-1};
};