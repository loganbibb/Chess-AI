#include <gtest/gtest.h>
#include "../src/include/Square.h"

// Test fixture for Square tests
class SquareTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up test fixtures if needed
    }
};

// Constructor tests
TEST_F(SquareTest, DefaultConstructor) {
    Square sq;
    // Default should be invalid (INT8_MAX)
    EXPECT_EQ((int8_t)sq, INT8_MAX);
}

TEST_F(SquareTest, ConstructorWithIndex) {
    Square sq(0);
    EXPECT_EQ((int8_t)sq, 0);  // a1
    
    Square sq2{63};
    EXPECT_EQ((int8_t)sq2, 63); // h8
}

TEST_F(SquareTest, ConstructorWithFileAndRank) {
    Square sq(0, 0);  // a1
    EXPECT_EQ(sq.file(), 0);
    EXPECT_EQ(sq.rank(), 0);
    
    Square sq2(7, 7);  // h8
    EXPECT_EQ(sq2.file(), 7);
    EXPECT_EQ(sq2.rank(), 7);
}

TEST_F(SquareTest, ConstructorWithString) {
    Square sq("a1");
    EXPECT_EQ((int8_t)sq, 0);
    
    Square sq2("h8");
    EXPECT_EQ((int8_t)sq2, 63);
    
    Square sq3("e4");
    EXPECT_EQ(sq3.file(), 4);
    EXPECT_EQ(sq3.rank(), 3);
}

// File and rank tests
TEST_F(SquareTest, FileAndRankConversion) {
    for (int8_t file = 0; file < 8; file++) {
        for (int8_t rank = 0; rank < 8; rank++) {
            Square sq(file, rank);
            EXPECT_EQ(sq.file(), file);
            EXPECT_EQ(sq.rank(), rank);
            EXPECT_EQ((int8_t)sq, file + rank * 8);
        }
    }
}

// Operator tests
TEST_F(SquareTest, EqualityOperator) {
    Square sq1(0);
    Square sq2(0);
    Square sq3(1);
    
    EXPECT_EQ(sq1, sq2);
    EXPECT_NE(sq1, sq3);
}

TEST_F(SquareTest, StringComparisonOperators) {
    Square sq("e4");
    EXPECT_TRUE(sq == "e4");
    EXPECT_FALSE(sq == "e5");
    EXPECT_TRUE(sq == std::string("e4"));
}

TEST_F(SquareTest, AssignmentOperator) {
    Square sq1(10);
    Square sq2;
    sq2 = sq1;
    EXPECT_EQ((int8_t)sq2, 10);
    
    Square sq3;
    sq3 = 25u;
    EXPECT_EQ((int8_t)sq3, 25);
}

// Increment/decrement tests
TEST_F(SquareTest, IncrementFile) {
    Square sq(0, 0);  // a1
    sq.inc_file();
    EXPECT_EQ(sq.file(), 1);
    EXPECT_EQ(sq.rank(), 0);
}

TEST_F(SquareTest, DecrementFile) {
    Square sq(5, 0);
    sq.dec_file();
    EXPECT_EQ(sq.file(), 4);
    EXPECT_EQ(sq.rank(), 0);
}

TEST_F(SquareTest, IncrementRank) {
    Square sq(0, 0);  // a1
    sq.inc_rank();
    EXPECT_EQ(sq.file(), 0);
    EXPECT_EQ(sq.rank(), 1);
}

TEST_F(SquareTest, DecrementRank) {
    Square sq(0, 5);
    sq.dec_rank();
    EXPECT_EQ(sq.file(), 0);
    EXPECT_EQ(sq.rank(), 4);
}

// Set square tests
TEST_F(SquareTest, SetSquareWithIndex) {
    Square sq;
    sq.set_square(42);
    EXPECT_EQ((int8_t)sq, 42);
}

TEST_F(SquareTest, SetSquareWithFileAndRank) {
    Square sq;
    sq.set_square(3, 5);
    EXPECT_EQ(sq.file(), 3);
    EXPECT_EQ(sq.rank(), 5);
}

// String conversion test
TEST_F(SquareTest, ToStringConversion) {
    Square sq(0);
    EXPECT_EQ(sq.to_string(), "a1");
    
    Square sq2(63);
    EXPECT_EQ(sq2.to_string(), "h8");
    
    Square sq3(4, 3);  // e4
    EXPECT_EQ(sq3.to_string(), "e4");
}

// Edge cases
TEST_F(SquareTest, AllBoardSquares) {
    for (int8_t i = 0; i < 64; i++) {
        Square sq(i);
        EXPECT_EQ((int8_t)sq, i);
    }
}
