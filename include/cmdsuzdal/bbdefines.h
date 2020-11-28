#if !defined CSZD_BBDEFINES_HEADER
#define CSZD_BBDEFINES_HEADER

#include <cstdint> // for uint64_t

namespace cSzd
{

    using BitBoardState = std::uint64_t;

    enum Cell
    {
        a1, b1, c1, d1, e1, f1, g1, h1,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a8, b8, c8, d8, e8, f8, g8, h8,
        InvalidCell
    };

    enum File
    {
        f_a, f_b, f_c, f_d, f_e, f_f, f_g, f_h,
        InvalidFile
    };
    enum Rank
    {
        r_1, r_2, r_3, r_4, r_5, r_6, r_7, r_8,
        InvalidRank
    };

    enum Diagonal
    {
        d_0, d_1, d_2, d_3, d_4, d_5, d_6, d_7, d_8, d_9, d_10, d_11, d_12, d_13, d_14,
        InvalidDiagonal
    };
    enum AntiDiagonal
    {
        a_0, a_1, a_2, a_3, a_4, a_5, a_6, a_7, a_8, a_9, a_10, a_11, a_12, a_13, a_14,
        InvalidAntiDiagonal
    };

    // Bitboard important definitions
    constexpr BitBoardState EmptyBB{};

    // Ranks Masks --- These are the rank indexes of the board:
    //     _________________________
    // r8|  7  7  7  7  7  7  7  7 |
    // r7|  6  6  6  6  6  6  6  6 |
    // r6|  5  5  5  5  5  5  5  5 |
    // r5|  4  4  4  4  4  4  4  4 |
    // r4|  3  3  3  3  3  3  3  3 |
    // r3|  2  2  2  2  2  2  2  2 |
    // r2|  1  1  1  1  1  1  1  1 |
    // r1|  0  0  0  0  0  0  0  0 |
    //     -------------------------
    //     fa fb fc fd fe ff fg fh
    constexpr BitBoardState Rank1BB{0x00000000000000FFULL};
    constexpr BitBoardState RanksBB[]{
        Rank1BB,
        Rank1BB << 8,
        Rank1BB << 16,
        Rank1BB << 24,
        Rank1BB << 32,
        Rank1BB << 40,
        Rank1BB << 48,
        Rank1BB << 56,
        0 // for invalid rank
    };

    // Files Masks --- These are the files indexes of the board:
    //    _________________________
    // r8|  0  1  2  3  4  5  6  7 |
    // r7|  0  1  2  3  4  5  6  7 |
    // r6|  0  1  2  3  4  5  6  7 |
    // r5|  0  1  2  3  4  5  6  7 |
    // r4|  0  1  2  3  4  5  6  7 |
    // r3|  0  1  2  3  4  5  6  7 |
    // r2|  0  1  2  3  4  5  6  7 |
    // r1|  0  1  2  3  4  5  6  7 |
    //    -------------------------
    //     fa fb fc fd fe ff fg fh
    constexpr BitBoardState File1BB{0x0101010101010101ULL};
    constexpr BitBoardState FilesBB[]{
        File1BB,
        File1BB << 1,
        File1BB << 2,
        File1BB << 3,
        File1BB << 4,
        File1BB << 5,
        File1BB << 6,
        File1BB << 7,
        0 // for invalid file
    };

    // Diagonals Masks --- These are the diagonal indexes of the board:
    //     _________________________
    // r8|  0  1  2  3  4  5  6  7 |
    // r7|  1  2  3  4  5  6  7  8 |
    // r6|  2  3  4  5  6  7  8  9 |
    // r5|  3  4  5  6  7  8  9 10 |
    // r4|  4  5  6  7  8  9 10 11 |
    // r3|  5  6  7  8  9 10 11 12 |
    // r2|  6  7  8  9 10 11 12 13 |
    // r1|  7  8  9 10 11 12 13 14 |
    //    -------------------------
    //     fa fb fc fd fe ff fg fh
    // and can be computed with the following formula:
    //   file_index - rank_index + 7
    constexpr BitBoardState DiagsBB[]{
        0x0100000000000000ULL, //  0
        0x0201000000000000ULL, //  1
        0x0402010000000000ULL, //  2
        0x0804020100000000ULL, //  3
        0x1008040201000000ULL, //  4
        0x2010080402010000ULL, //  5
        0x4020100804020100ULL, //  6
        0x8040201008040201ULL, //  7
        0x0080402010080402ULL, //  8
        0x0000804020100804ULL, //  9
        0x0000008040201008ULL, // 10
        0x0000000080402010ULL, // 11
        0x0000000000804020ULL, // 12
        0x0000000000008040ULL, // 13
        0x0000000000000080ULL, // 14
        0 // for invalid diagonal
    };

