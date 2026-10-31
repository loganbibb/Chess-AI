# Chess Engine Source Files

# Create a library with the chess engine implementation
add_library(chess_engine
    Square.cpp
    Piece.cpp
    Position.cpp
    PieceVector.cpp
)

# Set public include directories for the library
target_include_directories(chess_engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Create the main executable
add_executable(main
    main.cpp
)

# Link the main executable against the chess engine library
target_link_libraries(main
    PRIVATE
    chess_engine
)

# Set the output directory for the executable
set_target_properties(main
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
