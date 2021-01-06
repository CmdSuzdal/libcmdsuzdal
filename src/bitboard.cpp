#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    Cell BitBoard::activeCell() const
    {
        // if popCount() is not one, this method is probably called in error,
        // so InvalidCell is returned...
        if (popCount() != 1)
            return InvalidCell;

        unsigned int ndx;
        for (ndx = 0; ndx < 64; ndx++)
            if (bbs[ndx] != 0)
                break;

        return static_cast<Cell>(ndx);
    }

    BitBoard BitBoard::neighbourCells() const
    {
        BitBoard nb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < popCount()); ndx++) {
            if (bbs[ndx] != 0) {
                foundCells++;
                nb = nb | BitBoard(neighbour(static_cast<Cell>(ndx)));
            }
        }
        return nb;
    }
    BitBoard BitBoard::diagonalsCells() const
    {
        BitBoard nb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < popCount()); ndx++) {
            if (bbs[ndx] != 0) {
                foundCells++;
                nb = nb | BitBoard(diagonalsMask(static_cast<Cell>(ndx)) ^ singlecell(static_cast<Cell>(ndx)));
            }
        }
        return nb;
    }
    BitBoard BitBoard::fileRankCells() const
    {
        BitBoard nb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < popCount()); ndx++) {
            if (bbs[ndx] != 0) {
                foundCells++;
                nb = nb | BitBoard(fileRankMask(static_cast<Cell>(ndx)) ^ singlecell(static_cast<Cell>(ndx)));
            }
        }
        return nb;
    }
    BitBoard BitBoard::fileRankDiagonalsCells() const
    {
        return (diagonalsCells() | fileRankCells());
    }

    void BitBoard::shiftWest(unsigned int npos)
    {
        if (npos > 7)
            set(EmptyBB);
        else
            set((bbs >> npos) & WestShiftClearMask[npos - 1]);
    }
    void BitBoard::shiftEast(unsigned int npos)
    {
        if (npos > 7)
            set(EmptyBB);
        else
            set((bbs << npos) & EastShiftClearMask[npos - 1]);
    }
    void BitBoard::shiftNorth(unsigned int npos)
    {
        if (npos > 7)
            set(EmptyBB);
        else
            set((bbs << (npos * 8)) & NorthShiftClearMask[npos - 1]);
    }
    void BitBoard::shiftSouth(unsigned int npos)
    {
        if (npos > 7)
            set(EmptyBB);
        else
            set((bbs >> (npos * 8)) & SouthShiftClearMask[npos - 1]);
    }

    std::ostream &operator<<(std::ostream &os, const BitBoard &bb)
    {
        // We want to represent a BitBoard in the following way:
        //
        // 8| | | | | | | | |
        // 7| |x| | | | | | |
        // 6| | | |x| | | | |
        // 5| | | | | | | | |
        // 4| | | |x| | | | |
        // 3| | |x| | | | | |
        // 2| | | | |x|x|x| |
        // 1| | | | | | | |x|
        //   a b c d e f g h
        //
        // with the "x" representing the active cells

        os << std::endl << "  _ _ _ _ _ _ _ _";
        auto fillchar = ' ';
        for (auto rank = 7; rank >= 0; rank--) {
            os << std::endl << rank+1 << '|';
            auto startPos = rank * 8;
            if (rank == 0) fillchar = '_';
            for (auto file = 0; file < 8; file++) {
                os << ((bb.bbs[startPos + file] == 0) ? fillchar : 'x') << '|';
            }
        }
        os << std::endl << "  a b c d e f g h" << std::endl;
        return os;
    }

} // namespace cSzd
