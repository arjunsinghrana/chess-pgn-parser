#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <iostream>

using namespace std;

class ChessMove 
{
private:
    int moveNumber;
    string whiteMove;
    string blackMove;

public:
    // Constructor
    ChessMove(int moveNum, const string& white, const string& black);

    // Print contents of class
    void display();
};

#endif // CHESSMOVE_H