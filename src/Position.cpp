#include <iostream>
#include <iomanip>

#include "include/Move.h"
#include "include/Piece.h"
#include "include/Position.h"
#include "include/Unmove.h"

Position::Position(bool setup_starting){
    /* Creates a board with pieces at the starting positions. */
    eval = 0;
    if (setup_starting) {
        setup_starting_position();
    }
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

void Position::set_pieces(PieceVector new_pieces) {
    // To be used sparingly, as it does not check for validity of the new position. Primarily for testing purposes.
    pieces = new_pieces;
}

void Position::generate_pawn_moves(Square& sq, std::vector<Move>& moves) {
    /*
     * Handle pawn move generation. 
     * Generates a series of moves for a pawn at the given square, including normal moves, captures, en passant, and promotions.
     * Returns a vector of Moves.
     * NOTE: this function does not check for checks, so it may generate illegal moves. This is intentional, as it allows for 
     * faster move generation. The legality of moves will be checked in generate_moves().
    */
    Square candidate_sq;
    candidate_sq = sq; 
    std::vector<Move> pawn_moves;

    if (get_piece_color(pieces[sq]) == Colors::WHITE) {
        // nominal pawn move 
        candidate_sq.inc_rank(); 
        if (pieces[candidate_sq] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = candidate_sq;
            new_move.is_castle = false;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            pawn_moves.push_back(new_move);

            candidate_sq.inc_rank();
            if ((sq.rank() == 1) && (pieces(candidate_sq) == Piece::NOPIECE)) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
            }
        }
        // captures
        candidate_sq = sq + 9; // capture to the right
        if ((candidate_sq.file() <= 7) && (candidate_sq.rank() <= 7) && 
            (pieces[candidate_sq] != Piece::NOPIECE) && get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }
        candidate_sq = sq + 7; // capture to the left
        if ((candidate_sq.file() >= 0) && (candidate_sq.rank() <= 7) && 
            (pieces[candidate_sq] != Piece::NOPIECE) && get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }

        // en passant capture
        if (en_passant_square() >= 0 && en_passant_square() < 64) { // check if en passant square is valid
            if ((pieces[en_passant_square] == Piece::BPAWN) && 
                ((en_passant_square.file() == sq.file() + 1) || (en_passant_square.file() == sq.file() - 1)) &&
                (en_passant_square.rank() == sq.rank() + 1)) {
                    Move new_move;
                    new_move.from_square = sq;
                    new_move.to_square = en_passant_square;
                    new_move.is_en_passant = true;
                    pawn_moves.push_back(new_move);
                }
        }

    }
    else if (get_piece_color(pieces[sq]) == Colors::BLACK) { 
        // nominal pawn move 
        candidate_sq.dec_rank(); 
        if (pieces[candidate_sq] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = candidate_sq;
            new_move.is_castle = false;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            pawn_moves.push_back(new_move);

            candidate_sq.dec_rank();
            if ((sq.rank() == 6) && (pieces[candidate_sq] == Piece::NOPIECE)) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
            }
        }
        // captures
        candidate_sq = sq - 9; // capture to the right
        if ((candidate_sq.file() >= 0) && (candidate_sq.rank() >= 0) && 
            (pieces[candidate_sq] != Piece::NOPIECE) && get_piece_color(pieces[candidate_sq]) == Colors::WHITE) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }
        candidate_sq = sq - 7; // capture to the left
        if ((candidate_sq.file() <= 7) && (candidate_sq.rank() >= 0) && 
            (pieces[candidate_sq] != Piece::NOPIECE) && get_piece_color(pieces[candidate_sq]) == Colors::WHITE) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }

        // en passant capture
        if (en_passant_square() >= 0 && en_passant_square() < 64) { // check if en passant square is valid
            if ((pieces[en_passant_square] == Piece::WPAWN) && 
                ((en_passant_square.file() == sq.file() + 1) || (en_passant_square.file() == sq.file() - 1)) &&
                (en_passant_square.rank() == sq.rank() - 1)) {
                    Move new_move;
                    new_move.from_square = sq;
                    new_move.to_square = en_passant_square;
                    new_move.is_en_passant = true;
                    pawn_moves.push_back(new_move);
                }
        }
    }

    // check for promotions at the end of move generation, and add promotion moves if applicable.
    for (Move& move : pawn_moves) {
        if ((move.to_square.rank() == 7) && (side_to_move == Colors::WHITE)) {
            move.is_promotion = true;
            move.promotion_piece = Piece::WQUEEN; // for now, only generate queen promotions. TODO: add underpromotions.
        }
        else if ((move.to_square.rank() == 0) && (side_to_move == Colors::BLACK)) {
            move.is_promotion = true;
            move.promotion_piece = Piece::BQUEEN; // for now, only generate queen promotions. TODO: add underpromotions.
        }
    }

    // add generated pawn moves to moves vector
    moves.insert(moves.end(), pawn_moves.begin(), pawn_moves.end());
}

