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

    ChessPiece emptyPiece = {Color::EMPTY, Piece::EMPTY};

    bool validPosition(int row, int col) const;

    int rankToRow(char rank) const;
    char rowToRank(int row) const;

    int fileToCol(char file) const;

    void setChessPiece(int row, int col, const ChessPiece& piece);

    const ChessPiece& getChessPiece(int row, int col) const;

    void applyMove(const Color& color, const ChessMove& chessMove);

    void applyMoveByInferringRank(const Color& color, const ChessMove& chessMove);
    void applyMoveWithSourceFileAndRank(const ChessMove& chessMove);

    void applyMoveForPawn(const Color& color, const ChessMove& chessMove);
    bool isValidMove(const Color& color, const Piece& piece, int sourceRow, int sourceCol, int destRow, int destCol) const;

    vector<pair<int, int>> getDirectionsForPiece(const Piece& piece) const;
    void applyMoveWithSingleStep(const Color& color, const ChessMove& chessMove);
    void applyMoveWithMultipleSteps(const Color& color, const ChessMove& chessMove);

    void applyMoveForKingSideCastling(const Color& color);
    void applyMoveForQueenSideCastling(const Color& color);

public:
    ChessBoard();

    void reset();
    string toString() const;

    void applyTurn(const ChessTurn& turn);
};

#endif // CHESSBOARD_H