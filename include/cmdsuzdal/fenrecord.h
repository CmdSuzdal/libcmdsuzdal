#if !defined CSZD_FEN_HEADER
#define CSZD_FEN_HEADER

#include <string>
#include <string_view>

namespace cSzd
{
    const std::string_view FENInitialStandardPosition
       {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};

    const std::string_view FENEmptyChessBoard
       {"8/8/8/8/8/8/8/8 - - - 0 1"};

    // -------------------------------------------------------------------------
    // base struct for FEN Record representation
    struct FENRecord
    {
        std::string fen {FENInitialStandardPosition};

        // -------------------------
        FENRecord() = default;
        explicit FENRecord(const std::string_view &f) { fen = f;};

        // -------------------------
        bool isValid() const { return true; }
    };

} // namespace cSzd

#endif // #if !defined CSZD_FEN_HEADER