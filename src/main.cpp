// std includes
#include <iostream>
// my files
#include "include/Position.h"
#include "include/SearchEngine.h"

using namespace std;

int main() {
    // Set up a custom position: White pawn at e4, Black pawn at d5
    Position pos;
    PieceVector pieces = pos.get_pieces();
    pieces[Square("e4")] = Piece::WPAWN;
    pieces[Square("d5")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_capture = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("e4") && move.to_square == Square("d5")) {
            found_capture = true;
            break;
        }
    }
    std::cout << "found capture? " << (found_capture) << " White pawn at e4 should be able to capture at d5";
}