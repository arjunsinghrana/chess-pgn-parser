cmake_minimum_required(VERSION 3.15)

project(CHESS-PGN-PARSER)

# The compiled library code is here
add_subdirectory(src)

set(SOURCES main.cpp src/chessBoard.cpp src/chessMove.cpp src/chessPiece.cpp src/chessTurn.cpp src/utils.cpp)
add_executable(main.out main.cpp ${SOURCES})
