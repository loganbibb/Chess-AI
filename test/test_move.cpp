#include <gtest/gtest.h>
#include "../src/include/Move.h"

// Test fixture for Move tests
class MoveTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures if needed
    }
};

// Constructor and initialization tests
TEST_F(MoveTest, DefaultConstructor) {
    Move m;
    EXPECT_EQ((uint8_t)m.from_square, 0);
    EXPECT_EQ((uint8_t)m.to_square, 0);
    EXPECT_FALSE(m.is_check);
    EXPECT_FALSE(m.is_castle);
    EXPECT_FALSE(m.is_promotion);
    EXPECT_FALSE(m.is_en_passant);
    EXPECT_EQ(m.promotion_piece, Piece::NOPIECE);
}

// Basic move tests
TEST_F(MoveTest, SimpleMove) {
    Move m;
    m.from_square = Square(0);  // a1
    m.to_square = Square(1);    // a2
    
    EXPECT_EQ((uint8_t)m.from_square, 0);
    EXPECT_EQ((uint8_t)m.to_square, 1);
    EXPECT_FALSE(m.is_check);
    EXPECT_FALSE(m.is_castle);
}

TEST_F(MoveTest, PawnMove) {
    Move m;
    m.from_square = Square(4, 1);  // e2
    m.to_square = Square(4, 3);    // e4 (pawn opening move)
    
    EXPECT_EQ(m.from_square.file(), 4);
    EXPECT_EQ(m.from_square.rank(), 1);
    EXPECT_EQ(m.to_square.file(), 4);
    EXPECT_EQ(m.to_square.rank(), 3);
}

// Check move tests
TEST_F(MoveTest, CheckMove) {
    Move m;
    m.from_square = Square("e4");
    m.to_square = Square("e8");
    m.is_check = true;
    
    EXPECT_TRUE(m.is_check);
}

// Capture move tests
TEST_F(MoveTest, CaptureMove) {
    Move m;
    m.from_square = Square("e4");
    m.to_square = Square("d5");
    // Captures don't have a dedicated flag in Move struct
    
    EXPECT_EQ((uint8_t)m.from_square, (uint8_t)Square("e4"));
    EXPECT_EQ((uint8_t)m.to_square, (uint8_t)Square("d5"));
}

// Castling move tests
TEST_F(MoveTest, CastlingMove) {
    Move m;
    m.from_square = Square("e1");
    m.to_square = Square("g1");  // King-side castle
    m.is_castle = true;
    
    EXPECT_TRUE(m.is_castle);
    EXPECT_EQ((uint8_t)m.from_square, (uint8_t)Square("e1"));
    EXPECT_EQ((uint8_t)m.to_square, (uint8_t)Square("g1"));
}

TEST_F(MoveTest, CastlingQueenSide) {
    Move m;
    m.from_square = Square("e1");
    m.to_square = Square("c1");  // Queen-side castle
    m.is_castle = true;
    
    EXPECT_TRUE(m.is_castle);
    EXPECT_EQ((uint8_t)m.from_square, (uint8_t)Square("e1"));
    EXPECT_EQ((uint8_t)m.to_square, (uint8_t)Square("c1"));
}

// Promotion move tests
TEST_F(MoveTest, PawnPromotion) {
    Move m;
    m.from_square = Square("a7");
    m.to_square = Square("a8");
    m.is_promotion = true;
    m.promotion_piece = Piece::WQUEEN;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_EQ(m.promotion_piece, Piece::WQUEEN);
}

TEST_F(MoveTest, PromotionToKnight) {
    Move m;
    m.from_square = Square("h7");
    m.to_square = Square("h8");
    m.is_promotion = true;
    m.promotion_piece = Piece::WKNIGHT;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_EQ(m.promotion_piece, Piece::WKNIGHT);
}

TEST_F(MoveTest, PromotionToRook) {
    Move m;
    m.from_square = Square("e7");
    m.to_square = Square("e8");
    m.is_promotion = true;
    m.promotion_piece = Piece::WROOK;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_EQ(m.promotion_piece, Piece::WROOK);
}

TEST_F(MoveTest, PromotionToBishop) {
    Move m;
    m.from_square = Square("f7");
    m.to_square = Square("f8");
    m.is_promotion = true;
    m.promotion_piece = Piece::WBISHOP;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_EQ(m.promotion_piece, Piece::WBISHOP);
}

// En passant move tests
TEST_F(MoveTest, EnPassantMove) {
    Move m;
    m.from_square = Square("e4");
    m.to_square = Square("d5");
    m.is_en_passant = true;
    
    EXPECT_TRUE(m.is_en_passant);
}

// Complex move tests (combined flags)
TEST_F(MoveTest, CheckAndCapture) {
    Move m;
    m.from_square = Square("e4");
    m.to_square = Square("f6");
    m.is_check = true;
    
    EXPECT_TRUE(m.is_check);
}

TEST_F(MoveTest, PromotionWithCheck) {
    Move m;
    m.from_square = Square("a7");
    m.to_square = Square("a8");
    m.is_promotion = true;
    m.is_check = true;
    m.promotion_piece = Piece::WQUEEN;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_TRUE(m.is_check);
    EXPECT_EQ(m.promotion_piece, Piece::WQUEEN);
}

// Move equality/comparison tests
TEST_F(MoveTest, CompareMoves) {
    Move m1;
    m1.from_square = Square("e2");
    m1.to_square = Square("e4");
    
    Move m2;
    m2.from_square = Square("e2");
    m2.to_square = Square("e4");
    
    EXPECT_EQ((uint8_t)m1.from_square, (uint8_t)m2.from_square);
    EXPECT_EQ((uint8_t)m1.to_square, (uint8_t)m2.to_square);
}

// Black piece moves
TEST_F(MoveTest, BlackPawnMove) {
    Move m;
    m.from_square = Square("e7");
    m.to_square = Square("e5");
    
    EXPECT_EQ((uint8_t)m.from_square, (uint8_t)Square("e7"));
    EXPECT_EQ((uint8_t)m.to_square, (uint8_t)Square("e5"));
}

TEST_F(MoveTest, BlackPromotion) {
    Move m;
    m.from_square = Square("a2");
    m.to_square = Square("a1");
    m.is_promotion = true;
    m.promotion_piece = Piece::BQUEEN;
    
    EXPECT_TRUE(m.is_promotion);
    EXPECT_EQ(m.promotion_piece, Piece::BQUEEN);
}
