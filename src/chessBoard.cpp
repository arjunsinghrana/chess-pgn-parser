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
    return BOARD_SIZE - (rank - '0');
}

char ChessBoard::rowToRank(int row)
{
    return BOARD_SIZE - (row - '0');
}

int ChessBoard::fileToCol(char file)
{
    return file - 'a';
}

vector<pair<int, int>> ChessBoard::getDirectionsForPiece(Piece piece)
{
    switch (piece)
    {
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
    if (chessMove.sourceFile != '?' && chessMove.sourceRank != '?')
    {
        applyMoveWithSourceFileAndRank(chessMove);
        return;
    }

    if (chessMove.sourceFile != '?')
    {
        ChessPiece chessPiece = {color, chessMove.piece};

        int sourceCol = fileToCol(chessMove.sourceFile);

        for (int sourceRow = 0; sourceRow < BOARD_SIZE; sourceRow++)
        {
            if (chessPiece == board[sourceRow][sourceCol])
            {
                chessMove.sourceRank = rowToRank(sourceRow);
            }
        }

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

void ChessBoard::applyMoveWithSingleStep(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, chessMove.piece};
    ChessPiece emptyPiece = {Color::EMPTY, Piece::EMPTY};

    int col = fileToCol(chessMove.destinationFile);
    int row = rankToRow(chessMove.destinationRank);

    vector<pair<int, int>> directions = getDirectionsForPiece(chessMove.piece);

    int old_col = -1;
    int old_row = -1;
    bool found = false;
    for (int i = 0; i < directions.size(); i++)
    {
        old_col = col + directions[i].first;
        old_row = row + directions[i].second;

        if (validPosition(old_row, old_col) && chessPiece == board[old_row][old_col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[old_row][old_col] = emptyPiece;
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveWithMultipleSteps(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, chessMove.piece};
    ChessPiece emptyPiece = {Color::EMPTY, Piece::EMPTY};

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
            old_col += directions[i].first;
            old_row += directions[i].second;

            if (!validPosition(old_row, old_col))
            {
                break;
            }

            // Check that no other piece is in the way
            if (emptyPiece != board[old_row][old_col] && chessPiece != board[old_row][old_col])
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
        board[old_row][old_col] = emptyPiece;
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveWithSourceFileAndRank(ChessMove chessMove)
{
    ChessPiece chessPiece = board[rankToRow(chessMove.sourceRank)][fileToCol(chessMove.sourceFile)];
    board[rankToRow(chessMove.destinationRank)][fileToCol(chessMove.destinationFile)] = chessPiece;

    board[rankToRow(chessMove.sourceRank)][fileToCol(chessMove.sourceFile)] = {Color::EMPTY, Piece::EMPTY};
}

void ChessBoard::applyMoveForPawn(Color color, ChessMove chessMove)
{
    ChessPiece chessPiece = {color, chessMove.piece};

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
        if (chessPiece == board[index][col])
        {
            found = true;
            break;
        }
    }

    if (found)
    {
        board[index][col] = {Color::EMPTY, Piece::EMPTY};
        board[row][col] = chessPiece;
    }
}

void ChessBoard::applyMoveForKingSideCastling(Color color)
{
    switch (color)
    {
    case Color::WHITE:
        board[7][4] = {Color::EMPTY, Piece::EMPTY};
        board[7][7] = {Color::EMPTY, Piece::EMPTY};
        board[7][6] = {color, Piece::KING};
        board[7][5] = {color, Piece::ROOK};
        break;
    case Color::BLACK:
        board[0][4] = {Color::EMPTY, Piece::EMPTY};
        board[0][7] = {Color::EMPTY, Piece::EMPTY};
        board[0][6] = {color, Piece::KING};
        board[0][5] = {color, Piece::ROOK};
        break;
    default:
        break;
    }
}

void ChessBoard::applyMoveForQueenSideCastling(Color color)
{
    switch (color)
    {
    case Color::WHITE:
        board[7][4] = {Color::EMPTY, Piece::EMPTY};
        board[7][0] = {Color::EMPTY, Piece::EMPTY};
        board[7][2] = {color, Piece::KING};
        board[7][3] = {color, Piece::ROOK};
        break;
    case Color::BLACK:
        board[0][4] = {Color::EMPTY, Piece::EMPTY};
        board[0][0] = {Color::EMPTY, Piece::EMPTY};
        board[0][2] = {color, Piece::KING};
        board[0][3] = {color, Piece::ROOK};
        break;
    default:
        break;
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