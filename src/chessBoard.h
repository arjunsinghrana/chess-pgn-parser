#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <string>
#include <vector>

#include "chessPiece.h"

using namespace std;

class ChessBoard
{
private:
    const int BOARD_SIZE = 8;
    vector<vector<ChessPiece> > board;

public:
    ChessBoard();

    void reset();
    void print() const;

    void setChessPiece(int row, int col, ChessPiece piece);
};

#endif // CHESSBOARD_H