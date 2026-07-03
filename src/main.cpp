// std includes
#include <iostream>
// my files
#include "include/Position.h"

using namespace std;

int main() {
    // Set up: White king on e1, white knight on e2 pinned by black rook on e8
    Position pos; 
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("e2")] = Piece::WKNIGHT;
    pieces[Square("e8")] = Piece::BROOK;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);

    std::vector<Move> moves = pos.generate_legal_moves();

    // The knight on e2 is pinned along the e-file and should have no legal moves
    bool found_move_from_e2 = false;
    for (const auto &move : moves) {
        if (move.from_square == Square("e2")) {
            found_move_from_e2 = true;
            break;
        }
    }
    return 0;
}