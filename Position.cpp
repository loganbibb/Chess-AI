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
    eval = 0;
    // TODO: implement evaluation function
    return eval; 
}

inline PieceVector Position::get_pieces() {
    return pieces;
}

void Position::set_pieces(PieceVector new_pieces) {
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

void Position::make_move(Move move) {
    /**
     * Applies a move to the current position.
     * Special handling for castling, promotion, and en passant
     * TODO: pass in and populate an undo-state object to allow for unmaking moves. This will be necessary for the search algorithm.
     * TODO: create an undo-state class
     */

    // perform the basic from-to move. Additional conditions will be handled below
    pieces[move.to_square()] = pieces[move.from_square()];
    pieces[move.from_square()] = Pieces::NOPIECE;

    // handle castle
    if (move.is_castle) {
        if (side_to_move == Colors::WHITE) {
            white_castling_rights_kingside = false;
            white_castling_rights_queenside = false;
        } else {
            black_castling_rights_kingside = false;
            black_castling_rights_queenside = false;
        }
        // if white kingside castle, move the rook as well
        if (move.to_square == "g1") {
            pieces["f1"] = Pieces::WROOK;
            pieces["h1"] = Pieces::NOPIECE;
        }
        // if white queenside castle, move the rook as well
        else if (move.to_square == "c1") {
            pieces["d1"] = Pieces::WROOK;
            pieces["a1"] = Pieces::NOPIECE;
        }
        // if black kingside castle, move the rook as well
        else if (move.to_square == "g8") {
            pieces["f8"] = Pieces::BROOK;
            pieces["h8"] = Pieces::NOPIECE;
        }
        // if black queenside castle, move the rook as well
        else if (move.to_square == "c8") {
            pieces["d8"] = Pieces::BROOK;
            pieces["a8"] = Pieces::NOPIECE;
        }
        else {
            throw Exceptions::InvalidMoveException("Invalid castle move. Castle moves must be to g1, c1, g8, or c8.");
        }
    }

    // handle promotion
    if (move.is_promotion) {
        pieces[move.to_square] = move.promotion_piece;
    }

    // handle en passant
    if (move.is_en_passant) {
        if (side_to_move == Colors::WHITE) {
            pieces(move.to_square.file(), move.to_square.rank() - 1) = Pieces::NOPIECE;
        } else {
            pieces(move.to_square.file(), move.to_square.rank() + 1) = Pieces::NOPIECE;
        }
    }

}

void Position::show() {
    // Print out 8x8 board with pieces represented by their enum values.
    // Primarily for debugging. 
    std::cout << pieces.to_string() << std::endl;
}

