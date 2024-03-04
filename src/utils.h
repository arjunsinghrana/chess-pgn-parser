#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "chessMove.h"
#include "chessPiece.h"
#include "chessTurn.h"

using namespace std;

class Utils
{
public:
    static string removeSubstringInCurlyBrackets(const string& input);
    static string removeSubstringWithNumberAndThreeDots(const string& input);

    static vector<ChessTurn> parseChessMoves(const string& line);
    static ChessMove parseSANMove(string& moveStr);

    static string pieceToString(ChessPiece piece);

    static void rotate90(vector<vector<ChessPiece> >& board);
    static void rotate180(vector<vector<ChessPiece> >& board);
};

#endif // UTILS_H