#include <vector>

#include "Piece.h"

#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece {
public:
    Pawn(): Piece() {}
    Pawn(PieceColor _color, char _file, char _rank): Piece(_color, _file, _rank) {}
    
};

#endif