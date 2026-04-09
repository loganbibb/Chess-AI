#include <vector>

#include "Pieces.h"
#include "Move.h" 

#ifndef POSITION_H
#define POSITION_H

class Position {
    /*
    Position class represents the current state of the chess board. 
    It contains a vector of pieces and an evaluation score for the position. 
    It also has functions to generate legal moves and evaluate the position.
    */
    std::vector<Pieces> pieces; // initialize all squares to NOPIECE
    float eval = 0;
    Colors side_to_move = Colors::WHITE; 
    bool white_check = false;
    bool black_check = false;
    bool white_castling_rights_kingside = true; 
    bool white_castling_rights_queenside = true;
    bool black_castling_rights_kingside = true;
    bool black_castling_rights_queenside = true;


    // functions 
    void setup_starting_position();
public:
    Position();
    float get_eval();
    inline std::vector<Pieces> get_pieces();
    void set_pieces(std::vector<Pieces> new_pieces);
    std::vector<Position> generate_moves();
    void make_move(Move move);
    void unmake_move(Move move, Position old_position);
    void show();
    
};

#endif