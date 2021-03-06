#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/randomengine.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    class ARandomEngine: public Test {
        public:
            RandomEngine rEng;
            static int fakeRandomizerFirstMove(int n) { return 0; }
            static int fakeRandomizerLastMove(int n) { return n-1; }
        };

    TEST_F(ARandomEngine, GenerateInvalidMoveInStaleMatePosition)
    {
        ASSERT_EQ(rEng.move(ChessBoard("8/8/8/3k4/8/8/5q2/7K w - - 0 1")), InvalidMove);
    }
    TEST_F(ARandomEngine, GenerateInvalidMoveInCheckMatePosition)
    {
        ASSERT_EQ(rEng.move(ChessBoard("R2k4/8/3K4/8/8/8/8/8 b - - 0 1")), InvalidMove);
    }

    TEST_F(ARandomEngine, GenerateTheOnlyValidMoveIfOnlyAMoveIsPossible)
    {
        ASSERT_EQ(rEng.move(ChessBoard("R2k4/8/2K5/8/8/8/8/8 b - - 0 1")), chessMove(King, d8, e7));
        ASSERT_EQ(rEng.move(ChessBoard("8/8/2P5/2b5/8/6k1/8/7K w - - 0 1")), chessMove(Pawn, c6, c7));
    }

    TEST_F(ARandomEngine, GenerateInvalidMoveInEmptyChessBoard)
    {
        ChessBoard cb {FENEmptyChessBoard};
        ASSERT_EQ(rEng.move(cb), InvalidMove);
    }

    TEST_F(ARandomEngine, GenerateARandomMoveInInitialChessBoardFirstWhiteMove)
    {
        ChessBoard cb {};
        // To perform the test, we use the fake randomizer that returns always the first move
        rEng.setRandomizer(fakeRandomizerFirstMove);
        ASSERT_EQ(rEng.move(cb), chessMove(Knight, b1, a3));
    }
    TEST_F(ARandomEngine, GenerateARandomMoveInInitialChessBoardFirstBlackMove)
    {
        ChessBoard cb {};
        cb.doMove(chessMove(Pawn, e2, e4));
        // To perform the test, we use the fake randomizer that returns always the last move
        rEng.setRandomizer(fakeRandomizerLastMove);
        ASSERT_EQ(rEng.move(cb), chessMove(Knight, g8, h6));
    }

}   // namespace cSzd