    // Antidiagonals Masks --- These are the diagonal indexes of the board:
    //     _________________________
    // r8|  7  8  9 10 11 12 13 14 |
    // r7|  6  7  8  9 10 11 12 13 |
    // r6|  5  6  7  8  9 10 11 12 |
    // r5|  4  5  6  7  8  9 10 11 |
    // r4|  3  4  5  6  7  8  9 10 |
    // r3|  2  3  4  5  6  7  8  9 |
    // r2|  1  2  3  4  5  6  7  8 |
    // r1|  0  1  2  3  4  5  6  7 |
    //    -------------------------
    //     fa fb fc fd fe ff fg fh
    // and can be computed with the following formula:
    //   file_index + rank_index
    constexpr BitBoardState AntiDiagsBB[]{
        0x0000000000000001ULL, //  0
        0x0000000000000102ULL, //  1
        0x0000000000010204ULL, //  2
        0x0000000001020408ULL, //  3
        0x0000000102040810ULL, //  4
        0x0000010204081020ULL, //  5
        0x0001020408102040ULL, //  6
        0x0102040810204080ULL, //  7
        0x0204081020408000ULL, //  8
        0x4081020408000000ULL, //  9
        0x0810204080000000ULL, // 10
        0x1020408000000000ULL, // 11
        0x2040800000000000ULL, // 12
        0x4080000000000000ULL, // 13
        0x8000000000000000ULL, // 14
        0 // for invalid antidiagonal
    };

    constexpr BitBoardState DiagonalBB{0x8040201008040201ULL};
    constexpr BitBoardState AntiDiagonalBB{0x0102040810204080ULL};
    constexpr BitBoardState BothDiagonalsBB{DiagonalBB | AntiDiagonalBB};

    constexpr BitBoardState AllCellsBB{0xFFFFFFFFFFFFFFFFULL};
    constexpr BitBoardState AllBlackCellsBB{0xAA55AA55AA55AA55ULL};
    constexpr BitBoardState AllWhiteCellsBB{~AllBlackCellsBB};

    // ------
    // center of board can be defined with the intersection of files d,e and ranks 4,5
    constexpr BitBoardState BoardCenterBB{(RanksBB[r_4] | RanksBB[r_5]) &
                                          (FilesBB[f_d] | FilesBB[f_e])};
    //constexpr BitBoardState BoardCenterBB  { 0x0000001818000000ULL };

    // West shift clear matrix
    constexpr BitBoardState WestShiftClearMask[]{
        FilesBB[0] | FilesBB[1] | FilesBB[2] | FilesBB[3] | FilesBB[4] | FilesBB[5] | FilesBB[6],
        FilesBB[0] | FilesBB[1] | FilesBB[2] | FilesBB[3] | FilesBB[4] | FilesBB[5],
        FilesBB[0] | FilesBB[1] | FilesBB[2] | FilesBB[3] | FilesBB[4],
        FilesBB[0] | FilesBB[1] | FilesBB[2] | FilesBB[3],
        FilesBB[0] | FilesBB[1] | FilesBB[2],
        FilesBB[0] | FilesBB[1],
        FilesBB[0]};
    // East shift clear matrix
    constexpr BitBoardState EastShiftClearMask[]{
        FilesBB[1] | FilesBB[2] | FilesBB[3] | FilesBB[4] | FilesBB[5] | FilesBB[6] | FilesBB[7],
        FilesBB[2] | FilesBB[3] | FilesBB[4] | FilesBB[5] | FilesBB[6] | FilesBB[7],
        FilesBB[3] | FilesBB[4] | FilesBB[5] | FilesBB[6] | FilesBB[7],
        FilesBB[4] | FilesBB[5] | FilesBB[6] | FilesBB[7],
        FilesBB[5] | FilesBB[6] | FilesBB[7],
        FilesBB[6] | FilesBB[7],
        FilesBB[7]};
    // North shift clear matrix
    constexpr BitBoardState NorthShiftClearMask[]{
        RanksBB[1] | RanksBB[2] | RanksBB[3] | RanksBB[4] | RanksBB[5] | RanksBB[6] | RanksBB[7],
        RanksBB[2] | RanksBB[3] | RanksBB[4] | RanksBB[5] | RanksBB[6] | RanksBB[7],
        RanksBB[3] | RanksBB[4] | RanksBB[5] | RanksBB[6] | RanksBB[7],
        RanksBB[4] | RanksBB[5] | RanksBB[6] | RanksBB[7],
        RanksBB[5] | RanksBB[6] | RanksBB[7],
        RanksBB[6] | RanksBB[7],
        RanksBB[7]};
    // South shift clear matrix
    constexpr BitBoardState SouthShiftClearMask[]{
        RanksBB[0] | RanksBB[1] | RanksBB[2] | RanksBB[3] | RanksBB[4] | RanksBB[5] | RanksBB[6],
        RanksBB[0] | RanksBB[1] | RanksBB[2] | RanksBB[3] | RanksBB[4] | RanksBB[5],
        RanksBB[0] | RanksBB[1] | RanksBB[2] | RanksBB[3] | RanksBB[4],
        RanksBB[0] | RanksBB[1] | RanksBB[2] | RanksBB[3],
        RanksBB[0] | RanksBB[1] | RanksBB[2],
        RanksBB[0] | RanksBB[1],
        RanksBB[0]};
} // namespace cSzd

#endif // if !defined CSZD_BBDEFINES_HEADER
