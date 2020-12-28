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

        // FIXME to be completed evaluation of en-passant cell
        cm |= InvalidCell << EnPassantCellOffset;

        return cm;
    }

}