#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    enum ArmyColor { WhiteArmy, BlackArmy, InvalidArmy };

    // --- The Army ----------------------------------
    struct Army {
        // --------------------------
        BitBoard king;
        BitBoard pawns;

        // --------------------------
        explicit Army() : Army(WhiteArmy) {};
        explicit Army(ArmyColor c);

    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER