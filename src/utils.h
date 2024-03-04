#ifndef UTILS_H
#define UTILS_H

#include "chessMove.h"
#include "chessPiece.h"
#include "chessTurn.h"

#include <string>
#include <vector>

using namespace std;

class Utils
{
public:
    static string removeSubstringInCurlyBrackets(const string& input);
    static string removeSubstringWithNumberAndThreeDots(const string& input);

    static ChessMove parseSANMove(string& san);
    static vector<ChessTurn> parseChessMoves(const string& line);

    static string pieceToString(const ChessPiece& piece);

    static void rotate90(vector<vector<ChessPiece> >& board);
    static void rotate180(vector<vector<ChessPiece> >& board);
};

#endif // UTILS_H