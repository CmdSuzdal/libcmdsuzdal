#if !defined CSZD_BITBOARD_HEADER
#define CSZD_BITBOARD_HEADER

#include <vector>

#include "cmdsuzdal/bbdefines.h"

namespace cSzd
{

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

    BitBoardState clear() { bbs = EmptyBB; return bbs; }
    BitBoardState set(BitBoardState newBbs) { bbs = newBbs; return bbs; }

    // operators
    BitBoard &operator=(const BitBoard &rhs) = default;

    BitBoard operator|(const BitBoard &rhs) const
    {
      BitBoard bb(bbs | rhs.state());
      return bb;
    }
    BitBoard operator|(BitBoardState rhs) const
    {
      BitBoard bb(bbs | rhs);
      return bb;
    }
    BitBoard operator&(const BitBoard &rhs) const
    {
      BitBoard bb(bbs & rhs.state());
      return bb;
    }
    BitBoard operator&(BitBoardState rhs) const
    {
      BitBoard bb(bbs & rhs);
      return bb;
    }
    BitBoard operator^(const BitBoard &rhs) const
    {
      BitBoard bb(bbs ^ rhs.state());
      return bb;
    }
    BitBoard operator^(BitBoardState rhs) const
    {
      BitBoard bb(bbs ^ rhs);
      return bb;
    }
    bool operator==(const BitBoard &rhs) const
    {
      return bbs == rhs.state();
    }
    bool operator==(BitBoardState rhs) const
    {
      return bbs == rhs;
    }

    // Shift west (left)
    BitBoardState shiftWest(unsigned int npos);

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
      for (auto &c : cells)
        setCell(c);
      return bbs;
    }
    BitBoardState resetCell(File f, Rank r) { return (bbs &= ~(1ULL << (r * 8 + f))); }
    BitBoardState resetCell(Cell c) { return (bbs &= ~(1ULL << c)); }
    BitBoardState resetCell(const std::vector<Cell> &cells)
    {
      for (auto &c : cells)
        resetCell(c);
      return bbs;
    }

  private:
    BitBoardState bbs {};
  };

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
