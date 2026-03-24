#include "Pieces.h"
#include <vector>

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
    bool white_check = false;
    bool black_check = false;

    // functions 
    void setup_starting_position();
public:
    Position();
    float get_eval();
    inline std::vector<Pieces> get_pieces();
    void set_pieces(std::vector<Pieces> new_pieces);
    std::vector<Position> generate_moves();
    
    void show();
    
};

#endif