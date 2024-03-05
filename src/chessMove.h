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
    bool isCapture = false;
    bool isCheck = false;
    bool isCheckmate = false;
    bool isCastling = false;
    
    // Display contents of class
    void display();
};

#endif // CHESSMOVE_H