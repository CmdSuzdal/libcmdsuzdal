#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/army.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    TEST(ArmyTester, AfterInitWithInvalidArmyThereIsNobody)
    {
        Army army { InvalidArmy };
        ASSERT_EQ(army.color, InvalidArmy);
        ASSERT_EQ(army.pieces[King].popCount(), 0);
        ASSERT_EQ(army.pieces[Queen].popCount(), 0);
        ASSERT_EQ(army.pieces[Rook].popCount(), 0);
        ASSERT_EQ(army.pieces[Bishop].popCount(), 0);
        ASSERT_EQ(army.pieces[Knight].popCount(), 0);
        ASSERT_EQ(army.pieces[Pawn].popCount(), 0);
    }
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
    // --- Controlled Cells Tests ---

    // King alone ---
    TEST(ArmyTester, ControlledCellsOfAnEmptyArmyIsEmpty)
    {
        Army a {};
        ASSERT_EQ(a.controlledCells(), BitBoard(EmptyBB));
    }

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

    // Pawns alone ---
    TEST(ArmyTester, ChecksCellsControlledByInitialRowOfWhitePawns)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({a2, b2, c2, d2, e2, f2, g2, h2});
        ASSERT_EQ(a.controlledCells(), BitBoard({a3, b3, c3, d3, e3, f3, g3, h3}));
    }
    TEST(ArmyTester, ChecksCellsControlledByInitialRowOfBlackPawns)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({a7, b7, c7, d7, e7, f7, g7, h7});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, b6, c6, d6, e6, f6, g6, h6}));
    }

    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns1)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({a4});
        ASSERT_EQ(a.controlledCells(), BitBoard({b5}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns2)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({a4});
        ASSERT_EQ(a.controlledCells(), BitBoard({b3}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns3)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({b5, h7});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, c6, g8}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns4)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({f6, h2});
        ASSERT_EQ(a.controlledCells(), BitBoard({e5, g5, g1}));
    }

    // Knights ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({b1, g1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a3, c3, d2, e2, f3, h3}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKnightsInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({b8, g8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, c6, d7, e7, f6, h6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInD4)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({d4});
        ASSERT_EQ(a.controlledCells(), BitBoard({e6, f5, f3, e2, c2, b3, b5, c6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInH8)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Knight] = BitBoard({h8});
        ASSERT_EQ(a.controlledCells(), BitBoard({f7, g6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsOnAllTheCellsOfTheDiagonal)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({a1, b2, c3, d4, e5, f6, g7, h8});
        ASSERT_EQ(a.controlledCells(), BitBoard(
            {b1, d1, a2, c2, e2, b3, d3, f3, a4, c4, e4, g4,
             b5, d5, f5, h5, c6, e6, g6, d7, f7, h7, e8, g8}));
    }

    // Bishops simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteBishopsAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Bishop] = BitBoard({c1, f1});
        ASSERT_EQ(a.controlledCells(), BitBoard({b2, d2, e2, g2, a3, d3, e3, h3, c4, f4, b5, g5, a6, h6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackBishopsAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({c8, f8});
        ASSERT_EQ(a.controlledCells(), BitBoard({b7, d7, e7, g7, a6, d6, e6, h6, c5, f5, b4, g4, a3, h3}));
    }

    // Rooks simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteRooksAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({a1, h1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, b1, c1, d1, e1, f1, g1, h1, a2, h2, a3, h3, a4, h4, a5, h5, a6, h6, a7, h7, a8, h8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackRookAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({a8, h8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, h1, a2, h2, a3, h3, a4, h4, a5, h5, a6, h6, a7, h7, a8, b8, c8, d8, e8, f8, g8, h8}));
    }

    // Queens simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteQueenAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Queen] = BitBoard({d1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, b1, c1, e1, f1, g1, h1, c2, d2, e2, b3, d3, f3, a4, d4, g4, d5, h5, d6, d7, d8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackQueenAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Queen] = BitBoard({d8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a8, b8, c8, e8, f8, g8, h8, c7, d7, e7, b6, d6, f6, a5, d5, g5, d4, h4, d3, d2, d1}));
    }

    // To manage complex case of controlled cells with interferences,
    // we need a function that returns the Bitboard with all the cells
    // occupied by the army. We firstly test this function
    TEST(ArmyTester, WhiteArmyInInitialPositionOccupyTheRanks1and2)
    {
        Army a { WhiteArmy };
        ASSERT_EQ(a.occupiedCells(), BitBoard(RanksBB[r_1] | RanksBB[r_2]));
    }
    TEST(ArmyTester, BlackArmyInInitialPositionOccupyTheRanks7and8)
    {
        Army a { BlackArmy };
        ASSERT_EQ(a.occupiedCells(), BitBoard(RanksBB[r_7] | RanksBB[r_8]));
    }

    // --- OCCUPIED CELLS COMPLEX CASES (with interference) ----------------------------------------
    // Rooks ---
    TEST(ArmyTester, CheckCellsControlledByRookInA1WithPawnInA2)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({a1});
        a.pieces[Pawn] = BitBoard({a2});
        ASSERT_EQ(a.rooksControlledCells(), BitBoard({b1, c1, d1, e1, f1, g1, h1, a2}));
    }
    TEST(ArmyTester, CheckCellsControlledByARookInD4SurroundedByPawns)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({d4});
        a.pieces[Pawn] = BitBoard({d3, c4, e4, d5});
        ASSERT_EQ(a.rooksControlledCells(), BitBoard({d3, c4, e4, d5}));
    }
    TEST(ArmyTester, CheckCellsControlledByRooksComplex1)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({d4, g7});
        a.pieces[Pawn] = BitBoard({d5});
        a.pieces[Knight] = BitBoard({g6});
        a.pieces[King] = BitBoard({f6});
        ASSERT_EQ(a.rooksControlledCells(), BitBoard({d1, d2, d3, a4, b4, c4, e4, f4, g4, h4, d5, g6, a7, b7, c7, d7, e7, f7, h7, g8}));
    }
    TEST(ArmyTester, CheckCellsControlledByRooksComplex2)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({c4, c5});
        ASSERT_EQ(a.rooksControlledCells(), BitBoard({c1, c2, c3, a4, b4, c4, d4, e4, f4, g4, h4, a5, b5, c5, d5, e5, f5, g5, h5, c6, c7, c8}));
    }

    // Bishops ---
    TEST(ArmyTester, CheckCellsControlledByBishopInH8WithPawnInG7)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({h8});
        a.pieces[Pawn] = BitBoard({g7});
        ASSERT_EQ(a.bishopsControlledCells(), BitBoard({g7}));
    }
    TEST(ArmyTester, CheckCellsControlledByBishopComplexCase1)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Bishop] = BitBoard({d4, g6});
        a.pieces[Pawn] = BitBoard({b2,c2,d2,e2,f2});
        a.pieces[King] = BitBoard({f6});
        ASSERT_EQ(a.bishopsControlledCells(), BitBoard({b2, c2, f2, c3, d3, e3, e4, c5, e5, f5, h5, b6, f6, a7, f7, h7, e8}));
    }
    TEST(ArmyTester, CheckCellsControlledByBishopComplexCase2)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({b5, g3});
        a.pieces[Pawn] = BitBoard({d3, d7});
        a.pieces[King] = BitBoard({e5});
        a.pieces[Queen] = BitBoard({f1});
        ASSERT_EQ(a.bishopsControlledCells(), BitBoard({e1, f2, h2, d3, a4, c4, f4, h4, e5, a6, c6, d7}));
    }


} // namespace cSzd
