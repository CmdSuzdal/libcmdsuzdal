#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/bitboard.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    // --------------------------------------------------------
    TEST(BBTester, AfterDefinitionBitboardIsEmpty)
    {
        BitBoard bb;
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }
    // --------------------------------------------------------
    TEST(BBTester, AfterInitializationWithAnInvalidCellBitBoardIsEmpty)
    {
        BitBoard bb{InvalidCell};
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    // --------------------------------------------------------
    TEST(BBTester, AfterInitializationWithAnInvalidCellsArrayBitBoardIsEmpty)
    {
        BitBoard bb({InvalidCell, InvalidCell, InvalidCell});
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    // --------------------------------------------------------
    TEST(BBTester, AfterInitializationWithGoodAndInvalidCellsArrayBitBoardIsOK)
    {
        BitBoard bb({InvalidCell, e1, InvalidCell, f5, InvalidCell, h8});
        ASSERT_EQ(bb, BitBoard({e1, f5, h8}));
    }

    // --------------------------------------------------------
    TEST(BBTester, SetOfInvalidCellsHasNoImpactsOnBitBoard)
    {
        BitBoard bb;
        bb.setCell({InvalidCell, c7, InvalidCell, d5});
        bb.setCell(InvalidCell);
        bb.setCell(g2);
        ASSERT_EQ(bb, BitBoard({c7, d5, g2}));
    }

    TEST(BBTester, Cell_0_0_CorrespondToA1)
    {
        BitBoard bb;
        bb.setCell(f_a, r_1), BitBoard(1ULL << a1);
        ASSERT_EQ(bb, BitBoard(1ULL << a1));
    }

    TEST(BBTester, IfACellIsSetAndThenResetBitboardIsEmpty)
    {
        BitBoard bb;
        bb.setCell(f_a, r_1);
        bb.resetCell(f_a, r_1);
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    TEST(BBTester, Cell_3_7_CorrespondToH4)
    {
        BitBoard bb;
        bb.setCell(f_h, r_4), BitBoard(1ULL << h4);
        ASSERT_EQ(bb, BitBoard(1ULL << h4));
    }

    TEST(BBTester, IfASingleCellIsSetItCanBeObtainedBackByTheActiveCellMethod)
    {
        BitBoard bb{g2};
        ASSERT_EQ(bb.activeCell(), g2);
    }
    TEST(BBTester, IfMoreThanACellIsSetTheActiveCellMethodReturnsInvalidCell)
    {
        BitBoard bb({g2, h4});
        ASSERT_EQ(bb.activeCell(), InvalidCell);
    }

    TEST(BBTester, CheckCellSetByName)
    {
        BitBoard bb;
        bb.setCell(c4);
        ASSERT_EQ(bb, BitBoard(1ULL << (f_c + r_4 * 8)));
    }

    TEST(BBTester, Check1stRank)
    {
        BitBoard bb;
        bb.setCell(a1);
        bb.setCell(b1);
        bb.setCell(c1);
        bb.setCell(d1);
        bb.setCell(e1);
        bb.setCell(f1);
        bb.setCell(g1);
        bb.setCell(h1);
        ASSERT_EQ(bb, BitBoard(RanksBB[r_1]));
    }

    TEST(BBTester, Check2ndRank)
    {
        BitBoard bb;
        bb.setCell({a2, b2, c2, d2, e2, f2, g2, h2});
        ASSERT_EQ(bb, BitBoard(RanksBB[r_2]));
    }

    TEST(BBTester, Check3rdFile)
    {
        BitBoard bb;
        bb.setCell(c1);
        bb.setCell(c2);
        bb.setCell(c3);
        bb.setCell(c4);
        bb.setCell(c5);
        bb.setCell(c6);
        bb.setCell(c7);
        bb.setCell(c8);
        ASSERT_EQ(bb, BitBoard(FilesBB[f_c]));
    }

    TEST(BBTester, Check7thFile)
    {
        BitBoard bb;
        bb.setCell({g1, g2, g3, g4, g5, g6, g7, g8});
        ASSERT_EQ(bb, BitBoard(FilesBB[f_g]));
    }

    TEST(BBTester, CheckLowerLeftUpperRightDiagonal)
    {
        BitBoard bb;
        bb.setCell({a1, b2, c3, d4, e5, f6, g7, h8});
        ASSERT_EQ(bb, BitBoard(DiagonalBB));
    }

    TEST(BBTester, CheckLowerRightUpperLeftDiagonal)
    {
        BitBoard bb;
        bb.setCell({a8, b7, c6, d5, e4, f3, g2, h1});
        ASSERT_EQ(bb, BitBoard(AntiDiagonalBB));
    }

    TEST(BBTester, CheckCenterOfBoard)
    {
        BitBoard bb;
        bb.setCell({d4, e4, d5, e5});
        ASSERT_EQ(bb, BitBoard(BoardCenterBB));
    }

    TEST(BBTester, CheckBothDiagonals)
    {
        BitBoard bb;
        bb.setCell({a1, a8, b2, b7, c3, c6, d4, d5, e4, e5, f3, f6, g2, g7, h1, h8});
        ASSERT_EQ(bb, BitBoard(BothDiagonalsBB));
    }

    TEST(BBTester, CheckAllBlackCells)
    {
        BitBoard bb;
        bb.setCell({a1, a3, a5, a7, b2, b4, b6, b8,
                    c1, c3, c5, c7, d2, d4, d6, d8,
                    e1, e3, e5, e7, f2, f4, f6, f8,
                    g1, g3, g5, g7, h2, h4, h6, h8});
        ASSERT_EQ(bb, BitBoard(AllBlackCellsBB));
    }
    TEST(BBTester, CheckAllWhiteCells)
    {
        BitBoard bb;
        bb.setCell({a2, a4, a6, a8, b1, b3, b5, b7,
                    c2, c4, c6, c8, d1, d3, d5, d7,
                    e2, e4, e6, e8, f1, f3, f5, f7,
                    g2, g4, g6, g8, h1, h3, h5, h7});
        ASSERT_EQ(bb, BitBoard(AllWhiteCellsBB));
    }

    TEST(BBTester, IntersectionBetweenRank3AndFileFIsF3)
    {
        BitBoard bb;
        bb.setCell(f3);
        ASSERT_EQ(bb, BitBoard(RanksBB[r_3] & FilesBB[f_f]));
    }

    TEST(BBTester, AddAllBlackAndWhiteCellsToObtainBitboardFull)
    {
        BitBoard bb(AllBlackCellsBB);
        ASSERT_EQ(bb | BitBoard(AllWhiteCellsBB), BitBoard(AllCellsBB));
    }

    TEST(BBTester, RemoveWhiteCellsToFullBoardToObtainBlackCellsOnly)
    {
        BitBoard bb(AllCellsBB);
        // This is a not clear way to remove cells, but it works...
        ASSERT_EQ(bb & BitBoard(~AllWhiteCellsBB), BitBoard(AllBlackCellsBB));
    }

    TEST(BBTester, TestCopyConstructor)
    {
        BitBoard bb1(AllBlackCellsBB);
        ASSERT_EQ(bb1, BitBoard(AllBlackCellsBB));
        BitBoard bb2{bb1};
        ASSERT_EQ(bb2, BitBoard(AllBlackCellsBB));
    }

    TEST(BBTester, TestAssignmentOperator)
    {
        BitBoard bb1(AllBlackCellsBB);
        ASSERT_EQ(bb1, BitBoard(AllBlackCellsBB));
        BitBoard bb2;
        bb2 = bb1;
        ASSERT_EQ(bb2, BitBoard(AllBlackCellsBB));
    }

    TEST(BBTester, TestEqualityOperatorOnEmptyBitBoards)
    {
        BitBoard bb1, bb2;
        ASSERT_EQ(bb1, bb2);
    }

    TEST(BBTester, TestEqualityOperatorOnGenericBitBoards)
    {
        BitBoard bb1(AllBlackCellsBB), bb2(AllBlackCellsBB);
        ASSERT_EQ(bb1, bb2);
    }

    TEST(BBTester, UnionOperator_TestThatUnionOfBlackAndWhiteSquaresGiveAllBoard)
    {
        BitBoard bbBlack(AllBlackCellsBB);
        BitBoard bbWhite(AllWhiteCellsBB);
        auto bbAll = bbBlack | bbWhite;
        ASSERT_EQ(bbAll, BitBoard(AllCellsBB));
    }

    TEST(BBTester, IntersectionOperator_TestThatIntersectionOfFilesDandEwithRanks4and5GiveTheBoardCenter)
    {
        BitBoard centerFiles(FilesBB[f_d] | FilesBB[f_e]);
        BitBoard centerRanks(RanksBB[r_4] | RanksBB[r_5]);
        auto bbCenter = centerFiles & centerRanks;
        ASSERT_EQ(bbCenter, BitBoard(BoardCenterBB));
    }

    TEST(BBTester, IntersectionOfDifferentSetOfRanksGiveTheEmptyBoard)
    {
        BitBoard whiteCamp(RanksBB[r_1] | RanksBB[r_2]);
        BitBoard blackCamp(RanksBB[r_7] | RanksBB[r_8]);
        BitBoard bbEmpty = whiteCamp & blackCamp;
        ASSERT_EQ(bbEmpty, BitBoard(EmptyBB));
    }

    TEST(BBTester, TestXorOperator)
    {
        BitBoard diags(BothDiagonalsBB);
        BitBoard diagsNoCenter({a1, h1, b2, g2, c3, f3, c6, f6, b7, g7, a8, h8});
        ASSERT_EQ(diags ^ diagsNoCenter, BitBoard(BoardCenterBB));
    }

    TEST(BBTester, TestXorOperatorWithBitBoardState)
    {
        BitBoard whiteCamp(RanksBB[r_1] | RanksBB[r_2]);
        BitBoard blackCamp(RanksBB[r_7] | RanksBB[r_8]);
        ASSERT_EQ(whiteCamp ^ BitBoard((RanksBB[r_7] | RanksBB[r_8])), whiteCamp | blackCamp);
    }

    TEST(BBTester, TestClearBoardOperation)
    {
        BitBoard bb(AllBlackCellsBB);
        bb.clear();
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    TEST(BBTester, TestCopyOperator)
    {
        BitBoard bb(AllBlackCellsBB);
        BitBoard bb2 = bb;
        ASSERT_EQ(bb2, BitBoard(AllBlackCellsBB));
    }

    TEST(BBTester, ShiftWestOfEightOrMoreFilesReturnsEmptyBoard)
    {
        BitBoard bb(AllCellsBB);
        bb.shiftWest(8);
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    TEST(BBTester, ShiftWestLastFourEastFilesReturnsFourWestFiles)
    {
        BitBoard bb(FilesBB[f_e] | FilesBB[f_f] | FilesBB[f_g] | FilesBB[f_h]);
        bb.shiftWest(4);
        ASSERT_EQ(bb, BitBoard(FilesBB[f_a] | FilesBB[f_b] | FilesBB[f_c] | FilesBB[f_d]));
    }

    TEST(BBTester, ShiftEastOfEightOrMoreFilesReturnsEmptyBoard)
    {
        BitBoard bb(AllCellsBB);
        bb.shiftEast(111);
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    TEST(BBTester, ShiftEastOfOneFileBlackBoardReturnsWhiteBoardWithFirstFileEmpty)
    {
        BitBoard bb(AllBlackCellsBB);
        bb.shiftEast(1);
        ASSERT_EQ(bb, BitBoard(AllWhiteCellsBB & (~FilesBB[f_a])));
    }

    TEST(BBTester, ShiftNorthOfEightOrMoreFilesReturnsEmptyBoard)
    {
        BitBoard bb(AllCellsBB);
        bb.shiftNorth(9);
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    TEST(BBTester, ShiftBothDiagonalNorthOfThreeRanksReturnsAFunnyRoof)
    {
        //  ...xx... = 18
        //  ...xx... = 18
        //  ..x..x.. = 24
        //  .x....x. = 42
        //  x......x = 81
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        constexpr BitBoardState FunnyRoofBB = {0x1818244281000000ULL};
        BitBoard bb(BothDiagonalsBB);
        bb.shiftNorth(3);
        ASSERT_EQ(bb, BitBoard(FunnyRoofBB));
    }

    TEST(BBTester, ShiftRank5FileDCompoSouthOfFourRanksReturnsAFloorWithASpike)
    {
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ...x.... = 08
        //  ...x.... = 08
        //  ...x.... = 08
        //  xxxxxxxx = FF
        constexpr BitBoardState FloorWithASpikeBB = {0x00000000080808FFULL};
        BitBoard bb(FilesBB[f_d] | RanksBB[r_5]);
        bb.shiftSouth(4);
        ASSERT_EQ(bb, BitBoard(FloorWithASpikeBB));
    }
    TEST(BBTester, ShiftSouthOfMoreThan7RanksReturnsEmptyBoard)
    {
        BitBoard bb(AllCellsBB);
        bb.shiftSouth(8);
        ASSERT_EQ(bb, BitBoard(EmptyBB));
    }

    // Evaluation of neighbours
    TEST(BBTester, NeighboursMaskOfEmptyBitBoardIsEmpty)
    {
        BitBoard bb;
        ASSERT_EQ(bb.neighbourCells(), BitBoard(EmptyBB));
    }
    TEST(BBTester, NeighboursMaskOfWhiteCellsIsAFullBoard)
    {
        BitBoard bb {AllWhiteCellsBB};
        ASSERT_EQ(bb.neighbourCells(), BitBoard(AllCellsBB));
    }
    TEST(BBTester, NeighboursMaskOfE5IsComputedCorrectly)
    {
        //  ........ = 00
        //  ........ = 00
        //  ...xxx.. = 38
        //  ...x.x.. = 28
        //  ...xxx.. = 38
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        BitBoard bb(e5);
        BitBoardState n = 0x0000382838000000ULL;
        ASSERT_EQ(bb.neighbourCells(), BitBoard(n));
    }
    TEST(BBTester, NeighboursMaskOfB2IsComputedCorrectly)
    {
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  xxx..... = 07
        //  x.x..... = 05
        //  xxx..... = 07
        BitBoard bb(b2);
        BitBoardState n = 0x0000000000070507ULL;
        ASSERT_EQ(bb.neighbourCells(), BitBoard(n));
    }
    TEST(BBTester, NeighboursMaskOfH6IsComputedCorrectly)
    {
        //  ........ = 00
        //  ......xx = C0
        //  ......x. = 40
        //  ......xx = C0
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        BitBoard bb(h6);
        BitBoardState n = 0x00C040C000000000ULL;
        ASSERT_EQ(bb.neighbourCells(), BitBoard(n));
    }
    TEST(BBTester, NeighboursMaskOfH1IsComputedCorrectly)
    {
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ........ = 00
        //  ......xx = C0
        //  ......x. = 40
        BitBoard bb(h1);
        BitBoardState n = 0x000000000000C040ULL;
        ASSERT_EQ(bb.neighbourCells(), BitBoard(n));
    }

    // population count calculation tests
    TEST(BBTester, OnlyA1PopulationCountIs1)
    {
        BitBoard bb {a1};
        ASSERT_EQ(bb.popCount(), 1);
    }
    TEST(BBTester, BoardCenterPopulationCountIs4)
    {
        BitBoard bb(BoardCenterBB);
        ASSERT_EQ(bb.popCount(), 4);
    }
    TEST(BBTester, SingleRankPopulationCountIs8)
    {
        BitBoard bb(RanksBB[r_3]);
        ASSERT_EQ(bb.popCount(), 8);
    }
    TEST(BBTester, SingleFilePopulationCountIs8)
    {
        BitBoard bb(FilesBB[f_h]);
        ASSERT_EQ(bb.popCount(), 8);
    }
    TEST(BBTester, BoardDiagonalPopulationCountIs8)
    {
        BitBoard bb(DiagsBB[d_7]);
        ASSERT_EQ(bb.popCount(), 8);
    }
    TEST(BBTester, QueenMaskOfC3PopulationCountIs24)
    {
        BitBoard bb(queenMask(c3));
        ASSERT_EQ(bb.popCount(), 26);
    }
    TEST(BBTester, WhiteCellsPopulationCountIs32)
    {
        BitBoard bb(AllWhiteCellsBB);
        ASSERT_EQ(bb.popCount(), 32);
    }
    TEST(BBTester, FullBoardPopulationCountIs64)
    {
        BitBoard bb(AllCellsBB);
        ASSERT_EQ(bb.popCount(), 64);
    }

    // Check funtions tests
    TEST(BBTester, IfCellE3IsActiveThereAreActiveCellsInRank3AndFileE)
    {
        BitBoard bb {e3};
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_3]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_e]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_1]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_2]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_4]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_5]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_6]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_7]));
        ASSERT_FALSE(bb & BitBoard(RanksBB[r_8]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_a]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_b]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_c]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_d]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_f]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_g]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_h]));
    }

    TEST(BBTester, DiagonalTouchAllRanskAndFiles)
    {
        BitBoard bb {DiagonalBB};
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_1]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_2]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_3]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_4]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_5]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_6]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_7]));
        ASSERT_TRUE(bb & BitBoard(RanksBB[r_8]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_a]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_b]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_c]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_d]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_e]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_f]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_g]));
        ASSERT_TRUE(bb & BitBoard(FilesBB[f_h]));
    }

    TEST(BBTester, DiagonalsMaskOfA4DoesNotTouchLastThreeFiles)
    {
        BitBoard bb {diagonalsMask(a4)};
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_1]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_2]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_3]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_4]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_5]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_6]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_7]));
        ASSERT_TRUE (bb & BitBoard(RanksBB[r_8]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_a]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_b]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_c]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_d]));
        ASSERT_TRUE (bb & BitBoard(FilesBB[f_e]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_f]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_g]));
        ASSERT_FALSE(bb & BitBoard(FilesBB[f_h]));
    }

    // Evaluations of file/rank/diagonals evaluation
    TEST(BBTester, DiagonalsBitBoardOfEmptyBoardReturnsEmpty)
    {
        BitBoard bb;
        ASSERT_EQ(bb.diagonalsCells(), BitBoard(EmptyBB));
    }
    TEST(BBTester, DiagonalsBitBoardOfFullBoardReturnsFullBoard)
    {
        BitBoard bb {AllCellsBB};
        ASSERT_EQ(bb.diagonalsCells(), BitBoard(AllCellsBB));
    }
    TEST(BBTester, evalDiagonalOfActiveCellInE4)
    {
        BitBoard bb {e4};
        ASSERT_EQ(bb.diagonalsCells(), BitBoard({b1, h1, c2, g2, d3, f3, d5, f5, c6, g6, b7, h7, a8}));
    }
    TEST(BBTester, evalFileRankOfActiveCellInE4)
    {
        BitBoard bb {e4};
        ASSERT_EQ(bb.fileRankCells(), BitBoard({e1, e2, e3, a4, b4, c4, d4, f4, g4, h4, e5, e6, e7, e8}));
    }
    TEST(BBTester, evalFileRankDiagonalsOfActiveCellInE4)
    {
        BitBoard bb {e4};
        ASSERT_EQ(bb.fileRankDiagonalsCells(), BitBoard({b1, h1, c2, g2, d3, f3, d5, f5, c6, g6, b7, h7, a8,
                                                e1, e2, e3, a4, b4, c4, d4, f4, g4, h4, e5, e6, e7, e8}));
    }
    TEST(BBTester, evalDiagonalsOfActiveCellInC3)
    {
        BitBoard bb {c3};
        ASSERT_EQ(bb.diagonalsCells(), BitBoard({a1, e1, b2, d2, b4, d4, a5, e5, f6, g7, h8}));
    }
    TEST(BBTester, evalDiagonalsOfActiveCellInF5)
    {
        BitBoard bb {f5};
        ASSERT_EQ(bb.diagonalsCells(), BitBoard({b1, c2, d3, h3, e4, g4, e6, g6, d7, h7, c8}));
    }
    TEST(BBTester, evalDiagonalsOfActiveCellsInC3AndF5)
    {
        BitBoard bb ({c3, f5});
        ASSERT_EQ(bb.diagonalsCells(), BitBoard({a1, b1, e1, b2, c2, d2, d3, h3, b4, d4, e4, g4,
                                                 a5, e5, e6, f6, g6, d7, g7, h7, c8, h8}));
    }
    TEST(BBTester, evalFilesRanksOfActiveCellsInC3AndE5)
    {
        BitBoard bb ({c3, f5});
        ASSERT_EQ(bb.fileRankCells(), BitBoard({c1, f1, c2, f2, a3, b3, d3, e3, f3, g3, h3, c4, f4,
                                                a5, b5, c5, d5, e5, g5, h5, c6, f6, c7, f7, c8, f8}));
    }
    TEST(BBTester, evalFilesRanksDiagonalsOfActiveCellInC3AndE5)
    {
        BitBoard bb ({c3, f5});
        ASSERT_EQ(bb.fileRankDiagonalsCells(), BitBoard({a1, b1, e1, b2, c2, d2, d3, h3, b4, d4, e4, g4,
                                                a5, e5, e6, f6, g6, d7, g7, h7, c8, h8, c1, f1,
                                                f2, a3, b3, e3, f3, g3, c4, f4, b5, c5, d5, g5,
                                                h5, c6, c7, f7, f8}));
    }

    // isActive() methods
    TEST(BBTester, checkActiveCellsWhenTheWholeRank2IsActive)
    {
        BitBoard bb(RanksBB[r_2]);
        ASSERT_TRUE(bb.isActive(a2));
        ASSERT_TRUE(bb.isActive(b2));
        ASSERT_TRUE(bb.isActive(c2));
        ASSERT_TRUE(bb.isActive(d2));
        ASSERT_TRUE(bb.isActive(e2));
        ASSERT_TRUE(bb.isActive(f2));
        ASSERT_TRUE(bb.isActive(g2));
        ASSERT_TRUE(bb.isActive(h2));
    }
    TEST(BBTester, checkActiveCellsWhenTheWholeFileDIsActive)
    {
        BitBoard bb(FilesBB[f_d]);
        ASSERT_TRUE(bb.isActive(d1));
        ASSERT_TRUE(bb.isActive(d2));
        ASSERT_TRUE(bb.isActive(d3));
        ASSERT_TRUE(bb.isActive(d4));
        ASSERT_TRUE(bb.isActive(d5));
        ASSERT_TRUE(bb.isActive(d6));
        ASSERT_TRUE(bb.isActive(d7));
        ASSERT_TRUE(bb.isActive(d8));
    }

    TEST(BBTester, checkActiveCellsWhenDiagonal10IsActive)
    {
        BitBoard bb(DiagsBB[d_10]);
        ASSERT_TRUE(bb.isActive(f_d, r_1));
        ASSERT_TRUE(bb.isActive(f_e, r_2));
        ASSERT_TRUE(bb.isActive(f_f, r_3));
        ASSERT_TRUE(bb.isActive(f_g, r_4));
        ASSERT_TRUE(bb.isActive(f_h, r_5));
    }

} // namespace cSzd
