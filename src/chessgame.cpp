#include <algorithm>
#include "cmdsuzdal/chessgame.h"

namespace cSzd
{

    // --- Constructor(s) --------------------------------------
    ChessGame::ChessGame()
    {
        // The default constructors of FENRecord and ChessBoard
        // automatically prepares the initial standard position,
        // here we have only to prepare the vector of the possible
        // moves
        board.generateLegalMoves(possibleMoves);
    }
    ChessGame::ChessGame(const FENRecord &fen) :
        initialPosition(fen.fen),
        board(fen)
    {
        board.generateLegalMoves(possibleMoves);
    }
    ChessGame::ChessGame(const std::string_view fenStr) :
        initialPosition(fenStr),
        board(fenStr)
    {
        board.generateLegalMoves(possibleMoves);
    }
    // ---------------------------------------------------------

    void ChessGame::addMove(const ChessMove &m)
    {
        // do the moves
        board.doMove(m);
        // updates possible Moves
        board.generateLegalMoves(possibleMoves);
    }

    // ----------------------------------------------------------------------------------
    // Converts a string with a move in notational format to a ChessMove.
    // This function performs some checks, for example search the piece
    // that can perform the move and "complete" the move appropriately.
    // For example, il the string "e4" is found, this is a pawn move, and
    // of the side to move is White, the pawn can be only on "e3" or "e2".
    // If for example the pawn is present in e2, the following move is returned:
    //     chessMove(Pawn, e2, e4)
    // Consistency about the side to move and the current board status are also
    // performed. If the move is not valid/legal InvalidMove is returned.
    ChessMove ChessGame::checkNotationMove(const std::string_view nMove) const
    {
        ChessMove cm = InvalidMove;
        // Manages empty string
        if (nMove.size() == 0) {
            return InvalidMove;
        }

        if (nMove.at(0) == '0') {
            // This can be an castling move
            cm = castlingMoveNotationEvaluationAndConversion(nMove);
        }
        else if (nMove.size() == 2) {
            // just the destination cell is present, so this is a
            // simple (no-capture) pawn move.
            cm = simplePawnMoveNotationEvaluationAndConversion(nMove);
        }

        if (cm != InvalidMove) {
            // Move found: Check for validity (the move shall
            // be in the list of legal moves)
            if (std::find(possibleMoves.begin(), possibleMoves.end(), cm) != possibleMoves.end()) {
                // the move is legal
                return cm;
            }
        }
        return InvalidMove;
    }

    // ----------------------------------------------------------------------------------
    // Private methods

    // -----------------------------------------------------------------
    ChessMove ChessGame::castlingMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        if (board.sideToMove == WhiteArmy) {
            if ((nMove == "0-0") || (nMove == "00")) {
                return chessMove(King, e1, g1);
            }
            if ((nMove == "0-0-0") || (nMove == "000")) {
                return chessMove(King, e1, c1);
            }
        }
        else if (board.sideToMove == BlackArmy) {
            if ((nMove == "0-0") || (nMove == "00")) {
                return chessMove(King, e8, g8);
            }
            if ((nMove == "0-0-0") || (nMove == "000")) {
                return chessMove(King, e8, c8);
            }
        }
        return InvalidMove;
    }

    // -----------------------------------------------------------------
    ChessMove ChessGame::simplePawnMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        // just the destination cell is present, so this is a
        // simple (no-capture) pawn move. The only problem is
        // to find the starting cell. The position depends on
        // side to move and destination rank.
        // For example, "e4" when the side to move is white can be converted in:
        //    chessMove(Pawn, e2, e4) or
        //    chessMove(Pawn, e2, e3)
        // depending on the starting position of the pawn
        // If instead the side to move is black, "e4" can only be converted in:
        //    chessMove(Pawn, e5, e4)
        // If no pawn is found in the possible starting position,
        // InvalidMove is returned
        // -----------------------------
        Cell destCell = toCell(nMove);
        if (board.sideToMove == WhiteArmy) {
            if (rank(destCell) > r_2) {
                Cell startCell = static_cast<Cell>(destCell - 8);
                Piece p = board.armies[board.sideToMove].getPieceInCell(startCell);
                if (p == Pawn)
                    return chessMove(Pawn, startCell, destCell);
                else if (rank(destCell) == r_4) {
                    startCell = static_cast<Cell>(destCell - 16);
                    p = board.armies[board.sideToMove].getPieceInCell(startCell);
                    if (p == Pawn)
                        return chessMove(Pawn, startCell, destCell);
                }
            }
        }
        else if (board.sideToMove == BlackArmy) {
            if (rank(destCell) < r_7) {
                Cell startCell = static_cast<Cell>(destCell + 8);
                Piece p = board.armies[board.sideToMove].getPieceInCell(startCell);
                if (p == Pawn)
                    return chessMove(Pawn, startCell, destCell);
                else if (rank(destCell) == r_5) {
                    startCell = static_cast<Cell>(destCell + 16);
                    p = board.armies[board.sideToMove].getPieceInCell(startCell);
                    if (p == Pawn)
                        return chessMove(Pawn, startCell, destCell);
                }
            }
        }
        return InvalidMove;
    }






} // namespace cSzd
