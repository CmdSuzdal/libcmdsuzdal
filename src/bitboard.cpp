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

} // namespace cSzd
