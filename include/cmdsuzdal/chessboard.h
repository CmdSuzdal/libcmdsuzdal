#if !defined CSZD_CHESSBOARD_HEADER
#define CSZD_CHESSBOARD_HEADER

#include "cmdsuzdal/army.h"
#include "cmdsuzdal/fenrecord.h"

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
    //   ├─ Army whiteArmy;
    //   |    └─ BitBoard pieces[NumPieceTypes]
    //   |       ├─ pieces[King]  : BitBoard with the position of the white king
    //   |       ├─ pieces[Queen] : BitBoard with the position of the white queen(s)
    //   |       ├─ pieces[Bishop]: BitBoard with the position of the white bishop(s)
    //   |       ├─ pieces[Knight]: BitBoard with the position of the white knight(s)
    //   |       ├─ pieces[Rook]  : BitBoard with the position of the white rook(s)
    //   |       └─ pieces[Pawn]  : BitBoard with the position of the white pawn(s)
    //   ├─ Army blackArmy;
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
        Army whiteArmy = Army(WhiteArmy);
        Army blackArmy = Army(BlackArmy);
        ArmyColor sideToMove = WhiteArmy;
        unsigned int halfMoveClock = 0;
        unsigned int fullMoves = 1;

        // --------------------------
        explicit ChessBoard() = default;

    };
    // -----------------------------------------------


} // namespace cSzd

#endif // #if !defined CSZD_CHESSBOARD_HEADER