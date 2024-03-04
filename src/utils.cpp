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

vector<ChessMove> Utils::parseChessMoves(const string& input)
{
    string parsedLine;
    parsedLine = Utils::removeSubstringInCurlyBrackets(input);
    parsedLine = Utils::removeSubstringWithNumberAndThreeDots(parsedLine);

    vector<ChessMove> moves;

    bool newMove = false;
    int currentMove = -1;

    string word;
    stringstream ss(parsedLine);
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