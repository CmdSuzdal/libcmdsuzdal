#if !defined CSZD_FEN_HEADER
#define CSZD_FEN_HEADER

#include <string>

namespace cSzd
{
    // -------------------------------------------------------------------------
    // base struct for FEN Record representation
    struct FENRecord
    {
        std::string fen {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"};
    };

} // namespace cSzd

#endif // #if !defined CSZD_FEN_HEADER