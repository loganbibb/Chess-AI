#include <iostream>
#include <iomanip>

#include "Move.h"
#include "Piece.h"
#include "Position.h"
#include "Unmove.h"

Position::Position(){
    /* Creates a board with pieces at the starting positions. */
    eval = 0;
    setup_starting_position();
}

void Position::setup_starting_position() {
    // add pieces to board in starting positions
    // board is ordered from a1 to h8, with a1 being index 0 and h8 being index 63.
    pieces.resize(64, Piece::NOPIECE); // 8x8 board has 64 squares. Initialize all squares to NOPIECE first.
    // white pieces 
    pieces[0] = Piece::WROOK; 
    pieces[1] = Piece::WKNIGHT;
    pieces[2] = Piece::WBISHOP;
    pieces[3] = Piece::WQUEEN;
    pieces[4] = Piece::WKING;
    pieces[5] = Piece::WBISHOP;
    pieces[6] = Piece::WKNIGHT;
    pieces[7] = Piece::WROOK;
    for (int i = 8; i < 16; i++) {
        pieces[i] = Piece::WPAWN;
    }

    // black pieces
    pieces[56] = Piece::BROOK;
    pieces[57] = Piece::BKNIGHT;
    pieces[58] = Piece::BBISHOP;
    pieces[59] = Piece::BQUEEN;
    pieces[60] = Piece::BKING;
    pieces[61] = Piece::BBISHOP;
    pieces[62] = Piece::BKNIGHT;
    pieces[63] = Piece::BROOK;
    for (int i = 48; i < 56; i++) {
        pieces[i] = Piece::BPAWN;
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
    
    for (int i = 0; i < (int)pieces.size(); i++) {

    }

    return moves;
}

void Position::make_move(Move& move, Unmove& unmove) {
    /**
     * Applies a move to the current position.
     * Special handling for castling, promotion, and en passant
     * increment halfmove clock, and reset if pawn move or capture
     * Increment fullmove number if white to move
     * TODO: pass in and populate an undo-state object to allow for unmaking moves. This will be necessary for the search algorithm.
     * TODO: create an undo-state class
     */

    // populate unmove for later move unmake
    unmove.captured_piece = pieces[move.to_square];
    unmove.halfmove_num = halfmove_num;
    unmove.fullmove_num = fullmove_num;
    unmove.castling_rights = castling_rights;
    unmove.en_passant_square = en_passant_square;

    // halfmove clock 
    if (pieces[move.to_square] != Piece::NOPIECE || pieces[move.from_square] == Piece::WPAWN || pieces[move.from_square] == Piece::BPAWN) {
        halfmove_num = 0;
    } else {
        halfmove_num++;
    }

    // perform the basic from-to move. Additional conditions will be handled below

    pieces[move.to_square] = pieces[move.from_square];
    pieces[move.from_square] = Piece::NOPIECE;

    // handle castle
    if (move.is_castle) {
        if (side_to_move == Colors::WHITE) {
            castling_rights.white_kingside = false;
            castling_rights.white_queenside = false;
        } else {
            castling_rights.black_kingside = false;
            castling_rights.black_queenside = false;
        }
        // if white kingside castle, move the rook as well
        if (move.to_square == "g1") {
            pieces["f1"] = Piece::WROOK;
            pieces["h1"] = Piece::NOPIECE;
        }
        // if white queenside castle, move the rook as well
        else if (move.to_square == "c1") {
            pieces["d1"] = Piece::WROOK;
            pieces["a1"] = Piece::NOPIECE;
        }
        // if black kingside castle, move the rook as well
        else if (move.to_square == "g8") {
            pieces["f8"] = Piece::BROOK;
            pieces["h8"] = Piece::NOPIECE;
        }
        // if black queenside castle, move the rook as well
        else if (move.to_square == "c8") {
            pieces["d8"] = Piece::BROOK;
            pieces["a8"] = Piece::NOPIECE;
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
            pieces(move.to_square.file(), move.to_square.rank() - 1) = Piece::NOPIECE;
        } else {
            pieces(move.to_square.file(), move.to_square.rank() + 1) = Piece::NOPIECE;
        }
    }

    // handle checks 
    if (move.is_check) {
        if (side_to_move == Colors::WHITE) {
            black_check = true;
        } else {
            white_check = true;
        }
    }

    // update ep_square if applicable 
    if (pieces[move.to_square()] == Piece::WPAWN && move.to_square.rank() == 3) {
        en_passant_square = Square(move.to_square.file(), 2);
    } else if (pieces[move.to_square()] == Piece::BPAWN && move.to_square.rank() == 4) {
        en_passant_square = Square(move.to_square.file(), 5);
    } else {
        en_passant_square = Square(-1);
    }

    // side to move, fullmove clock
    if (side_to_move == Colors::WHITE) {
        side_to_move = Colors::BLACK;
    } else {
        side_to_move = Colors::WHITE;
        fullmove_num++;
    }

    // lastly, update side_to_move
    side_to_move = (side_to_move == Colors::WHITE)? Colors::BLACK : Colors::WHITE; 

}

void Position::unmake_move(Move& move, Unmove& unmove){
    // return side_to_move
    side_to_move = (side_to_move == Colors::WHITE)? Colors::BLACK : Colors::WHITE; 
    // Reset Position from unmove 
    pieces[move.from_square] = pieces[move.to_square];
    pieces[move.to_square] = unmove.captured_piece; 
    halfmove_num = unmove.halfmove_num; 
    fullmove_num = unmove.fullmove_num; 
    castling_rights = unmove.castling_rights; 
    en_passant_square = unmove.en_passant_square; 

    // special conditions 
    if (move.is_castle) { 
        // white kingside castle
        if (move.to_square == "g1") {
            pieces["f1"] = Piece::NOPIECE;
            pieces["h1"] = Piece::WROOK;
        }
        // white queenside castle
        else if (move.to_square == "c1") {
            pieces["d1"] = Piece::NOPIECE;
            pieces["a1"] = Piece::WROOK;
        }
        // black kingside castle
        else if (move.to_square == "g8") {
            pieces["f8"] = Piece::NOPIECE;
            pieces["h8"] = Piece::BROOK;
        }
        // black queenside castle
        else if (move.to_square == "c8") {
            pieces["d8"] = Piece::NOPIECE;
            pieces["a8"] = Piece::BROOK;
        }
        else {
            throw Exceptions::InvalidMoveException("Invalid castle move. Castle moves must be to g1, c1, g8, or c8.");
        }
    }

    if (move.is_promotion) {
        // in this case, side_to_move is actually the side the side that made move (updated above)
        // so piece should match side_to_move
        pieces[move.from_square] = (side_to_move == Colors::WHITE)? Piece::WPAWN : Piece::BPAWN;  
    }

    if (move.is_en_passant) {
        if (side_to_move == Colors::WHITE) {
            pieces(move.to_square.file(), move.to_square.rank() - 1) = Piece::BPAWN;
        } else {
            pieces(move.to_square.file(), move.to_square.rank() + 1) = Piece::WPAWN;
        }
        pieces[move.to_square] = Piece::NOPIECE; // override pieces[move.to_square] = unmove.captured_piece; 
    }
}

void Position::show() {
    // Print out 8x8 board with pieces represented by their enum values.
    // Primarily for debugging. 
    std::cout << pieces.to_string() << std::endl;
}

