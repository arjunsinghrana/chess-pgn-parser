#include "utils.h"

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

vector<ChessTurn> Utils::parseChessMoves(const string& input)
{
    string parsedLine;
    parsedLine = Utils::removeSubstringInCurlyBrackets(input);
    parsedLine = Utils::removeSubstringWithNumberAndThreeDots(parsedLine);

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
            turn.display();

            turns.push_back(turn);

            newMove = false;
        }
        
    }

    return turns;
}

ChessMove Utils::parseSANMove(string& san)
{
    ChessMove move;
    move.isCapture = false;
    move.isCheck = false;
    move.isCheckmate = false;
    move.isCastling = false;

    // Capture
    if (san.find("x") != string::npos) {
        move.isCapture = true;
    }

    // Checkmate
    if (san.find("#") != string::npos) {
        move.isCheckmate = true;
    }

    // Check
    if (san.find("+") != string::npos && !move.isCheckmate) {
        move.isCheck = true;
    }

    // Castling
    if (san == "O-O" || san == "O-O-O") {
        move.isCastling = true;
        return move;
    }

    // Upper case letters denote pieces
    if (isupper(san[0])) {
        move.piece = san[0];
        san = san.substr(1); // Remove piece from the SAN string
    } else {
        move.piece = 'P'; // Assume it's a pawn if no piece is specified
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

void Utils::rotate90(vector<vector<ChessPiece> >& board)
{
    int N = board.size();

    // Transpose the matrix
    for (int i = 0; i < N; ++i) {
        for (int j = i; j < N; ++j) {
            swap(board[i][j], board[j][i]);
        }
    }
    
    // Reverse each row
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N / 2; ++j) {
            swap(board[i][j], board[i][N - 1 - j]);
        }
    }
}

void Utils::rotate180(vector<vector<ChessPiece> >& board)
{
    rotate90(board);
    rotate90(board);
}

string Utils::pieceToString(ChessPiece piece)
{
    switch (piece)
    {
    case EMPTY:
        return "  ";
        break;
    case WHITE_PAWN:
        return "wP";
        break;
    case WHITE_ROOK:
        return "wR";
        break;
    case WHITE_KNIGHT:
        return "wN";
        break;
    case WHITE_BISHOP:
        return "wB";
        break;
    case WHITE_QUEEN:
        return "wQ";
        break;
    case WHITE_KING:
        return "wK";
        break;
    case BLACK_PAWN:
        return "bP";
        break;
    case BLACK_ROOK:
        return "bR";
        break;
    case BLACK_KNIGHT:
        return "bN";
        break;
    case BLACK_BISHOP:
        return "bB";
        break;
    case BLACK_QUEEN:
        return "bQ";
        break;
    case BLACK_KING:
        return "bK";
        break;
    
    default:
        return "??";
        break;
    }
}