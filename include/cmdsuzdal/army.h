#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    // --- The King ---------------------------------
    struct King {

        King() = default;
        King(Cell c) : bb(c) {};

        bool valid() { return bb.popCount() == 1; }

        // the bitboard
        BitBoard bb {};
    };
    // -----------------------------------------------

    // --- The Pawns Set -----------------------------
    struct PawnSet {

        PawnSet() = default;
        PawnSet(const Cell &c) : bb(c) {};
        PawnSet(const std::vector<Cell> &c) : bb(c) {};

        bool valid() { return !bb.activeCellsInMask(RanksBB[r_1] | RanksBB[r_8]); }

        // the bitboard
        BitBoard bb {};
    };
    // -----------------------------------------------

} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER