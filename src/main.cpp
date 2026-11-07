// std includes
#include <iostream>
// my files
#include "include/Position.h"
#include "include/SearchEngine.h"

using namespace std;

int main() {
    Position pos{false};
    PieceVector pieces = pos.get_pieces();
    pieces["a8"] = Piece::BKING;
    pieces["a7"] = Piece::BPAWN;
    pieces["b7"] = Piece::BPAWN;
    pieces["f4"] = Piece::WROOK;
    pieces["f1"] = Piece::WKING;
    pos.set_pieces(pieces);
    SearchEngine search_engine{pos};

    pos.set_side_to_move(Colors::WHITE);
    Move best_move = search_engine.search(1, Colors::WHITE);
}