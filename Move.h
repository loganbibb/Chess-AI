#ifndef MOVE_H
#define MOVE_H

struct Move {
    // Used to represent a move from one square to another. 
    char from_file = 0;
    char from_rank = 0;
    char to_file = 0;
    char to_rank = 0;
    // Piece* promotion_piece = nullptr; // if the move is a pawn promotion, this is the piece the pawn is promoted to
    // bool is_castling = false; // true if the move is a castling move
    // bool is_en_passant = false; // true if the move is an en passant capture
    // bool is_capture = false; // true if the move is a capture
};

#endif
