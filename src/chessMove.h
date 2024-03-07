#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <string>

#include "chessPiece.h"

using namespace std;

struct ChessMove 
{
    Piece piece = Piece::EMPTY;

    char sourceFile = '?';
    char sourceRank = '?';
    char destinationFile = '?';
    char destinationRank = '?';
    
    bool isKingSideCastling = false;
    bool isQueenSideCastling = false;

    bool isPromotion = false;
    Piece promotedPiece = Piece::EMPTY;
    
    string toString() const;
};

#endif // CHESSMOVE_H