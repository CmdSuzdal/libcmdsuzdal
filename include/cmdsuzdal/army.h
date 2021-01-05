#if !defined CSZD_ARMY_HEADER
#define CSZD_ARMY_HEADER

#include <vector>

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
        Piece getPieceInCell(Cell c) const;
        Cell getKingPosition() const;

        BitBoard controlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard controlledCellsByPieceType(Piece pType, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard kingControlledCells() const;
        BitBoard pawnsControlledCells() const;
        BitBoard singlePawnControlledCells(Cell nPos) const;
        BitBoard knightsControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard bishopsControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard rooksControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard queensControlledCells(const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

        BitBoard possibleMovesCellsByPieceTypeAndPosition(Piece pType, Cell pos,
                                                const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard kingPossibleMovesCells() const;
        BitBoard knightPossibleMovesCells(Cell c, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard bishopPossibleMovesCells(Cell c, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard rookPossibleMovesCells(Cell c, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard queenPossibleMovesCells(Cell c, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;
        BitBoard pawnPossibleMovesCells(Cell c, const BitBoard &intfBoard = BitBoard(EmptyBB)) const;

    private:
        BitBoard piecePossibleMovesCells(Piece pType, Cell nPos, const BitBoard &intfBoard) const;
    };
    // -----------------------------------------------
    inline bool operator==(const Army &lhs, const Army &rhs)
    {
        // Two armies are equal if they have the same BitBoards, and the same color
        return  ((lhs.pieces[King] == rhs.pieces[King]) &&
                (lhs.pieces[Queen] == rhs.pieces[Queen]) &&
                (lhs.pieces[Rook] == rhs.pieces[Rook]) &&
                (lhs.pieces[Bishop] == rhs.pieces[Bishop]) &&
                (lhs.pieces[Knight] == rhs.pieces[Knight]) &&
                (lhs.pieces[Pawn] == rhs.pieces[Pawn]) &&
                (lhs.color == rhs.color));
    }
    inline bool operator!=(const Army &lhs, const Army &rhs) { return !operator==(lhs, rhs); }

} // namespace cSzd

#endif // #if !defined CSZD_ARMY_HEADER