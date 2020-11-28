#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/bitboard.h"

using namespace std;
using namespace cSzd;
using namespace testing;

// --------------------------------------------------------
TEST(BBTester, AfterDefinitionBitboardIsEmpty)
{
    BitBoard bb;
    ASSERT_EQ(bb, BitBoard(EmptyBB));
}

TEST(BBTester, Cell_0_0_CorrespondToA1)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell(f_a, r_1), BitBoard(1ULL << a1));
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
    ASSERT_EQ(bb.setCell(f_h, r_4), BitBoard(1ULL << h4));
}

TEST(BBTester, CheckCellSetByName)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell(c4), 1ULL << (f_c + r_4 * 8));
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
    ASSERT_EQ(bb.setCell(h1), RanksBB[r_1]);
}

TEST(BBTester, Check2ndRank)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a2, b2, c2, d2, e2, f2, g2, h2}), RanksBB[r_2]);
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
    ASSERT_EQ(bb.setCell(c8), FilesBB[f_c]);
}

TEST(BBTester, Check7thFile)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({g1, g2, g3, g4, g5, g6, g7, g8}), FilesBB[f_g]);
}

TEST(BBTester, CheckLowerLeftUpperRightDiagonal)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a1, b2, c3, d4, e5, f6, g7, h8}), DiagonalBB);
}

TEST(BBTester, CheckLowerRightUpperLeftDiagonal)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a8, b7, c6, d5, e4, f3, g2, h1}), AntiDiagonalBB);
}

TEST(BBTester, CheckCenterOfBoard)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({d4, e4, d5, e5}), BoardCenterBB);
}

TEST(BBTester, CheckBothDiagonals)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a1, a8, b2, b7, c3, c6, d4, d5, e4, e5, f3, f6, g2, g7, h1, h8}), BothDiagonalsBB);
}

TEST(BBTester, CheckAllBlackCells)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a1, a3, a5, a7, b2, b4, b6, b8,
                          c1, c3, c5, c7, d2, d4, d6, d8,
                          e1, e3, e5, e7, f2, f4, f6, f8,
                          g1, g3, g5, g7, h2, h4, h6, h8}), AllBlackCellsBB);
}
TEST(BBTester, CheckAllWhiteCells)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell({a2, a4, a6, a8, b1, b3, b5, b7,
                          c2, c4, c6, c8, d1, d3, d5, d7,
                          e2, e4, e6, e8, f1, f3, f5, f7,
                          g2, g4, g6, g8, h1, h3, h5, h7}), AllWhiteCellsBB);
}

TEST(BBTester, IntersectionBetweenRank3AndFileFIsF3)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell(f3), RanksBB[r_3] & FilesBB[f_f]);
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
    BitBoard bb2 {bb1};
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

TEST(BBTester, ShiftWestOfEightOrMoreFilesReturnsEmptyBoard) {
    BitBoard bb(AllCellsBB);
    ASSERT_EQ(bb.shiftWest(8), EmptyBB);
}

TEST(BBTester, ShiftWestLastFourEastFilesReturnsFourWestFiles) {
    BitBoard bb(FilesBB[f_e] | FilesBB[f_f] | FilesBB[f_g] | FilesBB[f_h]);
    ASSERT_EQ(bb.shiftWest(4), FilesBB[f_a] | FilesBB[f_b] | FilesBB[f_c] | FilesBB[f_d]);
}

TEST(BBTester, ShiftEastOfEightOrMoreFilesReturnsEmptyBoard) {
    BitBoard bb(AllCellsBB);
    ASSERT_EQ(bb.shiftEast(111), EmptyBB);
}

TEST(BBTester, ShiftEastOfOneFileBlackBoardReturnsWhiteBoardWithFirstFileEmpty) {
    BitBoard bb(AllBlackCellsBB);
    ASSERT_EQ(bb.shiftEast(1), (AllWhiteCellsBB & (~FilesBB[f_a])));
}

TEST(BBTester, ShiftNorthOfEightOrMoreFilesReturnsEmptyBoard) {
  BitBoard bb(AllCellsBB);
  ASSERT_EQ(bb.shiftNorth(9), EmptyBB);
}

TEST(BBTester, ShiftBothDiagonalNorthOfThreeRanksReturnsAFunnyRoof) {
  constexpr BitBoardState FunnyRoofBB = {0x1818244281000000ULL};
  //  ...xx...
  //  ...xx...
  //  ..x..x..
  //  .x....x.
  //  x......x
  //  ........
  //  ........
  //  ........
  BitBoard bb(BothDiagonalsBB);
  ASSERT_EQ(bb.shiftNorth(3), FunnyRoofBB);
}

TEST(BBTester, ShiftRank5FileDCompoSouthOfFourRanksReturnsAFloorWithASpike) {
  constexpr BitBoardState FloorWithASpikeBB = {0x00000000080808FFULL};
  //  ........
  //  ........
  //  ........
  //  ........
  //  ...x....
  //  ...x....
  //  ...x....
  //  xxxxxxxx
  BitBoard bb(FilesBB[f_d] | RanksBB[r_5]);
  ASSERT_EQ(bb.shiftSouth(4), FloorWithASpikeBB);
}
