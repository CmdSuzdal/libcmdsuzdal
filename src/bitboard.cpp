#include <iostream>
#include "cmdsuzdal/bitboard.h"

namespace cSzd
{
    BitBoardState BitBoard::shiftWest(unsigned int npos)
    {
        if (npos > 7)
            return set(EmptyBB);

        // This works:
        //
        //return set((((state() & RanksBB[r_1]) >> npos) & RanksBB[r_1]) |
        //           (((state() & RanksBB[r_2]) >> npos) & RanksBB[r_2]) |
        //           (((state() & RanksBB[r_3]) >> npos) & RanksBB[r_3]) |
        //           (((state() & RanksBB[r_4]) >> npos) & RanksBB[r_4]) |
        //           (((state() & RanksBB[r_5]) >> npos) & RanksBB[r_5]) |
        //           (((state() & RanksBB[r_6]) >> npos) & RanksBB[r_6]) |
        //           (((state() & RanksBB[r_7]) >> npos) & RanksBB[r_7]) |
        //           (((state() & RanksBB[r_8]) >> npos) & RanksBB[r_8]));
        //
        // But we prefer this:
        //
        return set((bbs >> npos) & WestShiftClearMask[npos-1]);
    }

} // namespace cSzd
