#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessgame.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    TEST(ChessGameTester, AfterTheDefaultInitializationTheGameHasAChessBoardWithTheInitialPosition)
    {
        ChessGame cg;
        ASSERT_EQ(cg.board, ChessBoard());
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cg.board.sideToMove, WhiteArmy);
        ASSERT_EQ(cg.board.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cg.board.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cg.board.halfMoveClock, 0);
        ASSERT_EQ(cg.board.fullMoves, 1);
        ASSERT_TRUE(cg.board.isValid());
        ASSERT_FALSE(cg.board.isCheckMate());
        ASSERT_FALSE(cg.board.isStaleMate());
        ASSERT_FALSE(cg.board.isDrawnPosition());
        ASSERT_FALSE(cg.board.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessGameTester, AfterTheDefaultInitializationTheGameHasAFenRecordWithTheInitialPosition)
    {
        ChessGame cg;
        ASSERT_EQ(cg.initialPosition, FENRecord(FENInitialStandardPosition));
    }
    TEST(ChessGameTester, AfterTheDefaultInitializationThePossibleMovesAreComputedCorrectly)
    {
        ChessGame cg;
        ASSERT_EQ(cg.possibleMoves.size(), 20);
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, h3)) != cg.possibleMoves.end());

    }

} // namespace cSzd