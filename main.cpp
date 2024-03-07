#include <fstream>
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
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file" << endl;
        return 1;
    }

    // Go through file and concatenate the lines containing moves
    string line;
    bool found = false;
    while (getline(file, line)) 
    {
        // Skip empty lines
        if (line.empty())
        {
            continue;
        }

        // Skip tag pairs
        if (line[0] == '[')
        {
            continue;
        }

        // Filter out lines that are not moves
        if (isdigit(line[0]))
        {
            found = true;
            break;
        }
    }

    // Check if game was not found
    if (!found)
    {
        cerr << "Could not find game" << endl;
        return 1;
    }

    // Concatenate lines containing moves 
    stringstream ss;
    ss << line;
    while(getline(file, line))
    {
        if (!line.empty())
        {
            ss << " " << line;
        }
    }

    // Convert string containing Move Text into vector of Chess Turns
    vector<ChessTurn> turns = Utils::parseChessMoves(ss.str());

    ChessBoard board;
    for (const auto& turn : turns)
    {
        cout << turn.toString();
        board.applyTurn(turn);
        cout << board.toString();
    }

    return 0;
}