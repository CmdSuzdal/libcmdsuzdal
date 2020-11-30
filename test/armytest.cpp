#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/army.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    // ---- King -------------------------------------------------------
    TEST(ArmyTester, PositionIsValidIfOneKingIsOnTheBBoardOnE1)
    {
        King k {e1};
        ASSERT_TRUE(k.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfNoKingIsOnTheBBoard)
    {
        King k;
        ASSERT_FALSE(k.valid());
    }

    // ---- Pawn set ---------------------------------------------------
    TEST(ArmyTester, PositionIsValidIfNoPawns)
    {
        PawnSet pSet;
        ASSERT_TRUE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsValidIfOnePawnInA2)
    {
        PawnSet pSet {a2};
        ASSERT_TRUE(pSet.valid());
    }


} // namespace cSzd
