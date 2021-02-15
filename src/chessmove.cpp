#include "cmdsuzdal/chessmove.h"

namespace cSzd
{

    ChessMove chessMove(Piece movedPiece, Cell startCell, Cell destCell,
                        Piece takenPiece,
                        Piece promotedPiece)
    {
        // IMPORTANT NOTE: this method does not perform
        // any check in chess move validity. Just accept
        // everything. It is responsibility of the caller
        // to generate valid moves
        ChessMove cm {};
        cm |= (movedPiece & PieceMask) << MovedPieceOffset;
        cm |= (takenPiece & PieceMask) << TakenPieceOffset;
        cm |= (promotedPiece & PieceMask) << PromotedPieceOffset;
        cm |= (startCell & ValidCellMask) << StartCellOffset;
        cm |= (destCell & ValidCellMask) << DestinationCellOffset;

        // Evaluates en passant
        if (movedPiece == Pawn)
            cm |= computeEnPassant(startCell, destCell) << EnPassantCellOffset;
        else
            cm |= InvalidCell << EnPassantCellOffset;

        return cm;
    }

    Cell computeEnPassant(Cell from, Cell to)
    {
        auto r = rank(from);

        // If from cell is in 2nd rank and to = from + 16
        // we have an en passant in from + 8
        if ((r == r_2) && (to == (from + 16))) {
            return static_cast<Cell>(from + 8);
        }
        // If from cell is in 7th rank and to = from - 16
        // we have an en passant in from - 8
        if ((r == r_7) && (to == (from - 16))) {
            return static_cast<Cell>(from - 8);
        }
        return InvalidCell;
    }


}