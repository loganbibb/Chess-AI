#include "piece_colors.h"

#ifndef PIECE_H
#define PIECE_H

class Piece {
    PieceColor color;
    char rank;
    char file;
public:
    Piece(): color(NOCOLOR), rank(0), file(0) {}
    Piece(PieceColor _color, char _rank, char _file): color(_color), rank(_rank), file(_file) {}
    PieceColor get_color() {return color;}
};

#endif