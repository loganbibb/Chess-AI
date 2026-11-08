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
    Colors side_to_move {Colors::WHITE}; 
    // castling rights
    bool white_check {false};
    bool black_check {false};
    CastlingRights castling_rights;
    // en passant target square, if applicable. Otherwise, set to 0.
    Square en_passant_square;
    // halfmove clock for 50-move rule
    uint8_t halfmove_num {0};
    // full move number, starting at 1
    uint16_t fullmove_num {0};

    // functions 
    void setup_starting_position();
    void generate_pawn_moves(Square& sq, std::vector<Move>& moves) const;
    void generate_knight_moves(Square& sq, std::vector<Move>& moves) const;
    void generate_bishop_moves(Square& sq, std::vector<Move>& moves) const;
    void generate_rook_moves(Square& sq, std::vector<Move>& moves) const;
    void generate_queen_moves(Square& sq, std::vector<Move>& moves) const;
    void generate_king_moves(Square& sq, std::vector<Move>& moves) const;
    float get_phase() const;
    float get_piece_value(Square sq, float phase) const;
public:
    Position(bool setup_starting = true);
    float get_eval();
    inline PieceVector& get_pieces() {return pieces;};
    void set_pieces(PieceVector new_pieces);
    inline void set_side_to_move(Colors color) {side_to_move = color;};
    inline void set_castling_rights(CastlingRights new_rights) {castling_rights = new_rights;};
    inline void set_en_passant_square(Square sq) {en_passant_square = sq;};
    inline void set_halfmove_num(int8_t num) {halfmove_num = num;};
    inline void set_fullmove_num(uint16_t num) {fullmove_num = num;};
    inline Colors get_side_to_move() const {return side_to_move;};
    inline CastlingRights get_castling_rights() const {return castling_rights;};
    inline Square get_en_passant_square() const {return en_passant_square;};
    inline uint8_t get_halfmove_num() const {return halfmove_num;};
    inline uint16_t get_fullmove_num() const {return fullmove_num;};
    std::vector<Move> generate_moves();
    std::vector<Move> generate_legal_moves();
    double eval_terminal_position() const;
    void make_move(const Move& move, Unmove& unmove);
    void unmake_move(const Move& move, const Unmove& unmove);
    void print_moves(std::vector<Move> moves) const;
    void show() const;
    bool is_square_attacked(Square sq, Colors attacker) const;
    bool is_in_check(Square king_sq, Colors king_color) const;
    Square find_king(Colors king_color) const;
};