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
    ChessGame::ChessGame(const FENRecord &fen) :
        initialPosition(fen.fen),
        board(fen)
    {
        board.generateLegalMoves(possibleMoves);
    }
    ChessGame::ChessGame(const std::string_view fenStr) :
        initialPosition(fenStr),
        board(fenStr)
    {
        board.generateLegalMoves(possibleMoves);
    }
    // ---------------------------------------------------------

    void ChessGame::addMove(const ChessMove &m)
    {
        board.doMove(m);
    }


} // namespace cSzd