void Position::generate_knight_moves(Square& sq, std::vector<Move>& moves) {
    static const std::vector<std::pair<int, int>> knight_move_offsets = {
        {1, 2}, {2, 1}, {2, -1}, {1, -2}, 
        {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}
    };

    Square candidate_sq = sq; 
    Colors own_color = get_piece_color(pieces[sq]);
    for (const auto& offset : knight_move_offsets) {
        candidate_sq = sq.apply_offset(offset.first, offset.second);
        if (candidate_sq.in_bounds() && (pieces[candidate_sq] == Piece::NOPIECE || get_piece_color(pieces[candidate_sq]) != own_color)) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = candidate_sq;
            new_move.is_castle = false;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
    }
}

void Position::generate_bishop_moves(Square& sq, std::vector<Move>& moves) {
    static const int rank_offsets[] = {1, 1, -1, -1};
    static const int file_offsets[] = {1, -1, 1, -1};
    Square candidate_sq = sq;
    Colors own_color = get_piece_color(pieces[sq]);

    for (int i = 0; i < 4; i++) {
        candidate_sq = sq;
        while (true) {
            candidate_sq = sq.apply_offset(file_offsets[i], rank_offsets[i]);
            if (!candidate_sq.in_bounds()) {
                break;
            }
            if (get_piece_color(pieces[candidate_sq]) != own_color) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                moves.push_back(new_move);
                if (pieces[candidate_sq] != Piece::NOPIECE) {
                    break; // cannot jump over pieces, so stop looking in this direction after a capture
                }
            }
            else { // own piece is blocking
                break;
            }
        }
    }
}

void Position::generate_rook_moves(Square& sq, std::vector<Move>& moves) {
    static const int rank_offsets[] = {1, -1, 0, 0};
    static const int file_offsets[] = {0, 0, 1, -1};
    Square candidate_sq = sq;
    Colors own_color = get_piece_color(pieces[sq]);

    for (int i = 0; i < 4; i++) {
        candidate_sq = sq;
        while (true) {
            candidate_sq = sq.apply_offset(file_offsets[i], rank_offsets[i]);
            if (!candidate_sq.in_bounds()) {
                break;
            }
            if (get_piece_color(pieces[candidate_sq]) != own_color) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                moves.push_back(new_move);
                if (pieces[candidate_sq] != Piece::NOPIECE) {
                    break; // cannot jump over pieces, so stop looking in this direction after a capture
                }
            }
            else { // own piece is blocking
                break;
            }
        }
    }
}

void Position::generate_queen_moves(Square& sq, std::vector<Move>& moves) {
    // queen moves are just sum of rook and bishop moves
    generate_bishop_moves(sq, moves);
    generate_rook_moves(sq, moves);
}

