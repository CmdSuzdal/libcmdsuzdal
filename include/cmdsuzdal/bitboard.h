#if !defined CSZD_BITBOARD_HEADER
#define CSZD_BITBOARD_HEADER

#include <cstdint>   // for uint64_t

namespace cSzd
{

  typedef uint64_t BitBoardState;

  // Bitboard important definitions
  constexpr BitBoardState EmptyBB {};

  typedef enum cell_e {
    a1, b1, c1, d1, e1, f1, g1, h1,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a8, b8, c8, d8, e8, f8, g8, h8
  } Cell;

  typedef enum file_e {
    f_a, f_b, f_c, f_d, f_e, f_f, f_g, f_h
  } File;
  typedef enum rank_e {
    r_1, r_2, r_3, r_4, r_5, r_6, r_7, r_8
  } Rank;

  // base class for bitboard representation
  class BitBoard
  {
    public:
      BitBoard() = default;

      BitBoardState state() const { return bbs; }
      BitBoardState setCell(File f, Rank r) { return (bbs |= 1ULL << (r * 8 + f)); }
      BitBoardState resetCell(File f, Rank r) { return (bbs &= ~(1ULL << (r * 8 + f))); }
      BitBoardState setCellByName(Cell c) { return (bbs |= 1ULL << c); }
      BitBoardState resetCellByName(Cell c) { return (bbs &= ~(1ULL << c)); }

    private:
      BitBoardState bbs = EmptyBB;
  };

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
