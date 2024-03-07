#include "chessTurn.h"

#include <sstream>

ChessTurn::ChessTurn(int turn, ChessMove white, ChessMove black)
: turnNumber(turn), whiteMove(white), blackMove(black) {}

string ChessTurn::toString() const
{
    stringstream ss;

    ss << "ChessTurn: " << turnNumber << ", ";
    ss << "White Move: " << whiteMove.toString() << ", ";
    ss << "Black Move: " << blackMove.toString();
    ss << endl;

    return ss.str();
}