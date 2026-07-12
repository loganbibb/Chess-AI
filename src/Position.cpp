#include <algorithm>
#include <iostream>
#include <iomanip>

#include "include/Move.h"
#include "include/Piece.h"
#include "include/Position.h"
#include "include/Unmove.h"
#include "include/move_offsets.h"

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
        candidate_sq = sq.apply_offset(1, 1); // capture to the right
        if (candidate_sq.in_bounds() && 
            pieces[candidate_sq] != Piece::NOPIECE && get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }
        candidate_sq = sq.apply_offset(-1, 1); // capture to the left
        if (candidate_sq.in_bounds() && 
            pieces[candidate_sq] != Piece::NOPIECE && get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }

        // en passant capture
        if (en_passant_square.in_bounds()) { // check if en passant square is valid
            if (((en_passant_square.file() == sq.file() + 1) || (en_passant_square.file() == sq.file() - 1)) &&
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
        candidate_sq = sq.apply_offset(-1, -1); // capture to the right
        if (candidate_sq.in_bounds() && 
            (pieces[candidate_sq] != Piece::NOPIECE) && get_piece_color(pieces[candidate_sq]) == Colors::WHITE) {
                Move new_move;
                new_move.from_square = sq; 
                new_move.to_square = candidate_sq;
                new_move.is_castle = false;
                new_move.is_promotion = false; 
                new_move.is_en_passant = false;
                pawn_moves.push_back(new_move);
        }
        candidate_sq = sq.apply_offset(1, -1); // capture to the left
        if (candidate_sq.in_bounds() && 
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
        if (en_passant_square.in_bounds()) { // check if en passant square is valid
            if (((en_passant_square.file() == sq.file() + 1) || (en_passant_square.file() == sq.file() - 1)) &&
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
    Square candidate_sq = sq; 
    Colors own_color = get_piece_color(pieces[sq]);
    for (const auto& offset : offsets::knight_move_offsets) {
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
    Square candidate_sq = sq;
    Colors own_color = get_piece_color(pieces[sq]);

    for (int i = 0; i < 4; i++) {
        candidate_sq = sq;
        auto offset = offsets::bishop_move_offsets[i];
        while (true) {
            candidate_sq = sq.apply_offset(offset.first, offset.second);
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
            // continue to step in the same direction as the offset for the next iteration of the loop
            offset.first += offsets::bishop_move_offsets[i].first;
            offset.second += offsets::bishop_move_offsets[i].second;
        }
    }
}

void Position::generate_rook_moves(Square& sq, std::vector<Move>& moves) {
    Square candidate_sq = sq;
    Colors own_color = get_piece_color(pieces[sq]);

    for (int i = 0; i < 4; i++) {
        candidate_sq = sq;
        auto offset = offsets::rook_move_offsets[i];
        while (true) {
            candidate_sq.apply_offset(offset.first, offset.second, true);
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
    

    Square candidate_sq = sq; 
    Colors own_color = get_piece_color(pieces[sq]);

    // normal king moves
    for (const auto& offset : offsets::king_move_offsets) {
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
        if (castling_rights.white_kingside && 
            pieces["e1"] == Piece::WKING && pieces["h1"] == Piece::WROOK && 
            pieces["f1"] == Piece::NOPIECE && pieces["g1"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("g1");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
        if (castling_rights.white_queenside && 
            pieces["e1"] == Piece::WKING && pieces["a1"] == Piece::WROOK && 
            pieces["b1"] == Piece::NOPIECE && pieces["c1"] == Piece::NOPIECE && pieces["d1"] == Piece::NOPIECE) {
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
        if (castling_rights.black_kingside && 
            pieces["e8"] == Piece::WKING && pieces["h8"] == Piece::WROOK && 
            pieces["f8"] == Piece::NOPIECE && pieces["g8"] == Piece::NOPIECE) {
            Move new_move;
            new_move.from_square = sq; 
            new_move.to_square = Square("g8");
            new_move.is_castle = true;
            new_move.is_promotion = false; 
            new_move.is_en_passant = false;
            moves.push_back(new_move);
        }
        if (castling_rights.black_queenside && 
            pieces["e8"] == Piece::WKING && pieces["a8"] == Piece::WROOK && 
            pieces["b8"] == Piece::NOPIECE && pieces["c8"] == Piece::NOPIECE && pieces["d8"] == Piece::NOPIECE) {
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

double Position::eval_terminal_position() {
    /*
     * When this function is called, we assume we have already 
     * determined there are no legal moves for the side to move.
     * This function only returns the score based on whether 
     * the position is checkmate (return +/-inf) or stalemate (return 0).
    */
   if (is_in_check(find_king(side_to_move), side_to_move)) {
        // checkmate
        if (side_to_move == Colors::WHITE) {
            return -1E10;
        }
        else {
            return 1E10;
        }
   }
   else {
       // stalemate
       return 0;
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

std::vector<Move> Position::generate_legal_moves() {
    std::vector<Move> moves = generate_moves();
    std::vector<Move> legal_moves;
    for (auto& move : moves) {
        Unmove unmove; 
        Colors original_color = side_to_move;
        make_move(move, unmove);
        Square king_sq = find_king(original_color);
        bool legal_move = true;
        if (is_in_check(king_sq, original_color)) {
            // moved into check, which is illegal. Remove this move from the list of legal moves.
            legal_move = false; 
        }
        else if (move.is_castle) {
            // check if king passes through a square that is attacked (illegal)
            if (original_color == Colors::WHITE) {
                if (move.to_square == "g1" && (!castling_rights.white_kingside || is_square_attacked(Square("f1"), Colors::BLACK) || is_square_attacked(Square("g1"), Colors::BLACK))) {
                    legal_move = false; 
                }
                else if (move.to_square == "c1" && (!castling_rights.white_queenside || is_square_attacked(Square("f1"), Colors::BLACK) || is_square_attacked(Square("g1"), Colors::BLACK))) {
                    legal_move = false; 
                }
            }
            else { // black to move
                if (move.to_square == "g8" && (!castling_rights.black_kingside || is_square_attacked(Square("f8"), Colors::WHITE) || is_square_attacked(Square("g8"), Colors::WHITE))) {
                    legal_move = false; 
                }
                else if (move.to_square == "c8" && (!castling_rights.black_queenside || is_square_attacked(Square("d8"), Colors::WHITE) || is_square_attacked(Square("c8"), Colors::WHITE))) {
                    legal_move = false; 
                }
            }
        }
        unmake_move(move, unmove);
        if (legal_move) {
            legal_moves.push_back(move);
        }
    }
    return legal_moves;
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
    side_to_move = get_opposite_color(side_to_move);
    if (side_to_move == Colors::WHITE) {
        fullmove_num++;
    }

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

void Position::print_moves() {
    std::vector<Move> moves = generate_moves();

    for (const Move& move : moves) {
        std::string notation;

        if (move.is_castle) {
            notation = (move.to_square == "g1" || move.to_square == "g8") ? "O-O" : "O-O-O";
        } else {
            Piece moving_piece = pieces[move.from_square];
            bool is_capture = move.is_en_passant || pieces[move.to_square] != Piece::NOPIECE;

            switch (moving_piece) {
                case Piece::WKNIGHT:
                case Piece::BKNIGHT:
                    notation += "N";
                    break;
                case Piece::WBISHOP:
                case Piece::BBISHOP:
                    notation += "B";
                    break;
                case Piece::WROOK:
                case Piece::BROOK:
                    notation += "R";
                    break;
                case Piece::WQUEEN:
                case Piece::BQUEEN:
                    notation += "Q";
                    break;
                case Piece::WKING:
                case Piece::BKING:
                    notation += "K";
                    break;
                default:
                    break;
            }

            if (moving_piece == Piece::WPAWN || moving_piece == Piece::BPAWN) {
                if (is_capture) {
                    notation = move.from_square.to_string().substr(0, 1) + "x" + move.to_square.to_string();
                } else {
                    notation = move.to_square.to_string();
                }
            } else {
                if (is_capture) {
                    notation += "x";
                }
                notation += move.to_square.to_string();
            }

            if (move.is_promotion) {
                char promotion_char = 'q';
                if (move.promotion_piece == Piece::WROOK || move.promotion_piece == Piece::BROOK) {
                    promotion_char = 'r';
                } else if (move.promotion_piece == Piece::WBISHOP || move.promotion_piece == Piece::BBISHOP) {
                    promotion_char = 'b';
                } else if (move.promotion_piece == Piece::WKNIGHT || move.promotion_piece == Piece::BKNIGHT) {
                    promotion_char = 'n';
                }
                notation += "=" + std::string(1, promotion_char);
            }

            if (move.is_check) {
                notation += "+";
            }
        }

        std::cout << notation << std::endl;
    }
}

void Position::show() {
    // Print out 8x8 board with pieces represented by their enum values.
    // Primarily for debugging. 
    std::cout << pieces.to_string() << std::endl;
}

bool Position::is_square_attacked(Square sq, Colors attacker) {
    if (attacker == Colors::WHITE) {
        // check for white pawn attacks
        if (sq.file() > 0 && sq.rank() < 7 && pieces(sq.file() - 1, sq.rank() - 1) == Piece::WPAWN) {
            return true;
        }
        if (sq.file() < 7 && sq.rank() < 7 && pieces(sq.file() + 1, sq.rank() - 1) == Piece::WPAWN) {
            return true;
        }
        for (const auto& offset : offsets::knight_move_offsets) {
            Square candidate_sq = sq.apply_offset(offset.first, offset.second);
            if (candidate_sq.in_bounds() && pieces[candidate_sq] == Piece::WKNIGHT) {
                return true;
            }
        }
        for (const auto& offset : offsets::king_move_offsets) {
            Square candidate_sq = sq.apply_offset(offset.first, offset.second);
            if (candidate_sq.in_bounds() && pieces[candidate_sq] == Piece::WKING) {
                return true;
            }
        }
        Square candidate_sq = sq;
        std::pair<int, int> offset;
        for (int i = 0; i < 4; i++) {
            candidate_sq = sq;
            offset = offsets::bishop_move_offsets[i];
            while (true) {
                candidate_sq.apply_offset(offset.first, offset.second, true);
                if (!candidate_sq.in_bounds()) {
                    break;
                }
                if (get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                    break; // cannot be attacked in this direction if there is a piece blocking that is not the attacker
                }
                else if (pieces[candidate_sq] == Piece::WBISHOP || pieces[candidate_sq] == Piece::WQUEEN) {
                    return true; // attacked by bishop or queen in this direction
                }
            }
            candidate_sq = sq;
            offset = offsets::rook_move_offsets[i];
            while (true) {
                candidate_sq.apply_offset(offset.first, offset.second, true);
                if (!candidate_sq.in_bounds()) {
                    break;
                }
                if (get_piece_color(pieces[candidate_sq]) == Colors::BLACK) {
                    break; // cannot be attacked in this direction if there is a piece blocking that is not the attacker
                }
                else if (pieces[candidate_sq] == Piece::WROOK || pieces[candidate_sq] == Piece::WQUEEN) {
                    return true; // attacked by rook or queen in this direction
                }
            }
        }
    } 
    else if (attacker == Colors::BLACK) {
        // check for black pawn attacks
        if (sq.file() > 0 && sq.rank() > 0 && pieces(sq.file() - 1, sq.rank() + 1) == Piece::BPAWN) {
            return true;
        }
        if (sq.file() < 7 && sq.rank() > 0 && pieces(sq.file() + 1, sq.rank() + 1) == Piece::BPAWN) {
            return true;
        }
        for (const auto& offset : offsets::knight_move_offsets) {
            Square candidate_sq = sq.apply_offset(offset.first, offset.second);
            if (candidate_sq.in_bounds() && pieces[candidate_sq] == Piece::BKNIGHT) {
                return true;
            }
        }
        for (const auto& offset : offsets::king_move_offsets) {
            Square candidate_sq = sq.apply_offset(offset.first, offset.second);
            if (candidate_sq.in_bounds() && pieces[candidate_sq] == Piece::BKING) {
                return true;
            }
        }
        Square candidate_sq = sq;
        std::pair<int, int> offset;
        for (int i = 0; i < 4; i++) {
            candidate_sq = sq;
            offset = offsets::bishop_move_offsets[i];
            while (true) {
                candidate_sq.apply_offset(offset.first, offset.second, true);
                if (!candidate_sq.in_bounds()) {
                    break;
                }
                if (get_piece_color(pieces[candidate_sq]) == Colors::WHITE) {
                    break; // cannot be attacked in this direction if there is a piece blocking that is not the attacker
                }
                else if (pieces[candidate_sq] == Piece::BBISHOP || pieces[candidate_sq] == Piece::BQUEEN) {
                    return true; // attacked by bishop or queen in this direction
                }
            }
            candidate_sq = sq;
            offset = offsets::rook_move_offsets[i];
            while (true) {
                candidate_sq.apply_offset(offset.first, offset.second, true);
                if (!candidate_sq.in_bounds()) {
                    break;
                }
                if (get_piece_color(pieces[candidate_sq]) == Colors::WHITE) {
                    break; // cannot be attacked in this direction if there is a piece blocking that is not the attacker
                }
                else if (pieces[candidate_sq] == Piece::BROOK || pieces[candidate_sq] == Piece::BQUEEN) {
                    return true; // attacked by rook or queen in this direction
                }
            }
        }
    }
    return false; // no attacks found 
}

bool Position::is_in_check(Square king_sq, Colors king_color) {
    return is_square_attacked(king_sq, get_opposite_color(king_color));
}

Square Position::find_king(Colors king_color) {
    auto it = std::find(pieces.begin(), pieces.end(), (king_color == Colors::WHITE) ? Piece::WKING : Piece::BKING);
    auto dist = std::distance(pieces.begin(), it);
    if (dist < 0 || dist >= 64) {
        throw Exceptions::InvalidPositionException("King not found on the board.");
    }
    return Square(static_cast<int>(dist));
}