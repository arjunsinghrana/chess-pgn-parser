#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <vector>

#include "chessPiece.h"
#include "chessTurn.h"

using namespace std;

class ChessBoard
{
private:
    const int BOARD_SIZE = 8;
    vector<vector<ChessPiece>> board;

    void applyWhiteMove(ChessMove whiteMove);
    void applyBlackMove(ChessMove blackMove);

    int rankToRow(char rank);
    int fileToCol(char file);

    void applyMoveWithSourceFileAndRank(ChessMove chessMove);

    void applyMoveForWhitePawn(ChessMove chessMove);
    void applyMoveForBlackPawn(ChessMove chessMove);

public:
    ChessBoard();

    void reset();
    void print() const;

    void setChessPiece(int row, int col, ChessPiece piece);

    void applyTurn(ChessTurn turn);
};

#endif // CHESSBOARD_H