// std includes
#include <iostream>
// my files
#include "include/Position.h"

using namespace std;

int main() {
    Position pos;
    // Set up: White pawn at e4, black pawn at d4, en passant square at d3
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("d4")] = Piece::WPAWN;
    pos.set_pieces(pieces);

    Square target("e5");
    std::cout << pos.is_square_attacked(target, Colors::WHITE) << std::endl;
    return 0;
}