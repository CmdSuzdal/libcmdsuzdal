#if !defined CSZD_RANDOMENGINE_HEADER
#define CSZD_RANDOMENGINE_HEADER

#include "cmdsuzdal/chessengine.h"

namespace cSzd
{
    // RandomEngine: a chess "engine"  that generates a random valid move
    class RandomEngine: public ChessEngine
    {
        public:
            ChessMove move(const ChessBoard &cb);
    };

}  // namespace cSzd

#endif // #if !defined CSZD_RANDOMENGINE_HEADER
