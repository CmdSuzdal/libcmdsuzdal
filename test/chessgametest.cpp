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
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d2, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, h3)) != cg.possibleMoves.end());
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
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, a1, Rook)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c2, e1, Rook)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c5, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, e4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, h7, e4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, b8, a8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, b8, c8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d1, Queen)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, e8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, e8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, h8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h6, h5)) != cg.possibleMoves.end());
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
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, h6)) != cg.possibleMoves.end());
    }

    // ------------------------------------------------------------------------------------------------------
    // Aronian vs. Anand: Tata Steel Group A (2013), Wijk aan Zee NED, rd 4, Jan-15
    // https://www.chess.com/games/view/13459415
    // [Event "75th Tata Steel GpA"]
    // [Site "Wijk aan Zee NED"]
    // [Date "2013.01.15"]
    // [Round "?"]
    // [White "Levon Aronian"]
    // [Black "Viswanathan Anand"]
    // [Result "0-1"]
    //
    // 1. d4 d5 2. c4 c6 3. Nf3 Nf6 4. Nc3 e6 5. e3 Nbd7 6. Bd3 dxc4 7. Bxc4 b5 8. Bd3
    // Bd6 9. O-O O-O 10. Qc2 Bb7 11. a3 Rc8 12. Ng5 c5 13. Nxh7 Ng4 14. f4 cxd4 15.
    // exd4 Bc5 16. Be2 Nde5 17. Bxg4 Bxd4+ 18. Kh1 Nxg4 19. Nxf8 f5 20. Ng6 Qf6 21. h3
    // Qxg6 22. Qe2 Qh5 23. Qd3 Be3 0-1
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4)
    {
        ChessGame cg;
        ChessMove cm = chessMove(Pawn, d2, d4);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1"));
        ASSERT_EQ(cg.possibleMoves.size(), 20);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d7, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, h6)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5)
    {
        ChessGame cg {"rnbqkbnr/pppppppp/8/8/3P4/8/PPP1PPPP/RNBQKBNR b KQkq d3 0 1"};
        ChessMove cm = chessMove(Pawn, d7, d5);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq d6 0 2"));
        ASSERT_EQ(cg.possibleMoves.size(), 27);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c2, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, d2)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4)
    {
        ChessGame cg {"rnbqkbnr/ppp1pppp/8/3p4/3P4/8/PPP1PPPP/RNBQKBNR w KQkq d6 0 2"};
        ChessMove cm = chessMove(Pawn, c2, c4);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq c3 0 2"));
        ASSERT_EQ(cg.possibleMoves.size(), 28);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c7, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d5, c4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, d7)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6)
    {
        ChessGame cg {"rnbqkbnr/ppp1pppp/8/3p4/2PP4/8/PP2PPPP/RNBQKBNR b KQkq c3 0 2"};
        ChessMove cm = chessMove(Pawn, c7, c6);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/pp2pppp/2p5/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3"));
        ASSERT_EQ(cg.possibleMoves.size(), 30);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, f2, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g1, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, d2)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3)
    {
        ChessGame cg {"rnbqkbnr/pp2pppp/2p5/3p4/2PP4/8/PP2PPPP/RNBQKBNR w KQkq - 0 3"};
        ChessMove cm = chessMove(Knight, g1, f3);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkbnr/pp2pppp/2p5/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 1 3"));
        ASSERT_EQ(cg.possibleMoves.size(), 29);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c6, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d5, c4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , f7, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g8, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, d7)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6)
    {
        ChessGame cg {"rnbqkbnr/pp2pppp/2p5/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R b KQkq - 1 3"};
        ChessMove cm = chessMove(Knight, g8, f6);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 2 4"));
        ASSERT_EQ(cg.possibleMoves.size(), 32);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, c3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h1, g1)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3)
    {
        ChessGame cg {"rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/5N2/PP2PPPP/RNBQKB1R w KQkq - 2 4"};
        ChessMove cm = chessMove(Knight, b1, c3);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 3 4"));
        ASSERT_EQ(cg.possibleMoves.size(), 31);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c6, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d5, c4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, e6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h8, g8)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3_e6)
    {
        ChessGame cg {"rnbqkb1r/pp2pppp/2p2n2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R b KQkq - 3 4"};
        ChessMove cm = chessMove(Pawn, e7, e6);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 5"));
        ASSERT_EQ(cg.possibleMoves.size(), 35);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h1, g1)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3_e6_e3)
    {
        ChessGame cg {"rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N2N2/PP2PPPP/R1BQKB1R w KQkq - 0 5"};
        ChessMove cm = chessMove(Pawn, e2, e3);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 0 5"));
        ASSERT_EQ(cg.possibleMoves.size(), 33);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b7, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c6, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , d5, c4, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, b8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f8, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f8, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f8, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h8, g8)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3_e6_e3_Nbd7)
    {
        ChessGame cg {"rnbqkb1r/pp3ppp/2p1pn2/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R b KQkq - 0 5"};
        ChessMove cm = chessMove(Knight, b8, d7);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("r1bqkb1r/pp1n1ppp/2p1pn2/3p4/2PP4/2N1PN2/PP3PPP/R1BQKB1R w KQkq - 1 6"));
        ASSERT_EQ(cg.possibleMoves.size(), 35);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, c4, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f1, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, f1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e1, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h1, g1)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3_e6_e3_Nbd7___00_00)
    {
        ChessGame cg {"r1bqk2r/p2n1ppp/2pbpn2/1p6/3P4/2NBPN2/PP3PPP/R1BQK2R w KQkq - 2 9"};
        ChessMove cm = chessMove(King, e1, g1);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), cm) != cg.possibleMoves.end());
        cg.addMove(cm);
        ASSERT_EQ(cg.board, ChessBoard("r1bqk2r/p2n1ppp/2pbpn2/1p6/3P4/2NBPN2/PP3PPP/R1BQ1RK1 b kq - 3 9"));
        ASSERT_EQ(cg.possibleMoves.size(), 42);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b5, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , c6, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , h7, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, d7, b8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, d7, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, d7, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, d7, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, d7, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, h5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f6, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, b7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c8, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, b8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, f4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d6, h2, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, e7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, e8, g8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a8, b8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h8, g8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, h8, f8)) != cg.possibleMoves.end());
        cg.addMove(chessMove(King, e8, g8));
        ASSERT_EQ(cg.board, ChessBoard("r1bq1rk1/p2n1ppp/2pbpn2/1p6/3P4/2NBPN2/PP3PPP/R1BQ1RK1 w - - 4 10"));
        ASSERT_EQ(cg.possibleMoves.size(), 40);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a2, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, d4, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, e3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, g2, g4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h2, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, f3, e1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, f5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d3, h7, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, e1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d1, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g1, h1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, e1)) != cg.possibleMoves.end());
    }
    TEST(ChessGameTester, GameCheck_AronianAnand_WijkaanZee2013_d4_d5_c4_c6_Nf3_Nf6_Nc3_e6_e3_Nbd7___00_00___Qd3_Be3)
    {
        ChessGame cg {"2r3k1/pb4p1/4p3/1p3p1q/3b1Pn1/P1N4P/1P2Q1P1/R1B2R1K w - - 2 23"};
        ASSERT_EQ(cg.possibleMoves.size(), 34);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, a2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, e1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, e1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, d3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, e6, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, g4, Knight)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, e2, f2)) != cg.possibleMoves.end());

        cg.addMove(chessMove(Queen, e2, d3));
        ASSERT_EQ(cg.board, ChessBoard("2r3k1/pb4p1/4p3/1p3p1q/3b1Pn1/P1NQ3P/1P4P1/R1B2R1K b - - 3 23"));
        ASSERT_EQ(cg.possibleMoves.size(), 50);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , a7, a5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , b5, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , e6, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn  , g7, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, g4, h2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, a6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, a8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, b7, g2, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, c3, Knight)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, b6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, e5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, f6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, e3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, d4, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, a8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, b8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, d8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, e8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, c7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, c6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, c5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, c8, c3, Knight)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, h6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, h7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, h8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, g5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, g6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, f7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, e8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, h5, h3, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, f7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, f8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, h7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(King, g8, h8)) != cg.possibleMoves.end());
        cg.addMove(chessMove(Bishop, d4, e3));
        ASSERT_EQ(cg.board, ChessBoard("2r3k1/pb4p1/4p3/1p3p1q/5Pn1/P1NQb2P/1P4P1/R1B2R1K w - - 4 24"));
        ASSERT_EQ(cg.possibleMoves.size(), 36);
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, a3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, b2, b4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Pawn, h3, h4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, a4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, e2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Knight, c3, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Bishop, c1, e3, Bishop)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, a1, a2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, e1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, g1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, f2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Rook, f1, f3)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d5)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d6)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d7)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, d8)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, e3, Bishop)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, b1)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, c2)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, e4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, f5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, c4)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, b5, Pawn)) != cg.possibleMoves.end());
        ASSERT_TRUE(find(cg.possibleMoves.begin(), cg.possibleMoves.end(), chessMove(Queen, d3, e2)) != cg.possibleMoves.end());
        // White resigns
    }

    // ------------------------------------------------------------------------------
    // Move Generation from notation function test

    TEST(ChessGameTester, NotationToMove_EmptyStringGeneratesInvalidMove)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove(""), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromInitialPosition_e4_Generates_Pawn_e2_e4_Move)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove("e4"), chessMove(Pawn, e2, e4));
    }
    TEST(ChessGameTester, NotationToMove_FromInitialPosition_d3_Generates_Pawn_d2_d3_Move)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove("d3"), chessMove(Pawn, d2, d3));
    }
    TEST(ChessGameTester, NotationToMove_FromInitialPosition_g1_Generates_InvalidMove)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove("g1"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_WhiteToMove_ConvertPawnMoves)
    {
        ChessGame cg {"r2q1rk1/1p1nbppp/p2pbn2/4p3/4P3/1NN1BP2/PPPQ2PP/2KR1B1R w - - 5 11"};
        ASSERT_EQ(cg.checkNotationMove("f4"), chessMove(Pawn, f3, f4));
        ASSERT_EQ(cg.checkNotationMove("h4"), chessMove(Pawn, h2, h4));
        ASSERT_EQ(cg.checkNotationMove("h3"), chessMove(Pawn, h2, h3));
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_WhiteToMove_ConvertInvalidPawnMove)
    {
        ChessGame cg {"r2q1rk1/1p1nbppp/p2pbn2/4p3/4P3/1NN1BP2/PPPQ2PP/2KR1B1R w - - 5 11"};
        ASSERT_EQ(cg.checkNotationMove("f5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("g6"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("e5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("c3"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_BlackToMove_ConvertPawnMoves)
    {
        ChessGame cg {"r2q1rk1/1p1nbppp/p2pbn2/4p3/4P1P1/1NN1BP2/PPPQ3P/2KR1B1R b - - 0 11"};
        ASSERT_EQ(cg.checkNotationMove("d5"), chessMove(Pawn, d6, d5));
        ASSERT_EQ(cg.checkNotationMove("g5"), chessMove(Pawn, g7, g5));
        ASSERT_EQ(cg.checkNotationMove("a5"), chessMove(Pawn, a6, a5));
        ASSERT_EQ(cg.checkNotationMove("b6"), chessMove(Pawn, b7, b6));
        ASSERT_EQ(cg.checkNotationMove("b5"), chessMove(Pawn, b7, b5));
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_BlackToMove_ConvertInvalidPawnMove)
    {
        ChessGame cg {"r2q1rk1/1p1nbppp/p2pbn2/4p3/4P1P1/1NN1BP2/PPPQ3P/2KR1B1R b - - 0 11"};
        ASSERT_EQ(cg.checkNotationMove("e4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("a4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("b7"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("f6"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("f5"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_BlackToMove_Convert00)
    {
        ChessGame cg {"rn1qk2r/1p2bppp/p2pbn2/4p3/4P3/1NN1BP2/PPPQ2PP/R3KB1R b KQkq - 2 9"};
        // In this position 0-0 is possibile, 0-0-0 is not
        ASSERT_EQ(cg.checkNotationMove("0-0"), chessMove(King, e8, g8));
        ASSERT_EQ(cg.checkNotationMove("00"), chessMove(King, e8, g8));
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("000"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromASicilianVariantPosition_WhiteToMove_Convert000)
    {
        ChessGame cg {"rn1q1rk1/1p2bppp/p2pbn2/4p3/4P3/1NN1BP2/PPPQ2PP/R3KB1R w KQ - 3 10"};
        // In this position 0-0-0 is possibile, 0-0 is not
        ASSERT_EQ(cg.checkNotationMove("0-0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("00"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), chessMove(King, e1, c1));
        ASSERT_EQ(cg.checkNotationMove("000"), chessMove(King, e1, c1));
    }
    TEST(ChessGameTester, NotationToMove_FromAnItalianGame_WhiteToMove_Convert00_and000)
    {
        ChessGame cg {"r3k2r/ppp2ppp/3p1q2/n1b1p3/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 0 9"};
        // In this position both 0-0 and 0-0-0 are possibile
        ASSERT_EQ(cg.checkNotationMove("0-0"), chessMove(King, e1, g1));
        ASSERT_EQ(cg.checkNotationMove("00"), chessMove(King, e1, g1));
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), chessMove(King, e1, c1));
        ASSERT_EQ(cg.checkNotationMove("000"), chessMove(King, e1, c1));
    }
    TEST(ChessGameTester, NotationToMove_FromAnItalianGame_BlackToMove_Convert00_and000)
    {
        ChessGame cg {"r3k2r/ppp2ppp/3p1q2/n1b1p3/2B1P1b1/2NP1N2/PPPQ1PPP/2KR3R b kq - 1 9"};
        // In this position both 0-0 and 0-0-0 are possibile
        ASSERT_EQ(cg.checkNotationMove("0-0"), chessMove(King, e8, g8));
        ASSERT_EQ(cg.checkNotationMove("00"), chessMove(King, e8, g8));
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), chessMove(King, e8, c8));
        ASSERT_EQ(cg.checkNotationMove("000"), chessMove(King, e8, c8));
    }
    TEST(ChessGameTester, NotationToMove_FromAnItalianGame_WhiteToMove_PositionNotValidForCastling)
    {
        ChessGame cg {"r4rk1/ppp2ppp/3p1q2/n1b1p3/2B1P1b1/2NP1N2/PPPQ1PPP/2KR3R w - - 2 10"};
        // In this position no castling is possibile
        ASSERT_EQ(cg.checkNotationMove("0-0")  , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("00")   , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("000")  , InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_FromAnItalianGame_BlackToMove_PositionNotValidForCastling)
    {
        ChessGame cg {"r4rk1/ppp2ppp/3p1q2/n1b1p3/2B1P1b1/P1NP1N2/1PPQ1PPP/2KR3R b - - 0 10"};
        // In this position no castling is possibile
        ASSERT_EQ(cg.checkNotationMove("0-0")  , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("00")   , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0-0-0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("000")  , InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_ManageInvalidCastlingMoves)
    {
        ChessGame cg {"r3k2r/ppp2ppp/3p1q2/n1b1p3/2B1P1b1/2NP1N2/PPPQ1PPP/R3K2R w KQkq - 0 9"};
        // In this position both 0-0 and 0-0-0 are possibile
        ASSERT_EQ(cg.checkNotationMove("0x0")  , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0-1-0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0000") , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0-00") , InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("0 0 0"), InvalidMove);
    }

} // namespace cSzd