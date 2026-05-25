#include <stdint.h>
#include <string>

#include "PieceVector.h"
#include "Pieces.h"
#include "Square.h"

Pieces& PieceVector::operator() (uint8_t file, uint8_t rank) {
    // convert file and rank to index and return the piece at that index. 
    int index = (int) (rank * 8 + file);
    return this->at(index);
}

Pieces& PieceVector::operator()(const Square& square) {
    // convert file and rank to index and return the piece at that index. 
    return this->at(square());
}

Pieces& PieceVector::operator[](std::string sq_str) {
    // convert from string format "a1", "e4", etc. to index and return the piece at that index. 
    if (sq_str.length() != 2) {
        throw Exceptions::InvalidSquareException();
    }
    char file = sq_str[0] - 'a';
    char rank = sq_str[1] - '1';
    return (*this)(file, rank);
}

Pieces& PieceVector::operator[](const Square& square) {
    // convert from string format "a1", "e4", etc. to index and return the piece at that index. 
    return (*this)(square);
}

std::string PieceVector::to_string() {
    // convert the piece vector to a string representation of the board. 
    std::string board_string = "";
    for (int i = 0; i < 64; i++) {
        board_string += piece_to_string(this->at(i)) + " ";
        if ((i + 1) % 8 == 0) {
            board_string += "\n";
        }
    }
    return board_string;
}