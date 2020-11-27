#if !defined CSZD_BITBOARD_HEADER
#define CSZD_BITBOARD_HEADER

#include <vector>

#include "cmdsuzdal/bbdefines.h"

namespace cSzd
{

  // -------------------------------------------------------------------------
  // base struct for bitboard representation
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
  //     - Union operator ( | )
  //     - Intersection operator ( & ): exists in two flavour:
  //     - Exclusive OR operator ( ^ ): exists in two flavour:
  //     - Equality operator ( == ): with the usual two flavour
  //
  struct BitBoard
  {
    BitBoardState bbs {};

    BitBoard() = default;
    explicit BitBoard(const std::vector<Cell> &cells) { setCell(cells); }
    explicit BitBoard(BitBoardState bitbs) { bbs = bitbs; }

    // operators
    BitBoard &operator=(const BitBoard &rhs) = default;

    BitBoard operator|(const BitBoard &rhs) const
    {
      BitBoard bb(bbs | rhs.bbs);
      return bb;
    }
    BitBoard operator&(const BitBoard &rhs) const
    {
      BitBoard bb(bbs & rhs.bbs);
      return bb;
    }
    BitBoard operator^(const BitBoard &rhs) const
    {
      BitBoard bb(bbs ^ rhs.bbs);
      return bb;
    }

    // In C++ 20 it is possible to define a default comparison operator:
    //    bool operator<=>(const BitBoard &) const = default;
    // but we prefer to define only the equality operator because it is
    // not clear that a BitBoard is greater than or less than another
    bool operator==(const BitBoard &) const = default;

    // -------------------------------------------------------------------------------
    // waiting for apolis comments
    // -------------------------------------------------------------------------------
    // Bitboard modification methods
    //
    // Note that all these methods currently returns the BitBoard internal state for
    // an idea of "supposed efficiency" but I am not really sure that this is the
    // best solution. Maybe the approach used for the function:
    //    const BitBoard &setCell(File f, Rank r)
    // is clearer.... See f.e. test Cell_0_0_CorrespondToA1
    //
    // Another approach is not to return anything, like in the case of:
    //    void resetCell(File f, Rank r)
    // see test IfACellIsSetAndThenResetBitboardIsEmpty
    //
    BitBoardState clear() { bbs = EmptyBB; return bbs; }
    BitBoardState set(BitBoardState newBbs) { bbs = newBbs; return bbs; }
    const BitBoard &setCell(File f, Rank r) { (bbs |= 1ULL << (r * 8 + f)); return *this; }
    BitBoardState setCell(Cell c) { return (bbs |= 1ULL << c); }
    BitBoardState setCell(const std::vector<Cell> &cells)
    {
      for (auto &c : cells)
        setCell(c);
      return bbs;
    }
    void resetCell(File f, Rank r) { bbs &= ~(1ULL << (r * 8 + f)); }
    BitBoardState resetCell(Cell c) { return (bbs &= ~(1ULL << c)); }
    BitBoardState resetCell(const std::vector<Cell> &cells)
    {
      for (auto &c : cells)
        resetCell(c);
      return bbs;
    }

    // Shift west (left)
    BitBoardState shiftWest(unsigned int npos);
    // Shift east (right)
    BitBoardState shiftEast(unsigned int npos);
    // -------------------------------------------------------------------------------

  };

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
