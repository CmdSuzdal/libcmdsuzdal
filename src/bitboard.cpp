#include <iostream>
#include "cmdsuzdal/bitboard.h"

namespace cSzd
{
    BitBoardState BitBoard::shiftWest(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);
        return set((bbs >> npos) & WestShiftClearMask[npos-1]);
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

    BitBoardState BitBoard::neighbour(const Cell &c)
    {
        File f, w, e;
        Rank r, s, n;
        f = BitBoard::file(c);
        r = BitBoard::rank(c);
        w = static_cast<File>((f > 0) ? (f - 1) : InvalidFile);
        e = static_cast<File>((f < 7) ? (f + 1) : InvalidFile);
        s = static_cast<Rank>((r > 0) ? (r - 1) : InvalidRank);
        n = static_cast<Rank>((r < 7) ? (r + 1) : InvalidRank);
        return ((FilesBB[w] | FilesBB[f] | FilesBB[e]) &
                (RanksBB[n] | RanksBB[r] | RanksBB[s]))
                ^ BitBoard::singleCellState(c);
    }

} // namespace cSzd
