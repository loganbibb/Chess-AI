#include "pieces/Piece.h"
#include <vector>

#ifndef BOARD_H
#define BOARD_H

class Board {
    /*
    Board class to represent the chess board and pieces on it. 
    It also contains some auxiliary information, such as the evaluation of the board and 
    whether the white or black king is in check. 
    */
    std::vector<Piece> pieces;
    float eval = 0;
    bool white_check = false;
    bool black_check = false;

    // functions 
    Board();
    Board(const Board& inBoard);
    void create_starter_board();
    Board& operator=(const Board& inBoard);
public:
    float get_eval();
    std::vector<Board> generate_moves();
    
};

Board::Board(){
    /* Creates a board with pieces at the starting positions. */
    eval = 0;
    create_starter_board();
}

Board::Board(const Board& inBoard) {
    /* Copy constructor */
    eval = inBoard.eval;
    // deep copy inBoard pieces into this board pieces. vector deep copies by default
    pieces = inBoard.pieces;
}

Board& Board::operator=(const Board& inBoard) {
    /* Copy assignment constructor */
    if (&inBoard == this) {return *this;}
    eval = inBoard.eval;
    pieces = inBoard.pieces;
    return *this;
}

void Board::create_starter_board() {
    // add pieces to board in starting positions
    pieces.resize(32); // number of starting pieces, 16 for white and 16 for black 
    // white pieces 
    pieces[0] = Piece(WHITE, ROOK, 0, 0);
    pieces[1] = Piece(WHITE, KNIGHT, 1, 0);
    pieces[2] = Piece(WHITE, BISHOP, 2, 0);
    pieces[3] = Piece(WHITE, QUEEN, 3, 0);
    pieces[4] = Piece(WHITE, KING, 4, 0);
    pieces[5] = Piece(WHITE, BISHOP, 5, 0);
    pieces[6] = Piece(WHITE, KNIGHT, 6, 0);
    pieces[7] = Piece(WHITE, ROOK, 7, 0);
    for (int i = 0; i < 8; i++) {
        pieces[8 + i] = Piece(WHITE, PAWN, i, 1);
    }
    // black pieces
    pieces[16] = Piece(BLACK, ROOK, 0, 7);
    pieces[17] = Piece(BLACK, KNIGHT, 1, 7);
    pieces[18] = Piece(BLACK, BISHOP, 2, 7);
    pieces[19] = Piece(BLACK, QUEEN, 3, 7);
    pieces[20] = Piece(BLACK, KING, 4, 7);
    pieces[21] = Piece(BLACK, BISHOP, 5, 7);
    pieces[22] = Piece(BLACK, KNIGHT, 6, 7);
    pieces[23] = Piece(BLACK, ROOK, 7, 7);
    for (int i = 0; i < 8; i++) {
        pieces[24 + i] = Piece(BLACK, PAWN, i, 6);
    }
}

float Board::get_eval() {
    int pos_eval = 0;
    // TODO: implement evaluation function
    return pos_eval; 
}

std::vector<Board> Board::generate_moves() {
    std::vector<Board> moves;

    // TODO: implement move generation function
    
    for (int i = 0; i < pieces.size(); i++) {

    }

    return moves;
}

#endif