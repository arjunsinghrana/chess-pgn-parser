#include "utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

string Utils::removeSubstringInCurlyBrackets(const string& input) {
    stringstream result;

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
            result << c;
        }
    }

    return result.str();
}

string Utils::removeSubstringWithNumberAndThreeDots(const string& input) {
    stringstream result;

    stringstream ss (input);
    string word;
    while (ss >> word)
    {
        if (word.size() > 3 && word.substr(word.size() - 3, word.size()) == "...")
        {
            continue;
        }
        result << word << " ";
    }

    return result.str();
}

string Utils::removeCharactersFromString(const string& characters, const string& input) {
    string result = input;

    // Use remove_if with a lambda function
    result.erase(remove_if(result.begin(), result.end(),
                                [&characters](char c) {
                                    return characters.find(c) != string::npos;
                                }),
                 result.end());

    return result;
}

ChessMove Utils::parseSANMove(string& san)
{
    ChessMove move;

    // Remove characters for capture, check and checkmate from string
    string charactersToRemove = "x+#";
    san = removeCharactersFromString(charactersToRemove, san);

    size_t foundEquals = san.find("=");
    if (foundEquals != string::npos)
    {
        move.isPromotion = true;

        move.promotedPiece = charToPiece(san[foundEquals + 1]);
        san = san.substr(0, foundEquals);
    }

    // King Side Castling
    if ("O-O" == san) {
        move.isKingSideCastling = true;
        return move;
    }

    // Castling
    if ("O-O-O" == san) {
        move.isQueenSideCastling = true;
        return move;
    }

    // Return empty move for Result
    if ("1/2-1/2" == san || "1-0" == san || "0-1" == san)
    {
        return move;
    }

    // Upper case letters denote pieces
    if (isupper(san[0])) {
        move.piece = charToPiece(san[0]);
        san = san.substr(1); // Remove piece from the SAN string
    } else {
        move.piece = charToPiece('P'); // Assume it's a pawn if no piece is specified
    }

    // Parsing the destination square
    move.destinationFile = san[san.length() - 2];
    move.destinationRank = san[san.length() - 1];

    // Parsing the source square if provided
    if (san.length() >= 3) {
        if (isalpha(san[0])) {
            move.sourceFile = san[0];
        }
        if (isdigit(san[1])) {
            move.sourceRank = san[1];
        }
    }

    return move;
}

string Utils::parseFileAndConcatenateChessMoves(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Error: Unable to open file: " << filename << endl;
        return "";
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
        return "";
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

    return ss.str();
}

vector<ChessTurn> Utils::parseChessMoves(const string& input)
{
    // cout << "input" << input << endl;
    string parsedLine;
    parsedLine = Utils::removeSubstringInCurlyBrackets(input);
    // cout << "parsedLine: " << parsedLine << endl;
    parsedLine = Utils::removeSubstringWithNumberAndThreeDots(parsedLine);
    // cout << "parsedLine: " << parsedLine << endl;

    vector<ChessTurn> turns;

    bool newMove = false;
    int turnNumber = -1;

    string word;
    stringstream ss(parsedLine);
    while (ss >> word)
    {
        if (!newMove && isdigit(word[0]))
        {
            newMove = true;
            turnNumber = stoi(word.substr(0, word.size() - 1));
        }

        string whiteMove;
        string blackMove;
        if (newMove)
        {
            ss >> whiteMove;
            ss >> blackMove;

            ChessTurn turn(turnNumber, parseSANMove(whiteMove), parseSANMove(blackMove));
            turns.push_back(turn);

            newMove = false;
        }
        
    }

    return turns;
}

string Utils::pieceToString(const Piece& piece)
{
    switch (piece)
    {
    case Piece::EMPTY:
        return "  ";
        break;
    case Piece::PAWN:
        return "P";
        break;
    case Piece::ROOK:
        return "R";
        break;
    case Piece::KNIGHT:
        return "N";
        break;
    case Piece::BISHOP:
        return "B";
        break;
    case Piece::QUEEN:
        return "Q";
        break;
    case Piece::KING:
        return "K";
        break;
    default: 
        return "";
        break;
    }
}

Piece Utils::charToPiece(char piece)
{
    if (piece == 'P')
    {
        return Piece::PAWN;
    }
    else if (piece == 'R')
    {
        return Piece::ROOK;
    }
    else if (piece == 'N')
    {
        return Piece::KNIGHT;
    }
    else if (piece == 'B')
    {
        return Piece::BISHOP;
    }
    else if (piece == 'Q')
    {
        return Piece::QUEEN;
    }
    else if (piece == 'K')
    {
        return Piece::KING;
    }
    else 
    {
        return Piece::EMPTY;
    }
}

string Utils::colorToString(const Color& color)
{
    switch (color)
    {
        case Color::WHITE: 
            return "w";
        case Color::BLACK:
            return "b";
        default:
            return "";
    }
}

string Utils::chessPieceToString(const ChessPiece& chessPiece)
{
    return colorToString(chessPiece.color) + pieceToString(chessPiece.piece);
}
