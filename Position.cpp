#include <iostream>
#include <iomanip>

#include "Position.h"

Position::Position(){
    /* Creates a board with pieces at the starting positions. */
    eval = 0;
    setup_starting_position();
}

void Position::setup_starting_position() {
    // add pieces to board in starting positions
    // board is ordered from a1 to h8, with a1 being index 0 and h8 being index 63.
    pieces.resize(64, Pieces::NOPIECE); // 8x8 board has 64 squares. Initialize all squares to NOPIECE first.
    // white pieces 
    pieces[0] = Pieces::WROOK; 
    pieces[1] = Pieces::WKNIGHT;
    pieces[2] = Pieces::WBISHOP;
    pieces[3] = Pieces::WQUEEN;
    pieces[4] = Pieces::WKING;
    pieces[5] = Pieces::WBISHOP;
    pieces[6] = Pieces::WKNIGHT;
    pieces[7] = Pieces::WROOK;
    for (int i = 8; i < 16; i++) {
        pieces[i] = Pieces::WPAWN;
    }

    // black pieces
    pieces[56] = Pieces::BROOK;
    pieces[57] = Pieces::BKNIGHT;
    pieces[58] = Pieces::BBISHOP;
    pieces[59] = Pieces::BQUEEN;
    pieces[60] = Pieces::BKING;
    pieces[61] = Pieces::BBISHOP;
    pieces[62] = Pieces::BKNIGHT;
    pieces[63] = Pieces::BROOK;
    for (int i = 48; i < 56; i++) {
        pieces[i] = Pieces::BPAWN;
    }

}

float Position::get_eval() {
    int pos_eval = 0;
    // TODO: implement evaluation function
    return pos_eval; 
}

inline std::vector<Pieces> Position::get_pieces() {
    return pieces;
}

void Position::set_pieces(std::vector<Pieces> new_pieces) {
    // To be used sparingly, as it does not check for validity of the new position. Primarily for testing purposes.
    pieces = new_pieces;
}

std::vector<Position> Position::generate_moves() {
    std::vector<Position> moves;

    // TODO: implement move generation function
    
    for (int i = 0; i < pieces.size(); i++) {

    }

    return moves;
}

void Position::show() {
    // Print out 8x8 board with pieces represented by their enum values.
    // Primarily for debugging. 
    for (int i = 8; i > 0; i--) {
        for (int j = 0; j < 8; j++) {
            std::cout << std::setw(3) << piece_to_string(pieces[(i-1)*8 + j]);
        }
        std::cout << std::endl;
    }
}