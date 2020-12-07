#if !defined CSZD_FEN_HEADER
#define CSZD_FEN_HEADER

#include <string>
#include <string_view>

#include "cmdsuzdal/army.h"

namespace cSzd
{
    constexpr std::string_view FENDelim {" "};
    constexpr std::string_view FENInitialStandardPosition
       {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
    constexpr std::string_view FENEmptyChessBoard
       {"8/8/8/8/8/8/8/8 - - - 0 1"};

    // -------------------------------------------------------------------------
    // base struct for FEN Record representation
    struct FENRecord
    {

        // -------------------------
        explicit FENRecord();
        explicit FENRecord(const std::string_view f);

        void loadPosition(const std::string_view f);

        // -------------------------
        bool isValid() const;
        const std::string_view value() { return std::string_view {fen.c_str()}; }
        const std::string_view piecePlacement() const { return pPlacement; }
        ArmyColor sideToMove() const { return activeArmy; }
        BitBoard castlingAvailability() const { return cstlAvail; }
        BitBoard enPassantTargetSquare() const { return enPassantCell; }
        unsigned int halfMoveClock() const { return hmc; }
        unsigned int fullMoves() const { return fm; }

        const BitBoard extractBitBoard(ArmyColor c = InvalidArmy, Piece p = InvalidPiece) const;

    private:
        static const std::string pieceSetFENCharacters(ArmyColor c, Piece p);

        std::string fen {FENInitialStandardPosition};
        std::string_view pPlacement;
        ArmyColor activeArmy;
        BitBoard cstlAvail;
        BitBoard enPassantCell;
        unsigned int hmc;
        unsigned int fm;
    };

} // namespace cSzd

#endif // #if !defined CSZD_FEN_HEADER