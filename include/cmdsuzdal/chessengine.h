#if !defined CSZD_CHESSENGINE_HEADER
#define CSZD_CHESSENGINE_HEADER

#include "cmdsuzdal/chessboard.h"

namespace cSzd
{
    // ChessEngine base pure abstract class --------------------------------
    // A ChessEngine is an entity that, given a chessboard,
    // generates a valid move.
    class ChessEngine
    {
        public:
            // Given a chess board, selects a valid move
            virtual ChessMove move(const ChessBoard &cb) = 0;
    };

}  // namespace cSzd

#endif // #if !defined CSZD_CHESSENGINE_HEADER
