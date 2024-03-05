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

ChessMove Utils::parseSANMove(string& san)
{
    ChessMove move;

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

void Utils::rotate90(vector<vector<ChessPiece>>& board)
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

void Utils::rotate180(vector<vector<ChessPiece>>& board)
{
    rotate90(board);
    rotate90(board);
}