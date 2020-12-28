#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include "cmdsuzdal/bitboard.h"
#include "cmdsuzdal/chessdefines.h"

namespace cSzd
{

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
        BitBoard occupiedCells() const;
        BitBoard controlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard kingControlledCells() const;
        BitBoard pawnsControlledCells() const;
        BitBoard knightsControlledCells() const;
        BitBoard bishopsControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard rooksControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard queensControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard kingPossibleMoveCells(const BitBoard &opponentControlled) const;
    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER