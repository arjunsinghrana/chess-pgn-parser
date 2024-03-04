#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <string>

using namespace std;

struct ChessMove 
{
    char piece;
    char sourceFile;
    char sourceRank;
    char destinationFile;
    char destinationRank;
    bool isCapture;
    bool isCheck;
    bool isCheckmate;
    bool isCastling;
    
    // Display contents of class
    void display();
};

#endif // CHESSMOVE_H