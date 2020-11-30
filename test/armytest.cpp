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
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank1)
    {
        PawnSet pSet {b1};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank8)
    {
        PawnSet pSet {e8};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank8WithOtherCorrectPawns)
    {
        PawnSet pSet {{a2, d4, f6, g8}};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsValidIfEightPawnsNotInBoundaryRanks)
    {
        PawnSet pSet {{a2, b3, b5, d4, e5, f6, g2}};
        ASSERT_TRUE(pSet.valid());
    }

} // namespace cSzd
