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
        return InvalidMove;
    }

}