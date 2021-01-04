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
    BitBoard ChessBoard::controlledCells(ArmyColor a) const
    {
        ArmyColor enemyColor = (a == WhiteArmy) ? BlackArmy : WhiteArmy;
        return armies[a].controlledCells(armies[enemyColor].occupiedCells());
    }

    bool ChessBoard::armyIsInCheck(ArmyColor a) const
    {
        // An army is in check if King position intersecates
        // the controlled cells of the opposite army
        ArmyColor enemyColor = (a == WhiteArmy) ? BlackArmy : WhiteArmy;
        return ((armies[a].pieces[King] & controlledCells(enemyColor))
             != BitBoard(EmptyBB)) ? true : false;
    }
    // -----------------------------------------------------------------
    ArmyColor ChessBoard::armyInCheck() const
    {
        // A king is in check if its position intersecates
        // the controlled cells of the opposite army
        auto blackKingInCkeck = armyIsInCheck(BlackArmy);
        auto whiteKingInCkeck = armyIsInCheck(WhiteArmy);

        // if both kings are in check, position is not valid
        // and InvalidArmy is returned
        if (blackKingInCkeck && whiteKingInCkeck)
            return InvalidArmy;
        else if (blackKingInCkeck)
            return BlackArmy;
        else if (whiteKingInCkeck)
            return WhiteArmy;

        return InvalidArmy;
    }
    // -----------------------------------------------------------------
    bool ChessBoard::isCheckMate() const
    {
        // If the army with the move is in check and there are no valid moves,
        // this is checkmate
        if (armyInCheck() == sideToMove) {
            std::vector<ChessMove> moves;
            generateLegalMoves(moves);
            if (moves.size() == 0)
                return true;
        }
        return false;
    }
    // -----------------------------------------------------------------
    bool ChessBoard::isStaleMate() const
    {
        // If the army with the move is NOT in check and there are
        // no valid moves, this is stalemate
        if (armyInCheck() == InvalidArmy) {
            std::vector<ChessMove> moves;
            generateLegalMoves(moves);
            if (moves.size() == 0)
                return true;
        }
        return false;
    }
    // -----------------------------------------------------------------
    bool ChessBoard::isDrawnPosition() const
    {
        return isStaleMate();
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

        // No More that 16 pieces for army shall be present
        if (armies[WhiteArmy].numPieces() > 16) return false;
        if (armies[BlackArmy].numPieces() > 16) return false;

        // If both kings are in check, position is not valid
        if (armyIsInCheck(WhiteArmy) && armyIsInCheck(BlackArmy)) return false;

        // If king of an army is in check and move is assigned
        // to other army, position is not valid
        if (armyIsInCheck(WhiteArmy) && sideToMove == BlackArmy) return false;
        if (armyIsInCheck(BlackArmy) && sideToMove == WhiteArmy) return false;

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

    // ---------------------------------------------------------------------------------
    // Generates all the legal moves for the Army starting from the current position
    // taking into account an opponent Army. The opponent army is necessary to generate
    // the move, but also to check for the legality of moves: illegal moves are those
    // that places the King in check. If a valid Piece type is specified, only the
    // moves for that Piece type are generated, otherwise, the moves for all the
    // pieces are generated
    void ChessBoard::generateLegalMoves(std::vector<ChessMove> &moves, Piece pType) const
    {
        ChessBoard fakeCB = *this;

        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        // Iterates over all Pieces of the specified type.
        // If pType is InvalidPiece, all the piece are considered
        BitBoard moveBB;
        auto foundPieces = 0;
        BitBoard bbToCheck;
        if (pType == InvalidPiece) {
            bbToCheck = armies[sideToMove].occupiedCells();
        }
        else {
            bbToCheck = armies[sideToMove].pieces[pType];
        }
        for (auto startPos = 0; (startPos < 64) && (foundPieces < bbToCheck.popCount()); startPos++) {
            if (bbToCheck.bbs[startPos] != 0) {
                // piece found in position startPos
                foundPieces++;
                pType = armies[sideToMove].getPieceInCell(static_cast<Cell>(startPos));
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(pType,
                                static_cast<Cell>(startPos), armies[opponentColor].occupiedCells());
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB.bbs[destPos] != 0) {
                        ++foundMove;
                        auto takenPiece = armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos));
                        // Possible move found:
                        //    Piece of type pType from startPos --- to ---> destPos, taking takenPiece (can be InvalidPiece)
                        // We need to validate the move: after the move the king shall not be in check
                        // otherwise the move is not valid and shall be discarded
                        // ...move the knight
                        fakeCB.armies[sideToMove].pieces[pType] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        // ...remove the piece from the opponent army if necessary
                        if (takenPiece != InvalidPiece) {
                            fakeCB.armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                        // ... check for check
                        if (!fakeCB.armyIsInCheck(sideToMove)) {
                            // If at the end the move is valid, it can be added to the vector of moves.
                            // If the piece is a pawn and the destination position is on the last rank,
                            // this is a promotion, so the moves to be added are four: one for each type
                            // of promotion (Queen, Rook, Bishop, Knight). To add this kind of moves, we
                            // use a dedicated function
                            if ((pType == Pawn) && (((sideToMove == WhiteArmy) && (rank(static_cast<Cell>(destPos)) == r_8)) ||
                                                    ((sideToMove == BlackArmy) && (rank(static_cast<Cell>(destPos)) == r_1)))) {
                                // promotion moves
                                addPromotionMoves(moves, static_cast<Cell>(startPos),
                                                    static_cast<Cell>(destPos),
                                                    takenPiece);

                            } else {
                                // normal move
                                moves.push_back(chessMove(pType,
                                    static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                                    takenPiece));
                            }
                        }
                        // ...restore the armies
                        fakeCB.armies[sideToMove].pieces[pType] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        if (takenPiece != InvalidPiece) {
                            fakeCB.armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                    }
                }
                if (pType == Pawn) {
                    checkForEnPassant(static_cast<Cell>(startPos), moves);
                }
            }
        }
    }

    void ChessBoard::addPromotionMoves(std::vector<ChessMove> &moves, Cell startPos,
                                       Cell destPos, Piece takenPiece) const
    {
        // add all the possible promotions
         moves.push_back(chessMove(Pawn, startPos, destPos, takenPiece, Queen));
         moves.push_back(chessMove(Pawn, startPos, destPos, takenPiece, Rook));
         moves.push_back(chessMove(Pawn, startPos, destPos, takenPiece, Bishop));
         moves.push_back(chessMove(Pawn, startPos, destPos, takenPiece, Knight));
    }

    void ChessBoard::checkForEnPassant(Cell c, std::vector<ChessMove> &moves) const
    {
        Rank pawnRank;
        File pawnFile;
        auto enPassantCell = enPassantTargetSquare.activeCell();

        if (enPassantCell != InvalidCell) {
            pawnRank = rank(c);
            if ((sideToMove == WhiteArmy) && pawnRank == r_5) {
                // there are chances that we have an en passant move for white
                pawnFile = file(c);
                if (pawnFile > f_a) {
                    // checks the file to the left of the pawn
                    if (c + 7 == enPassantCell) {
                        // en passant move!
                        moves.push_back(chessMove(Pawn, c, enPassantCell, Pawn));
                    }
                }
                if (pawnFile < f_h) {
                    // checks the file to the right of the pawn
                    if (c + 9 == enPassantCell) {
                        // en passant move!
                        moves.push_back(chessMove(Pawn, c, enPassantCell, Pawn));
                    }
                }
            }
            if ((sideToMove == BlackArmy) && pawnRank == r_4) {
                // there are chances that we have an en passant move for black
                pawnFile = file(c);
                if (pawnFile > f_a) {
                    // checks the file to the right of the pawn
                    if (c - 9 == enPassantCell) {
                        // en passant move!
                        moves.push_back(chessMove(Pawn, c, enPassantCell, Pawn));
                    }
                }
                if (pawnFile < f_h) {
                    // checks the file to the left of the pawn
                    if (c - 7 == enPassantCell) {
                        // en passant move!
                        moves.push_back(chessMove(Pawn, c, enPassantCell, Pawn));
                    }
                }
            }
        }
    }

} // namespace cSzd