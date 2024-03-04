#include "chessTurn.h"

#include <iostream>

ChessTurn::ChessTurn(int turn, ChessMove white, ChessMove black)
: turnNumber(turn), whiteMove(white), blackMove(black) {}

void ChessTurn::display()
{
    cout << "ChessTurn: " << turnNumber << ",";
    cout << "White Move: ";
    whiteMove.display();
    cout << "Black Move: ";
    blackMove.display();
    cout << endl;
}