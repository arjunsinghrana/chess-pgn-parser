#ifndef CHESSTURN_H
#define CHESSTURN_H

#include "chessMove.h"

using namespace std;

class ChessTurn
{
public:
    int turnNumber;
    ChessMove whiteMove;
    ChessMove blackMove;

    ChessTurn(int turn, ChessMove white, ChessMove black);

    // Display contents of class
    void display() const;
};

#endif // CHESSTURN_H