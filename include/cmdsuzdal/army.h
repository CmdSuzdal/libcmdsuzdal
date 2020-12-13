#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include "cmdsuzdal/bitboard.h"

namespace cSzd
{

    enum ArmyColor : unsigned int { WhiteArmy, BlackArmy, InvalidArmy };

    constexpr unsigned int NumPieceTypes = 6;
    enum Piece : unsigned int { King = 0, Queen = 1, Bishop = 2,
                 Knight = 3, Rook = 4 , Pawn = 5, InvalidPiece };

    // --- The Army ----------------------------------
    struct Army {
        // --------------------------
        BitBoard pieces[NumPieceTypes] = {};
        ArmyColor color = InvalidArmy;

        // --------------------------
        explicit Army() = default;
        explicit Army(ArmyColor c);

        // --------------------------
        unsigned int numPieces() const;

        private:

    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER