#if !defined CSZD_BITBOARD_HEADER
#define CSZD_BITBOARD_HEADER

#include <iostream>
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

        BitBoard operator~() const
        {
            return BitBoard(~bbs);
        }

        // Population count
        unsigned int popCount() const { return bbs.count(); }

        // Returns the active cell of the Bitboard (Assuming only one cell is active)
        Cell activeCell() const;

        // -------------------------------------------------------------------------------
        // Bitboard modification methods
        //
        void clear() { bbs = EmptyBB; }
        void set(BitBoardState newBbs) { bbs = newBbs; }
        void setCell(File f, Rank r)
        {
            (bbs |= 1ULL << (r * 8 + f));
        }
        void setCell(Cell c)
        {
            if (c != InvalidCell)
                bbs |= 1ULL << c;
        }
        void setCell(const std::vector<Cell> &cells)
        {
            for (auto &c : cells)
                setCell(c);
        }
        void resetCell(File f, Rank r) { bbs &= ~(1ULL << (r * 8 + f)); }
        void resetCell(Cell c) { bbs &= ~(1ULL << c); }
        void resetCell(const std::vector<Cell> &cells)
        {
            for (auto &c : cells)
                resetCell(c);
        }

        // Shift west (left)
        void shiftWest(unsigned int npos);
        // Shift east (right)
        void shiftEast(unsigned int npos);
        // Shift north (up)
        void shiftNorth(unsigned int npos);
        // Shift south (bottom)
        void shiftSouth(unsigned int npos);
        // -------------------------------------------------------------------------------

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

        // iostream << operator
        friend std::ostream &operator<<(std::ostream &os, const BitBoard &bb);

        // Cell status extraction operator
        int operator[](int i) const;

        // In C++ 20 it is possible to define a default three way comparison operator:
        //    bool operator<=>(const BitBoard &) const = default;
        // Note that We cannot currently use the C++20 default comparison operator
        // to allow compilation in OSX environment (Travis) with AppleCLang 9
        friend inline bool operator==(const BitBoard &lhs, const BitBoard &rhs) { return lhs.bbs == rhs.bbs; }
        friend inline bool operator!=(const BitBoard &lhs, const BitBoard &rhs) { return !operator==(lhs, rhs); }
        // Note that we do not implement the <, <=, >= and > operators because them are not defined for bitset
        // and because it is not clear what is the meaning of these operators for a generic BitBoard:
        //   - a BitBoard can be considered "less than" a second one if it has less active cells
        //     than the second, but in this case it possible to have different BitBoards
        //     that are != followind the definition of the == operator above, but that are not "<" nor ">"
        //     one of the other (any bitboard with the same number of active cells in different positions)

        operator bool() const { return bbs != EmptyBB; }

    private:
        BitBoardState bbs{};

    };


} // namespace cSzd

#endif // #if !defined CSZD_BITBOARD_HEADER
