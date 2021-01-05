#include "cmdsuzdal/chessgame.h"

namespace cSzd
{

    // --- Constructor(s) --------------------------------------
    ChessGame::ChessGame()
    {
        // The default constructors of FENRecord and ChessBoard
        // automatically prepares the initial standard position,
        // here we have only to prepare the vector of the possible
        // moves
        board.generateLegalMoves(possibleMoves);
    }
    // ---------------------------------------------------------

} // namespace cSzd
