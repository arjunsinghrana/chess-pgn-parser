cmake_minimum_required(VERSION 3.15)

project(CHESS-PGN-PARSER)

# The compiled library code is here
add_subdirectory(src)

set(SOURCES parser.cpp src/chessBoard.cpp src/chessMove.cpp src/chessPiece.cpp src/utils.cpp)
add_executable(parser.out parser.cpp ${SOURCES})
