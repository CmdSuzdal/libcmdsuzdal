#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/bitboard.h"

using namespace std;
using namespace cSzd;
using namespace testing;

// Not important Bitboard definitions (just for tests)
constexpr BitBoardState A1ActiveBB { 0x0000000000000001ULL };
constexpr BitBoardState Rank1BB    { 0x00000000000000FFULL};
constexpr BitBoardState RanksBB[]  {
    Rank1BB,
    Rank1BB << 8,
    Rank1BB << 16,
    Rank1BB << 24,
    Rank1BB << 32,
    Rank1BB << 40,
    Rank1BB << 48,
    Rank1BB << 56,
};
constexpr BitBoardState File1BB    { 0x0101010101010101ULL};
constexpr BitBoardState FilesBB[]  {
    File1BB,
    File1BB << 1,
    File1BB << 2,
    File1BB << 3,
    File1BB << 4,
    File1BB << 5,
    File1BB << 6,
    File1BB << 7,
};

constexpr BitBoardState DiagonalBB      { 0x8040201008040201ULL };
constexpr BitBoardState AntiDiagonalBB  { 0x0102040810204080ULL };
constexpr BitBoardState BothDiagonalsBB { DiagonalBB | AntiDiagonalBB };

constexpr BitBoardState AllCellsBB      { 0xFFFFFFFFFFFFFFFFULL };
constexpr BitBoardState AllBlackCellsBB { 0xAA55AA55AA55AA55ULL };
constexpr BitBoardState AllWhiteCellsBB { ~AllBlackCellsBB };

// ------
// center of board can be defined with the intersection of files d,e and ranks 4,5
constexpr BitBoardState BoardCenterBB  { (RanksBB[r_4] | RanksBB[r_5]) &
                                         (FilesBB[f_d] | FilesBB[f_e]) };
//constexpr BitBoardState BoardCenterBB  { 0x0000001818000000ULL };

// --------------------------------------------------------
TEST(BBTester, AfterDefinitionBitboardIsEmpty)
{
    BitBoard bb;
    ASSERT_EQ(bb.state(), EmptyBB);
}

TEST(BBTester, Cell_0_0_CorrespondToA1)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell(f_a, r_1), 1ULL << a1);
}

TEST(BBTester, IfACellIsSetAndThenResetBitboardIsEmpty)
{
    BitBoard bb;
    bb.setCell(f_a, r_1);
    ASSERT_EQ(bb.resetCell(f_a, r_1), EmptyBB);
}

TEST(BBTester, Cell_3_7_CorrespondToH4)
{
    BitBoard bb;
    ASSERT_EQ(bb.setCell(f_h, r_4), 1ULL << h4);
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
    BitBoard bb;
    bb.addCells(AllBlackCellsBB);
    ASSERT_EQ(bb.addCells(AllWhiteCellsBB), AllCellsBB);
}

TEST(BBTester, RemoveWhiteCellsToFullBoardToObtainBlackCellsOnly)
{
    BitBoard bb;
    bb.addCells(AllCellsBB);
    ASSERT_EQ(bb.delCells(AllWhiteCellsBB), AllBlackCellsBB);
}
