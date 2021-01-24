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
        else if (nMove.find("=") != std::string::npos) {
            // Promotion move!
            cm = promotionMoveNotationEvaluationAndConversion(nMove);
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
    ChessMove ChessGame::promotionMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        if (nMove.size() == 4) {
            // If the lengh is 4, the move is the simplest form of the promotion move
            // For example, for white:
            //   <f>8=<P>   - where <f> is the file (a...h),
            //        <P> the promoted piece (one of (Q, R, B, N))
            // The '=' shall be in the 3rd positions
            if (nMove.at(2) != '=') {
                // invalid notation move
                return InvalidMove;
            }
            // extract the file from the 1st char
            char file_c = nMove.at(0) - 'a';
            if ((file_c < 0) || (file_c >= 8)) {
                // invalid file
                return InvalidMove;
            }
            File file = static_cast<File>(file_c);
            // extract the promoted piece from the 4th character in string
            char ppiece_c =  nMove.at(3);
            Piece ppiece = InvalidPiece;
            switch (ppiece_c) {
                case 'Q':
                    ppiece = Queen;
                    break;
                case 'N':
                    ppiece = Knight;
                    break;
                case 'R':
                    ppiece = Rook;
                    break;
                case 'B':
                    ppiece = Bishop;
                    break;
                default:
                    return InvalidMove;
                    break;
            }
            if  (board.sideToMove == WhiteArmy) {
                // The destination cell shall be in the 2nd position and shall be an 8
                if (nMove.at(1) != '8') {
                    // invalid notation move
                    return InvalidMove;
                }
                return chessMove(Pawn, toCell(file, r_7), toCell(file, r_8), InvalidPiece, ppiece);
            }
            if  (board.sideToMove == BlackArmy) {
                // The destination cell shall be in the 2nd position and shall be an 1
                if (nMove.at(1) != '1') {
                    // invalid notation move
                    return InvalidMove;
                }
                return chessMove(Pawn, toCell(file, r_2), toCell(file, r_1), InvalidPiece, ppiece);
            }
        }
        else if (nMove.size() == 6) {
            // If size of move is 6 it can be a promotion move with capture
            return promotionMoveWithCaptureNotationEvaluationAndConversion(nMove);
        }
        return InvalidMove;
    }


    ChessMove ChessGame::promotionMoveWithCaptureNotationEvaluationAndConversion(const std::string_view nMove) const
     {
        // Format of a promotion move for white:
        //
        //   <fs>x<fd>8=<P>   - where:
        //     <fs> is the starting file (a...h),
        //     <fd> is the destination file (a...h)
        //     <P> the promoted piece (one of (Q, R, B, N))
        // - The 'x' shall be in the 2nd positions
        // - The '=' shall be in the 5th positions
        // - side to move shall have a pawn in <fs>7 (we will not check for this, move validity check will do this)
        // - enemy shall have a piece in <fd>8. We will check for this because we need the piece type
        //   to compose the move
        if ((nMove.at(1) != 'x') || (nMove.at(4) != '=')) {
            // invalid notation move
            return InvalidMove;
        }
        char fileStart_c = nMove.at(0) - 'a';
        if ((fileStart_c < 0) || (fileStart_c >= 8)) {
            // invalid file
            return InvalidMove;
        }
        File fileStart = static_cast<File>(fileStart_c);
        char fileDest_c = nMove.at(2) - 'a';
        if ((fileDest_c < 0) || (fileDest_c >= 8)) {
            // invalid file
            return InvalidMove;
        }
        File fileDest = static_cast<File>(fileDest_c);
        // extract the promoted piece from the 6th character in string
        char ppiece_c =  nMove.at(5);
        Piece ppiece = InvalidPiece;
        switch (ppiece_c) {
            case 'Q':
                ppiece = Queen;
                break;
            case 'N':
                ppiece = Knight;
                break;
            case 'R':
                ppiece = Rook;
                break;
            case 'B':
                ppiece = Bishop;
                break;
            default:
                return InvalidMove;
                break;
        }
        ArmyColor opponentColor = (board.sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        if  (board.sideToMove == WhiteArmy) {
            // The destination cell shall be in the 4th position and shall be an 8
            if (nMove.at(3) != '8') {
                // invalid notation move
                return InvalidMove;
            }
            // The enemy shall have a piece in toCell(fileDest, 8) (in any case we do not check)
            Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, r_8));
            return chessMove(Pawn, toCell(fileStart, r_7), toCell(fileDest, r_8), cPiece, ppiece);
        }
        else if  (board.sideToMove == BlackArmy) {
            // The destination cell shall be in the 4th position and shall be an 1
            if (nMove.at(3) != '1') {
                // invalid notation move
                return InvalidMove;
            }
            // The enemy shall have a piece in toCell(fileDest, 8) (in any case we do not check)
            Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, r_1));
            return chessMove(Pawn, toCell(fileStart, r_2), toCell(fileDest, r_1), cPiece, ppiece);
        }

        // If here sideToMove has an incorrect value
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
