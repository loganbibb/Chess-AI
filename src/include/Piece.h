#pragma once

#include <string> 
#include "error_types.h"

enum class Piece {
    // create enum class for pieces with negative values for black pieces and positive values for white pieces.
    NOPIECE = 0,
    BPAWN = -1,
    BKNIGHT = -2,
    BBISHOP = -3,
    BROOK = -4,
    BQUEEN = -5,
    BKING = -6,
    WPAWN = 1,
    WKNIGHT = 2,
    WBISHOP = 3,
    WROOK = 4,
    WQUEEN = 5,
    WKING = 6
};

enum class Colors {
    WHITE,
    BLACK,
    NOCOLOR
};

std::string piece_to_string(const Piece& piece);

inline Colors get_piece_color(const Piece& piece) {
    if (piece == Piece::NOPIECE) {
        return Colors::NOCOLOR;
    }
    else if(int(piece) > 0) {
        return Colors::WHITE;
    }
    else {
        return Colors::BLACK;
    }
}