#if !defined CSZD_CHESSBOARD_HEADER
#define CSZD_CHESSBOARD_HEADER

#include "cmdsuzdal/army.h"
#include "cmdsuzdal/fenrecord.h"
#include "cmdsuzdal/chessmove.h"

namespace cSzd
{

    // ------------------------------------------------------------------------
    // ChessBoard is a class used to represent a valid chess position based on
    // usage of BitBoards. For the Armies rapresentation, the BitBoard-based
    // Army class is used. Other game information are also stored (used the FEN
    // format as a reference)
    //
    // ChessBoard
    //   |
    //   ├─ Army armies[WhiteArmy];
    //   |    └─ BitBoard pieces[NumPieceTypes]
    //   |       ├─ pieces[King]  : BitBoard with the position of the white king
    //   |       ├─ pieces[Queen] : BitBoard with the position of the white queen(s)
    //   |       ├─ pieces[Bishop]: BitBoard with the position of the white bishop(s)
    //   |       ├─ pieces[Knight]: BitBoard with the position of the white knight(s)
    //   |       ├─ pieces[Rook]  : BitBoard with the position of the white rook(s)
    //   |       └─ pieces[Pawn]  : BitBoard with the position of the white pawn(s)
    //   ├─ Army armies[BlackArmy];
    //   |    └─ BitBoard pieces[NumPieceTypes]
    //   |       ├─ pieces[King]  : BitBoard with the position of the black king
    //   |       ├─ pieces[Queen] : BitBoard with the position of the black queen(s)
    //   |       ├─ pieces[Bishop]: BitBoard with the position of the black bishop(s)
    //   |       ├─ pieces[Knight]: BitBoard with the position of the black knight(s)
    //   |       ├─ pieces[Rook]  : BitBoard with the position of the black rook(s)
    //   |       └─ pieces[Pawn]  : BitBoard with the position of the black pawn(s)
    //   ├─ BitBoard castlingAvail;
    //   ├─ BitBoard enPassantMove;
    //   ├─ ArmyColor sideToMove;
    //   ├─ unsigned int halfMoveClock;
    //   └─ unsigned int fullMoves;
    //
    // ------------------------------------------------------------------------

    // --- The ChessBoard -----------------------------
    struct ChessBoard {
        // --------------------------
        Army armies[2] = { Army(WhiteArmy), Army(BlackArmy) };
        ArmyColor sideToMove = WhiteArmy;
        BitBoard castlingAvailability = BitBoard({b1, g1, b8, g8});
        BitBoard enPassantTargetSquare;
        unsigned int halfMoveClock = 0;
        unsigned int fullMoves = 1;

        // --------------------------
        explicit ChessBoard() = default;
        explicit ChessBoard(const FENRecord &fen);
        explicit ChessBoard(const std::string_view fenStr);

        BitBoard wholeArmyBitBoard(ArmyColor a = InvalidArmy) const;
        BitBoard controlledCells(ArmyColor a) const;

        // If one of the kings is in check, returns the color of the army
        // in check. Otherwise, returns InvalidArmy. If the position is not
        // valid and both the kings are in check, InvalidArmy is returned.
        // In the latter case, the isValid() function can be used to
        // discriminate the condition
        ArmyColor armyInCheck() const ;
        bool armyIsInCheck(ArmyColor a) const;

        // --------------------------
        void loadPosition(const FENRecord &fen);
        void loadPosition(const std::string_view fenStr);
        bool isValid() const;

        void generateLegalMoves(std::vector<ChessMove> &moves, Piece pType = InvalidPiece);
        //void generatePawnsLegalMoves(std::vector<ChessMove> &moves);

    private:
        bool checkEnPassantTargetSquareValidity() const;


    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_CHESSBOARD_HEADER