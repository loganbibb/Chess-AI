#include "include/Piece.h"

std::string piece_to_string(const Piece& piece) {
    switch (piece) {
        case Piece::NOPIECE:
            return "--";
        case Piece::BPAWN:
            return "BP";
        case Piece::BKNIGHT:
            return "BN";
        case Piece::BBISHOP:
            return "BB";
        case Piece::BROOK:
            return "BR";
        case Piece::BQUEEN:
            return "BQ";
        case Piece::BKING:
            return "BK";
        case Piece::WPAWN:
            return "WP";
        case Piece::WKNIGHT:
            return "WN";
        case Piece::WBISHOP:
            return "WB";
        case Piece::WROOK:
            return "WR";
        case Piece::WQUEEN:
            return "WQ";
        case Piece::WKING:
            return "WK";
        default:
            return "UNKNOWN PIECE";
    }
}

Colors get_piece_color(const Piece& piece) {
    if (piece == Piece::NOPIECE) {
        return Colors::NOCOLOR;
    }
    else if(int(piece) > 0) {
        return Colors::WHITE;
    }
    else {
        return Colors::BLACK;
    }
}

Colors get_opposite_color(const Colors& color) {
    if (color == Colors::WHITE) {
        return Colors::BLACK;
    }
    else if (color == Colors::BLACK) {
        return Colors::WHITE;
    }
    else {
        throw Exceptions::InvalidColorException("Cannot get opposite color of NOCOLOR.");
    }
}
