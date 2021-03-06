#include "cmdsuzdal/randomengine.h"

namespace cSzd
{
    int moveRandomizer(int numMoves)
    {
        std::uniform_int_distribution<int> dist(0, numMoves-1);
        std::random_device rd;
        return dist(rd);
    }

    ChessMove RandomEngine::move(const ChessBoard &cb)
    {
        std::vector<ChessMove> moves;
        cb.generateLegalMoves(moves);
        if (moves.size() > 0) {
            return moves[randomizer(moves.size())];
        }
        return InvalidMove;
    }
}
