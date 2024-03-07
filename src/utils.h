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
    static string removeCharactersFromString(const string& characters, const string& input);

    static ChessMove parseSANMove(string& san);
    static vector<ChessTurn> parseChessMoves(const string& line);

    static string pieceToString(const Piece& piece);
    static Piece charToPiece(char piece);

    static string colorToString(const Color& color);

    static string chessPieceToString(const ChessPiece& chessPiece);
};

#endif // UTILS_H