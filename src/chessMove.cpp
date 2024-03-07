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
    cout << "Is King Side Castling? " << (isKingSideCastling ? "Yes" : "No") << ", ";
    cout << "Is Queen Side Castling? " << (isQueenSideCastling ? "Yes" : "No") << "}" << endl;
}