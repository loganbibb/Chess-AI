# GoogleTest configuration for chess engine tests

# Add all test source files
add_executable(
    chess_tests
    test_square.cpp
    test_piece.cpp
    test_move.cpp
    test_position.cpp
)

# Link against GoogleTest and chess engine library
target_link_libraries(
    chess_tests
    PRIVATE
    GTest::gtest_main
    chess_engine
)

# Enable testing
gtest_discover_tests(chess_tests)
