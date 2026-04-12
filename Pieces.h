
#include <string> 

#ifndef PIECES_H
#define PIECES_H

enum class Pieces {
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
    BLACK
};

std::string piece_to_string(const Pieces& piece);
#endif