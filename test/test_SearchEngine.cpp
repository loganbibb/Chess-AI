#include <gtest/gtest.h>
#include "../src/include/SearchEngine.h"

// Test fixture for Position tests
class SearchEngineTest : public ::testing::Test {
protected:
    Position pos{false}; // default constructor sets up starting position
    SearchEngine search_engine{pos};
    
    void set_up_starting_position() {
        pos = Position(true);
    }
};

// Move generation tests
TEST_F(SearchEngineTest, BackRankMateInOne) {
    auto& pieces = pos.get_pieces();
    pieces["a8"] = Piece::BKING;
    pieces["a7"] = Piece::BPAWN;
    pieces["b7"] = Piece::BPAWN;
    pieces["f4"] = Piece::WROOK;
    pieces["f1"] = Piece::WKING;
    pos.set_pieces(pieces);

    pos.set_side_to_move(Colors::WHITE);
    Move best_move = search_engine.search(1, Colors::WHITE);
    EXPECT_EQ(best_move.from_square, Square("f4"));
    EXPECT_EQ(best_move.to_square, Square("f8"));

}