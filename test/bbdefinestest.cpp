#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/bbdefines.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    TEST(BBDefinesTester, CellToRankAndFileConversionTests)
    {
        ASSERT_EQ(file(f2), f_f);
        ASSERT_EQ(rank(f2), r_2);
        ASSERT_EQ(file(a3), f_a);
        ASSERT_EQ(rank(a3), r_3);
        ASSERT_EQ(file(c7), f_c);
        ASSERT_EQ(rank(c7), r_7);
        ASSERT_EQ(file(h8), f_h);
        ASSERT_EQ(rank(h8), r_8);
        pair<File, Rank> c;
        c = coords(b5);
        ASSERT_EQ(c.first, f_b);
        ASSERT_EQ(c.second, r_5);
        c = coords(e1);
        ASSERT_EQ(c.first, f_e);
        ASSERT_EQ(c.second, r_1);
    }

    TEST(BBDefinesTester, NeighboursCellsOfD4AreComputedCorrectly)
    {
        ASSERT_EQ(w(d4), c4);
        ASSERT_EQ(nw(d4), c5);
        ASSERT_EQ(n(d4), d5);
        ASSERT_EQ(ne(d4), e5);
        ASSERT_EQ(e(d4), e4);
        ASSERT_EQ(se(d4), e3);
        ASSERT_EQ(s(d4), d3);
        ASSERT_EQ(sw(d4), c3);
    }

    TEST(BBDefinesTester, NeighboursCellsOfB7AreComputedCorrectly)
    {
        ASSERT_EQ(w(b7), a7);
        ASSERT_EQ(nw(b7), a8);
        ASSERT_EQ(n(b7), b8);
        ASSERT_EQ(ne(b7), c8);
        ASSERT_EQ(e(b7), c7);
        ASSERT_EQ(se(b7), c6);
        ASSERT_EQ(s(b7), b6);
        ASSERT_EQ(sw(b7), a6);
    }

    TEST(BBDefinesTester, NeighboursCellsOfA1AreComputedCorrectly)
    {
        ASSERT_EQ(w(a1), InvalidCell);
        ASSERT_EQ(nw(a1), InvalidCell);
        ASSERT_EQ(n(a1), a2);
        ASSERT_EQ(ne(a1), b2);
        ASSERT_EQ(e(a1), b1);
        ASSERT_EQ(se(a1), InvalidCell);
        ASSERT_EQ(s(a1), InvalidCell);
        ASSERT_EQ(sw(a1), InvalidCell);
    }

    TEST(BBDefinesTester, NeighboursCellsOfH3AreComputedCorrectly)
    {
        ASSERT_EQ(w(h3), g3);
        ASSERT_EQ(nw(h3), g4);
        ASSERT_EQ(n(h3), h4);
        ASSERT_EQ(ne(h3), InvalidCell);
        ASSERT_EQ(e(h3), InvalidCell);
        ASSERT_EQ(se(h3), InvalidCell);
        ASSERT_EQ(s(h3), h2);
        ASSERT_EQ(sw(h3), g2);
    }

    TEST(BBDefinesTester, CellToDiagonalsConversionTests)
    {
        ASSERT_EQ(diag(f2), d_11);
        ASSERT_EQ(antiDiag(f2), a_6);
        ASSERT_EQ(diag(a3), d_5);
        ASSERT_EQ(antiDiag(a3), a_2);
        ASSERT_EQ(diag(c7), d_3);
        ASSERT_EQ(antiDiag(c7), a_8);
        ASSERT_EQ(diag(h8), d_7);
        ASSERT_EQ(antiDiag(h8), a_14);
        pair<Diagonal, AntiDiagonal> diags;
        diags = diagonals(b5);
        ASSERT_EQ(diags.first, d_4);
        ASSERT_EQ(diags.second, a_5);
        diags = diagonals(e1);
        ASSERT_EQ(diags.first, d_11);
        ASSERT_EQ(diags.second, a_4);
    }

    // Tests for calcCellAfterSteps methods
    TEST(BBDefinesTester, calcCellAfterStepsTest)
    {
        ASSERT_EQ(calcCellAfterSteps(a1,  5,  0), a6);
        ASSERT_EQ(calcCellAfterSteps(a1,  0,  5), f1);

        ASSERT_EQ(calcCellAfterSteps(d4,  2,  1), e6);
        ASSERT_EQ(calcCellAfterSteps(d4,  1,  2), f5);
        ASSERT_EQ(calcCellAfterSteps(d4, -1,  2), f3);
        ASSERT_EQ(calcCellAfterSteps(d4, -2,  1), e2);
        ASSERT_EQ(calcCellAfterSteps(d4, -2, -1), c2);
        ASSERT_EQ(calcCellAfterSteps(d4, -1, -2), b3);
        ASSERT_EQ(calcCellAfterSteps(d4,  1, -2), b5);
        ASSERT_EQ(calcCellAfterSteps(d4,  2, -1), c6);

        ASSERT_EQ(calcCellAfterSteps(c2,  6, -2), a8);
        ASSERT_EQ(calcCellAfterSteps(c2,  1, -3), InvalidCell);
        ASSERT_EQ(calcCellAfterSteps(b7,  1,  3), e8);
        ASSERT_EQ(calcCellAfterSteps(b7,  2, -1), InvalidCell);
        ASSERT_EQ(calcCellAfterSteps(f5,  3,  2), h8);
        ASSERT_EQ(calcCellAfterSteps(f5,  1,  3), InvalidCell);
        ASSERT_EQ(calcCellAfterSteps(d2,  -1,  -3), a1);
        ASSERT_EQ(calcCellAfterSteps(d2,  -2,  -1), InvalidCell);
    }

    // File+Rank to Cell method (toCell())
    TEST(BBTester, chechFileRankToCellMethod)
    {
        ASSERT_EQ(toCell(f_a, r_1), a1);
        ASSERT_EQ(toCell(f_b, r_5), b5);
        ASSERT_EQ(toCell(f_c, r_2), c2);
        ASSERT_EQ(toCell(f_d, r_8), d8);
        ASSERT_EQ(toCell(f_e, r_7), e7);
        ASSERT_EQ(toCell(f_f, r_4), f4);
        ASSERT_EQ(toCell(f_g, r_3), g3);
        ASSERT_EQ(toCell(f_h, r_6), h6);
    }


}