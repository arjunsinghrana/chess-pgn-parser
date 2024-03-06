#include "chessBoard.h"

#include "utils.h"

#include <iostream>


using namespace std;


ChessBoard::ChessBoard()
{
    board.resize(BOARD_SIZE, vector<ChessPiece>(BOARD_SIZE, {Color::EMPTY, Piece::EMPTY}));
    reset();
}

void ChessBoard::print() const
{
    for (int i = 0; i < BOARD_SIZE; ++i) 
    {
        for (int j = 0; j < BOARD_SIZE; ++j) 
        {
            cout << Utils::chessPieceToString(board[i][j]) << "|";
        }
        cout << endl;
    }
    cout << endl;
}

void ChessBoard::setChessPiece(int row, int col, ChessPiece piece)
{
    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE)
    {
        board[row][col] = piece;
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

int ChessBoard::rankToRow(char rank)
{
    return BOARD_SIZE - (rank- '0');
}

int ChessBoard::fileToCol(char file)
{
    return file - 'a';
}

void ChessBoard::applyMove(Color color, ChessMove chessMove)
{
    if (chessMove.sourceFile != '?' && chessMove.sourceRank != '?')
    {
        applyMoveWithSourceFileAndRank(chessMove);
        return;
    }

    switch (chessMove.piece)
    {
    case Piece::PAWN:
        if (Color::WHITE == color)
        {
            applyMoveForWhitePawn(chessMove);
        }
        else if (Color::BLACK == color)
        {
            applyMoveForBlackPawn(chessMove);
        }
        break;
    case Piece::KNIGHT:
        applyMoveForKnight(color, chessMove);
        break;
    case Piece::BISHOP:
        applyMoveForBishop(color, chessMove);
        break;
    case Piece::ROOK:
        applyMoveForRook(color, chessMove);
        break;
    case Piece::KING:
        applyMoveForKing(color, chessMove);
        break;
    case Piece::QUEEN:
        applyMoveForQueen(color, chessMove);
        break;
    default:
        break;
    }
}

void ChessBoard::applyMoveWithSourceFileAndRank(ChessMove chessMove)
{
    ChessPiece chessPiece = board[rankToRow(chessMove.sourceRank)][fileToCol(chessMove.sourceFile)];
    board[rankToRow(chessMove.destinationRank)][fileToCol(chessMove.destinationFile)] = chessPiece;

    board[rankToRow(chessMove.sourceRank)][fileToCol(chessMove.sourceFile)] = {Color::EMPTY, Piece::EMPTY};
}

void ChessBoard::applyMoveForWhitePawn(ChessMove chessMove)
{
    ChessPiece chessPiece = {Color::WHITE, Piece::PAWN};

    int row = rankToRow(chessMove.destinationRank);
    int col = fileToCol(chessMove.destinationFile);

    bool found = false;
    int i = 0;
    for (; !found && i < BOARD_SIZE; i++)
    {
        if (chessPiece == board[i][col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[i][col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForBlackPawn(ChessMove chessMove)
{
    ChessPiece chessPiece = {Color::BLACK, Piece::PAWN};

    int row = rankToRow(chessMove.destinationRank);
    int col = fileToCol(chessMove.destinationFile);

    bool found = false;
    int i = BOARD_SIZE - 1;
    for (; !found && i >= 0; i--)
    {
        if (chessPiece == board[i][col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[i][col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForKnight(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, Piece::KNIGHT};

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    int moves[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                    {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    int old_col = -1;
    int old_row = -1;
    bool found = false;
    for (int i = 0; i < 8; i++)
    {
        old_col = col + moves[i][0];
        old_row = row + moves[i][1];

        if (validPosition(old_row, old_col) && chessPiece == board[old_row][old_col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[old_row][old_col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForBishop(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, Piece::BISHOP};

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    int directions[4][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    int old_col = -1;
    int old_row = -1;
    bool found = false;

    for (int i = 0; i < 4; i++)
    {
        old_col = col;
        old_row = row;

        while (true)
        {
            old_col += directions[i][0];
            old_row += directions[i][1];

            if (!validPosition(old_row, old_col))
            {
                break;
            }

            if (chessPiece == board[old_row][old_col])
            {
                cout << "old row and old col for bishop: " << old_row << " " << old_col << endl;
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
        board[old_row][old_col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForRook(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, Piece::ROOK};

    int row = rankToRow(chessMove.destinationRank);
    int col = fileToCol(chessMove.destinationFile);

    // Check file/col
    int old_row = -1;
    bool foundInFile = false;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (chessPiece == board[i][col])
        {
            old_row = i;
            foundInFile = true;
            break;
        }
    }

    // Check rank/row
    int old_col = -1;
    bool foundInRow = false;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (chessPiece == board[row][i])
        {
            old_col = i;
            foundInRow = true;
            break;
        }
    }

    if (foundInFile)
    {
        board[old_row][col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
    else if (foundInRow)
    {
        board[row][old_col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }

}

void ChessBoard::applyMoveForKing(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, Piece::KING};

    int row = rankToRow(chessMove.destinationRank);
    int col = fileToCol(chessMove.destinationFile);

    int moves[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                        {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    int old_row = -1;
    int old_col = -1;
    bool found = false;
    for(int i = 0; i < 8; i++)
    {
        old_col = col + moves[i][0];
        old_row = row + moves[i][1];

        if (!validPosition(old_row, old_col))
        {
            break;
        }

        if (chessPiece == board[old_row][old_col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[old_row][old_col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForQueen(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, Piece::QUEEN};

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    int directions[8][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1},
                             {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int old_col = -1;
    int old_row = -1;
    bool found = false;

    for (int i = 0; i < 8; i++)
    {
        old_col = col;
        old_row = row;

        while (true)
        {
            old_col += directions[i][0];
            old_row += directions[i][1];

            if (!validPosition(old_row, old_col))
            {
                break;
            }

            if (chessPiece == board[old_row][old_col])
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
        board[old_row][old_col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

bool ChessBoard::validPosition(int row, int col)
{
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

void ChessBoard::applyTurn(ChessTurn turn)
{
    applyMove(Color::WHITE, turn.whiteMove);
    applyMove(Color::BLACK, turn.blackMove);
}