// std includes
#include <iostream>
// my files
#include "include/Position.h"
#include "include/SearchEngine.h"

using namespace std;

int main() {
    // Set up a custom position: White pawn at e4, Black pawn at d5
    Position pos{false};
    SearchEngine search_engine(pos);
    auto& pieces = pos.get_pieces();
    pieces["a8"] = Piece::BKING;
    pieces["a7"] = Piece::BPAWN;
    pieces["b7"] = Piece::BPAWN;
    pieces["f4"] = Piece::WROOK;
    pieces["f1"] = Piece::WKING;
    pos.set_pieces(pieces);

    pos.set_side_to_move(Colors::WHITE);
    Move best_move = search_engine.search(2, Colors::WHITE);
    std::cout << best_move.from_square.to_string() << " -> " << best_move.to_square.to_string() << std::endl;
}