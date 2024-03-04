#include "chessBoard.h"

#include "utils.h"

#include <iostream>


using namespace std;


ChessBoard::ChessBoard()
{
    board.resize(BOARD_SIZE, vector<ChessPiece>(BOARD_SIZE, EMPTY));
    reset();
}

void ChessBoard::print()
{
    vector<vector<ChessPiece> > boardCopy = board;
    Utils::rotate180(boardCopy);

    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int j = 0; j < BOARD_SIZE; ++j) 
        {
            cout << Utils::pieceToString(boardCopy[i][j]) << "|";
        }
        cout << endl;
    }
}

void ChessBoard::setChessPiece(int row, int col, ChessPiece piece)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        board[row][col] = piece;
    }
}

void ChessBoard::reset()
{
    // Set pieces on the board
    setChessPiece(0, 0, WHITE_ROOK);
    setChessPiece(0, 1, WHITE_KNIGHT);
    setChessPiece(0, 2, WHITE_BISHOP);
    setChessPiece(0, 3, WHITE_QUEEN);
    setChessPiece(0, 4, WHITE_KING);
    setChessPiece(0, 5, WHITE_BISHOP);
    setChessPiece(0, 6, WHITE_KNIGHT);
    setChessPiece(0, 7, WHITE_ROOK);

    setChessPiece(1, 0, WHITE_PAWN);
    setChessPiece(1, 1, WHITE_PAWN);
    setChessPiece(1, 2, WHITE_PAWN);
    setChessPiece(1, 3, WHITE_PAWN);
    setChessPiece(1, 4, WHITE_PAWN);
    setChessPiece(1, 5, WHITE_PAWN);
    setChessPiece(1, 6, WHITE_PAWN);
    setChessPiece(1, 7, WHITE_PAWN);

    setChessPiece(7, 0, BLACK_ROOK);
    setChessPiece(7, 1, BLACK_KNIGHT);
    setChessPiece(7, 2, BLACK_BISHOP);
    setChessPiece(7, 3, BLACK_QUEEN);
    setChessPiece(7, 4, BLACK_KING);
    setChessPiece(7, 5, BLACK_BISHOP);
    setChessPiece(7, 6, BLACK_KNIGHT);
    setChessPiece(7, 7, BLACK_ROOK);

    setChessPiece(6, 0, BLACK_PAWN);
    setChessPiece(6, 1, BLACK_PAWN);
    setChessPiece(6, 2, BLACK_PAWN);
    setChessPiece(6, 3, BLACK_PAWN);
    setChessPiece(6, 4, BLACK_PAWN);
    setChessPiece(6, 5, BLACK_PAWN);
    setChessPiece(6, 6, BLACK_PAWN);
    setChessPiece(6, 7, BLACK_PAWN);
}