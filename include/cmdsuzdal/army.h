#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    // The King
    struct King {

        King() = default;
        King(Cell c) {};

        bool valid() { return true; }

    };

} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER