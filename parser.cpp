#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "src/chessBoard.h"
#include "src/chessMove.h"
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
        // Filter out lines that are not moves
        if (!line.empty() && isdigit(line[0]))
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

    vector<ChessMove> moves = Utils::parseChessMoves(ss.str());

    ChessBoard board;
    board.print();

    return 0;
}