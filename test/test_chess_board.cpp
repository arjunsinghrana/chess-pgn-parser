#include <gtest/gtest.h>

#include <filesystem>
#include <iostream>

#include "../src/chessBoard.h"
#include "../src/utils.h"

using namespace std;

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

TEST(ChessBoardTest, EnPassant) {
    
    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / "../../test/pgn/captures" / "pawn_en_passant.pgn";

    // Concatenate all chess moves into a single string
    const string concatenatedChessMoves = Utils::parseFileAndConcatenateChessMoves(filePath.string());

    // Convert string containing moves into vector of Chess Turns
    const vector<ChessTurn> turns = Utils::parseChessMoves(concatenatedChessMoves);

    ChessBoard board;
    for (const auto& turn : turns)
    {
        board.applyTurn(turn);
    }

    stringstream ss;
    ss << "bR|bN|bB|bQ|bK|bB|bN|bR|" << endl;
    ss << "bP|bP|bP|  |bP|bP|bP|  |" << endl;
    ss << "  |  |  |wP|  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |bP|" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "wP|wP|wP|wP|  |wP|wP|wP|" << endl;
    ss << "wR|wN|wB|wQ|wK|wB|wN|wR|" << endl;
    ss << endl;

    EXPECT_EQ(board.toString(), ss.str());
}

TEST(ChessBoardTest, FischerSpassky) {

    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / "../../test/pgn/games" / "fischer_spassky_game.pgn";

    // Concatenate all chess moves into a single string
    const string concatenatedChessMoves = Utils::parseFileAndConcatenateChessMoves(filePath.string());

    // Convert string containing moves into vector of Chess Turns
    const vector<ChessTurn> turns = Utils::parseChessMoves(concatenatedChessMoves);

    ChessBoard board;

    for (const auto& turn : turns)
    {
        board.applyTurn(turn);
    }

    stringstream ss;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << "  |  |  |  |wR|  |bP|  |" << endl;
    ss << "  |  |bK|  |  |  |bP|  |" << endl;
    ss << "  |bP|  |  |  |  |wP|  |" << endl;
    ss << "  |wP|  |bB|  |wP|  |  |" << endl;
    ss << "  |  |  |wK|  |bN|  |  |" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << endl;

    EXPECT_EQ(board.toString(), ss.str());
}

TEST(ChessBoardTest, KorchnoiSpassky) {

    filesystem::path currentDir = filesystem::current_path();
    filesystem::path filePath = currentDir / "../../test/pgn/games" / "korchnoi_spassky_game.pgn";

    // Concatenate all chess moves into a single string
    const string concatenatedChessMoves = Utils::parseFileAndConcatenateChessMoves(filePath.string());

    // Convert string containing moves into vector of Chess Turns
    const vector<ChessTurn> turns = Utils::parseChessMoves(concatenatedChessMoves);

    ChessBoard board;

    for (const auto& turn : turns)
    {
        board.applyTurn(turn);
    }

    stringstream ss;
    ss << "  |  |  |bQ|  |  |bK|  |" << endl;
    ss << "  |  |  |  |  |bR|wP|  |" << endl;
    ss << "  |  |  |  |  |  |wR|  |" << endl;
    ss << "  |  |  |  |wQ|  |  |  |" << endl;
    ss << "  |  |  |  |wP|  |  |bP|" << endl;
    ss << "  |  |  |  |  |  |  |wP|" << endl;
    ss << "  |  |  |  |  |  |wP|wK|" << endl;
    ss << "  |  |  |  |  |  |  |  |" << endl;
    ss << endl;

    EXPECT_EQ(board.toString(), ss.str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
