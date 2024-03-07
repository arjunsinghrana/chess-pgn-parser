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

    bool validPosition(int row, int col) const;

    int rankToRow(char rank) const;
    char rowToRank(int row) const;

    int fileToCol(char file) const;

    void applyMove(Color color, ChessMove chessMove);

    void applyMoveWithSourceFileAndRank(ChessMove chessMove);

    void applyMoveForPawn(Color color, ChessMove chessMove);

    vector<pair<int, int>> getDirectionsForPiece(Piece piece) const;
    void applyMoveWithSingleStep(Color color, ChessMove chessMove);
    void applyMoveWithMultipleSteps(Color color, ChessMove chessMove);

    void applyMoveForKingSideCastling(Color color);
    void applyMoveForQueenSideCastling(Color color);

public:
    ChessBoard();

    void reset();
    void print() const;

    void setChessPiece(int row, int col, ChessPiece piece);

    void applyTurn(ChessTurn turn);
};

#endif // CHESSBOARD_H