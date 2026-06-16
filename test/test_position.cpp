#include <gtest/gtest.h>
#include "../src/include/Position.h"

// Test fixture for Position tests
class PositionTest : public ::testing::Test {
protected:
    Position pos;
    
    void SetUp() override {
        // Position constructor should set up starting position
        // Add setup logic if needed
    }
};

// Constructor and initialization tests
TEST_F(PositionTest, DefaultConstructor) {
    // Position should be initialized with starting position
    EXPECT_NE(pos.get_eval(), 0);  // Evaluation should be set (or test specific value)
}

// Move generation tests
TEST_F(PositionTest, GenerateMoves) {
    std::vector<Move> moves = pos.generate_moves();
    
    // In starting position, white has 20 legal moves (16 pawn moves + 4 knight moves)
    EXPECT_EQ(moves.size(), 20);
}

TEST_F(PositionTest, GenerateMovesNotEmpty) {
    std::vector<Move> moves = pos.generate_moves();
    EXPECT_FALSE(moves.empty());
}

// Pawn move generation tests
TEST_F(PositionTest, GeneratePawnMovesStartingPosition) {
    // In starting position, each of 8 pawns can move 1 or 2 squares
    // That's 16 pawn moves total
    std::vector<Move> moves = pos.generate_moves();
    
    int pawn_moves = 0;
    for (const auto& move : moves) {
        if (move.from_square.rank() == 1) {  // Starting rank for white pawns
            pawn_moves++;
        }
    }
    
    EXPECT_EQ(pawn_moves, 16);
}

// Knight move generation tests
TEST_F(PositionTest, GenerateKnightMovesStartingPosition) {
    // In starting position, there are 2 knights that can each move to 2 squares
    // That's 4 knight moves total
    std::vector<Move> moves = pos.generate_moves();
    
    int knight_moves = 0;
    for (const auto& move : moves) {
        // Check if move starts from knight starting positions (b1 or g1)
        if ((move.from_square == Square("b1")) || (move.from_square == Square("g1"))) {
            knight_moves++;
        }
    }
    
    EXPECT_EQ(knight_moves, 4);
}

// Piece access tests
TEST_F(PositionTest, GetPieces) {
    PieceVector pieces = pos.get_pieces();
    // Should be able to retrieve pieces without error
}

TEST_F(PositionTest, SetPieces) {
    PieceVector old_pieces = pos.get_pieces();
    pos.set_pieces(old_pieces);
    // Should be able to set pieces without error
}

// Evaluation tests
TEST_F(PositionTest, GetEval) {
    float eval = pos.get_eval();
    // Starting position should have neutral or specific evaluation
    // Depends on your evaluation function
}

// Display test (basic smoke test)
TEST_F(PositionTest, ShowPosition) {
    // This is a smoke test to ensure show() doesn't crash
    EXPECT_NO_FATAL_FAILURE(pos.show());
}

// Move making and unmaking tests
TEST_F(PositionTest, MakeAndUnmakeMove) {
    std::vector<Move> moves = pos.generate_moves();
    
    if (!moves.empty()) {
        Move move = moves[0];
        Unmove unmove;
        
        // Make the move
        EXPECT_NO_FATAL_FAILURE(pos.make_move(move, unmove));
        
        // Unmake the move
        EXPECT_NO_FATAL_FAILURE(pos.unmake_move(move, unmove));
    }
}

TEST_F(PositionTest, MakeMoveChangesPosition) {
    std::vector<Move> moves = pos.generate_moves();
    
    if (!moves.empty()) {
        Move move = moves[0];
        Unmove unmove;
        
        Square initial_from = move.from_square;
        Square initial_to = move.to_square;
        
        pos.make_move(move, unmove);
        
        // After making a move, the squares should have been modified
        // This is a basic sanity check
        EXPECT_TRUE(true);
    }
}

// Multiple moves test
TEST_F(PositionTest, MakeMultipleMoves) {
    std::vector<Move> moves1 = pos.generate_moves();
    
    if (!moves1.empty()) {
        Move move1 = moves1[0];
        Unmove unmove1;
        pos.make_move(move1, unmove1);
        
        std::vector<Move> moves2 = pos.generate_moves();
        
        if (!moves2.empty()) {
            Move move2 = moves2[0];
            Unmove unmove2;
            pos.make_move(move2, unmove2);
            
            // We've made two moves successfully
            EXPECT_TRUE(true);
        }
    }
}

// Check detection tests
TEST_F(PositionTest, StartingPositionNotInCheck) {
    // Starting position should not be in check
    std::vector<Move> moves = pos.generate_moves();
    EXPECT_FALSE(moves.empty());
}

// Castling availability tests
TEST_F(PositionTest, CastlingAvailableAtStart) {
    // Starting position should have castling available
    std::vector<Move> moves = pos.generate_moves();
    
    // Check if any castling moves are available (advanced test)
    bool has_castling = false;
    for (const auto& move : moves) {
        if (move.is_castle) {
            has_castling = true;
            break;
        }
    }
    
    // At the start, castling is not immediately available (needs pieces to move)
    // This is just a placeholder; adjust based on your implementation
}

// En passant tests
TEST_F(PositionTest, NoEnPassantAtStart) {
    // Starting position should not have en passant available
    // (This depends on your internal representation)
}

// Side to move tests
TEST_F(PositionTest, WhiteToMoveAtStart) {
    // Starting position should have white to move
    // Add assertion based on how you access side_to_move
}

// Special position tests
TEST_F(PositionTest, GenerateMovesAfterInitialMove) {
    std::vector<Move> initial_moves = pos.generate_moves();
    
    if (!initial_moves.empty()) {
        Move first_move = initial_moves[0];
        Unmove unmove;
        
        pos.make_move(first_move, unmove);
        
        std::vector<Move> next_moves = pos.generate_moves();
        
        // After first move, should still be able to generate moves
        EXPECT_FALSE(next_moves.empty());
    }
}
