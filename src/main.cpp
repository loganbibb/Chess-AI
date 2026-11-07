// std includes
#include <iostream>
// my files
#include "include/Position.h"

using namespace std;

int main() {
    Position pos;
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e7")] = Piece::WPAWN;
    pieces[Square("e8")] = Piece::NOPIECE;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);

    std::vector<Move> moves = pos.generate_legal_moves();
}