#include <gtest/gtest.h>
#include <algorithm>
#include <iostream>
#include "../src/include/SearchEngine.h"

// Test fixture for Position tests
class SearchEngineTest : public ::testing::Test {
protected:
    Position pos{false}; // default constructor sets up starting position
    SearchEngine search_engine{pos};
    
    void set_up_starting_position() {
        pos = Position(true);
    }
    
    void set_up_kings(Square white_king_square = Square("e1"), Square black_king_square = Square("e8")) {
        PieceVector pieces = pos.get_pieces();
        if (std::find(pieces.begin(), pieces.end(), Piece::WKING) == pieces.end()) {
            ASSERT_EQ(pieces[white_king_square], Piece::NOPIECE);
            pieces[white_king_square] = Piece::WKING;
        }
        if (std::find(pieces.begin(), pieces.end(), Piece::BKING) == pieces.end()) {
            ASSERT_EQ(pieces[black_king_square], Piece::NOPIECE);
            pieces[black_king_square] = Piece::BKING;
        }
        pos.set_pieces(pieces);
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
    EXPECT_EQ(best_move.from_square.to_string(), "f4");
    EXPECT_EQ(best_move.to_square.to_string(), "f8");
}

TEST_F(SearchEngineTest, BackRankMateInOneSearchDepthTwo) {
    auto& pieces = pos.get_pieces();
    pieces["a8"] = Piece::BKING;
    pieces["a7"] = Piece::BPAWN;
    pieces["b7"] = Piece::BPAWN;
    pieces["f4"] = Piece::WROOK;
    pieces["f1"] = Piece::WKING;
    pos.set_pieces(pieces);

    pos.set_side_to_move(Colors::WHITE);
    Move best_move = search_engine.search(2, Colors::WHITE);
    EXPECT_EQ(best_move.from_square.to_string(), "f4");
    EXPECT_EQ(best_move.to_square.to_string(), "f8");
}

TEST_F(SearchEngineTest, StalemateDetection) {
    auto& pieces = pos.get_pieces();
    pieces["a8"] = Piece::BKING;
    pieces["a7"] = Piece::BPAWN;
    pieces["b7"] = Piece::BPAWN;
    pieces["h6"] = Piece::BBISHOP;
    pieces["c2"] = Piece::BQUEEN;
    pieces["f4"] = Piece::WROOK;
    pieces["a1"] = Piece::WKING;
    pos.set_pieces(pieces);
    testing::internal::CaptureStdout();
    pos.show();
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output << std::endl;

    pos.set_side_to_move(Colors::WHITE);
    Move best_move = search_engine.search(4, Colors::WHITE);
    EXPECT_EQ(best_move.from_square.to_string(), "f4");
    EXPECT_EQ(best_move.to_square.to_string(), "f8");
    Unmove unmove;
    pos.make_move(best_move, unmove);

    testing::internal::CaptureStdout();
    pos.show();
    output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, pos.get_pieces().to_string() + "\n");
    std::cout << output;
}
