#if !defined CSZD_BBDEFINES_HEADER
#define CSZD_BBDEFINES_HEADER

#include <cstdint>   // for uint64_t

namespace cSzd
{

  using BitBoardState = std::uint64_t;

  enum Cell {
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
    f_a, f_b, f_c, f_d, f_e, f_f, f_g, f_h, InvalidFile
  };
  enum Rank
  {
    r_1, r_2, r_3, r_4, r_5, r_6, r_7, r_8, InvalidRank
  };

  // Bitboard important definitions
  constexpr BitBoardState EmptyBB{};
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
    0   // for invalid rank
  };
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
