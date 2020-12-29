#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

#include "cmdsuzdal/bitboard.h"
#include "cmdsuzdal/chessdefines.h"
#include "cmdsuzdal/chessmove.h"

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
        Piece getPieceInCell(Cell c) const;

        BitBoard controlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard kingControlledCells() const;
        BitBoard pawnsControlledCells() const;
        BitBoard knightsControlledCells() const;
        BitBoard bishopsControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard rooksControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard queensControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard kingPossibleMovesCells(const BitBoard &opponentControlled) const;
        BitBoard knightPossibleMovesCells(Cell nPos) const;

        void generateLegalMoves(std::vector<ChessMove> &moves, const Army &opponentArmy) const;
        void generateKingLegalMoves(std::vector<ChessMove> &moves, const Army &opponentArmy) const;
    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER