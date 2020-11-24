#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/bitboard.h"

using namespace std;
using namespace cSzd;
using namespace testing;

// Not important Bitboard definitions (just for tests)
constexpr BitBoardState A1ActiveBB { 0x0000000000000001ULL };

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
    ASSERT_EQ(bb.setCellByName(c4), 1ULL << (f_c + r_4 * 8));
}