#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "chessMove.h"
#include "chessPiece.h"

using namespace std;

class Utils
{
public:
    static string removeSubstringInCurlyBrackets(const string& input);
    static string removeSubstringWithNumberAndThreeDots(const string& input);

    static vector<ChessMove> parseChessMoves(const string& line);

    static string pieceToString(ChessPiece piece);

    static void rotate90(vector<vector<ChessPiece> >& board);
    static void rotate180(vector<vector<ChessPiece> >& board);
};

#endif // UTILS_H