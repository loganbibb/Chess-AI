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
