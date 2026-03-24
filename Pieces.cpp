#include "Pieces.h"

std::string piece_to_string(Pieces piece) {
    switch (piece) {
        case Pieces::NOPIECE:
            return "--";
        case Pieces::BPAWN:
            return "BP";
        case Pieces::BKNIGHT:
            return "BN";
        case Pieces::BBISHOP:
            return "BB";
        case Pieces::BROOK:
            return "BR";
        case Pieces::BQUEEN:
            return "BQ";
        case Pieces::BKING:
            return "BK";
        case Pieces::WPAWN:
            return "WP";
        case Pieces::WKNIGHT:
            return "WN";
        case Pieces::WBISHOP:
            return "WB";
        case Pieces::WROOK:
            return "WR";
        case Pieces::WQUEEN:
            return "WQ";
        case Pieces::WKING:
            return "WK";
        default:
            return "UNKNOWN PIECE";
    }
}
