#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/army.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    TEST(ArmyTester, AfterInitWhiteArmyHasOneKingInE1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.king, BitBoard(e1));
        ASSERT_EQ(army.king.popCount(), 1);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasEightPawnInTheSecondRank)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.pawns, BitBoard(RanksBB[r_2]));
        ASSERT_EQ(army.pawns.popCount(), 8);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasOneKingInE8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.king, BitBoard(e8));
        ASSERT_EQ(army.king.popCount(), 1);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasEightPawnInTheSeventhRank)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.pawns, BitBoard(RanksBB[r_7]));
        ASSERT_EQ(army.pawns.popCount(), 8);
    }
    TEST(ArmyTester, AfterDefaultInitArmyIsTheWhiteArmy)
    {
        Army army {};
        ASSERT_EQ(army.king, BitBoard(e1));
        ASSERT_EQ(army.pawns, BitBoard(RanksBB[r_2]));
        ASSERT_EQ(army.king.popCount(), 1);
        ASSERT_EQ(army.pawns.popCount(), 8);
    }


} // namespace cSzd
