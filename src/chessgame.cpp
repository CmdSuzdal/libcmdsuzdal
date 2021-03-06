#include <algorithm>
#include "cmdsuzdal/chessgame.h"

namespace cSzd
{

    // --- Constructor(s) --------------------------------------
    ChessGame::ChessGame()
    {
        loadPosition();
    }
    ChessGame::ChessGame(const FENRecord &fen)
    {
        loadPosition(fen.fen);
    }
    ChessGame::ChessGame(const std::string_view fenStr)
    {
        loadPosition(fenStr);
    }
    // ---------------------------------------------------------

    // Load a position using a string containing a FEN string
    void ChessGame::loadPosition(const std::string_view fenStr)
    {
        initialPosition = FENRecord(fenStr);
        board.loadPosition(fenStr);
        board.generateLegalMoves(possibleMoves);
    }

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
        if (nMove.size() == 0)
            return InvalidMove;

        // If no side has the move, returns InvalidMove
        if (board.sideToMove == InvalidArmy)
            return InvalidMove;

        // Removes the annotations
        auto move = removeAnnotions(nMove);

        if (move.at(0) == '0') {
            // This can be an castling move
            cm = castlingMoveNotationEvaluationAndConversion(move);
        }
        else {
            // If the move starts with 'K', 'Q', 'R', 'B' or 'N'
            // it is a piece move, otherwise it is a pawn move
            std::string pieces = "KQRBN";
            if (pieces.find(move.at(0)) != std::string::npos) {
                // piece move
                cm = pieceMoveNotationEvaluationAndConversion(move);
            }
            else {
                // pawn move
                cm = pawnMoveNotationEvaluationAndConversion(move);
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
    // Converts a string with a move in long algebraic notational format to a ChessMove.
    // This function checks if the move is legal and return the appropriate chessMove
    // or InvalidMove if the move is not legal or not recognized.
    // For example, if the string "e2e4" is found, and the chess board is in the initial
    // position the following move is returned:
    //     chessMove(Pawn, e2, e4)
    //
    ChessMove ChessGame::checkLongAlgebraicMove(const std::string_view laMove) const
    {
        // Long Algebraic move has the format <start_cell><dest_cell>[<p>] where:
        //   - <start_cell> is the start cell in the classical <file><rank> format
        //     with <file> in {a, b, c, d, e ,f, g, h} and <rank> in {1, 2, 3, 4, 5, 6, 7, 8}
        //   - <dest_cell> is the destination cell in the classical <file><rank> format
        //   - <p> (optional) is the promoted piece type in case of promotion move.
        //     p is one of:
        //       - q or Q if promotion to Queen
        //       - r or R if promotion to Rook
        //       - b or B if promotion to Bishop
        //       - n or N if promotion to Knight
        //

        // If no side has the move, returns InvalidMove regardless of string content
        if (board.sideToMove == InvalidArmy)
            return InvalidMove;
        // String can only have size of 4 or 5 (for promotion move)
        if ((laMove.size() < 4) || (laMove.size() > 5))
            return InvalidMove;

        return chessMove(Pawn, e2, e4);
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
        Cell dCell = InvalidCell;
        Cell sCell = InvalidCell;
        if (nMove.size() == 3) {
            dCell = toCell(nMove.substr(1, 2));
            // Try to determine the start cell
            sCell = determineStartCell(p, dCell);
            if ((p != InvalidPiece) && (sCell != InvalidCell) && (dCell != InvalidCell))
                return chessMove(p, sCell, dCell);
        }
        else if (nMove.size() == 4) {
            // move with disambiguation character (file or rank)
            dCell = toCell(nMove.substr(2, 3));
            char disChar = nMove.at(1);
            File disFile = toFile(disChar);
            if (disFile != InvalidFile) {
                // Move with disambiguation file
                sCell = determineStartCell(p, dCell, InvalidPiece,
                            std::tuple<File, Rank>{disFile, InvalidRank});
            }
            Rank disRank = toRank(disChar);
            if (disRank != InvalidRank) {
                // Move with disambiguation rank
                sCell = determineStartCell(p, dCell, InvalidPiece,
                            std::tuple<File, Rank>{InvalidFile, disRank});
            }
            if ((p != InvalidPiece) && (sCell != InvalidCell) && (dCell != InvalidCell))
                return chessMove(p, sCell, dCell);
        }
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
        Piece capturedPiece = InvalidPiece;
        Cell dCell = InvalidCell;
        Cell sCell = InvalidCell;
        if (nMove.size() == 4) {
            dCell = toCell(nMove.substr(2, 3));
            // Try to determine the start cell and the taken piece
            capturedPiece = board.armies[(board.sideToMove == WhiteArmy)
                                           ? BlackArmy : WhiteArmy].getPieceInCell(dCell);
            sCell = determineStartCell(p, dCell, capturedPiece);
            if ((p != InvalidPiece) && (sCell != InvalidCell) && (dCell != InvalidCell)
                                                            && (capturedPiece != InvalidPiece))
                return chessMove(p, sCell, dCell, capturedPiece);
        }
        else if (nMove.size() == 5) {
            dCell = toCell(nMove.substr(3, 4));
            // Try to determine the start cell and the taken piece
            capturedPiece = board.armies[(board.sideToMove == WhiteArmy)
                                           ? BlackArmy : WhiteArmy].getPieceInCell(dCell);
            char disChar = nMove.at(1);
            File disFile = toFile(disChar);
            if (disFile != InvalidFile) {
                // Move with disambiguation file
                sCell = determineStartCell(p, dCell, capturedPiece,
                            std::tuple<File, Rank>{disFile, InvalidRank});
            }
            Rank disRank = toRank(disChar);
            if (disRank != InvalidRank) {
                // Move with disambiguation rank
                sCell = determineStartCell(p, dCell, capturedPiece,
                            std::tuple<File, Rank>{InvalidFile, disRank});
            }
            if ((p != InvalidPiece) && (sCell != InvalidCell) &&
                    (dCell != InvalidCell) && (capturedPiece != InvalidPiece))
                return chessMove(p, sCell, dCell, capturedPiece);
        }
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

        // if here, the sideToMove is Black, because the InvalidArmy case is filtered
        // at the beginning od the checkNotationMove() function
        // The destination rank shall be in the 4th position and shall be an 1
        if (toRank(nMove.at(3)) != r_1) {
            // invalid notation move
            return InvalidMove;
        }
        // The enemy shall have a piece in toCell(fileDest, 8) (in any case we do not check)
        Piece cPiece = board.armies[opponentColor].getPieceInCell(toCell(fileDest, r_1));
        return chessMove(Pawn, toCell(fileStart, r_2), toCell(fileDest, r_1), cPiece, ppiece);
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

        // the move shall have a lenght of exactly 4 chars
        if ((nMove.size() != 4))
            return InvalidMove;

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

    Cell ChessGame::determineStartCell(Piece p, Cell dCell, Piece capturedPiece,
                                            std::tuple<File, Rank> suggested) const
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

                    // Move found... validate with suggestions
                    if (std::get<0>(suggested) != InvalidFile) {
                        // File of the found possible start cell
                        // shall correspond to the suggested one
                        if (file(static_cast<Cell>(startPos)) != std::get<0>(suggested)) {
                            // not good...
                            continue;
                        }
                    }
                    if (std::get<1>(suggested) != InvalidRank) {
                        // Rank of the found possible start cell
                        // shall correspond to the suggested one
                        if (rank(static_cast<Cell>(startPos)) != std::get<1>(suggested)) {
                            // not good...
                            continue;
                        }
                    }
                    // Move really found! If a valid move was still not found,
                    // this becames the candidate, otherwise there is ambiguity
                    // and invalid move is returned
                    if (tentativeStartCell == InvalidCell) {
                        tentativeStartCell = static_cast<Cell>(startPos);
                    }
                    else {
                        return InvalidCell;
                    }
                }
            }
        }
        return tentativeStartCell;
    }

    // -------------------------------------------------------------------------
    const std::string_view ChessGame::removeAnnotions(const std::string_view nMove)
    {
        // ANNOTATIONS:
        //   '+' = check
        //   '#' = checkmate
        //   '!' = good move
        //   '?' = bad move
        //   '!!' = excellent move
        //   '??' = blunder
        //   '!?' = interesting move (that can be questionable)
        //   '?!' = questionable move (that can be interesting)
        //
        // Some annotations can be composed:
        //
        //   '+?' '+??' '+?!' '+!' '+!!' '+!?'
        //
        // Some other composition does not make sense
        // but we do not consider them wrong (FOR THE MOMENT):
        //
        //   '#?' '#??' '#!' '#!!' '#!?' '#?!'
        //
        // These composition are conceptually wrong and should be refused:
        //   '?+' '!+' '?+?' '??+' '!+!' '!!+' '!+?' '!?+' '?+!' '?!+'
        //   '?#' '!#' '?#?' '??#' '!#!' '!!#' '!#?' '!?#' '?#!' '?!#'
        //   '++' '##' '+#' '#+'

        // At the end of the string, there can be the game result:
        //   '1-0' = win for white
        //   '0-1' = win for black
        //   '1/2-1/2' = draw
        //
        // Any of the combination that make sense above can be
        // associated to the game result
        //

        if (nMove.size() < 3)
            return nMove;

        int currentPosition = nMove.size() - 1;

        // Removes '!' and '?'
        int charsRemoved = 0;
        while ((currentPosition > 1) && (charsRemoved < 2)) {
            if ((nMove.at(currentPosition) == '!') ||
                 (nMove.at(currentPosition) == '?')) {
                --currentPosition;
                ++charsRemoved;
            }
            else
                break;
        }

        // Removes '+' and '#'
        charsRemoved = 0;
        while ((currentPosition > 1) && (charsRemoved < 1)) {
            if ((nMove.at(currentPosition) == '+') ||
                (nMove.at(currentPosition) == '#')) {
                --currentPosition;
                ++charsRemoved;
            }
            else
                break;
        }

        return nMove.substr(0, currentPosition + 1);
    }

} // namespace cSzd
