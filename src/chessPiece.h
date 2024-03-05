#ifndef CHESSPIECE_H
#define CHESSPIECE_H

enum class Color { EMPTY, WHITE, BLACK };
enum class Piece { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

struct ChessPiece
{
    Color color;
    Piece piece;
};

#endif // CHESSPIECE_H