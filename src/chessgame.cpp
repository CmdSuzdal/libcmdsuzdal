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
        // WARNING: MOVES WITH CHECK SYMBOL AT THE END (+, ++, #)
        // are currently not supported

        ChessMove cm = InvalidMove;
        // Manages empty string
        if (nMove.size() == 0)
            return InvalidMove;

        // If no side has the move, returns InvalidMove
        if (board.sideToMove == InvalidArmy)
            return InvalidMove;

        if (nMove.at(0) == '0') {
            // This can be an castling move
            cm = castlingMoveNotationEvaluationAndConversion(nMove);
        }
        else {
            // If the move starts with 'K', 'Q', 'R', 'B' or 'N'
            // it is a piece move, otherwise it is a pawn move
            std::string pieces = "KQRBN";
            if (pieces.find(nMove.at(0)) != std::string::npos) {
                // piece move
                cm = pieceMoveNotationEvaluationAndConversion(nMove);
            }
            else {
                // pawn move
                cm = pawnMoveNotationEvaluationAndConversion(nMove);
            }
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
    ChessMove ChessGame::pieceMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        if (nMove.find('x') != std::string::npos) {
            // capture move
            return pieceCaptureMoveNotationEvaluationAndConversion(nMove);
        }

        // The generic "Simple" tree character Piece
        // (no capture, no ambiguity) move has the format:
        //      <Piece><cell>
        //
        // where:
        //      <Piece> = one of K | Q | B | N | R
        //      <cell>  = the destination cell, e.g. a1, e4, g7, h4
        //
        // Examples:
        //      Nf3
        //      Bg5
        //      Rh1
        //      Qd2
        //      Kd4
        //

        // A no capture move shall be a length of at least 3
        if (nMove.size() < 3)
            return InvalidMove;

        Piece p = toPiece(nMove.at(0));
        Cell dCell = toCell(nMove.substr(1, 2));
        // Try to determine the start cell
        Cell sCell = determineStartCell(p, dCell);
        if ((p != InvalidPiece) && (sCell != InvalidCell) && (dCell != InvalidCell))
            return chessMove(p, sCell, dCell);
        return InvalidMove;
    }

    // -----------------------------------------------------------------
    ChessMove ChessGame::pieceCaptureMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        // The generic "Simple" (no ambiguity) capture move of a Piece has the format:
        //      <Piece>x<cell>
        //
        // where:
        //      <Piece> = one of K | Q | B | N | R
        //      <cell>  = the destination cell, e.g. a1, e4, g7, h4
        //
        // Examples:
        //      Nxf3
        //      Bxg5
        //      Rxh1
        //      Qxd2
        //      Kxd4
        //

        // A capture move shall be a length of at least 4
        if (nMove.size() < 4)
            return InvalidMove;

        Piece p = toPiece(nMove.at(0));
        Cell dCell = toCell(nMove.substr(2, 3));
        // Try to determine the start cell and the taken piece
        Piece capturedPiece = board.armies[(board.sideToMove == WhiteArmy)
                                            ? BlackArmy : WhiteArmy].getPieceInCell(dCell);
        Cell sCell = determineStartCell(p, dCell, capturedPiece);
        if ((p != InvalidPiece) && (sCell != InvalidCell) && (dCell != InvalidCell)
                                                          && (capturedPiece != InvalidPiece))
            return chessMove(p, sCell, dCell, capturedPiece);
        return InvalidMove;
    }

    // -----------------------------------------------------------------
    ChessMove ChessGame::pawnMoveNotationEvaluationAndConversion(const std::string_view nMove) const
    {
        if (nMove.size() == 2) {
            // just the destination cell is present, so this is a
            // simple (no-capture) pawn move.
            return simplePawnMoveNotationEvaluationAndConversion(nMove);
        }
        else if (nMove.find('=') != std::string::npos) {
            // Promotion move!
            return promotionMoveNotationEvaluationAndConversion(nMove);
        }
        else if (nMove.find('x') != std::string::npos) {
            // capture (no promotion move)
            return pawnCaptureNoPromotionMove(nMove);
        }
        // cannot understand this pawn move...
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
            File file = toFile(nMove.at(0));
            if (file == InvalidFile)
                return InvalidMove;

            // extract the promoted piece from the 4th character in string
            Piece ppiece = toPiece(nMove.at(3));

            // Checks the destination rank
            if  (board.sideToMove == WhiteArmy) {
                // The destination rank shall be in the 2nd position and shall be an 8
                if (toRank(nMove.at(1)) != r_8) {
                    // invalid notation move
                    return InvalidMove;
                }
                return chessMove(Pawn, toCell(file, r_7), toCell(file, r_8), InvalidPiece, ppiece);
            }
            if  (board.sideToMove == BlackArmy) {
                // The destination rank shall be in the 2nd position and shall be an 1
                if (toRank(nMove.at(1)) != r_1) {
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

        File fileStart = toFile(nMove.at(0));
        if (fileStart == InvalidFile)
            return InvalidMove;

        File fileDest = toFile(nMove.at(2));
        if (fileDest == InvalidFile)
            return InvalidMove;

        // extract the promoted piece from the 6th character in string
        Piece ppiece = toPiece(nMove.at(5));

        // Checks the destination rank
        ArmyColor opponentColor = (board.sideToMove == WhiteArmy) ? BlackArmy : WhiteArmy;
        if  (board.sideToMove == WhiteArmy) {
            // The destination rank shall be in the 4th position and shall be an 8
            if (toRank(nMove.at(3)) != r_8) {
                // invalid notation move
                return InvalidMove;
            }
            // The enemy shall have a piece in toCell(fileDest, 8) (in any case we do not check)
            Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, r_8));
            return chessMove(Pawn, toCell(fileStart, r_7), toCell(fileDest, r_8), cPiece, ppiece);
        }
        else if  (board.sideToMove == BlackArmy) {
            // The destination rank shall be in the 4th position and shall be an 1
            if (toRank(nMove.at(3)) != r_1) {
                // invalid notation move
                return InvalidMove;
            }
            // The enemy shall have a piece in toCell(fileDest, 8) (in any case we do not check)
            Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, r_1));
            return chessMove(Pawn, toCell(fileStart, r_2), toCell(fileDest, r_1), cPiece, ppiece);
        }
        // If here sideToMove has an incorrect value
        // We never arrive here because sideToMove is filtered at beginning
        return InvalidMove; // GCOV_EXCL_LINE
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
                Cell startCell = s(destCell);
                Piece p = board.armies[board.sideToMove].getPieceInCell(startCell);
                if (p == Pawn)
                    return chessMove(Pawn, startCell, destCell);
                else if (rank(destCell) == r_4) {
                    startCell = s(startCell);
                    p = board.armies[board.sideToMove].getPieceInCell(startCell);
                    if (p == Pawn)
                        return chessMove(Pawn, startCell, destCell);
                }
            }
        }
        else if (board.sideToMove == BlackArmy) {
            if (rank(destCell) < r_7) {
                Cell startCell = n(destCell);
                Piece p = board.armies[board.sideToMove].getPieceInCell(startCell);
                if (p == Pawn)
                    return chessMove(Pawn, startCell, destCell);
                else if (rank(destCell) == r_5) {
                    startCell = n(startCell);
                    p = board.armies[board.sideToMove].getPieceInCell(startCell);
                    if (p == Pawn)
                        return chessMove(Pawn, startCell, destCell);
                }
            }
        }
        return InvalidMove;
    }

    ChessMove ChessGame::pawnCaptureNoPromotionMove(const std::string_view nMove) const
    {
        // A pawn capture move has the following format:
        //    <s_f>x<d_f><d_r>    where:
        //       <s_f>  = start file (a...h)
        //       <d_f>  = destination file (a...h)
        //       <d_r>  = destination rank (1...8)
        //
        // For example:   exd4, cxb6
        // The target cell (<d_f><d_r>) shall contain an enemy piece, or
        // can be an en passant target square. Additionally there are some other
        // condition for the move to be valid: The appropriate start cell <s_f><s_r>
        // shall be occupied by a pawn of the Army that is moving. <s_r> can be computed
        // with the following formula:
        //    if sideToMove is White  ---> <s_r> = <d_r> - 1
        //    if sideToMove is Black  ---> <s_r> = <d_r> + 1
        // The distance between <s_f> and <d_f> shall be 1. For example:
        //    if <d_f> = c   ---> <s_f> can only be 'b' or 'd'
        //    if <d_f> = h   ---> <s_f> can only be 'g'
        //
        // In any case we perform here only the strictly necessary tests to be sure of
        // the validity of the string and to get the information necessary to build the
        // ChessMove. We rely on the final move validity check for final acceptance

        // if the 'x' character is not in the 2nd position, the move is not valid
        if ((nMove.at(1) != 'x')) {
            // invalid notation move
            return InvalidMove;
        }
        // Extract start and destination files
        File fileStart = toFile(nMove.at(0));
        File fileDest = toFile(nMove.at(2));
        // extract destination rank
        Rank rankDest = toRank(nMove.at(3));

        // Checks for correctness
        if (fileStart == InvalidFile || fileDest == InvalidFile || rankDest == InvalidRank)
            return InvalidMove;

        // Computes start rank and extract captured piece
        Rank rankStart;
        ArmyColor opponentColor;
        if  (board.sideToMove == WhiteArmy) {
            rankStart = prevRank(rankDest);
            opponentColor = BlackArmy;
        }
        else if (board.sideToMove == BlackArmy) {
            rankStart = nextRank(rankDest);
            opponentColor = WhiteArmy;
        }
        if (rankStart == InvalidRank)
            return InvalidMove;

        // Extracts the captured piece. We do not check for correcteness
        Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, rankDest));

        // We do not check that the start cell contains a Pawn
        // we rely in future checks for move validity
        return chessMove(Pawn, toCell(fileStart, rankStart), toCell(fileDest, rankDest), cPiece);
    }

    Cell ChessGame::determineStartCell(Piece p, Cell dCell, Piece capturedPiece) const
    {
        // Depending on Piece type, select the proper bitboard
        BitBoard bbToCheck = board.armies[board.sideToMove].pieces[p];
        // Search the pieces...
        auto foundPieces = 0;
        Cell tentativeStartCell = InvalidCell;
        for (auto startPos = 0; (startPos < 64) && (foundPieces < bbToCheck.popCount()); startPos++) {
            if (bbToCheck[startPos] != 0) {
                // piece found in position startPos
                foundPieces++;
                // Check if the move is possible
                if (std::find(possibleMoves.begin(), possibleMoves.end(),
                        chessMove(p, static_cast<Cell>(startPos), dCell, capturedPiece)) != possibleMoves.end()) {
                    // Move found... if a valid move was still not found,
                    // this becames the candidate, otherwise there is ambiguity
                    // and invalid move is returned
                    if (tentativeStartCell == InvalidCell)
                        tentativeStartCell = static_cast<Cell>(startPos);
                    else
                        return InvalidCell;
                }
            }
        }
        return tentativeStartCell;
    }

} // namespace cSzd
