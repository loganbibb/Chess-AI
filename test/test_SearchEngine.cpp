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

    void make_move(Square from, Square to) {
        Move move;
        move.from_square = from;
        move.to_square = to;
        Unmove unmove;
        pos.make_move(move, unmove);
    }

    void make_move(std::string from, std::string to) {
        Move move;
        move.from_square = Square(from);
        move.to_square = Square(to);
        Unmove unmove;
        pos.make_move(move, unmove);
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

    void show_board() {
        testing::internal::CaptureStdout();
        pos.show();
        std::string output = testing::internal::GetCapturedStdout();
        std::cout << output << std::endl;
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

TEST_F(SearchEngineTest, BasicCapture) {
    set_up_starting_position();
    make_move("e2", "e4"); // white pawn to e4
    make_move("e7", "e5"); // black pawn to e5
    make_move("d1", "h5"); // white queen to h5
    make_move("g8", "f6"); // black knight to c6
    make_move("a2", "a3"); // white blunders! white pawn to a3, hanging the queen!

    show_board();

    EXPECT_EQ(pos.get_side_to_move(), Colors::BLACK);
    Move best_move = search_engine.search(6, Colors::BLACK);
    EXPECT_EQ(best_move.from_square.to_string(), "f6");
    EXPECT_EQ(best_move.to_square.to_string(), "h5");
}
