#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    // --- The Base Item (piece or pawn set) --------
    // This class is used as abstract base class
    // for all piece and piecesets
    struct ItemsSet {
        ItemsSet() = default;
        ItemsSet(const Cell &c) : bb(c) {};
        ItemsSet(const std::vector<Cell> &c) : bb(c) {};

        virtual bool valid() const = 0;

        // the bitboard
        BitBoard bb {};
    };
    // -----------------------------------------------


    // --- The King ---------------------------------
    struct King : ItemsSet {

        King() = default;
        King(Cell c) : ItemsSet(c) {};

        bool valid() const { return bb.popCount() == 1; }

    };
    // -----------------------------------------------

    // --- The Pawns Set -----------------------------
    struct PawnsSet : ItemsSet {

        PawnsSet() = default;
        PawnsSet(const Cell &c) : ItemsSet(c) {};
        PawnsSet(const std::vector<Cell> &c) : ItemsSet(c) {};

        bool valid() const { return !bb.activeCellsInMask(RanksBB[r_1] | RanksBB[r_8]); }

    };
    // -----------------------------------------------

} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER