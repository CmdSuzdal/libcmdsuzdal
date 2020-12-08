#include "cmdsuzdal/chessboard.h"

namespace cSzd
{
    // -----------------------------------------------------------------
    ChessBoard::ChessBoard(const FENRecord &fen)
    {
        loadPosition(fen);
    }

    // -----------------------------------------------------------------
    ChessBoard::ChessBoard(const std::string_view fenStr)
        : ChessBoard(FENRecord(fenStr)) {}

    // -----------------------------------------------------------------
    void ChessBoard::loadPosition(const FENRecord &fen)
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
    // -----------------------------------------------------------------
    void ChessBoard::loadPosition(const std::string_view fenStr)
    {
        loadPosition(FENRecord(fenStr));
    }

    // -----------------------------------------------------------------
    bool ChessBoard::isValid() const
    {
        // One and only one king per army shall be present in the board
        if ((whiteArmy.pieces[King].popCount() != 1) ||
            (blackArmy.pieces[King].popCount() != 1)) {
            return false;
        }
        // kings shall not be in contact
        if (whiteArmy.pieces[King].activeCellsInMask(
            blackArmy.pieces[King].neighbourCells().bbs)) return false;

        // No pawns (of any color) in 1st or 8th ranks
        if (whiteArmy.pieces[Pawn].activeCellsInMask(
            RanksBB[r_1] | RanksBB[r_8])) return false;
        if (blackArmy.pieces[Pawn].activeCellsInMask(
            RanksBB[r_1] | RanksBB[r_8])) return false;

        // More that 16 pieces for army
        if (whiteArmy.numPieces() > 16) return false;
        if (blackArmy.numPieces() > 16) return false;

        return true;
    }


} // namespace cSzd