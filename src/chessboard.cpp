#include "cmdsuzdal/chessboard.h"

namespace cSzd
{
    ChessBoard::ChessBoard(const FENRecord &fen)
    {
        whiteArmy.pieces[King]   = fen.extractBitBoard(WhiteArmy, King);
        whiteArmy.pieces[Queen]  = fen.extractBitBoard(WhiteArmy, Queen);
        whiteArmy.pieces[Rook]   = fen.extractBitBoard(WhiteArmy, Rook);
        whiteArmy.pieces[Knight] = fen.extractBitBoard(WhiteArmy, Knight);
        whiteArmy.pieces[Bishop] = fen.extractBitBoard(WhiteArmy, Bishop);
        whiteArmy.pieces[Pawn]   = fen.extractBitBoard(WhiteArmy, Pawn);
        blackArmy.pieces[King]   = fen.extractBitBoard(BlackArmy, King);
        blackArmy.pieces[Queen]  = fen.extractBitBoard(BlackArmy, Queen);
        blackArmy.pieces[Rook]   = fen.extractBitBoard(BlackArmy, Rook);
        blackArmy.pieces[Knight] = fen.extractBitBoard(BlackArmy, Knight);
        blackArmy.pieces[Bishop] = fen.extractBitBoard(BlackArmy, Bishop);
        blackArmy.pieces[Pawn]   = fen.extractBitBoard(BlackArmy, Pawn);
        sideToMove = fen.sideToMove();
        castlingAvailability = fen.castlingAvailability();
        enPassantTargetSquare = fen.enPassantTargetSquare();
        halfMoveClock = fen.halfMoveClock();
        fullMoves = fen.fullMoves();
    }

} // namespace cSzd