#include "chessMove.h"

#include "utils.h"

#include <sstream>

using namespace std;

string ChessMove::toString() const
{
    stringstream ss;
    ss << "ChessMove: {";
    ss << "Piece: " << Utils::pieceToString(piece) << ", ";
    ss << "Source Square: " << sourceFile << sourceRank << ", ";
    ss << "Destination Square: " << destinationFile << destinationRank << ", ";
    ss << "Is King Side Castling? " << (isKingSideCastling ? "Yes" : "No") << ", ";
    ss << "Is Queen Side Castling? " << (isQueenSideCastling ? "Yes" : "No") << ", ";
    ss << "Is Promotion? " << (isPromotion ? "Yes" : "No") << ", ";
    ss << "Promoted Piece: " << Utils::pieceToString(promotedPiece) << "}" << endl;

    return ss.str();
}