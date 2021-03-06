#if !defined CSZD_RANDOMENGINE_HEADER
#define CSZD_RANDOMENGINE_HEADER

#include <random>

#include "cmdsuzdal/chessengine.h"

namespace cSzd
{
    int moveRandomizer(int numMoves);

    // RandomEngine: a chess "engine"  that generates a random valid move
    class RandomEngine: public ChessEngine
    {
        public:
            ChessMove move(const ChessBoard &cb);
            void setRandomizer(int (*r)(int)) { randomizer = r; }
        private:
            int (*randomizer)(int) = moveRandomizer;
    };
}  // namespace cSzd

#endif // #if !defined CSZD_RANDOMENGINE_HEADER
