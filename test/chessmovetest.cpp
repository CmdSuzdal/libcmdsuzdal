#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessmove.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    TEST(ChessMoveTester, DummyTest)
    {
        ASSERT_EQ(chessMove(Pawn, e2, e3), InvalidMove);
    }
}
