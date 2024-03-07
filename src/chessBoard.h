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

    bool validPosition(int row, int col);

    void applyMove(Color color, ChessMove chessMove);

    int rankToRow(char rank);
    char rowToRank(int row);

    int fileToCol(char file);

    void applyMoveWithSourceFileAndRank(ChessMove chessMove);

    void applyMoveForWhitePawn(ChessMove chessMove);
    void applyMoveForBlackPawn(ChessMove chessMove);


    vector<pair<int, int>> getDirectionsForPiece(Piece piece);
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