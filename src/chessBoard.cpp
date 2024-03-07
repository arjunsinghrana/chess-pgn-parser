#include "chessBoard.h"

#include "utils.h"

#include <iostream>


using namespace std;


ChessBoard::ChessBoard()
{
    board.resize(BOARD_SIZE, vector<ChessPiece>(BOARD_SIZE, emptyPiece));
    reset();
}

void ChessBoard::print() const
{
    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int j = 0; j < BOARD_SIZE; ++j) 
        {
            cout << Utils::chessPieceToString(getChessPiece(i, j)) << "|";
        }
        cout << endl;
    }
    cout << endl;
}

void ChessBoard::setChessPiece(int row, int col, const ChessPiece& piece)
{
    if (validPosition(row, col))
    {
        board[row][col] = piece;
    }
}

const ChessPiece& ChessBoard::getChessPiece(int row, int col) const
{
    if (validPosition(row, col))
    {
        return board[row][col];
    }
    else
    {
        return emptyPiece;
    }
}

void ChessBoard::reset()
{
    // Set pieces on the board
    setChessPiece(7, 0, {Color::WHITE, Piece::ROOK});
    setChessPiece(7, 1, {Color::WHITE, Piece::KNIGHT});
    setChessPiece(7, 2, {Color::WHITE, Piece::BISHOP});
    setChessPiece(7, 3, {Color::WHITE, Piece::QUEEN});
    setChessPiece(7, 4, {Color::WHITE, Piece::KING});
    setChessPiece(7, 5, {Color::WHITE, Piece::BISHOP});
    setChessPiece(7, 6, {Color::WHITE, Piece::KNIGHT});
    setChessPiece(7, 7, {Color::WHITE, Piece::ROOK});

    setChessPiece(6, 0, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 1, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 2, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 3, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 4, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 5, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 6, {Color::WHITE, Piece::PAWN});
    setChessPiece(6, 7, {Color::WHITE, Piece::PAWN});

    setChessPiece(0, 0, {Color::BLACK, Piece::ROOK});
    setChessPiece(0, 1, {Color::BLACK, Piece::KNIGHT});
    setChessPiece(0, 2, {Color::BLACK, Piece::BISHOP});
    setChessPiece(0, 3, {Color::BLACK, Piece::QUEEN});
    setChessPiece(0, 4, {Color::BLACK, Piece::KING});
    setChessPiece(0, 5, {Color::BLACK, Piece::BISHOP});
    setChessPiece(0, 6, {Color::BLACK, Piece::KNIGHT});
    setChessPiece(0, 7, {Color::BLACK, Piece::ROOK});

    setChessPiece(1, 0, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 1, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 2, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 3, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 4, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 5, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 6, {Color::BLACK, Piece::PAWN});
    setChessPiece(1, 7, {Color::BLACK, Piece::PAWN});
}

int ChessBoard::rankToRow(char rank) const
{
    return BOARD_SIZE - (rank - '0');
}

char ChessBoard::rowToRank(int row) const
{
    return BOARD_SIZE - (row - '0');
}

int ChessBoard::fileToCol(char file) const
{
    return file - 'a';
}

