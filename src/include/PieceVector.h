#pragma once 

#include <array> 
#include <vector>
#include <string>
#include <stdint.h>

#include "error_types.h"
#include "Piece.h"
#include "Square.h"

class PieceVector : public std::array<Piece, 64> {
    /*
    PieceVector is a wrapper for a vector of pieces. It is used to represent the pieces on the board in a position. 
    It is essentially a vector of 64 pieces, where each piece represents the piece on the corresponding square. 
    This class can be used to easily convert between a vector of pieces and a string representation of the board.
    */
    public:
    PieceVector() : std::array<Piece, 64>() {
        this->fill(Piece::NOPIECE); // initialize all squares to NOPIECE
    } 
    std::string to_string();
    Piece& operator()(int8_t file, int8_t rank);
    Piece& operator()(const Square& square);
    Piece& operator[](std::string sq_str);
    Piece& operator[](const Square& square);
    Piece& operator[](int index) {
        if (index < 0 || index >= 64) {
            throw Exceptions::IndexError();
        }
        return std::array<Piece,64>::operator[](index);
    }
};