void Position::generate_king_moves(Square& sq, std::vector<Move>& moves) {
    static const std::vector<std::pair<int, int>> king_move_offsets = {
        {1, 1}, {1, 0}, {1, -1}, 
        {0, -1}, {-1, -1}, {-1, 0}, 
        {-1, 1}, {0, 1}
    };

    Square candidate_sq = sq; 
    Colors own_color = get_piece_color(pieces[sq]);

    // normal king moves
    for (const auto& offset : king_move_offsets) {
        candidate_sq = sq.apply_offset(offset.first, offset.second);
        if (candidate_sq.in_bounds() && (pieces[candidate_sq] == Piece::NOPIECE || get_piece_color(pieces[candidate_sq]) != own_color)) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = candidate_sq;
            new_move.is_castle = false;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
    }

    // castling moves
    // Note: pseudo-legal castling moves are generated here. 
    // Only check if there are pieces in the way and if the king and rook have castling rights. 
    // Check conditions will be handled in generate_moves() to avoid unnecessary checks during move generation.
    if (side_to_move == Colors::WHITE) {
        if (castling_rights.white_kingside && pieces["f1"] == Piece::NOPIECE && pieces["g1"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("g1");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
        if (castling_rights.white_queenside && pieces["b1"] == Piece::NOPIECE && pieces["c1"] == Piece::NOPIECE && pieces["d1"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("c1");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
    }
    else { // black to move 
        if (castling_rights.black_kingside && pieces["f8"] == Piece::NOPIECE && pieces["g8"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("g8");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
        if (castling_rights.black_queenside && pieces["b8"] == Piece::NOPIECE && pieces["c8"] == Piece::NOPIECE && pieces["d8"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("c8");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
    }

}

std::vector<Move> Position::generate_moves() {
    std::vector<Move> moves;

    // TODO: implement move generation for all pieces. For now, only implement pawn move generation as a proof of concept.
    if (side_to_move == Colors::WHITE) {
        for (int i = 0; i < 64; i++) {
            if (pieces[i] == Piece::WPAWN) {
                Square sq(i);
                generate_pawn_moves(sq, moves);
            }
            else if (pieces[i] == Piece::WKNIGHT) {
                Square sq(i);
                generate_knight_moves(sq, moves);
            }
            else if (pieces[i] == Piece::WBISHOP) {
                Square sq(i);
                generate_bishop_moves(sq, moves);
            }
            else if (pieces[i] == Piece::WROOK) {
                Square sq(i);
                generate_rook_moves(sq, moves);
            }
            else if (pieces[i] == Piece::WQUEEN) {
                Square sq(i);
                generate_queen_moves(sq, moves);
            }
            else if (pieces[i] == Piece::WKING) {
                Square sq(i);
                generate_king_moves(sq, moves);
            }
        }
    }
    else {
        for (int i = 0; i < 64; i++) {
            if (pieces[i] == Piece::BPAWN) {
                Square sq(i);
                generate_pawn_moves(sq, moves);
            }
            else if (pieces[i] == Piece::BKNIGHT) {
                Square sq(i);
                generate_knight_moves(sq, moves);
            }
            else if (pieces[i] == Piece::BBISHOP) {
                Square sq(i);
                generate_bishop_moves(sq, moves);
            }
            else if (pieces[i] == Piece::BROOK) {
                Square sq(i);
                generate_rook_moves(sq, moves);
            }
            else if (pieces[i] == Piece::BQUEEN) {
                Square sq(i);
                generate_queen_moves(sq, moves);
            }
            else if (pieces[i] == Piece::BKING) {
                Square sq(i);
                generate_king_moves(sq, moves);
            }
        }
    }

    return moves;
}

void Position::make_move(Move& move, Unmove& unmove) {
    /**
     * Applies a move to the current position.
     * Special handling for castling, promotion, and en passant
     * increment halfmove clock, and reset if pawn move or capture
     * Increment fullmove number if white to move
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
        en_passant_square = Square(); // Square constructor defaults to index = INT8_MAX, which we will use to represent no en passant square.
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

bool is_check(Position& pos, Colors color, Square sq) {
    // TODO: implement check detection function. This will be necessary for move generation and for evaluating positions.
    return false;
};

