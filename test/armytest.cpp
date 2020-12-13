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
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(e1));
        ASSERT_EQ(army.pieces[King].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasEightPawnInTheSecondRank)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(army.pieces[Pawn].popCount(), 8);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasOneKingInE8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(e8));
        ASSERT_EQ(army.pieces[King].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasEightPawnInTheSeventhRank)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(army.pieces[Pawn].popCount(), 8);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasOneQueenInD1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Queen], BitBoard(d1));
        ASSERT_EQ(army.pieces[Queen].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasOneQueenInD8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Queen], BitBoard(d8));
        ASSERT_EQ(army.pieces[Queen].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoBishopsInC1AndF1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(army.pieces[Bishop].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoBishopsInC8AndF8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(army.pieces[Bishop].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoKnightsInB1AndG1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(army.pieces[Knight].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoKnightsInB8AndG8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(army.pieces[Knight].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoRooksInA1AndH1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(army.pieces[Rook].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoRooksInA8AndH8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(army.pieces[Rook].popCount(), 2);
    }
    TEST(ArmyTester, AfterDefaultInitThereIsNoArmy)
    {
        Army army {};
        ASSERT_EQ(army.color, InvalidArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Queen], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Rook], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Pawn], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[King].popCount(), 0);
        ASSERT_EQ(army.pieces[Queen].popCount(), 0);
        ASSERT_EQ(army.pieces[Bishop].popCount(), 0);
        ASSERT_EQ(army.pieces[Knight].popCount(), 0);
        ASSERT_EQ(army.pieces[Rook].popCount(), 0);
        ASSERT_EQ(army.pieces[Pawn].popCount(), 0);
    }

    // numPieces() method testing
    TEST(ArmyTester, AfterDefaultInitThereAreNoPieces)
    {
        Army a {};
        ASSERT_EQ(a.numPieces(), 0);
    }
    TEST(ArmyTester, AfterWhiteArmyInitThereAre16Pieces)
    {
        Army a { WhiteArmy };
        ASSERT_EQ(a.numPieces(), 16);
    }
    TEST(ArmyTester, AfterBlackArmyInitThereAre16Pieces)
    {
        Army a { BlackArmy };
        ASSERT_EQ(a.numPieces(), 16);
    }

    // ------------------------------------------------------------------------
    // Controlled Cells Tests
    TEST(ArmyTester, ChecksCellsControlledByWhiteKingInE5)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[King] = BitBoard{e5};
        ASSERT_EQ(a.controlledCells(), BitBoard({d4, e4, f4, d5, f5, d6, e6, f6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKingInG7)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[King] = BitBoard{g7};
        ASSERT_EQ(a.controlledCells(), BitBoard({f6, g6, h6, f7, h7, f8, g8, h8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKingInA1)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[King] = BitBoard{a1};
        ASSERT_EQ(a.controlledCells(), BitBoard({b1, a2, b2}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKingInH8)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[King] = BitBoard{h8};
        ASSERT_EQ(a.controlledCells(), BitBoard({g7, h7, g8}));
    }

} // namespace cSzd
