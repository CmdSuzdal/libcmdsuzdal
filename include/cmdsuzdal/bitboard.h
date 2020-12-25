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
        // assignment operator
        BitBoard &operator=(const BitBoard &rhs) = default;

        BitBoard &operator|=(const BitBoard &rhs)
        {
            bbs |= rhs.bbs;
            return *this;
        }
        friend BitBoard operator|(BitBoard lhs, const BitBoard &rhs)
        {
            lhs |= rhs;
            return lhs;
        }

        BitBoard &operator&=(const BitBoard &rhs)
        {
            bbs &= rhs.bbs;
            return *this;
        }
        friend BitBoard operator&(BitBoard lhs, const BitBoard &rhs)
        {
            lhs &= rhs;
            return lhs;
        }

        BitBoard &operator^=(const BitBoard &rhs)
        {
            bbs ^= rhs.bbs;
            return *this;
        }
        friend BitBoard operator^(BitBoard lhs, const BitBoard &rhs)
        {
            lhs ^= rhs;
            return lhs;
        }

        // Population count
        unsigned int popCount() const { return bbs.count(); }

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
        BitBoardState setCell(Cell c)
        {
            if (c != InvalidCell)
                bbs |= 1ULL << c;
            return bbs;
        }
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
        // Bitboard utility methods

        // Given file and rank returns the cell
        static Cell toCell(File f, Rank r) { return static_cast<Cell>(r * 8 + f); }

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
        static Cell calcCellAfterSteps(const Cell &c, int stepNorth, int stepEast);

        // Given a cell, returns any sort of "related" cells BitBoard states
        static BitBoard singlecell(const Cell &c) { return BitBoard(1ULL << c); }
        static BitBoard neighbour(const Cell &c);
        static BitBoard fileMask(const Cell &c) { return BitBoard(FilesBB[file(c)]); }
        static BitBoard rankMask(const Cell &c) { return BitBoard(RanksBB[rank(c)]); }
        static BitBoard fileRankMask(const Cell &c) { return fileMask(c) | rankMask(c); }
        static BitBoard diagMask(const Cell &c) { return BitBoard(DiagsBB[diag(c)]); }
        static BitBoard antiDiagMask(const Cell &c) { return BitBoard(AntiDiagsBB[antiDiag(c)]); }
        static BitBoard diagonalsMask(const Cell &c) { return diagMask(c) | antiDiagMask(c); }
        static BitBoard queenMask(const Cell &c) { return fileMask(c) | rankMask(c) | diagMask(c) | antiDiagMask(c); }

        // -------------------------------------------------------------------------------
        // Bitboard generation methods: returns a BitBoard object composed by cells generated
        // by the current object active cells

        // - Neighbours cells ('king')
        BitBoard neighbourCells() const;

        // - Diagonals cells ('bishop')
        BitBoard diagonalsCells() const;

        // - File & Rank cells ('rook')
        BitBoard fileRankCells() const;

        // - File + Rank + Diagonals cells ('queen')
        BitBoard fileRankDiagonalsCells() const;
        // -------------------------------------------------------------------------------

        // Check functions: return a boolean check on various conditions
        bool isActive(Cell c) const { return ((bbs & BitBoard(c).bbs) != EmptyBB); }
        bool isActive(File f, Rank r) const { return isActive(toCell(f, r)); }
        // returns true if at least one of the cell in the given mask is active
        bool activeCellsInMask(BitBoardState bbMask) const { return ((bbs & bbMask) != EmptyBB); }
    };

    // In C++ 20 it is possible to define a default three way comparison operator:
    //    bool operator<=>(const BitBoard &) const = default;
    // Note that We cannot currently use the C++20 default comparison operator
    // to allow compilation in OSX environment (Travis) with AppleCLang 9
    inline bool operator==(const BitBoard &lhs, const BitBoard &rhs) { return lhs.bbs == rhs.bbs; }
    inline bool operator!=(const BitBoard &lhs, const BitBoard &rhs) { return !operator==(lhs, rhs); }
    // Note that we do not implement the <, <=, >= and > operators because them are not defined for bitset
    // and because it is not clear what is the meaning of these operators for a generic BitBoard:
    //   - a BitBoard can be considered "less than" a second one if it has less active cells
    //     than the second, but in this case it possible to have different BitBoards
    //     that are != followind the definition of the == operator above, but that are not "<" nor ">"
    //     one of the other (any bitboard with the same number of active cells in different positions)

} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