vector<pair<int, int>> ChessBoard::getDirectionsForPiece(const Piece& piece) const
{
    switch (piece)
    {
    case Piece::PAWN:
        return {{-1, 0}, {-1, -1}, {-1, 1}}; // Default for White pawn
    case Piece::ROOK:
        return {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    case Piece::BISHOP:
        return {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    case Piece::QUEEN:
        return {{1, 1}, {-1, 1}, {1, -1}, {-1, -1},
                {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    case Piece::KNIGHT:
        return {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                    {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    case Piece::KING:
        return {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, 
                    {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    default:
        return {};
    }
}

void ChessBoard::applyMove(Color color, ChessMove chessMove)
{
    // Source File is provided. We can infer the Source Rank.
    if (chessMove.sourceFile != '?' && chessMove.sourceRank == '?')
    {
        const ChessPiece chessPiece = {color, chessMove.piece};

        int sourceCol = fileToCol(chessMove.sourceFile);

        for (int sourceRow = 0; sourceRow < BOARD_SIZE; sourceRow++)
        {
            if (chessPiece == getChessPiece(sourceRow, sourceCol))
            {
                switch(chessPiece.piece)
                {
                    case Piece::PAWN: 
                        if (!isValidMove(color, chessPiece.piece, sourceRow, sourceCol, 
                        rankToRow(chessMove.destinationRank), fileToCol(chessMove.destinationFile)))
                        {
                            break;
                        }
                    default:
                        chessMove.sourceRank = rowToRank(sourceRow);
                        break;
                }
            }
        }
    }

    if (chessMove.sourceFile != '?' && chessMove.sourceRank != '?')
    {
        applyMoveWithSourceFileAndRank(chessMove);
        return;
    }

    if (chessMove.isKingSideCastling)
    {
        applyMoveForKingSideCastling(color);
        return;
    }

    if (chessMove.isQueenSideCastling)
    {
        applyMoveForQueenSideCastling(color);
        return;
    }

    switch (chessMove.piece)
    {
    case Piece::PAWN:
        applyMoveForPawn(color, chessMove);
        break;
    case Piece::KNIGHT:
        applyMoveWithSingleStep(color, chessMove);
        break;
    case Piece::BISHOP:
        applyMoveWithMultipleSteps(color, chessMove);
        break;
    case Piece::ROOK:
        applyMoveWithMultipleSteps(color, chessMove);
        break;
    case Piece::KING:
        applyMoveWithSingleStep(color, chessMove);
        break;
    case Piece::QUEEN:
        applyMoveWithMultipleSteps(color, chessMove);
        break;
    default:
        break;
    }
}

void ChessBoard::applyMoveWithSingleStep(const Color& color, const ChessMove& chessMove)
{
    const ChessPiece chessPiece = {color, chessMove.piece};

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    vector<pair<int, int>> directions = getDirectionsForPiece(chessMove.piece);

    int old_col = -1;
    int old_row = -1;
    bool found = false;
    for (int i = 0; i < directions.size(); i++)
    {
        old_row = row + directions[i].first;
        old_col = col + directions[i].second;

        if (chessPiece == getChessPiece(old_row, old_col))
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        setChessPiece(old_row, old_col, emptyPiece);
        setChessPiece(row, col, chessPiece);
    }
}

void ChessBoard::applyMoveWithMultipleSteps(const Color& color, const ChessMove& chessMove)
{
    const ChessPiece chessPiece = {color, chessMove.piece};

    vector<pair<int, int>> directions = getDirectionsForPiece(chessMove.piece);

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    int old_col = -1;
    int old_row = -1;
    bool found = false;

    for (int i = 0; i < directions.size(); i++)
    {
        old_col = col;
        old_row = row;

        while (true)
        {
            old_row += directions[i].first;
            old_col += directions[i].second;

            // Break as we cannot go further in this direction
            if (!validPosition(old_row, old_col))
            {
                break;
            }

            // Break if we have another piece blocking the way
            if (emptyPiece != getChessPiece(old_row, old_col) 
             && chessPiece != getChessPiece(old_row, old_col))
            {
                break;
            }

            if (chessPiece == getChessPiece(old_row, old_col))
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    if (found)
    {
        setChessPiece(old_row, old_col, emptyPiece);
        setChessPiece(row, col, chessPiece);
    }
}

void ChessBoard::applyMoveWithSourceFileAndRank(const ChessMove& chessMove)
{
    int sourceRow = rankToRow(chessMove.sourceRank);
    int sourceCol = fileToCol(chessMove.sourceFile);

    int destRow = rankToRow(chessMove.destinationRank);
    int destCol = fileToCol(chessMove.destinationFile);

    setChessPiece(destRow, destCol, getChessPiece(sourceRow, sourceCol));
    setChessPiece(sourceRow, sourceCol, emptyPiece);
}

void ChessBoard::applyMoveForPawn(const Color& color, const ChessMove& chessMove)
{
    const ChessPiece chessPiece = {color, chessMove.piece};

    int row = rankToRow(chessMove.destinationRank);
    int col = fileToCol(chessMove.destinationFile);

    bool found = false;

    int index;
    int update;

    if (Color::WHITE == color)
    {
        index = BOARD_SIZE - 1;
        update = -1;
    }
    else if (Color::BLACK == color)
    {
        index = 0;
        update = 1;
    }

    for (; !found && index >= 0 && index < BOARD_SIZE; index += update)
    {
        if (chessPiece == getChessPiece(index, col))
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        setChessPiece(index, col, emptyPiece);
        setChessPiece(row, col, chessPiece);
    }
}

bool ChessBoard::isValidMove(const Color& color, const Piece& piece, int sourceRow, int sourceCol, int destRow, int destCol) const 
{
    if (Piece::PAWN == piece)
    {
        int d = 0;
        if (Color::WHITE == color)
        {
            d = 1;
        }
        else 
        {
            d = -1;
        }
        
        for (const pair<int, int>& direction : getDirectionsForPiece(piece))
        {
            if (sourceRow + d * direction.first == destRow && sourceCol + direction.second == destCol)
            {
                return true;
            }
        }
    }

    return false;
}

void ChessBoard::applyMoveForKingSideCastling(const Color& color)
{
    switch (color)
    {
    case Color::WHITE:
        setChessPiece(7, 4, emptyPiece);
        setChessPiece(7, 7, emptyPiece);
        setChessPiece(7, 6, {color, Piece::KING});
        setChessPiece(7, 5, {color, Piece::ROOK});
        break;
    case Color::BLACK:
        setChessPiece(0, 4, emptyPiece);
        setChessPiece(0, 7, emptyPiece);
        setChessPiece(0, 6, {color, Piece::KING});
        setChessPiece(0, 5, {color, Piece::ROOK});
        break;
    default:
        break;
    }
}

void ChessBoard::applyMoveForQueenSideCastling(const Color& color)
{
    switch (color)
    {
    case Color::WHITE:
        setChessPiece(7, 4, emptyPiece);
        setChessPiece(7, 0, emptyPiece);
        setChessPiece(7, 2, {color, Piece::KING});
        setChessPiece(7, 3, {color, Piece::ROOK});
        break;
    case Color::BLACK:
        setChessPiece(0, 4, emptyPiece);
        setChessPiece(0, 0, emptyPiece);
        setChessPiece(0, 2, {color, Piece::KING});
        setChessPiece(0, 3, {color, Piece::ROOK});
        break;
    default:
        break;
    }
}

bool ChessBoard::validPosition(int row, int col) const
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

void ChessBoard::applyTurn(const ChessTurn& turn)
{
    applyMove(Color::WHITE, turn.whiteMove);
    applyMove(Color::BLACK, turn.blackMove);
}