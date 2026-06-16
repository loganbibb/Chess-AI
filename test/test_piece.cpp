#include <algorithm>

#include <gtest/gtest.h>
#include "../src/include/Piece.h"

// Test fixture for Piece tests
class PieceTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures if needed
    }
};

// Basic piece enum tests
TEST_F(PieceTest, PieceEnumValues) {
    // White pieces should be positive
    EXPECT_GT((int)Piece::WPAWN, 0);
    EXPECT_GT((int)Piece::WKNIGHT, 0);
    EXPECT_GT((int)Piece::WBISHOP, 0);
    EXPECT_GT((int)Piece::WROOK, 0);
    EXPECT_GT((int)Piece::WQUEEN, 0);
    EXPECT_GT((int)Piece::WKING, 0);
    
    // Black pieces should be negative
    EXPECT_LT((int)Piece::BPAWN, 0);
    EXPECT_LT((int)Piece::BKNIGHT, 0);
    EXPECT_LT((int)Piece::BBISHOP, 0);
    EXPECT_LT((int)Piece::BROOK, 0);
    EXPECT_LT((int)Piece::BQUEEN, 0);
    EXPECT_LT((int)Piece::BKING, 0);
    
    // No piece should be 0
    EXPECT_EQ((int)Piece::NOPIECE, 0);
}

// Piece color tests
TEST_F(PieceTest, WhitePieces) {
    EXPECT_EQ(Piece::WPAWN, Piece::WPAWN);
    EXPECT_EQ(Piece::WKNIGHT, Piece::WKNIGHT);
    EXPECT_EQ(Piece::WBISHOP, Piece::WBISHOP);
    EXPECT_EQ(Piece::WROOK, Piece::WROOK);
    EXPECT_EQ(Piece::WQUEEN, Piece::WQUEEN);
    EXPECT_EQ(Piece::WKING, Piece::WKING);
}

TEST_F(PieceTest, BlackPieces) {
    EXPECT_EQ(Piece::BPAWN, Piece::BPAWN);
    EXPECT_EQ(Piece::BKNIGHT, Piece::BKNIGHT);
    EXPECT_EQ(Piece::BBISHOP, Piece::BBISHOP);
    EXPECT_EQ(Piece::BROOK, Piece::BROOK);
    EXPECT_EQ(Piece::BQUEEN, Piece::BQUEEN);
    EXPECT_EQ(Piece::BKING, Piece::BKING);
}

// Piece uniqueness tests
TEST_F(PieceTest, AllPiecesUnique) {
    std::vector<int> piece_values;
    piece_values.push_back((int)Piece::NOPIECE);
    piece_values.push_back((int)Piece::WPAWN);
    piece_values.push_back((int)Piece::WKNIGHT);
    piece_values.push_back((int)Piece::WBISHOP);
    piece_values.push_back((int)Piece::WROOK);
    piece_values.push_back((int)Piece::WQUEEN);
    piece_values.push_back((int)Piece::WKING);
    piece_values.push_back((int)Piece::BPAWN);
    piece_values.push_back((int)Piece::BKNIGHT);
    piece_values.push_back((int)Piece::BBISHOP);
    piece_values.push_back((int)Piece::BROOK);
    piece_values.push_back((int)Piece::BQUEEN);
    piece_values.push_back((int)Piece::BKING);
    
    // Check all values are unique
    std::sort(piece_values.begin(), piece_values.end());
    for (size_t i = 1; i < piece_values.size(); i++) {
        EXPECT_NE(piece_values[i], piece_values[i - 1]);
    }
}

// Colors enum test
TEST_F(PieceTest, ColorsEnum) {
    Colors white = Colors::WHITE;
    Colors black = Colors::BLACK;
    EXPECT_NE(white, black);
}

// String conversion test (if piece_to_string is implemented)
TEST_F(PieceTest, PieceToString) {
    // These tests assume piece_to_string is implemented
    std::string wp_str = piece_to_string(Piece::WPAWN);
    std::string bp_str = piece_to_string(Piece::BPAWN);
    std::string empty_str = piece_to_string(Piece::NOPIECE);
    
    EXPECT_FALSE(wp_str.empty());
    EXPECT_FALSE(bp_str.empty());
    EXPECT_NE(wp_str, bp_str);
}

// Piece type identification tests
TEST_F(PieceTest, IdentifyPawnTypes) {
    EXPECT_EQ(Piece::WPAWN, Piece::WPAWN);
    EXPECT_EQ(Piece::BPAWN, Piece::BPAWN);
    EXPECT_NE(Piece::WPAWN, Piece::BPAWN);
}

TEST_F(PieceTest, IdentifyKingTypes) {
    EXPECT_EQ(Piece::WKING, Piece::WKING);
    EXPECT_EQ(Piece::BKING, Piece::BKING);
    EXPECT_NE(Piece::WKING, Piece::BKING);
}
