#include "chessMove.h"

using namespace std;

ChessMove::ChessMove(int moveNum, const string& white, const string& black) 
: moveNumber(moveNum), whiteMove(white), blackMove(black) {}

void ChessMove::display() 
{
    cout << "Move " << moveNumber << ": " << whiteMove << " " << blackMove << endl;
}