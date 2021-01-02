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

    // Generates all the legal moves for the Army starting from the current position
    // taking into account an opponent Army. The opponent army is necessary to generate
    // the move, but also to check for the legality of moves: illegal moves are those
    // that places the King in check
    void ChessBoard::generateLegalMoves(std::vector<ChessMove> &moves)
    {
        generateKingLegalMoves(moves);
        generateKnightsLegalMoves(moves);
        generateBishopsLegalMoves(moves);
        generateRooksLegalMoves(moves);
        generateQueensLegalMoves(moves);
        generatePawnsLegalMoves(moves);
    }

    void ChessBoard::generateKingLegalMoves(std::vector<ChessMove> &moves)
    {
        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        BitBoard moveBB;
        int startPos;
        // before to proceed we need the king position. Only one king is present in an army
        for (startPos = 0; startPos < 64; startPos++) {
            if (armies[sideToMove].pieces[King].bbs[startPos] != 0)
                break;
        }
        moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(King, armies[sideToMove].getKingPosition());
        // remove the invalid moves (the ones that places the king under check)
        moveBB &= ~armies[opponentColor].controlledCells();
        auto foundCells = 0;
        for (auto destPos = 0; (destPos < 64) && (foundCells < moveBB.popCount()); destPos++) {
            if (moveBB.bbs[destPos] != 0) {
                ++foundCells;
                moves.push_back(chessMove(King,
                    static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                    armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos))));
            }
        }
    }

    // ---------------------------------------------------------------------------------
    void ChessBoard::generateKnightsLegalMoves(std::vector<ChessMove> &moves)
    {
        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        // Iterates over all knights
        BitBoard moveBB;
        auto foundKnights = 0;
        for (auto startPos = 0; (startPos < 64) && (foundKnights < armies[sideToMove].pieces[Knight].popCount()); startPos++) {
            if (armies[sideToMove].pieces[Knight].bbs[startPos] != 0) {
                // knight in position ndx
                foundKnights++;
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(Knight, static_cast<Cell>(startPos));
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB.bbs[destPos] != 0) {
                        ++foundMove;
                        auto takenPiece = armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos));
                        // Possible move found:
                        //    Knight from startPos --- to ---> destPos, taking takenPiece (can be InvalidPiece)
                        // We need to validate the move: after the move the king shall not be in check
                        // otherwise the move is not valid and shall be discarded
                        // ...move the knight
                        armies[sideToMove].pieces[Knight] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        // ...remove the piece from the opponent army if necessary
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                        // ... check for check
                        if (!armyIsInCheck(sideToMove)) {
                            // If at the end the move is valid, it can be added to the vector of moves
                            moves.push_back(chessMove(Knight,
                                static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                                takenPiece));
                        }
                        // ...restore the armies
                        armies[sideToMove].pieces[Knight] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                    }
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------
    void ChessBoard::generateBishopsLegalMoves(std::vector<ChessMove> &moves)
    {
        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        // Iterates over all bishops
        BitBoard moveBB;
        auto foundPieces = 0;
        for (auto startPos = 0; (startPos < 64) && (foundPieces < armies[sideToMove].pieces[Bishop].popCount()); startPos++) {
            if (armies[sideToMove].pieces[Bishop].bbs[startPos] != 0) {
                // piece in position ndx
                foundPieces++;
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(Bishop, static_cast<Cell>(startPos),
                                                             armies[opponentColor].occupiedCells());
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB.bbs[destPos] != 0) {
                        ++foundMove;
                        auto takenPiece = armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos));
                        // Possible move found:
                        //    Bishop from startPos --- to ---> destPos, taking takenPiece (can be InvalidPiece)
                        // We need to validate the move: after the move the king shall not be in check
                        // otherwise the move is not valid and shall be discarded
                        // ...move the piece
                        armies[sideToMove].pieces[Bishop] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        // ...remove the piece from the opponent army if necessary
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                        // ... check for check
                        if (!armyIsInCheck(sideToMove)) {
                            // If at the end the move is valid, it can be added to the vector of moves
                            moves.push_back(chessMove(Bishop,
                                static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                                takenPiece));
                        }
                        // ...restore the armies
                        armies[sideToMove].pieces[Bishop] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                    }
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------
    void ChessBoard::generateRooksLegalMoves(std::vector<ChessMove> &moves)
    {
        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        // Iterates over all rooks
        BitBoard moveBB;
        auto foundPieces = 0;
        for (auto startPos = 0; (startPos < 64) && (foundPieces < armies[sideToMove].pieces[Rook].popCount()); startPos++) {
            if (armies[sideToMove].pieces[Rook].bbs[startPos] != 0) {
                // piece in position ndx
                foundPieces++;
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(Rook, static_cast<Cell>(startPos),
                                                             armies[opponentColor].occupiedCells());
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB.bbs[destPos] != 0) {
                        ++foundMove;
                        auto takenPiece = armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos));
                        // Possible move found:
                        //    Rook from startPos --- to ---> destPos, taking takenPiece (can be InvalidPiece)
                        // We need to validate the move: after the move the king shall not be in check
                        // otherwise the move is not valid and shall be discarded
                        // ...move the piece
                        armies[sideToMove].pieces[Rook] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        // ...remove the piece from the opponent army if necessary
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                        // ... check for check
                        if (!armyIsInCheck(sideToMove)) {
                            // If at the end the move is valid, it can be added to the vector of moves
                            moves.push_back(chessMove(Rook,
                                static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                                takenPiece));
                        }
                        // ...restore the armies
                        armies[sideToMove].pieces[Rook] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                    }
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------
    void ChessBoard::generateQueensLegalMoves(std::vector<ChessMove> &moves)
    {
        ArmyColor opponentColor = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        // Iterates over all queens
        BitBoard moveBB;
        auto foundPieces = 0;
        for (auto startPos = 0; (startPos < 64) && (foundPieces < armies[sideToMove].pieces[Queen].popCount()); startPos++) {
            if (armies[sideToMove].pieces[Queen].bbs[startPos] != 0) {
                // piece in position ndx
                foundPieces++;
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(Queen, static_cast<Cell>(startPos),
                                                             armies[opponentColor].occupiedCells());
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB.bbs[destPos] != 0) {
                        ++foundMove;
                        auto takenPiece = armies[opponentColor].getPieceInCell(static_cast<Cell>(destPos));
                        // Possible move found:
                        //    Queen from startPos --- to ---> destPos, taking takenPiece (can be InvalidPiece)
                        // We need to validate the move: after the move the king shall not be in check
                        // otherwise the move is not valid and shall be discarded
                        // ...move the piece
                        armies[sideToMove].pieces[Queen] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        // ...remove the piece from the opponent army if necessary
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                        // ... check for check
                        if (!armyIsInCheck(sideToMove)) {
                            // If at the end the move is valid, it can be added to the vector of moves
                            moves.push_back(chessMove(Queen,
                                static_cast<Cell>(startPos), static_cast<Cell>(destPos),
                                takenPiece));
                        }
                        // ...restore the armies
                        armies[sideToMove].pieces[Queen] ^=
                                BitBoard({static_cast<Cell>(startPos), static_cast<Cell>(destPos)});
                        if (takenPiece != InvalidPiece) {
                            armies[opponentColor].pieces[takenPiece] ^= BitBoard(static_cast<Cell>(destPos));
                        }
                    }
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------
    void ChessBoard::generatePawnsLegalMoves(std::vector<ChessMove> &moves)
    {
        // FIXME --- TO BE COMPLETED
    }






} // namespace cSzd