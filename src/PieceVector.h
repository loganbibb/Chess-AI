#pragma once 

#include <vector> 
#include <string>
#include <stdint.h>

#include "error_types.h"
#include "Pieces.h"
#include "Square.h"

class PieceVector : public std::vector<Pieces> {
    /*
    PieceVector is a wrapper for a vector of pieces. It is used to represent the pieces on the board in a position. 
    It is essentially a vector of 64 pieces, where each piece represents the piece on the corresponding square. 
    This class can be used to easily convert between a vector of pieces and a string representation of the board.
    */
    public:
    PieceVector() : std::vector<Pieces>(64, Pieces::NOPIECE) {} // initialize all squares to NOPIECE
    std::string to_string();
    Pieces& operator()(uint8_t file, uint8_t rank);
    Pieces& operator()(const Square& square);
    Pieces& operator[](std::string sq_str);
    Pieces& operator[](const Square& square);
    Pieces& operator[](int index) {
        if (index < 0 || index >= 64) {
            throw Exceptions::IndexError();
        }
        return std::vector<Pieces>::operator[](index);
    }
};