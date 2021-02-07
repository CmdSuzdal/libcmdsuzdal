#if !defined CSZD_CHESSGAME_HEADER
#define CSZD_CHESSGAME_HEADER

#include "cmdsuzdal/chessboard.h"

namespace cSzd
{

    // ------------------------------------------------------------------------
    // ChessGame is a class used to represent a complete chess game.
    // A chess game is composed by a starting position the sequence of moves
    // of the main variation and a set of secondary variations.
    // A ChessBoard is used to represent the "current" position of the game.
    // Due to the fact that a ChessGame can be used for two purposes, *real
    // time play* and *analysis*, two possible scenarios of usage of the
    // ChessGame class are possible:
    //   - Real Time Play: in this case only a variation is present, and the
    //     ChessBoard is used to represent the last position of the game in
    //     progress.
    //   - Analysis: this is the complex case: more than one variation can be
    //     present, and the ChessBoard can be used to represent any of the
    //     position of any variation
    //
    // Because we proceed using a TDD iterative approach, in the first steps
    // only the simpler Real Time Play scenario is considered, later we will
    // introduce the additional functionality and informations to manage the
    // analysis scenario.
    //
    // The other additional requirement that we will address somewhere in the
    // future, is the support of the PGN format for both import and export
    // operations.
    //
    // ChessGame
    //   |
    //   ├─ FENRecord initialPosition
    //   |    The FEN record of the initial position of the game.
    //   ├─ ChessBoard board
    //   |    The board rapresentation of the current position of the game.
    //   |    This can be the last position in a real time game, or any
    //   |    position of a game under analysis.
    //   ├─ std::vector<ChessMove> possibleMoves
    //   |    The legal moves available in the current position
    //   |
    //   |
    //   |
    //
    //   ├─ TO BE COMPLETED
    //   |    └─ ├─
    //
    // ------------------------------------------------------------------------


    // --- The ChessGame ---------------------------------
    struct ChessGame {

        // -----------------------------------------------------
        FENRecord initialPosition;
        ChessBoard board;
        std::vector<ChessMove> possibleMoves;
        // -----------------------------------------------------

        // --- Constructor(s) ----------------------------------
        explicit ChessGame();
        explicit ChessGame(const FENRecord &fen);
        explicit ChessGame(const std::string_view fenStr);
        // -----------------------------------------------------

        // Add a move to the currently active variant
        void addMove(const ChessMove &m);

        // Check a move in notation format, and convert to
        // ChessMove if valid and legal. Returns InvalidMove
        // if not legal respect to the current position
        ChessMove checkNotationMove(const std::string_view nMove) const;

    private:
        // Pawn move support methods
        ChessMove castlingMoveNotationEvaluationAndConversion(const std::string_view nMove) const;
        ChessMove pieceMoveNotationEvaluationAndConversion(const std::string_view nMove) const ;
        ChessMove pieceCaptureMoveNotationEvaluationAndConversion(const std::string_view nMove) const;

        ChessMove pawnMoveNotationEvaluationAndConversion(const std::string_view nMove) const ;
        ChessMove promotionMoveNotationEvaluationAndConversion(const std::string_view nMove) const;
        ChessMove promotionMoveWithCaptureNotationEvaluationAndConversion(const std::string_view nMove) const;
        ChessMove simplePawnMoveNotationEvaluationAndConversion(const std::string_view nMove) const;
        ChessMove pawnCaptureNoPromotionMove(const std::string_view nMove) const;

        // Pieces move support methods
        Cell determineStartCell(Piece p, Cell dCell, Piece capturedPiece = InvalidPiece) const;

    };
    // ---------------------------------------------------

} // namespace cSzd

#endif // #if !defined CSZD_CHESSGAME_HEADER