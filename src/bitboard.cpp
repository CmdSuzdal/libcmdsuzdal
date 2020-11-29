#include <iostream>
#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    unsigned int BitBoard::popCount() const
    {
        // Kernigham method, fast for sparsely populated bitboards.
        // See https://www.chessprogramming.org/Population_Count
        // for other approaches
        BitBoardState bbState = bbs;
        unsigned int pc = 0;
        while(bbState) {
            ++pc;
            bbState &= bbState - 1;   // Reset LS1B (Least Significant One)
        }
        return pc;
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

    BitBoardState BitBoard::neighbourMask(const Cell &c)
    {
        File f, w, e;
        Rank r, s, n;
        f = BitBoard::file(c);
        r = BitBoard::rank(c);
        w = BitBoard::west(c);
        e = BitBoard::east(c);
        s = BitBoard::south(c);
        n = BitBoard::north(c);
        return ((FilesBB[w] | FilesBB[f] | FilesBB[e]) &
                (RanksBB[n] | RanksBB[r] | RanksBB[s])) ^
               BitBoard::singleCellState(c);
    }

} // namespace cSzd
