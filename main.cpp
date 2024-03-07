#include <iostream>
#include <sstream>
#include <vector>

#include "src/chessBoard.h"
#include "src/chessTurn.h"
#include "src/utils.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Check compiler arguments
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Open file
    string filename = argv[1];

    // Concatenate all chess moves into a single string
    const string concatenatedChessMoves = Utils::parseFileAndConcatenateChessMoves(filename);

    // Convert string containing moves into vector of Chess Turns
    const vector<ChessTurn> turns = Utils::parseChessMoves(concatenatedChessMoves);

    ChessBoard board;
    for (const auto& turn : turns)
    {
        cout << turn.toString();
        board.applyTurn(turn);
        cout << board.toString();
    }

    return 0;
}