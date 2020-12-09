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

        BitBoardState bbs{};

        BitBoard() = default;
        explicit BitBoard(const Cell &c) { setCell(c); }
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

        // Population count
        unsigned int popCount() const;

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
        BitBoardState clear()
        {
            bbs = EmptyBB;
            return bbs;
        }
        BitBoardState set(BitBoardState newBbs)
        {
            bbs = newBbs;
            return bbs;
        }
        const BitBoard &setCell(File f, Rank r)
        {
            (bbs |= 1ULL << (r * 8 + f));
            return *this;
        }
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
        // Shift north (up)
        BitBoardState shiftNorth(unsigned int npos);
        // Shift south (bottom)
        BitBoardState shiftSouth(unsigned int npos);
        // -------------------------------------------------------------------------------

        // -------------------------------------------------------------------------------
        // Bitboard generation methods
        // Returns a BitBoard object composed by the neighbour cells of the current object
        // active cells
        BitBoard neighbourCells() const;
        // -------------------------------------------------------------------------------


        // -------------------------------------------------------------------------------
        // Bitboard utility methods

        // Given a cell, returns the associated BitBoard state (the BitBoard state on
        // which the given cell is the only one active)
        static BitBoardState singleCellState(const Cell &c) { return (1ULL << c); }

        // Given a cell, returns File, Rank, Diagonal, AntiDiagonal (and combinations)
        static File file(const Cell &c) { return static_cast<File>(c % 8); }
        static Rank rank(const Cell &c) { return static_cast<Rank>(c >> 3); }
        static Diagonal diag(const Cell &c) { return static_cast<Diagonal>(file(c) - rank(c) + 7); }
        static AntiDiagonal antiDiag(const Cell &c) { return static_cast<AntiDiagonal>(file(c) + rank(c)); }
        static std::pair<File, Rank> coords(const Cell &c)
        {
            return std::make_pair(file(c), rank(c));
        }
        static std::pair<Diagonal, AntiDiagonal> diagonals(const Cell &c)
        {
            return std::make_pair(diag(c), antiDiag(c));
        }

        // Given a cell, returns west/east files and south/north ranks
        static File west(const Cell &c)
        {
            auto f = file(c);
            return static_cast<File>((f > 0) ? (f - 1) : InvalidFile);
        }
        static File east(const Cell &c)
        {
            auto f = file(c);
            return static_cast<File>((f < 7) ? (f + 1) : InvalidFile);
        }
        static Rank south(const Cell &c)
        {
            auto r = rank(c);
            return static_cast<Rank>((r > 0) ? (r - 1) : InvalidRank);
        }
        static Rank north(const Cell &c)
        {
            auto r = rank(c);
            return static_cast<Rank>((r < 7) ? (r + 1) : InvalidRank);
        }

        // "Compass rose" methods
        static Cell w(const Cell &c) { return static_cast<Cell>((file(c) > 0) ? c - 1 : InvalidCell); }
        static Cell nw(const Cell &c) { return static_cast<Cell>((file(c) > 0 && rank(c) < 7) ? c + 7 : InvalidCell); }
        static Cell n(const Cell &c) { return static_cast<Cell>((rank(c) < 7) ? c + 8 : InvalidCell); }
        static Cell ne(const Cell &c) { return static_cast<Cell>((file(c) < 7 && rank(c) < 7) ? c + 9 : InvalidCell); }
        static Cell e(const Cell &c) { return static_cast<Cell>((file(c) < 7) ? c + 1 : InvalidCell); }
        static Cell se(const Cell &c) { return static_cast<Cell>((file(c) < 7 && rank(c) > 0) ? c - 7 : InvalidCell); }
        static Cell s(const Cell &c) { return static_cast<Cell>((rank(c) > 0) ? c - 8 : InvalidCell); }
        static Cell sw(const Cell &c) { return static_cast<Cell>((file(c) > 0 && rank(c) > 0) ? c - 9 : InvalidCell); }

        // Given a cell, returns any sort of "related" cells BitBoard states
        static BitBoardState neighbourMask(const Cell &c);
        static BitBoardState fileMask(const Cell &c) { return FilesBB[file(c)]; }
        static BitBoardState rankMask(const Cell &c) { return RanksBB[rank(c)]; }
        static BitBoardState fileRankMask(const Cell &c) { return fileMask(c) | rankMask(c); }
        static BitBoardState diagMask(const Cell &c) { return DiagsBB[diag(c)]; }
        static BitBoardState antiDiagMask(const Cell &c) { return AntiDiagsBB[antiDiag(c)]; }
        static BitBoardState diagonalsMask(const Cell &c) { return diagMask(c) | antiDiagMask(c); }
        static BitBoardState queenMask(const Cell &c) { return fileMask(c) | rankMask(c) | diagMask(c) | antiDiagMask(c); }

        // Check functions: return a boolean check on various conditions
        // returns true if at least one of the cell in the given mask is active
        bool activeCellsInMask(BitBoardState bbMask) const { return ((bbs & bbMask) != EmptyBB); }
    };

    // In C++ 20 it is possible to define a default three way comparison operator:
    //    bool operator<=>(const BitBoard &) const = default;
    // but we prefer to define only the equality operator because it is
    // not clear when a BitBoard is greater than or less than another
    // NOTE: we cannot currently use the C++20 default comparison operator
    // to allow compilation in OSX environment (Travis) with AppleCLang 9
    //    bool operator==(const BitBoard &) const = default;
    inline bool operator==(const BitBoard &lhs, const BitBoard &rhs) { return lhs.bbs == rhs.bbs; }
    inline bool operator!=(const BitBoard &lhs, const BitBoard &rhs) { return !operator==(lhs, rhs); }

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
