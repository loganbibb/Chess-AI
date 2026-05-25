#include <vector>
#include <stdint.h>

#include "CastlingRights.h"
#include "Move.h" 
#include "Pieces.h"
#include "PieceVector.h"
#include "Square.h"
#include "Unmove.h"

#pragma once 

class Position {
    /*
    Position class represents the current state of the chess board. 
    It contains a vector of pieces and an evaluation score for the position. 
    It also has functions to generate legal moves and evaluate the position.
    */
    PieceVector pieces; // initialize all squares to NOPIECE
    float eval {0};
    Colors side_to_move {Colors::WHITE}; 
    // castling rights
    bool white_check {false};
    bool black_check {false};
    CastlingRights castling_rights;
    // en passant target square, if applicable. Otherwise, set to 0.
    Square en_passant_square {-1};
    // halfmove clock for 50-move rule
    uint8_t halfmove_clock {0};
    // full move number, starting at 1
    uint16_t fullmove_num {0};


    // functions 
    void setup_starting_position();
public:
    Position();
    float get_eval();
    inline PieceVector get_pieces();
    void set_pieces(PieceVector new_pieces);
    std::vector<Position> generate_moves();
    void make_move(Move& move, Unmove& unmove);
    void unmake_move(Move& move, Unmove& unmove);
    void show();
    
};