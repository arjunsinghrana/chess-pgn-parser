#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class ChessMove 
{
private:
    int moveNumber;
    std::string whiteMove;
    std::string blackMove;

public:
    ChessMove(int moveNum, const std::string& white, const std::string& black) : moveNumber(moveNum), whiteMove(white), blackMove(black) {}

    void display() 
    {
        cout << "Move " << moveNumber << ": " << whiteMove << " " << blackMove << endl;
    }
};

string removeSubstringInCurlyBrackets(const string& input) {
    string result;

    bool withinCurlyBrackets = false;
    for (char c : input) {
        if (c == '{') {
            withinCurlyBrackets = true;
            continue;
        }
        if (c == '}') {
            withinCurlyBrackets = false;
            continue;
        }
        if (!withinCurlyBrackets) {
            result += c;
        }
    }

    return result;
}

string removeSubstringWithNumberAndThreeDots(const string& input) {
    string reversed = input;
    reverse(reversed.begin(), reversed.end());

    string result;
    stringstream ss (reversed);
    string word;
    while (ss >> word)
    {
        if (word.size() > 3 && word.substr(0, 3) == "...")
        {
            continue;
        }
        result += word + " ";
    }

    if (!result.empty())
    {
        result.pop_back();
    }

    reverse(result.begin(), result.end());
    return result;
}

vector<ChessMove> parseChessMoves(const string& line)
{
    string parsedLine;
    parsedLine = removeSubstringInCurlyBrackets(line);
    parsedLine = removeSubstringWithNumberAndThreeDots(parsedLine);

    stringstream ss(parsedLine);

    vector<ChessMove> moves;

    bool newMove = false;
    int currentMove = -1;
    string word;
    while (ss >> word)
    {
        if (!newMove && isdigit(word[0]))
        {
            newMove = true;
            currentMove = stoi(word.substr(0, word.size() - 1));
        }

        string whiteMove;
        string blackMove;
        if (newMove)
        {
            ss >> whiteMove;
            ss >> blackMove;

            ChessMove move(currentMove, whiteMove, blackMove);
            move.display();

            moves.push_back(move);

            newMove = false;
        }
        
    }

    return moves;
}

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

    parseChessMoves(ss.str());

    return 0;
}