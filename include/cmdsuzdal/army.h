#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    enum ArmyColor { WhiteArmy, BlackArmy, InvalidArmy };

    constexpr unsigned int NumPieceTypes = 6;
    enum Piece { King = 0, Queen = 1, Bishop = 2,
                 Knight = 3, Rook = 4 , Pawn = 5 };

    // --- The Army ----------------------------------
    struct Army {
        // --------------------------
        BitBoard pieces[NumPieceTypes] = {};
        //BitBoard pawns;

        // --------------------------
        explicit Army() = default;
        explicit Army(ArmyColor c);

    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER