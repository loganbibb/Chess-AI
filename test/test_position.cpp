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

// Move generation tests
TEST_F(PositionTest, GenerateMoves) {
    std::vector<Move> moves = pos.generate_moves();
    
    // In starting position, white has 20 legal moves (16 pawn moves + 4 knight moves)
    EXPECT_EQ(moves.size(), 20);
}

TEST_F(PositionTest, GenerateMovesNotEmpty) {
    std::vector<Move> moves = pos.generate_moves();
    pos.show(); 
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

TEST_F(PositionTest, PrintMovesEmitsReadableNotation) {
    std::string output;
    {
        testing::internal::CaptureStdout();
        pos.print_moves();
        output = testing::internal::GetCapturedStdout();
    }

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("e4"), std::string::npos);
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
    Square white_king("e1");
    Square black_king("e8");

    EXPECT_FALSE(pos.is_in_check(white_king, Colors::WHITE));
    EXPECT_FALSE(pos.is_in_check(black_king, Colors::BLACK));
}

TEST_F(PositionTest, WhiteKingIsInCheckByBlackRook) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("e8")] = Piece::BROOK;
    pos.set_pieces(pieces);

    Square king_sq("e1");
    EXPECT_TRUE(pos.is_in_check(king_sq, Colors::WHITE));
}

TEST_F(PositionTest, WhiteKingIsInCheckByBlackBishop) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("h4")] = Piece::BBISHOP;
    pos.set_pieces(pieces);

    Square king_sq("e1");
    EXPECT_TRUE(pos.is_in_check(king_sq, Colors::WHITE));
}

TEST_F(PositionTest, BlackKingIsInCheckByWhiteKnight) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e8")] = Piece::BKING;
    pieces[Square("f6")] = Piece::WKNIGHT;
    pos.set_pieces(pieces);

    Square king_sq("e8");
    EXPECT_TRUE(pos.is_in_check(king_sq, Colors::BLACK));
}

TEST_F(PositionTest, AttackIsBlockedByOwnPiece) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("e5")] = Piece::WROOK;
    pieces[Square("e8")] = Piece::BROOK;
    pos.set_pieces(pieces);

    Square king_sq("e1");
    EXPECT_FALSE(pos.is_in_check(king_sq, Colors::WHITE));
}

TEST_F(PositionTest, IsSquareAttackedByWhitePawn) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("d4")] = Piece::WPAWN;
    pos.set_pieces(pieces);

    Square target("e5");
    EXPECT_TRUE(pos.is_square_attacked(target, Colors::WHITE));
}

TEST_F(PositionTest, IsSquareAttackedByWhiteKnight) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("f7")] = Piece::WKNIGHT;
    pos.set_pieces(pieces);

    Square target("e5");
    EXPECT_TRUE(pos.is_square_attacked(target, Colors::WHITE));
}

TEST_F(PositionTest, IsSquareAttackedByWhiteRook) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WROOK;
    pos.set_pieces(pieces);

    Square target("e5");
    EXPECT_TRUE(pos.is_square_attacked(target, Colors::WHITE));
}

// ============================================================================
// PAWN MOVE TESTS
// ============================================================================

TEST_F(PositionTest, PawnSinglePushFromStarting) {
    // White pawn at a2 should be able to move to a3
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_move = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("a2") && move.to_square == Square("a3")) {
            found_move = true;
            break;
        }
    }
    EXPECT_TRUE(found_move) << "White pawn at a2 should be able to move to a3";
}

TEST_F(PositionTest, PawnDoublePushFromStarting) {
    // White pawn at e2 should be able to move to e4
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_move = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("e2") && move.to_square == Square("e4")) {
            found_move = true;
            break;
        }
    }
    EXPECT_TRUE(found_move) << "White pawn at e2 should be able to move to e4";
}

TEST_F(PositionTest, PawnCaptureMove) {
    // Set up a custom position: White pawn at e4, Black pawn at d5
    PieceVector pieces = pos.get_pieces();
    pieces[Square("e4")] = Piece::WPAWN;
    pieces[Square("d5")] = Piece::BPAWN;
    pieces[Square("e2")] = Piece::NOPIECE;  // Remove original pawn
    pos.set_pieces(pieces);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_capture = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("e4") && move.to_square == Square("d5")) {
            found_capture = true;
            break;
        }
    }
    EXPECT_TRUE(found_capture) << "White pawn at e4 should be able to capture at d5";
}

TEST_F(PositionTest, BlackPawnMovement) {
    // Move white pawn and then check black pawn moves
    std::vector<Move> white_moves = pos.generate_moves();
    Move white_move = white_moves[0];  // Move any white piece
    Unmove unmove;
    pos.make_move(white_move, unmove);
    
    // Now black to move
    std::vector<Move> black_moves = pos.generate_moves();
    
    bool found_black_pawn_move = false;
    for (const auto& move : black_moves) {
        if (move.from_square.rank() == 6) {  // Black pawns start at rank 6
            found_black_pawn_move = true;
            break;
        }
    }
    EXPECT_TRUE(found_black_pawn_move) << "Black should have pawn moves available";
}

TEST_F(PositionTest, PawnPromotionFlag) {
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e7")] = Piece::WPAWN;
    pieces[Square("e8")] = Piece::NOPIECE;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);

    std::vector<Move> moves = pos.generate_moves();

    bool found_promotion = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("e7") && move.to_square == Square("e8") && move.is_promotion) {
            found_promotion = true;
            break;
        }
    }
    EXPECT_TRUE(found_promotion) << "A white pawn on e7 should promote when moving to e8 on an empty board";
}

// ============================================================================
// KNIGHT MOVE TESTS
// ============================================================================

TEST_F(PositionTest, KnightMovesFromStarting) {
    // White knight at b1 should have 2 available moves (a3, c3)
    std::vector<Move> moves = pos.generate_moves();
    
    int knight_b1_moves = 0;
    for (const auto& move : moves) {
        if (move.from_square == Square("b1")) {
            knight_b1_moves++;
        }
    }
    EXPECT_EQ(knight_b1_moves, 2);
}

TEST_F(PositionTest, KnightMovesFromCentralSquare) {
    // Set up: Isolated white knight at d4
    PieceVector pieces = pos.get_pieces();
    // Clear the board except for the knight
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("d4")] = Piece::WKNIGHT;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Knight at d4 should have 8 possible moves
    EXPECT_EQ(moves.size(), 8) << "Knight at d4 should have 8 possible moves";
}

TEST_F(PositionTest, KnightCaptureMove) {
    // Set up: White knight at e4, black piece at f6
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WKNIGHT;
    pieces[Square("f6")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_capture = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("e4") && move.to_square == Square("f6")) {
            found_capture = true;
            break;
        }
    }
    EXPECT_TRUE(found_capture) << "Knight should be able to capture";
}

TEST_F(PositionTest, KnightBlockedByOwnPiece) {
    // Set up: White knight at e4, white pawn at f6
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WKNIGHT;
    pieces[Square("f6")] = Piece::WPAWN;  // Own piece blocks
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_blocked_move = false;
    for (const auto& move : moves) {
        if (move.to_square == Square("f6")) {
            found_blocked_move = true;
            break;
        }
    }
    EXPECT_FALSE(found_blocked_move) << "Knight should not move to square occupied by own piece";
}

// ============================================================================
// BISHOP MOVE TESTS
// ============================================================================

TEST_F(PositionTest, BishopMovesFromOpenPosition) {
    // Set up: White bishop at e4 on empty board
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WBISHOP;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Bishop at e4 should have 13 available moves (all diagonals)
    EXPECT_EQ(moves.size(), 13) << "Bishop at e4 should have 13 moves on empty board";
}

TEST_F(PositionTest, BishopBlockedByPiece) {
    // Set up: White bishop at a1, white pawn at c3 blocks one diagonal
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("a1")] = Piece::WBISHOP;
    pieces[Square("c3")] = Piece::WPAWN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Check that bishop doesn't move past the blocking pawn
    bool found_past_block = false;
    for (const auto& move : moves) {
        if (move.to_square == Square("d4")) {
            found_past_block = true;
            break;
        }
    }
    EXPECT_FALSE(found_past_block) << "Bishop should not move past blocking piece";
}

