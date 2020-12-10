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
    BitBoard ChessBoard::wholeArmyBitBoard(ArmyColor a) const
    {
        if (a == WhiteArmy || a == BlackArmy) {
            return armies[a].pieces[King] | armies[a].pieces[Queen] |
                armies[a].pieces[Bishop] | armies[a].pieces[Knight] |
                armies[a].pieces[Rook] | armies[a].pieces[Pawn];
        }
        else if (a == InvalidArmy) {
            return wholeArmyBitBoard(WhiteArmy) |
                wholeArmyBitBoard(BlackArmy);
        }
        return BitBoard(EmptyBB);
    }

    // -----------------------------------------------------------------
    void ChessBoard::loadPosition(const FENRecord &fen)
    {
        armies[WhiteArmy].pieces[King]   = fen.extractBitBoard(WhiteArmy, King);
        armies[WhiteArmy].pieces[Queen]  = fen.extractBitBoard(WhiteArmy, Queen);
        armies[WhiteArmy].pieces[Rook]   = fen.extractBitBoard(WhiteArmy, Rook);
        armies[WhiteArmy].pieces[Knight] = fen.extractBitBoard(WhiteArmy, Knight);
        armies[WhiteArmy].pieces[Bishop] = fen.extractBitBoard(WhiteArmy, Bishop);
        armies[WhiteArmy].pieces[Pawn]   = fen.extractBitBoard(WhiteArmy, Pawn);
        armies[BlackArmy].pieces[King]   = fen.extractBitBoard(BlackArmy, King);
        armies[BlackArmy].pieces[Queen]  = fen.extractBitBoard(BlackArmy, Queen);
        armies[BlackArmy].pieces[Rook]   = fen.extractBitBoard(BlackArmy, Rook);
        armies[BlackArmy].pieces[Knight] = fen.extractBitBoard(BlackArmy, Knight);
        armies[BlackArmy].pieces[Bishop] = fen.extractBitBoard(BlackArmy, Bishop);
        armies[BlackArmy].pieces[Pawn]   = fen.extractBitBoard(BlackArmy, Pawn);
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
        if ((armies[WhiteArmy].pieces[King].popCount() != 1) ||
            (armies[BlackArmy].pieces[King].popCount() != 1)) {
            return false;
        }
        // kings shall not be in contact
        if (armies[WhiteArmy].pieces[King].activeCellsInMask(
            armies[BlackArmy].pieces[King].neighbourCells().bbs)) return false;

        // No pawns (of any color) in 1st or 8th ranks
        if (armies[WhiteArmy].pieces[Pawn].activeCellsInMask(
            RanksBB[r_1] | RanksBB[r_8])) return false;
        if (armies[BlackArmy].pieces[Pawn].activeCellsInMask(
            RanksBB[r_1] | RanksBB[r_8])) return false;

        // More that 16 pieces for army
        if (armies[WhiteArmy].numPieces() > 16) return false;
        if (armies[BlackArmy].numPieces() > 16) return false;

        // lastly check en passant cell validity
        return checkEnPassantTargetSquareValidity();
    }

    // -----------------------------------------------------------------
    bool ChessBoard::checkEnPassantTargetSquareValidity() const
    {
        // If en passant target square not defined, there is no problem
        if (enPassantTargetSquare.popCount() == 0)
            return true;

        // if more than one e.p. target square are defined,
        // there are problems for sure
        if (enPassantTargetSquare.popCount() > 1)
            return false;

        // if here, exactly one cell is marked as en passant targets

        // if e.p. target square is not in 3rd or 6th rank,
        // position is not valid
        if (!enPassantTargetSquare.activeCellsInMask(RanksBB[r_3] | RanksBB[r_6]))
            return false;

        // if here, exactly one cell in 3rd or 6th row is marked
        // as an en passant target
        BitBoard frontCell = enPassantTargetSquare;
        BitBoard backCell = enPassantTargetSquare;
        if (enPassantTargetSquare.activeCellsInMask(RanksBB[r_3])) {
            // e.p. target square is in 3rd row. Side to move shall
            // be the black, front (north) cell shall be occupied by
            // a white pawn and back (south) cell shall be empty
            if (sideToMove == BlackArmy) {
                frontCell.shiftNorth(1);
                backCell.shiftSouth(1);
                if ((armies[WhiteArmy].pieces[Pawn] & frontCell) == BitBoard(EmptyBB))
                    return false;
                if ((wholeArmyBitBoard() & backCell) != BitBoard(EmptyBB))
                    return false;
            }
            else {
                return false;
            }
        }
        else {
            // e.p. target square is in 6th row. Side to move shall
            // be the white, front (south) cell shall be occupied by
            // a black pawn and back (north) cell shall be empty
            if (sideToMove == WhiteArmy) {
                frontCell.shiftSouth(1);
                backCell.shiftNorth(1);
                if ((armies[BlackArmy].pieces[Pawn] & frontCell) == BitBoard(EmptyBB))
                    return false;
                if ((wholeArmyBitBoard() & backCell) != BitBoard(EmptyBB))
                    return false;
            }
            else {
                return false;
            }
        }

        // if here, e.p. target cell is OK
        return true;
    }
} // namespace cSzd