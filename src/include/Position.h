#pragma once 

#include <vector>
#include <stdint.h>

#include "CastlingRights.h"
#include "Move.h" 
#include "Piece.h"
#include "PieceVector.h"
#include "Square.h"
#include "Unmove.h"

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
    Square en_passant_square;
    // halfmove clock for 50-move rule
    int8_t halfmove_num {0};
    // full move number, starting at 1
    uint16_t fullmove_num {0};

    // functions 
    void setup_starting_position();
    void generate_pawn_moves(Square& sq, std::vector<Move>& moves);
    void generate_knight_moves(Square& sq, std::vector<Move>& moves);
    void generate_bishop_moves(Square& sq, std::vector<Move>& moves);
    void generate_rook_moves(Square& sq, std::vector<Move>& moves);
    void generate_queen_moves(Square& sq, std::vector<Move>& moves);
    void generate_king_moves(Square& sq, std::vector<Move>& moves);
    friend bool is_check(Position& pos, Colors color);
public:
    Position();
    float get_eval();
    inline PieceVector& get_pieces() {return pieces;};
    void set_pieces(PieceVector new_pieces);
    std::vector<Move> generate_moves();
    void make_move(Move& move, Unmove& unmove);
    void unmake_move(Move& move, Unmove& unmove);
    void show();
    
};