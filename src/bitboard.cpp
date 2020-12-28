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
        return (diagonalsCells() | fileRankCells());
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

    BitBoard BitBoard::neighbour(const Cell &c)
    {
        File f, w, e;
        Rank r, s, n;
        f = file(c);
        r = rank(c);
        w = west(c);
        e = east(c);
        s = south(c);
        n = north(c);
        return (BitBoard((FilesBB[w] | FilesBB[f] | FilesBB[e]) &
                (RanksBB[n] | RanksBB[r] | RanksBB[s]))) ^
               BitBoard::singlecell(c);
    }

} // namespace cSzd
