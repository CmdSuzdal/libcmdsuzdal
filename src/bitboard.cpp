#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    BitBoard BitBoard::neighbourCells() const
    {
        BitBoard nb;
        BitBoardState checkMask = 1;
        for (auto ndx = 0; ndx < 64; ndx++) {
            if ((bbs & checkMask) != EmptyBB) {
                nb = nb | BitBoard(neighbourMask(static_cast<Cell>(ndx)));
            }
            checkMask <<= 1;
        }
        return nb;
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