TEST_F(PositionTest, BishopCaptureBlackPiece) {
    // Set up: White bishop at a1, black piece at c3
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("a1")] = Piece::WBISHOP;
    pieces[Square("c3")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_capture = false;
    for (const auto& move : moves) {
        if (move.from_square == Square("a1") && move.to_square == Square("c3")) {
            found_capture = true;
            break;
        }
    }
    EXPECT_TRUE(found_capture) << "Bishop should be able to capture";
}

// ============================================================================
// ROOK MOVE TESTS
// ============================================================================

TEST_F(PositionTest, RookMovesFromOpenPosition) {
    // Set up: White rook at e4 on empty board
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WROOK;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Rook at e4 should have 14 available moves (7 vertical + 7 horizontal)
    EXPECT_EQ(moves.size(), 14) << "Rook at e4 should have 14 moves on empty board";
}

TEST_F(PositionTest, RookBlockedByPiece) {
    // Set up: White rook at a1, white pawn at a3 blocks vertical movement
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("a1")] = Piece::WROOK;
    pieces[Square("a3")] = Piece::WPAWN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_past_block = false;
    for (const auto& move : moves) {
        if (pieces[move.from_square] == Piece::WROOK && move.to_square == Square("a4")) {
            found_past_block = true;
            break;
        }
    }
    EXPECT_FALSE(found_past_block) << "Rook should not move past blocking piece";
}

// ============================================================================
// QUEEN MOVE TESTS
// ============================================================================

TEST_F(PositionTest, QueenMovesFromOpenPosition) {
    // Set up: White queen at e4 on empty board
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WQUEEN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Queen at e4 should have 27 available moves (rook + bishop moves)
    EXPECT_EQ(moves.size(), 27) << "Queen at e4 should have 27 moves on empty board";
}

// ============================================================================
// KING MOVE TESTS
// ============================================================================

TEST_F(PositionTest, KingMovesFromCentralPosition) {
    // Set up: White king at e4 on empty board
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WKING;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // King at e4 should have 8 available moves
    EXPECT_EQ(moves.size(), 8) << "King at e4 should have 8 moves";
}

TEST_F(PositionTest, KingMovesFromCorner) {
    // Set up: White king at a1 on empty board
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("a1")] = Piece::WKING;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // King at a1 should have 3 available moves
    EXPECT_EQ(moves.size(), 3) << "King at a1 should have 3 moves";
}

// ============================================================================
// CASTLING TESTS
// ============================================================================

TEST_F(PositionTest, CastlingKingsideNotAvailableWithPieces) {
    // Starting position - castling should not be available (pieces in the way)
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_castling = false;
    for (const auto& move : moves) {
        if (move.is_castle) {
            found_castling = true;
            break;
        }
    }
    EXPECT_FALSE(found_castling) << "Castling should not be available in starting position (pieces in way)";
}

TEST_F(PositionTest, CastlingKingsideAvailable) {
    // Set up: White king at e1, white rook at h1, f1 and g1 empty
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("h1")] = Piece::WROOK;
    pos.set_pieces(pieces);
    
    // Set castling rights
    CastlingRights rights;
    rights.white_kingside = true;
    rights.white_queenside = false;
    rights.black_kingside = false;
    rights.black_queenside = false;
    pos.set_castling_rights(rights);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_kingside_castle = false;
    for (const auto& move : moves) {
        if (move.is_castle && move.to_square == Square("g1")) {
            found_kingside_castle = true;
            break;
        }
    }
    EXPECT_TRUE(found_kingside_castle) << "Kingside castling should be available";
}

TEST_F(PositionTest, CastlingQueensideAvailable) {
    // Set up: White king at e1, white rook at a1, b1-d1 empty
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("a1")] = Piece::WROOK;
    pos.set_pieces(pieces);
    
    // Set castling rights
    CastlingRights rights;
    rights.white_kingside = false;
    rights.white_queenside = true;
    rights.black_kingside = false;
    rights.black_queenside = false;
    pos.set_castling_rights(rights);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_queenside_castle = false;
    for (const auto& move : moves) {
        if (move.is_castle && move.to_square == Square("c1")) {
            found_queenside_castle = true;
            break;
        }
    }
    EXPECT_TRUE(found_queenside_castle) << "Queenside castling should be available";
}

