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
        PawnsSet pSet;
        ASSERT_TRUE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsValidIfOnePawnInA2)
    {
        PawnsSet pSet {a2};
        ASSERT_TRUE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank1)
    {
        PawnsSet pSet {b1};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank8)
    {
        PawnsSet pSet {e8};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsNotValidIfOnePawnInRank8WithOtherCorrectPawns)
    {
        PawnsSet pSet {{a2, d4, f6, g8}};
        ASSERT_FALSE(pSet.valid());
    }
    TEST(ArmyTester, PositionIsValidIfEightPawnsNotInBoundaryRanks)
    {
        PawnsSet pSet {{a2, b3, b5, d4, e5, f6, g2}};
        ASSERT_TRUE(pSet.valid());
    }

} // namespace cSzd
