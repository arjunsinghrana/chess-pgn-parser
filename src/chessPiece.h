#ifndef CHESSPIECE_H
#define CHESSPIECE_H

enum class Color { EMPTY, WHITE, BLACK };
enum class Piece { EMPTY, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };

struct ChessPiece
{
    Color color;
    Piece piece;

    bool operator==(const ChessPiece& other) const
    {
        return color == other.color && piece == other.piece;
    }

    bool operator!=(const ChessPiece& other) const
    {
        return !operator==(other);
    }
};

#endif // CHESSPIECE_H