#include "cmdsuzdal/randomengine.h"

namespace cSzd
{
    ChessMove RandomEngine::move(const ChessBoard &cb)
    {
        std::vector<ChessMove> moves;
        cb.generateLegalMoves(moves);
        if (moves.size() > 0) {
            return moves[0];
        }
        return InvalidMove;
    }
}
