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

} // namespace cSzd