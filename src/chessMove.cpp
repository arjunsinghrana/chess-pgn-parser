#include "chessMove.h"

#include "utils.h"

#include <iostream>

using namespace std;

void ChessMove::display() const
{
    cout << "ChessMove: {";
    cout << "Piece: " << Utils::pieceToString(piece) << ", ";
    cout << "Source Square: " << sourceFile << sourceRank << ", ";
    cout << "Destination Square: " << destinationFile << destinationRank << ", ";
    cout << "Is Capture? " << (isCapture ? "Yes" : "No") << ", ";
    cout << "Is Check? " << (isCheck ? "Yes" : "No") << ", ";
    cout << "Is Checkmate? " << (isCheckmate ? "Yes" : "No") << ", ";
    cout << "Is Castling? " << (isCastling ? "Yes" : "No") << "}" << endl;
}