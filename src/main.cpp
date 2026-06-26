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
    pieces[Square("e4")] = Piece::WPAWN;
    pieces[Square("d4")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    pos.set_en_passant_square(Square("e3"));
    pos.set_side_to_move(Colors::BLACK);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_en_passant = false;
    for (const auto& move : moves) {
        if (move.is_en_passant && move.from_square == Square("e4") && move.to_square == Square("d3")) {
            found_en_passant = true;
            break;
        }
    }
    return 0;
}