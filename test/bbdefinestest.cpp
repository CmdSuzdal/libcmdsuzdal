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
    TEST(BBDefinesTester, chechFileRankToCellMethod)
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
    TEST(BBDefinesTester, CheckFileRankToCellMethodForInvalidValues)
    {
        ASSERT_EQ(toCell(InvalidFile, r_1), InvalidCell);
        ASSERT_EQ(toCell(f_a, InvalidRank), InvalidCell);
        ASSERT_EQ(toCell(static_cast<File>(8), r_1), InvalidCell);
        ASSERT_EQ(toCell(static_cast<File>(9), r_3), InvalidCell);
        ASSERT_EQ(toCell(static_cast<File>(42), r_7), InvalidCell);
        ASSERT_EQ(toCell(f_b, static_cast<Rank>(8)), InvalidCell);
        ASSERT_EQ(toCell(f_c, static_cast<Rank>(9)), InvalidCell);
        ASSERT_EQ(toCell(f_h, static_cast<Rank>(112345)), InvalidCell);
    }

    TEST(BBDefinesTester, FileMasksAreComputedCorrectly)
    {
        ASSERT_EQ(fileMask(a2), FilesBB[f_a]);
        ASSERT_EQ(fileMask(b1), FilesBB[f_b]);
        ASSERT_EQ(fileMask(c4), FilesBB[f_c]);
        ASSERT_EQ(fileMask(d3), FilesBB[f_d]);
        ASSERT_EQ(fileMask(e6), FilesBB[f_e]);
        ASSERT_EQ(fileMask(f5), FilesBB[f_f]);
        ASSERT_EQ(fileMask(g8), FilesBB[f_g]);
        ASSERT_EQ(fileMask(h7), FilesBB[f_h]);
    }

    TEST(BBDefinesTester, RankMasksAreComputedCorrectly)
    {
        ASSERT_EQ(rankMask(a6), RanksBB[r_6]);
        ASSERT_EQ(rankMask(b7), RanksBB[r_7]);
        ASSERT_EQ(rankMask(c8), RanksBB[r_8]);
        ASSERT_EQ(rankMask(d1), RanksBB[r_1]);
        ASSERT_EQ(rankMask(e2), RanksBB[r_2]);
        ASSERT_EQ(rankMask(f3), RanksBB[r_3]);
        ASSERT_EQ(rankMask(g4), RanksBB[r_4]);
        ASSERT_EQ(rankMask(h5), RanksBB[r_5]);
    }

    TEST(BBDefinesTester, FileRankMasksAreComputedCorrectly)
    {
        ASSERT_EQ(fileRankMask(a6), FilesBB[f_a] | RanksBB[r_6]);
        ASSERT_EQ(fileRankMask(b7), FilesBB[f_b] | RanksBB[r_7]);
        ASSERT_EQ(fileRankMask(c8), FilesBB[f_c] | RanksBB[r_8]);
        ASSERT_EQ(fileRankMask(d1), FilesBB[f_d] | RanksBB[r_1]);
        ASSERT_EQ(fileRankMask(e2), FilesBB[f_e] | RanksBB[r_2]);
        ASSERT_EQ(fileRankMask(f3), FilesBB[f_f] | RanksBB[r_3]);
        ASSERT_EQ(fileRankMask(g4), FilesBB[f_g] | RanksBB[r_4]);
        ASSERT_EQ(fileRankMask(h5), FilesBB[f_h] | RanksBB[r_5]);
    }

    TEST(BBDefinesTester, DiagonalMasksAreComputedCorrectly)
    {
        ASSERT_EQ(diagMask(a8), DiagsBB[d_0]);
        ASSERT_EQ(diagMask(b8), DiagsBB[d_1]);
        ASSERT_EQ(diagMask(a6), DiagsBB[d_2]);
        ASSERT_EQ(diagMask(d8), DiagsBB[d_3]);
        ASSERT_EQ(diagMask(d7), DiagsBB[d_4]);
        ASSERT_EQ(diagMask(e7), DiagsBB[d_5]);
        ASSERT_EQ(diagMask(c4), DiagsBB[d_6]);
        ASSERT_EQ(diagMask(f6), DiagsBB[d_7]);
        ASSERT_EQ(diagMask(b1), DiagsBB[d_8]);
        ASSERT_EQ(diagMask(h6), DiagsBB[d_9]);
        ASSERT_EQ(diagMask(d1), DiagsBB[d_10]);
        ASSERT_EQ(diagMask(e1), DiagsBB[d_11]);
        ASSERT_EQ(diagMask(g2), DiagsBB[d_12]);
        ASSERT_EQ(diagMask(g1), DiagsBB[d_13]);
        ASSERT_EQ(diagMask(h1), DiagsBB[d_14]);
    }

    TEST(BBDefinesTester, AntiDiagonalMasksAreComputedCorrectly)
    {
        ASSERT_EQ(antiDiagMask(a1), AntiDiagsBB[a_0]);
        ASSERT_EQ(antiDiagMask(a2), AntiDiagsBB[a_1]);
        ASSERT_EQ(antiDiagMask(c1), AntiDiagsBB[a_2]);
        ASSERT_EQ(antiDiagMask(b3), AntiDiagsBB[a_3]);
        ASSERT_EQ(antiDiagMask(b4), AntiDiagsBB[a_4]);
        ASSERT_EQ(antiDiagMask(d3), AntiDiagsBB[a_5]);
        ASSERT_EQ(antiDiagMask(f2), AntiDiagsBB[a_6]);
        ASSERT_EQ(antiDiagMask(a8), AntiDiagsBB[a_7]);
        ASSERT_EQ(antiDiagMask(e5), AntiDiagsBB[a_8]);
        ASSERT_EQ(antiDiagMask(h3), AntiDiagsBB[a_9]);
        ASSERT_EQ(antiDiagMask(g5), AntiDiagsBB[a_10]);
        ASSERT_EQ(antiDiagMask(e8), AntiDiagsBB[a_11]);
        ASSERT_EQ(antiDiagMask(g7), AntiDiagsBB[a_12]);
        ASSERT_EQ(antiDiagMask(g8), AntiDiagsBB[a_13]);
        ASSERT_EQ(antiDiagMask(h8), AntiDiagsBB[a_14]);
    }

    TEST(BBDefinesTester, DiagonalAntiDiagonalMasksAreComputedCorrectly)
    {
        ASSERT_EQ(diagonalsMask(a6), DiagsBB[d_2] | AntiDiagsBB[a_5]);
        ASSERT_EQ(diagonalsMask(b7), DiagsBB[d_2] | AntiDiagsBB[a_7]);
        ASSERT_EQ(diagonalsMask(c8), DiagsBB[d_2] | AntiDiagsBB[a_9]);
        ASSERT_EQ(diagonalsMask(d1), DiagsBB[d_10] | AntiDiagsBB[a_3]);
        ASSERT_EQ(diagonalsMask(e2), DiagsBB[d_10] | AntiDiagsBB[a_5]);
        ASSERT_EQ(diagonalsMask(f3), DiagsBB[d_10] | AntiDiagsBB[a_7]);
        ASSERT_EQ(diagonalsMask(g4), DiagsBB[d_10] | AntiDiagsBB[a_9]);
        ASSERT_EQ(diagonalsMask(h5), DiagsBB[d_10] | AntiDiagsBB[a_11]);
    }

    TEST(BBDefinesTester, QueenMasksAreComputedCorrectly)
    {
        ASSERT_EQ(queenMask(a8), FilesBB[f_a] | RanksBB[r_8] | DiagsBB[d_0]  | AntiDiagsBB[a_7]);
        ASSERT_EQ(queenMask(b8), FilesBB[f_b] | RanksBB[r_8] | DiagsBB[d_1]  | AntiDiagsBB[a_8]);
        ASSERT_EQ(queenMask(a6), FilesBB[f_a] | RanksBB[r_6] | DiagsBB[d_2]  | AntiDiagsBB[a_5]);
        ASSERT_EQ(queenMask(d8), FilesBB[f_d] | RanksBB[r_8] | DiagsBB[d_3]  | AntiDiagsBB[a_10]);
        ASSERT_EQ(queenMask(d7), FilesBB[f_d] | RanksBB[r_7] | DiagsBB[d_4]  | AntiDiagsBB[a_9]);
        ASSERT_EQ(queenMask(e7), FilesBB[f_e] | RanksBB[r_7] | DiagsBB[d_5]  | AntiDiagsBB[a_10]);
        ASSERT_EQ(queenMask(c4), FilesBB[f_c] | RanksBB[r_4] | DiagsBB[d_6]  | AntiDiagsBB[a_5]);
        ASSERT_EQ(queenMask(f6), FilesBB[f_f] | RanksBB[r_6] | DiagsBB[d_7]  | AntiDiagsBB[a_10]);
        ASSERT_EQ(queenMask(b1), FilesBB[f_b] | RanksBB[r_1] | DiagsBB[d_8]  | AntiDiagsBB[a_1]);
        ASSERT_EQ(queenMask(h6), FilesBB[f_h] | RanksBB[r_6] | DiagsBB[d_9]  | AntiDiagsBB[a_12]);
        ASSERT_EQ(queenMask(d1), FilesBB[f_d] | RanksBB[r_1] | DiagsBB[d_10] | AntiDiagsBB[a_3]);
        ASSERT_EQ(queenMask(e1), FilesBB[f_e] | RanksBB[r_1] | DiagsBB[d_11] | AntiDiagsBB[a_4]);
        ASSERT_EQ(queenMask(g2), FilesBB[f_g] | RanksBB[r_2] | DiagsBB[d_12] | AntiDiagsBB[a_7]);
        ASSERT_EQ(queenMask(g1), FilesBB[f_g] | RanksBB[r_1] | DiagsBB[d_13] | AntiDiagsBB[a_6]);
        ASSERT_EQ(queenMask(h1), FilesBB[f_h] | RanksBB[r_1] | DiagsBB[d_14] | AntiDiagsBB[a_7]);
        ASSERT_EQ(queenMask(a1), FilesBB[f_a] | RanksBB[r_1] | DiagsBB[d_7]  | AntiDiagsBB[a_0]);
        ASSERT_EQ(queenMask(a2), FilesBB[f_a] | RanksBB[r_2] | DiagsBB[d_6]  | AntiDiagsBB[a_1]);
        ASSERT_EQ(queenMask(c1), FilesBB[f_c] | RanksBB[r_1] | DiagsBB[d_9]  | AntiDiagsBB[a_2]);
        ASSERT_EQ(queenMask(b3), FilesBB[f_b] | RanksBB[r_3] | DiagsBB[d_6]  | AntiDiagsBB[a_3]);
        ASSERT_EQ(queenMask(b4), FilesBB[f_b] | RanksBB[r_4] | DiagsBB[d_5]  | AntiDiagsBB[a_4]);
        ASSERT_EQ(queenMask(d3), FilesBB[f_d] | RanksBB[r_3] | DiagsBB[d_8]  | AntiDiagsBB[a_5]);
        ASSERT_EQ(queenMask(f2), FilesBB[f_f] | RanksBB[r_2] | DiagsBB[d_11]  | AntiDiagsBB[a_6]);
        ASSERT_EQ(queenMask(a8), FilesBB[f_a] | RanksBB[r_8] | DiagsBB[d_14]  | AntiDiagsBB[a_7]);
        ASSERT_EQ(queenMask(e5), FilesBB[f_e] | RanksBB[r_5] | DiagsBB[d_7]  | AntiDiagsBB[a_8]);
        ASSERT_EQ(queenMask(h3), FilesBB[f_h] | RanksBB[r_3] | DiagsBB[d_12]  | AntiDiagsBB[a_9]);
        ASSERT_EQ(queenMask(g5), FilesBB[f_g] | RanksBB[r_5] | DiagsBB[d_9] | AntiDiagsBB[a_10]);
        ASSERT_EQ(queenMask(e8), FilesBB[f_e] | RanksBB[r_8] | DiagsBB[d_4] | AntiDiagsBB[a_11]);
        ASSERT_EQ(queenMask(g7), FilesBB[f_g] | RanksBB[r_7] | DiagsBB[d_7] | AntiDiagsBB[a_12]);
        ASSERT_EQ(queenMask(g8), FilesBB[f_g] | RanksBB[r_8] | DiagsBB[d_6] | AntiDiagsBB[a_13]);
        ASSERT_EQ(queenMask(h8), FilesBB[f_h] | RanksBB[r_8] | DiagsBB[d_7] | AntiDiagsBB[a_14]);
    }

    // String to file/rank/cell conversion functions
    TEST(BBDefinesTester, StringToFileConvertion_ValidFiles)
    {
        ASSERT_EQ(toFile('a'), f_a);
        ASSERT_EQ(toFile('b'), f_b);
        ASSERT_EQ(toFile('c'), f_c);
        ASSERT_EQ(toFile('d'), f_d);
        ASSERT_EQ(toFile('e'), f_e);
        ASSERT_EQ(toFile('f'), f_f);
        ASSERT_EQ(toFile('g'), f_g);
        ASSERT_EQ(toFile('h'), f_h);
    }
    TEST(BBDefinesTester, StringToFileConvertion_InvalidFiles)
    {
        ASSERT_EQ(toFile('i'), InvalidFile);
        ASSERT_EQ(toFile('j'), InvalidFile);
        ASSERT_EQ(toFile('A'), InvalidFile);
        ASSERT_EQ(toFile('H'), InvalidFile);
        ASSERT_EQ(toFile('K'), InvalidFile);
        ASSERT_EQ(toFile(' '), InvalidFile);
        ASSERT_EQ(toFile('\0'), InvalidFile);
        ASSERT_EQ(toFile('\\'), InvalidFile);
        ASSERT_EQ(toFile('1'), InvalidFile);
        ASSERT_EQ(toFile('2'), InvalidFile);
        ASSERT_EQ(toFile('3'), InvalidFile);
        ASSERT_EQ(toFile('4'), InvalidFile);
        ASSERT_EQ(toFile('5'), InvalidFile);
        ASSERT_EQ(toFile('6'), InvalidFile);
        ASSERT_EQ(toFile('7'), InvalidFile);
        ASSERT_EQ(toFile('8'), InvalidFile);
    }
    TEST(BBDefinesTester, StringToRankConvertion_ValidRanks)
    {
        ASSERT_EQ(toRank('1'), r_1);
        ASSERT_EQ(toRank('2'), r_2);
        ASSERT_EQ(toRank('3'), r_3);
        ASSERT_EQ(toRank('4'), r_4);
        ASSERT_EQ(toRank('5'), r_5);
        ASSERT_EQ(toRank('6'), r_6);
        ASSERT_EQ(toRank('7'), r_7);
        ASSERT_EQ(toRank('8'), r_8);
    }
    TEST(BBDefinesTester, StringToRankConvertion_InvalidRanks)
    {
        ASSERT_EQ(toRank('0'), InvalidRank);
        ASSERT_EQ(toRank('9'), InvalidRank);
        ASSERT_EQ(toRank('a'), InvalidRank);
        ASSERT_EQ(toRank('b'), InvalidRank);
        ASSERT_EQ(toRank('c'), InvalidRank);
        ASSERT_EQ(toRank('d'), InvalidRank);
        ASSERT_EQ(toRank('e'), InvalidRank);
        ASSERT_EQ(toRank('f'), InvalidRank);
        ASSERT_EQ(toRank('g'), InvalidRank);
        ASSERT_EQ(toRank('h'), InvalidRank);
    }
    TEST(BBDefinesTester, StringToCellConvertion_ValidCells)
    {
        ASSERT_EQ(toCell("a1"), a1);
        ASSERT_EQ(toCell("a2"), a2);
        ASSERT_EQ(toCell("a3"), a3);
        ASSERT_EQ(toCell("a4"), a4);
        ASSERT_EQ(toCell("a5"), a5);
        ASSERT_EQ(toCell("a6"), a6);
        ASSERT_EQ(toCell("a7"), a7);
        ASSERT_EQ(toCell("a8"), a8);

        ASSERT_EQ(toCell("b1"), b1);
        ASSERT_EQ(toCell("b2"), b2);
        ASSERT_EQ(toCell("b3"), b3);
        ASSERT_EQ(toCell("b4"), b4);
        ASSERT_EQ(toCell("b5"), b5);
        ASSERT_EQ(toCell("b6"), b6);
        ASSERT_EQ(toCell("b7"), b7);
        ASSERT_EQ(toCell("b8"), b8);

        ASSERT_EQ(toCell("c1"), c1);
        ASSERT_EQ(toCell("c2"), c2);
        ASSERT_EQ(toCell("c3"), c3);
        ASSERT_EQ(toCell("c4"), c4);
        ASSERT_EQ(toCell("c5"), c5);
        ASSERT_EQ(toCell("c6"), c6);
        ASSERT_EQ(toCell("c7"), c7);
        ASSERT_EQ(toCell("c8"), c8);

        ASSERT_EQ(toCell("d1"), d1);
        ASSERT_EQ(toCell("d2"), d2);
        ASSERT_EQ(toCell("d3"), d3);
        ASSERT_EQ(toCell("d4"), d4);
        ASSERT_EQ(toCell("d5"), d5);
        ASSERT_EQ(toCell("d6"), d6);
        ASSERT_EQ(toCell("d7"), d7);
        ASSERT_EQ(toCell("d8"), d8);

        ASSERT_EQ(toCell("e1"), e1);
        ASSERT_EQ(toCell("e2"), e2);
        ASSERT_EQ(toCell("e3"), e3);
        ASSERT_EQ(toCell("e4"), e4);
        ASSERT_EQ(toCell("e5"), e5);
        ASSERT_EQ(toCell("e6"), e6);
        ASSERT_EQ(toCell("e7"), e7);
        ASSERT_EQ(toCell("e8"), e8);

        ASSERT_EQ(toCell("f1"), f1);
        ASSERT_EQ(toCell("f2"), f2);
        ASSERT_EQ(toCell("f3"), f3);
        ASSERT_EQ(toCell("f4"), f4);
        ASSERT_EQ(toCell("f5"), f5);
        ASSERT_EQ(toCell("f6"), f6);
        ASSERT_EQ(toCell("f7"), f7);
        ASSERT_EQ(toCell("f8"), f8);

        ASSERT_EQ(toCell("g1"), g1);
        ASSERT_EQ(toCell("g2"), g2);
        ASSERT_EQ(toCell("g3"), g3);
        ASSERT_EQ(toCell("g4"), g4);
        ASSERT_EQ(toCell("g5"), g5);
        ASSERT_EQ(toCell("g6"), g6);
        ASSERT_EQ(toCell("g7"), g7);
        ASSERT_EQ(toCell("g8"), g8);

        ASSERT_EQ(toCell("h1"), h1);
        ASSERT_EQ(toCell("h2"), h2);
        ASSERT_EQ(toCell("h3"), h3);
        ASSERT_EQ(toCell("h4"), h4);
        ASSERT_EQ(toCell("h5"), h5);
        ASSERT_EQ(toCell("h6"), h6);
        ASSERT_EQ(toCell("h7"), h7);
        ASSERT_EQ(toCell("h8"), h8);

    }
    TEST(BBDefinesTester, StringToCellConvertion_InvalidCells)
    {
        ASSERT_EQ(toCell("d0"), InvalidCell);
        ASSERT_EQ(toCell("a9"), InvalidCell);
        ASSERT_EQ(toCell("i1"), InvalidCell);
        ASSERT_EQ(toCell("A1"), InvalidCell);
        ASSERT_EQ(toCell("a11"), InvalidCell);
        ASSERT_EQ(toCell(""), InvalidCell);
        ASSERT_EQ(toCell("d"), InvalidCell);
        ASSERT_EQ(toCell("2"), InvalidCell);
        ASSERT_EQ(toCell("  "), InvalidCell);
        ASSERT_EQ(toCell("\0"), InvalidCell);
        ASSERT_EQ(toCell("h7\0"), h7);   // is this correct ??
    }

}