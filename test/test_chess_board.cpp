#include <gtest/gtest.h>
#include <iostream>

#include "../src/chessBoard.h"

TEST(ChessBoardTest, InitialiseBoard) {
    ChessBoard board;

    stringstream ss;
    ss << "bR|bN|bB|bQ|bK|bB|bN|bR|" << endl;
    ss << "bP|bP|bP|bP|bP|bP|bP|bP|" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "wP|wP|wP|wP|wP|wP|wP|wP|" << endl;
    ss << "wR|wN|wB|wQ|wK|wB|wN|wR|" << endl;
    ss << endl;

    ASSERT_EQ(board.toString(), ss.str());
}

TEST(ChessBoardTest, MovePawns) {
    ChessMove whiteMove;
    whiteMove.piece = Piece::PAWN;
    whiteMove.destinationFile = 'e';
    whiteMove.destinationRank = '4';

    ChessMove blackMove;
    blackMove.piece = Piece::PAWN;
    blackMove.destinationFile = 'f';
    blackMove.destinationRank = '5';

    ChessTurn turn(1, whiteMove, blackMove);

    ChessBoard board;
    board.applyTurn(turn);

    stringstream ss;
    ss << "bR|bN|bB|bQ|bK|bB|bN|bR|" << endl;
    ss << "bP|bP|bP|bP|bP|  |bP|bP|" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |bP|  |  |" << endl;
    ss << "  |  |  |  |wP|  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "wP|wP|wP|wP|  |wP|wP|wP|" << endl;
    ss << "wR|wN|wB|wQ|wK|wB|wN|wR|" << endl;
    ss << endl;

    EXPECT_EQ(board.toString(), ss.str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
