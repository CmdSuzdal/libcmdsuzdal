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

}   // namespace cSzd
