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
        std::string fen {FENInitialStandardPosition};

        // -------------------------
        FENRecord() = default;
        explicit FENRecord(const std::string_view f) { fen = f;};

        // -------------------------
        bool isValid() const;
        const std::string_view piecePlacement() const;
        ArmyColor sideToMove() const;
        BitBoard castlingAvailability() const;
        BitBoard enPassantTargetSquare() const;
        unsigned int halfMoveClock() const;
        unsigned int fullMoves() const;

        const BitBoard extractBitBoard(ArmyColor c = InvalidArmy, Piece p = InvalidPiece) const;

    private:
        static const std::string pieceSetFENCharacters(ArmyColor c, Piece p);

    };

} // namespace cSzd

#endif // #if !defined CSZD_FEN_HEADER