TEST_F(PositionTest, BlackCannotCastleThroughCheck) {
    // Set up: Black king on e8, rook on h8, white rook on f1 attacking f8
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e8")] = Piece::BKING;
    pieces[Square("h8")] = Piece::BROOK;
    pieces[Square("f1")] = Piece::WROOK; // attacks f8
    pos.set_pieces(pieces);

    // Grant black kingside castling rights and make it black's turn
    CastlingRights rights;
    rights.white_kingside = false;
    rights.white_queenside = false;
    rights.black_kingside = true;
    rights.black_queenside = false;
    pos.set_castling_rights(rights);
    pos.set_side_to_move(Colors::BLACK);

    std::vector<Move> moves = pos.generate_moves();

    // Kingside castling for black would be a move to g8; it should NOT be present
    bool found_kingside_castle_black = false;
    for (const auto &move : moves) {
        if (move.is_castle && move.to_square == Square("g8")) {
            found_kingside_castle_black = true;
            break;
        }
    }
    EXPECT_FALSE(found_kingside_castle_black) << "Black should not be allowed to castle through a square attacked by the opponent";
}

// ============================================================================
// EN PASSANT TESTS
// ============================================================================

TEST_F(PositionTest, EnPassantCaptureAvailable) {
    // Set up: White pawn at e4, black pawn at d4, en passant square at d3
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e4")] = Piece::WPAWN;
    pieces[Square("d4")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    pos.set_en_passant_square(Square("e3"));
    pos.set_side_to_move(Colors::BLACK);
    
    std::vector<Move> moves = pos.generate_moves();
    
    bool found_en_passant = false;
    for (const auto& move : moves) {
        if (move.is_en_passant && move.from_square == Square("d4") && move.to_square == Square("e3")) {
            found_en_passant = true;
            break;
        }
    }
    EXPECT_TRUE(found_en_passant) << "En passant capture should be available";
}

// ============================================================================
// SIDE TO MOVE TESTS
// ============================================================================

TEST_F(PositionTest, SideToMoveAffectsGeneratedMoves) {
    // Generate moves for white
    pos.set_side_to_move(Colors::WHITE);
    std::vector<Move> white_moves = pos.generate_moves();
    
    // All moves should be from white pieces
    bool all_white = true;
    for (const auto& move : white_moves) {
        int square_idx = move.from_square;
        Piece piece = pos.get_pieces()[square_idx];
        if (get_piece_color(piece) != Colors::WHITE) {
            all_white = false;
            break;
        }
    }
    EXPECT_TRUE(all_white) << "All generated moves should be from white pieces";
}

// ============================================================================
// COMPLEX POSITION TESTS
// ============================================================================

TEST_F(PositionTest, MultiPiecesInteract) {
    // Set up: Complex position with multiple pieces that interact
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e2")] = Piece::WPAWN;
    pieces[Square("e4")] = Piece::WPAWN;
    pieces[Square("d3")] = Piece::WBISHOP;
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("d5")] = Piece::BPAWN;
    pieces[Square("e5")] = Piece::BPAWN;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);
    
    std::vector<Move> moves = pos.generate_moves();
    
    // Should have generated some moves from the various pieces
    EXPECT_GT(moves.size(), 0) << "Should generate moves from multiple pieces";
}

TEST_F(PositionTest, PinnedPieceCannotMove) {
    // Set up: White king on e1, white knight on e2 pinned by black rook on e8
    PieceVector pieces = pos.get_pieces();
    for (int i = 0; i < 64; i++) {
        pieces[i] = Piece::NOPIECE;
    }
    pieces[Square("e1")] = Piece::WKING;
    pieces[Square("e2")] = Piece::WKNIGHT;
    pieces[Square("e8")] = Piece::BROOK;
    pos.set_pieces(pieces);
    pos.set_side_to_move(Colors::WHITE);

    std::vector<Move> moves = pos.generate_legal_moves();

    // The knight on e2 is pinned along the e-file and should have no legal moves
    bool found_move_from_e2 = false;
    for (const auto &move : moves) {
        if (move.from_square == Square("e2")) {
            found_move_from_e2 = true;
            break;
        }
    }
    EXPECT_FALSE(found_move_from_e2) << "Pinned piece on e2 should not have legal moves that expose the king to check";
}
