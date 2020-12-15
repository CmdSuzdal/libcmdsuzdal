#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    BitBoard BitBoard::neighbourCells() const
    {
        BitBoard nb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < popCount()); ndx++) {
            if (bbs[ndx] != 0) {
                foundCells++;
                nb = nb | neighbour(static_cast<Cell>(ndx));
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
                nb = nb | (diagonalsMask(static_cast<Cell>(ndx)) ^ singlecell(static_cast<Cell>(ndx)));
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
                nb = nb | (fileRankMask(static_cast<Cell>(ndx)) ^ singlecell(static_cast<Cell>(ndx)));
            }
        }
        return nb;
    }
    BitBoard BitBoard::fileRankDiagonalsCells() const
    {
        return diagonalsCells() | fileRankCells();
    }

    BitBoardState BitBoard::shiftWest(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);
        return set((bbs >> npos) & WestShiftClearMask[npos - 1]);
    }
    BitBoardState BitBoard::shiftEast(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);
        return set((bbs << npos) & EastShiftClearMask[npos - 1]);
    }
    BitBoardState BitBoard::shiftNorth(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);
        set((bbs << (npos * 8)) & NorthShiftClearMask[npos - 1]);
        return bbs;
    }
    BitBoardState BitBoard::shiftSouth(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);
        return set((bbs >> (npos * 8)) & SouthShiftClearMask[npos - 1]);
    }

    Cell BitBoard::calcCellAfterSteps(const Cell &c, int stepNorth, int stepEast)
    {
        // Computes the position of the cells reached starting from Cell c
        // and performing stepNorth steps towards north and stepEast steps
        // towards east. If stepNorth is negative the steps are done towards
        // south, if stepEast is negative, the steps are done towards west
        auto newRank = (static_cast<int>(rank(c)) + stepNorth);
        auto newFile = (static_cast<int>(file(c)) + stepEast);
        if (newFile < 0 || newFile > 7 || newRank < 0 || newRank > 7)
            return InvalidCell;

        return static_cast<Cell>(c + stepEast + (stepNorth * 8));
    }

    BitBoard BitBoard::neighbour(const Cell &c)
    {
        File f, w, e;
        Rank r, s, n;
        f = BitBoard::file(c);
        r = BitBoard::rank(c);
        w = BitBoard::west(c);
        e = BitBoard::east(c);
        s = BitBoard::south(c);
        n = BitBoard::north(c);
        return (BitBoard((FilesBB[w] | FilesBB[f] | FilesBB[e]) &
                (RanksBB[n] | RanksBB[r] | RanksBB[s]))) ^
               BitBoard::singlecell(c);
    }

} // namespace cSzd
