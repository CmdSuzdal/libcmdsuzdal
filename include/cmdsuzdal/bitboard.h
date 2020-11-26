#if !defined CSZD_BITBOARD_HEADER
#define CSZD_BITBOARD_HEADER

#include <cstdint>   // for uint64_t
#include <vector>

namespace cSzd
{

  typedef uint64_t BitBoardState;

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

  typedef enum file_e
  {
    f_a, f_b, f_c, f_d, f_e, f_f, f_g, f_h
  } File;
  typedef enum rank_e
  {
    r_1, r_2, r_3, r_4, r_5, r_6, r_7, r_8
  } Rank;

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

  // -------------------------------------------------------------------------
  // base class for bitboard representation
  // After some refactoring one question remains: we REALLY need a class??
  // -----
  // Currently defined:
  //
  // - Constructors:
  //     - BitBoard() - default: define an empty bitboard
  //     - BitBoard(const std::vector<Cell> &cells) - define a bitboard
  //         with the list of cells busy passed as a parameter
  //     - BitBoard(BitBoardState bitbs) - define a bitboard initialized
  //         with the state passed as a parameter
  // - Operators:
  //     - Union operator ( | ): exists in two flavour:
  //         - union with another BitBoard
  //         - union with a BitBoardState
  //     - Intersection operator ( & ): exists in two flavour:
  //         - intersection with another BitBoard
  //         - intersection with a BitBoardState
  //     - Exclusive OR operator ( ^ ): exists in two flavour:
  //         - exclusive or with another BitBoard
  //         - exclusive or with a BitBoardState
  //     - Equality operator ( == ): with the usual two flavour
  //
  class BitBoard
  {
  public:
    BitBoard() = default;
    explicit BitBoard(const std::vector<Cell> &cells) { setCell(cells); }
    explicit BitBoard(BitBoardState bitbs) { bbs = bitbs; }

    // operators
    BitBoard operator|(const BitBoard &rhs) const
    {
      BitBoard bb(this->state() | rhs.state());
      return bb;
    }
    BitBoard operator|(BitBoardState rhs) const
    {
      BitBoard bb(this->state() | rhs);
      return bb;
    }
    BitBoard operator&(const BitBoard &rhs) const
    {
      BitBoard bb(this->state() & rhs.state());
      return bb;
    }
    BitBoard operator&(BitBoardState rhs) const
    {
      BitBoard bb(this->state() & rhs);
      return bb;
    }
    BitBoard operator^(const BitBoard &rhs) const
    {
      BitBoard bb(this->state() ^ rhs.state());
      return bb;
    }
    BitBoard operator^(BitBoardState rhs) const
    {
      BitBoard bb(this->state() ^ rhs);
      return bb;
    }
    bool operator==(const BitBoard &rhs) const
    {
      return this->state() == rhs.state();
    }
    bool operator==(BitBoardState rhs) const
    {
      return this->state() == rhs;
    }

    // Special BitBoards
    static BitBoard Center() {return BitBoard(BoardCenterBB); }

    // set cells methods
    BitBoardState state() const
    {
      return bbs;
    }
    BitBoardState setCell(File f, Rank r) { return (bbs |= 1ULL << (r * 8 + f)); }
    BitBoardState setCell(Cell c) { return (bbs |= 1ULL << c); }
    BitBoardState setCell(const std::vector<Cell> &cells)
    {
      for (auto c : cells)
        setCell(c);
      return state();
    }
    BitBoardState resetCell(File f, Rank r) { return (bbs &= ~(1ULL << (r * 8 + f))); }
    BitBoardState resetCell(Cell c) { return (bbs &= ~(1ULL << c)); }
    BitBoardState resetCell(const std::vector<Cell> &cells)
    {
      for (auto c : cells)
        resetCell(c);
      return state();
    }

  private:
    BitBoardState bbs = EmptyBB;
  };

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
