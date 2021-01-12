#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessgame.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    TEST(ChessGameTester, AfterTheDefaultInitializationTheGameHasAChessBoardWithTheInitialPosition)
    {
        ChessGame cg;
        ASSERT_EQ(cg.board, ChessBoard());
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cg.board.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cg.board.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cg.board.sideToMove, WhiteArmy);
        ASSERT_EQ(cg.board.castlingAvailability, BitBoard({c1, g1, c8, g8}));
        ASSERT_EQ(cg.board.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cg.board.halfMoveClock, 0);
        ASSERT_EQ(cg.board.fullMoves, 1);
        ASSERT_TRUE(cg.board.isValid());
        ASSERT_FALSE(cg.board.isCheckMate());
        ASSERT_FALSE(cg.board.isStaleMate());
        ASSERT_FALSE(cg.board.isDrawnPosition());
        ASSERT_FALSE(cg.board.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessGameTester, AfterTheDefaultInitializationTheGameHasAFenRecordWithTheInitialPosition)
    {
        ChessGame cg;
        ASSERT_EQ(cg.initialPosition, FENRecord(FENInitialStandardPosition));
    }
    TEST(ChessGameTester, AfterTheDefaultInitializationThePossibleMovesAreComputedCorrectly)
    {
        ChessGame cg;
        ASSERT_EQ(cg.possibleMoves.size(), 20);
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, h3)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, InitializationUsingAFENRecordOfTheInitialStandardPosition)
    {
        ChessGame cg{FENRecord(FENInitialStandardPosition)};
        ASSERT_EQ(cg.board, ChessBoard());
        ASSERT_EQ(cg.initialPosition, FENRecord(FENInitialStandardPosition));
        ASSERT_EQ(cg.possibleMoves.size(), 20);
    }
    TEST(ChessGameTester, InitializationUsingAFENStringOfTheInitialStandardPosition)
    {
        ChessGame cg{FENInitialStandardPosition};
        ASSERT_EQ(cg.board, ChessBoard());
        ASSERT_EQ(cg.initialPosition, FENRecord(FENInitialStandardPosition));
        ASSERT_EQ(cg.possibleMoves.size(), 20);
    }
    TEST(ChessGameTester, InitializationUsingAFENStringOfAGenericGameIsOK)
    {
        // https://lichess.org/Y89AL6UG/black#33
        ChessGame cg{"1r1qr1k1/ppp2ppb/4pn1p/2b5/4P2N/1P4P1/PBn1N1BP/R2QRK2 b - - 3 17"};
        ASSERT_EQ(cg.board, ChessBoard("1r1qr1k1/ppp2ppb/4pn1p/2b5/4P2N/1P4P1/PBn1N1BP/R2QRK2 b - - 3 17"));
        ASSERT_EQ(cg.initialPosition, FENRecord("1r1qr1k1/ppp2ppb/4pn1p/2b5/4P2N/1P4P1/PBn1N1BP/R2QRK2 b - - 3 17"));
        ASSERT_EQ(cg.possibleMoves.size(), 48);
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, a1, Rook)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, e1, Rook)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, e4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, e4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, b8, a8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, b8, c8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d1, Queen)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, e8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, e8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, h8)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h6, h5)) != cg.possibleMoves.end());
        ASSERT_EQ(cg.board.sideToMove, BlackArmy);
        ASSERT_EQ(cg.board.castlingAvailability, BitBoard(EmptyBB));
        ASSERT_EQ(cg.board.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cg.board.halfMoveClock, 3);
        ASSERT_EQ(cg.board.fullMoves, 17);
        ASSERT_TRUE(cg.board.isValid());
        ASSERT_FALSE(cg.board.isCheckMate());
        ASSERT_FALSE(cg.board.isStaleMate());
        ASSERT_FALSE(cg.board.isDrawnPosition());
        ASSERT_FALSE(cg.board.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessGameTester, AfterDefaultInitialization_InsertAValidMove_E2_to_E4)
    {
        ChessGame cg;
        cg.addMove(chessMove(Pawn, e2, e4));
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"));
        ASSERT_EQ(cg.possibleMoves.size(), 20);
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(std::find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, h6)) != cg.possibleMoves.end());
    }


} // namespace cSzd