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
        return (armies[a].pieces[King] & controlledCells(enemyColor));
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
        // If stalemate, position is drawn
        if (isStaleMate())
            return true;

        // Fifty-moves rule: if 100 or more half-moves has been performed,
        // the position can be claimed as draw BUT if half-moves are less than
        // 150 the position is not declared drawn automatically. If the
        // half-moves are equal or greater than 150 the position is drawn.
        // From Wikipedia: https://en.wikipedia.org/wiki/Fifty-move_rule
        // The relevant part of the official FIDE laws of chess is quoted below:
        //     9.3 The game is drawn, upon a correct claim by a player having the move, if:
        //         9.3.1 he writes his move, which cannot be changed, on his scoresheet
        //               and declares to the arbiter his intention to make this move which
        //               will result in the last 50 moves by each player having been made
        //               without the movement of any pawn and without any capture, or
        //     (b) 9.3.2 the last 50 moves by each player have been completed without the
        //               movement of any pawn and without any capture.
        //
        // A claim does not have to be made at the first opportunity - it can be made any
        // time when there have been no captures or pawn moves in the last fifty moves.
        //
        // A game is not automatically declared a draw under the fifty-move rule - the draw
        // must be claimed by a player on his turn to move. Therefore, a game can continue
        // beyond a point where a draw could be claimed under the rule. [...]
        //
        // If seventy-five moves are made without a pawn move or capture being made, the
        // game is drawn unless the seventy-fifth move delivers a checkmate. No claim needs
        // to be made by either player, the draw is mandatorily applied by the arbiter.
        //     9.6 If one or both of the following occur(s) then the game is drawn:
        //         9.6.2 any series of at least 75 moves have been made by each player
        //               without the movement of any pawn and without any capture. If the
        //               last move resulted in checkmate, that shall take precedence.
        if (halfMoveClock >= 150)
            return true;

        return false;
    }

    bool ChessBoard::drawnCanBeCalledAndCannotBeRefused() const
    {
        // Drawn can be called by a player (and cannot be refused) for the fifty-moves rules
        // (see isDrawnPosition() function)
        if (halfMoveClock >= 100)
            return true;

        return false;
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
        if (armies[WhiteArmy].pieces[King] &
            armies[BlackArmy].pieces[King].neighbourCells()) {
            return false;
        }

        // No pawns (of any color) in 1st or 8th ranks
        if ((armies[WhiteArmy].pieces[Pawn] | armies[BlackArmy].pieces[Pawn]) &
              BitBoard(RanksBB[r_1] | RanksBB[r_8])) {
            return false;
        }

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

        // Clear the vector of moves
        moves.clear();

        // Search for moves...
        for (auto startPos = 0; (startPos < 64) && (foundPieces < bbToCheck.popCount()); startPos++) {
            if (bbToCheck[startPos] != 0) {
                // piece found in position startPos
                foundPieces++;
                pType = armies[sideToMove].getPieceInCell(static_cast<Cell>(startPos));
                moveBB = armies[sideToMove].possibleMovesCellsByPieceTypeAndPosition(pType,
                                static_cast<Cell>(startPos), armies[opponentColor].occupiedCells());
                auto foundMove = 0;
                for (auto destPos = 0; (destPos < 64) && (foundMove < moveBB.popCount()); destPos++) {
                    if (moveBB[destPos] != 0) {
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
                if (pType == King) {
                    checkForCastlingMoves(moves);
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

    // ---------------------------------------------------------------------------------
    void ChessBoard::checkForCastlingMoves(std::vector<ChessMove> &moves) const
    {
        // This function checks is king castling moves are currently possible.
        // For the castling to be possible, the appropriate Cells in the
        // castlingAvailability BitBoard shall be set, and the temporarly
        // inhibit factor shall not be present at this time. Inhibit factors are:
        //  - king is in check
        //  - Friendly or foe pieces present between the king and the rook(s)
        //  - At least one of the cells when the king pass, or the destination
        //    cell of the king is under check of any enemy piece

        // If any king is in check we are unlucky...
        if (armyInCheck() != InvalidArmy)
            return;

        if (sideToMove == WhiteArmy) {
            if (castlingAvailability & BitBoard(g1)) {
                // White 0-0 is still possible, checks for inhibit factors
                // 1. Friend or foe pieces occupy one of f1 and g1
                // 2. During movement, the king shall not occupy any
                //    foe controlled cell
                if (!((wholeArmyBitBoard() | controlledCells(BlackArmy)) & BitBoard({f1, g1}))) {
                    // ***** Add white 0-0 ******
                    moves.push_back(chessMove(King, e1, g1));
                }
            }
            if (castlingAvailability & BitBoard(c1)) {
                // White 0-0-0 is still possible, checks for inhibit factors
                // 1. Friend or foe pieces occupy one of b1, c1, d1
                // 2. During movement, the king shall not occupy any
                //    foe controlled cell
                if (!((wholeArmyBitBoard() | controlledCells(BlackArmy)) & BitBoard({b1, c1, d1}))) {
                    // Cells are free and not controlled by enemy
                    // ***** Add white 0-0-0 ******
                    moves.push_back(chessMove(King, e1, c1));
                }
            }
        }
        else if (sideToMove == BlackArmy) {
            if (castlingAvailability & BitBoard(g8)) {
                // Black 0-0 is still possible, checks for inhibit factors
                // 1. Friend or foe pieces occupy one of f8 and g8
                // 2. During movement, the king shall not occupy any
                //    foe controlled cell
                if (!((wholeArmyBitBoard() | controlledCells(WhiteArmy)) & BitBoard({f8, g8}))) {
                    // ***** Add black 0-0 ******
                    moves.push_back(chessMove(King, e8, g8));
                }
            }
            if (castlingAvailability & BitBoard(c8)) {
                // Black 0-0-0 is still possible, checks for inhibit factors
                // 1. Friend or foe pieces occupy one of b8, c8, d8
                // 2. During movement, the king shall not occupy any
                //    foe controlled cell
                if (!((wholeArmyBitBoard() | controlledCells(WhiteArmy)) & BitBoard({b8, c8, d8}))) {
                    // Cells are free and not controlled by enemy
                    // ***** Add black 0-0-0 ******
                    moves.push_back(chessMove(King, e8, c8));
                }
            }
        }
    }

    // ---------------------------------------------------------------------------------
    // Modify the ChessBoard assuming the specified move is executed by the active Army.
    // N.B.: This method does not perform any check on move validity: it is responsibility
    // of the caller to perform such check (possibly using the generateLegalMoves() method)
    void ChessBoard::doMove(const ChessMove &m)
    {
        ArmyColor enemyArmy = (sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        Piece movedPiece = chessMoveGetMovedPiece(m);
        Piece takenPiece = chessMoveGetTakenPiece(m);
        Cell startCell = chessMoveGetStartingCell(m);
        Cell destCell = chessMoveGetDestinationCell(m);

        // Check if it is a castling move and in such a case move the rook
        // (the king will be moved by the "normal move" code below).
        // Additionally, the castlingAvailability bitboard is updated
        if (isACastlingMove(m)) {
            if (sideToMove == WhiteArmy) {
                // white army
                if (destCell == g1) {
                    // white 0-0
                    armies[sideToMove].pieces[Rook] ^=
                                BitBoard({h1, f1});
                } else {
                    // white 0-0-0
                    armies[sideToMove].pieces[Rook] ^=
                                BitBoard({a1, d1});
                }
                castlingAvailability &= ~BitBoard({c1, g1});
            } else {
                // black army
                if (destCell == g8) {
                    // black 0-0
                    armies[sideToMove].pieces[Rook] ^=
                                BitBoard({h8, f8});
                } else {
                    // black 0-0-0
                    armies[sideToMove].pieces[Rook] ^=
                                BitBoard({a8, d8});
                }
                castlingAvailability &= ~BitBoard({c8, g8});
            }
        }
        armies[sideToMove].pieces[movedPiece] ^=
            BitBoard({startCell, destCell});
        if (takenPiece != InvalidPiece) {
            // remove the taken piece from the opposite army
            // FIXME --- TO BE COMPLETED --- manage en-passant capture!
            armies[enemyArmy].pieces[takenPiece] ^= BitBoard(destCell);
        }
        // If we move a Pawn or we capture a piece, reset half move counter,
        // otherwise increases it
        if ((movedPiece == Pawn) || (takenPiece != InvalidPiece))
            halfMoveClock = 0;
        else
            ++(halfMoveClock);
        // If the move was to Black, increase full moves counter
        if (sideToMove == BlackArmy)
            ++(fullMoves);

        // Updates castling availability
        // If a King move is performed from the king initial position,
        // castling availability could change
        if (movedPiece == King) {
            if ((sideToMove == WhiteArmy) && (startCell == e1)) {
                castlingAvailability &= ~BitBoard({c1, g1});
            }
            else if ((sideToMove == BlackArmy) && (startCell == e8)) {
                castlingAvailability &= ~BitBoard({c8, g8});
            }
        }
        // If a Rook move from initial position is performed,
        // castling availability could change
        if (movedPiece == Rook) {
            if (sideToMove == WhiteArmy) {
                if (startCell == a1)
                    castlingAvailability &= ~BitBoard(c1);
                if (startCell == h1)
                    castlingAvailability &= ~BitBoard(g1);
            }
            else if (sideToMove == BlackArmy) {
                if (startCell == a8)
                    castlingAvailability &= ~BitBoard(c8);
                if (startCell == h8)
                    castlingAvailability &= ~BitBoard(g8);
            }
        }
        // If a Rook is taken, castling availability could change
        if (takenPiece == Rook) {
            if (sideToMove == WhiteArmy) {
                if (destCell == a8)
                    castlingAvailability &= ~BitBoard(c8);
                else if (destCell == h8)
                    castlingAvailability &= ~BitBoard(g8);
            }
            else if (sideToMove == BlackArmy) {
                if (destCell == a1)
                    castlingAvailability &= ~BitBoard(c1);
                else if (destCell == h1)
                    castlingAvailability &= ~BitBoard(g1);
            }
        }

        // Updates en passant target square
        enPassantTargetSquare = BitBoard(chessMoveGetEnPassantCell(m));

        // Updates side to move
        sideToMove = enemyArmy;
    }

    std::ostream &operator<<(std::ostream &os, const ChessBoard &cb)
    {
        // We want to represent an ChessBoard like a Bitboard, with
        // piece symbols instead of the 'x' in the active cells of there
        // two armies. We use "K Q B N R P" for white pieces
        // and "k q b n r p" for black pieces. Additional info, like
        // side to move, castling availability, etc. are also printed
        //
        // Examples:
        //  - ChessBoard in initial position:
        //   _ _ _ _ _ _ _ _
        // 8|r|n|b|q|k|b|n|r|
        // 7|p|p|p|p|p|p|p|p|
        // 6| | | | | | | | |
        // 5| | | | | | | | |
        // 4| | | | | | | | |
        // 3| | | | | | | | |
        // 2|P|P|P|P|P|P|P|P|
        // 1|R|N|B|Q|K|B|N|R|
        //   a b c d e f g h
        //

        os << std::endl << "  * ChessBoard *";
        os << std::endl << "  _ _ _ _ _ _ _ _";
        auto fillchar = ' ';
        for (auto rank = 7; rank >= 0; rank--) {
            os << std::endl << rank+1 << '|';
            auto startPos = rank * 8;
            if (rank == 0) fillchar = '_';
            for (auto file = 0; file < 8; file++) {
                if (cb.armies[WhiteArmy].pieces[King][startPos + file] != 0)
                   os << 'K' << '|';
                else if (cb.armies[WhiteArmy].pieces[Queen][startPos + file] != 0)
                   os << 'Q' << '|';
                else if (cb.armies[WhiteArmy].pieces[Bishop][startPos + file] != 0)
                   os << 'B' << '|';
                else if (cb.armies[WhiteArmy].pieces[Knight][startPos + file] != 0)
                   os << 'N' << '|';
                else if (cb.armies[WhiteArmy].pieces[Rook][startPos + file] != 0)
                   os << 'R' << '|';
                else if (cb.armies[WhiteArmy].pieces[Pawn][startPos + file] != 0)
                   os << 'P' << '|';
                else if (cb.armies[BlackArmy].pieces[King][startPos + file] != 0)
                   os << 'k' << '|';
                else if (cb.armies[BlackArmy].pieces[Queen][startPos + file] != 0)
                   os << 'q' << '|';
                else if (cb.armies[BlackArmy].pieces[Bishop][startPos + file] != 0)
                   os << 'b' << '|';
                else if (cb.armies[BlackArmy].pieces[Knight][startPos + file] != 0)
                   os << 'n' << '|';
                else if (cb.armies[BlackArmy].pieces[Rook][startPos + file] != 0)
                   os << 'r' << '|';
                else if (cb.armies[BlackArmy].pieces[Pawn][startPos + file] != 0)
                   os << 'p' << '|';
                else
                   os << fillchar << '|';
            }
        }
        os << std::endl << "  a b c d e f g h" << std::endl;

        os << std::endl << "  *Castling av.*";
        os << cb.castlingAvailability << std::endl;
        os << "  *en-pass. t.s.*";
        os << cb.enPassantTargetSquare << std::endl;

        return os;
    }

    // --------------------------------------------------------------------------------------------------
    // Private methods

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
        if (enPassantTargetSquare & ~BitBoard(RanksBB[r_3] | RanksBB[r_6]))
            return false;

        // if here, exactly one cell in 3rd or 6th row is marked
        // as an en passant target
        BitBoard frontCell = enPassantTargetSquare;
        BitBoard backCell = enPassantTargetSquare;
        if (enPassantTargetSquare & BitBoard(RanksBB[r_3])) {
            // e.p. target square is in 3rd row. Side to move shall
            // be the black, front (north) cell shall be occupied by
            // a white pawn and back (south) cell shall be empty
            if (sideToMove == BlackArmy) {
                frontCell.shiftNorth(1);
                backCell.shiftSouth(1);
                if (!(armies[WhiteArmy].pieces[Pawn] & frontCell))
                    return false;
                if (wholeArmyBitBoard() & backCell)
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
                if (!(armies[BlackArmy].pieces[Pawn] & frontCell))
                    return false;
                if (wholeArmyBitBoard() & backCell)
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
