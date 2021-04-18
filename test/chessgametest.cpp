#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessgame.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    // ------------------------------------------------------------------------------
    class AChessGameEngine: public Test {
        public:
            ChessGame cg;
            void checkForInitialPosition() {
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
    };

    // ------------------------------------------------------------------------------
    // ChessGame TESTS
    // ------------------------------------------------------------------------------
    TEST_F(AChessGameEngine, ContainsAChessBoardWithTheInitialPositionAfterTheDefaultInitialization)
    {
        checkForInitialPosition();
    }

    TEST_F(AChessGameEngine, IsAbleToLoadTheInitialPositionUsingAFenString)
    {
        cg.loadPosition(FENInitialStandardPosition);
        checkForInitialPosition();
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

        ASSERT_EQ(cg.checkNotationMove("h3%"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("h3$%&"), InvalidMove);
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
    TEST(ChessGameTester, NotationToMove_ConvertWhitePromotionWithNoCapture_AndOtherInvalidExamples)
    {
        ChessGame cg {"8/1P2P3/6k1/8/2K5/8/8/8 w - - 0 1"};
        // In this position promotion of b7 and e7 pawns is possible
        // Correct notation moves are for example "b8=Q" and "e8=N"
        ASSERT_EQ(cg.checkNotationMove("b8=Q"), chessMove(Pawn, b7, b8, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("e8=Q"), chessMove(Pawn, e7, e8, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("e8=N"), chessMove(Pawn, e7, e8, InvalidPiece, Knight));
        ASSERT_EQ(cg.checkNotationMove("e8=B"), chessMove(Pawn, e7, e8, InvalidPiece, Bishop));
        ASSERT_EQ(cg.checkNotationMove("e8=R"), chessMove(Pawn, e7, e8, InvalidPiece, Rook));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("g8=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("g4=N"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("e8=K"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("e8="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("===="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Q=G8"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("e8Q="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("x8=Q"), InvalidMove);

        ASSERT_EQ(cg.checkNotationMove("b8=Q%"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("b8=Q$"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("b8=Q|||"), InvalidMove);

    }
    TEST(ChessGameTester, NotationToMove_ConvertBlackPromotionWithNoCapture_AndOtherInvalidExamples)
    {
        ChessGame cg {"8/8/6k1/8/2K5/8/2p4p/8 b - - 0 1"};
        // In this position promotion of c2 and h2 pawns is possible
        // Correct notation moves are for example "c1=Q" and "h1=N"
        ASSERT_EQ(cg.checkNotationMove("c1=Q"), chessMove(Pawn, c2, c1, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("h1=Q"), chessMove(Pawn, h2, h1, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("h1=N"), chessMove(Pawn, h2, h1, InvalidPiece, Knight));
        ASSERT_EQ(cg.checkNotationMove("h1=B"), chessMove(Pawn, h2, h1, InvalidPiece, Bishop));
        ASSERT_EQ(cg.checkNotationMove("c1=R"), chessMove(Pawn, c2, c1, InvalidPiece, Rook));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("g1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("g5=N"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("c1=K"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("c1="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("===="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Q=C1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("c1Q="), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("x1=Q"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_ConvertWhitePromotionWithCapture_AndOtherInvalidExamples)
    {
        ChessGame cg {"2q1b3/1P2P3/6k1/8/3K4/8/8/8 w - - 0 1"};
        // In this position promotion of b7 pawn is possible
        // Correct notation moves are for example "b8=Q" or "bxc8=Q"
        ASSERT_EQ(cg.checkNotationMove("b8=Q"), chessMove(Pawn, b7, b8, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("bxc8=Q"), chessMove(Pawn, b7, c8, Queen, Queen));
        ASSERT_EQ(cg.checkNotationMove("bxc8=N"), chessMove(Pawn, b7, c8, Queen, Knight));
        ASSERT_EQ(cg.checkNotationMove("bxc8=B"), chessMove(Pawn, b7, c8, Queen, Bishop));
        ASSERT_EQ(cg.checkNotationMove("bxc8=R"), chessMove(Pawn, b7, c8, Queen, Rook));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("bxc8=K"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("bxc9=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xc8=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("bc8=N"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("b8=r"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("c8=R"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_ConvertBlackPromotionWithCapture_AndOtherInvalidExamples)
    {
        ChessGame cg {"8/8/6k1/8/2K5/6p1/2p4p/3Q3B b - - 0 1"};
        // In this position promotion of c2 pawn is possible
        // Correct notation moves are for example "c1=Q" or "cxd1=Q"
        ASSERT_EQ(cg.checkNotationMove("c1=Q"), chessMove(Pawn, c2, c1, InvalidPiece, Queen));
        ASSERT_EQ(cg.checkNotationMove("cxd1=Q"), chessMove(Pawn, c2, d1, Queen, Queen));
        ASSERT_EQ(cg.checkNotationMove("cxd1=N"), chessMove(Pawn, c2, d1, Queen, Knight));
        ASSERT_EQ(cg.checkNotationMove("cxd1=B"), chessMove(Pawn, c2, d1, Queen, Bishop));
        ASSERT_EQ(cg.checkNotationMove("cxd1=R"), chessMove(Pawn, c2, d1, Queen, Rook));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("c:d1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd1xQ"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("ixh1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("_x_1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cx_1=N"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxD1=N"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd0=B"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_ConvertWhitePawnMoveWithCapture_AndExamplesOfInvalidMoves)
    {
        ChessGame cg {"8/1k6/4p3/1p1p4/P1P5/5K2/8/8 w - - 0 1"};
        // In this position the following white moves with no capture are possible:
        ASSERT_EQ(cg.checkNotationMove("a5"), chessMove(Pawn, a4, a5));
        ASSERT_EQ(cg.checkNotationMove("c5"), chessMove(Pawn, c4, c5));

        // and these are the moves with capture:
        ASSERT_EQ(cg.checkNotationMove("axb5"), chessMove(Pawn, a4, b5, Pawn));
        ASSERT_EQ(cg.checkNotationMove("cxb5"), chessMove(Pawn, c4, b5, Pawn));
        ASSERT_EQ(cg.checkNotationMove("cxd5"), chessMove(Pawn, c4, d5, Pawn));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("AxB5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("yxb5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("axj5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("axb9"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cdx0"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("abb2"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxb1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd5%"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd5$$"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd5$$£?°°°"), InvalidMove);
    }
    TEST(ChessGameTester, NotationToMove_ConvertBlackPawnMoveWithCapture_AndExamplesOfInvalidMoves)
    {
        ChessGame cg {"8/1k6/4p3/1p1p4/P1P5/5K2/8/8 b - - 0 1"};
        // In this position the following black moves with no capture are possible:
        ASSERT_EQ(cg.checkNotationMove("b4"), chessMove(Pawn, b5, b4));
        ASSERT_EQ(cg.checkNotationMove("d4"), chessMove(Pawn, d5, d4));
        ASSERT_EQ(cg.checkNotationMove("e5"), chessMove(Pawn, e6, e5));

        // and these are the moves with capture:
        ASSERT_EQ(cg.checkNotationMove("bxa4"), chessMove(Pawn, b5, a4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("bxc4"), chessMove(Pawn, b5, c4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("dxc4"), chessMove(Pawn, d5, c4, Pawn));

        // Examples of invalid moves
        ASSERT_EQ(cg.checkNotationMove("bxa8"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("_xa8"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("bx_8"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_ConvertWhitePawnMoveWithCaptureComplex)
    {
        ChessGame cg {"8/8/k2p2q1/1p1pRP1n/P1B3P1/8/8/6K1 w - - 0 1"};
        // In this position the following white moves with no capture are possible:
        ASSERT_EQ(cg.checkNotationMove("a5"), chessMove(Pawn, a4, a5));
        ASSERT_EQ(cg.checkNotationMove("f6"), chessMove(Pawn, f5, f6));
        ASSERT_EQ(cg.checkNotationMove("g5"), chessMove(Pawn, g4, g5));

        // and these are the moves with capture:
        ASSERT_EQ(cg.checkNotationMove("axb5"), chessMove(Pawn, a4, b5, Pawn));
        ASSERT_EQ(cg.checkNotationMove("fxg6"), chessMove(Pawn, f5, g6, Queen));

        // This move is possible, but invalid (check)
        ASSERT_EQ(cg.checkNotationMove("gxh5"), InvalidMove);

        // If we change sligtly the position, also the latter move becames valid
        ChessGame cg1 {"8/8/k2p2q1/1p1pRP1n/P1B3P1/8/7K/8 w - - 0 1"};
        ASSERT_EQ(cg1.checkNotationMove("a5"), chessMove(Pawn, a4, a5));
        ASSERT_EQ(cg1.checkNotationMove("f6"), chessMove(Pawn, f5, f6));
        ASSERT_EQ(cg1.checkNotationMove("g5"), chessMove(Pawn, g4, g5));
        ASSERT_EQ(cg1.checkNotationMove("axb5"), chessMove(Pawn, a4, b5, Pawn));
        ASSERT_EQ(cg1.checkNotationMove("fxg6"), chessMove(Pawn, f5, g6, Queen));
        ASSERT_EQ(cg1.checkNotationMove("gxh5"), chessMove(Pawn, g4, h5, Knight));

    }
    TEST(ChessGameTester, NotationToMove_ConvertBlackPawnMoveWithCaptureComplex)
    {
        ChessGame cg {"8/8/k2p2q1/1p1pRP1n/P1B3P1/8/8/6K1 b - - 0 1"};
        // In this position the following white moves with no capture are possible:
        ASSERT_EQ(cg.checkNotationMove("d4"), chessMove(Pawn, d5, d4));

        // and these are the moves with capture:
        ASSERT_EQ(cg.checkNotationMove("bxc4"), chessMove(Pawn, b5, c4, Bishop));
        ASSERT_EQ(cg.checkNotationMove("dxe5"), chessMove(Pawn, d6, e5, Rook));

        // This moves are possible, but invalid (check)
        ASSERT_EQ(cg.checkNotationMove("b4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("bxa4"), InvalidMove);

        // If we change sligtly the position, also the latter moves becames valid
        ChessGame cg1 {"8/k7/3p2q1/1p1pRP1n/P1B3P1/8/6K1/8 b - - 0 1"};
        ASSERT_EQ(cg1.checkNotationMove("d4"), chessMove(Pawn, d5, d4));
        ASSERT_EQ(cg1.checkNotationMove("bxc4"), chessMove(Pawn, b5, c4, Bishop));
        ASSERT_EQ(cg1.checkNotationMove("dxe5"), chessMove(Pawn, d6, e5, Rook));
        ASSERT_EQ(cg1.checkNotationMove("b4"), chessMove(Pawn, b5, b4));
        ASSERT_EQ(cg1.checkNotationMove("bxa4"), chessMove(Pawn, b5, a4, Pawn));
    }


    // For coverage...
    TEST(ChessGameTester, NotationToMove_ConvertSimpleBlackPromotionWithCapture_WhenInvalidArmy)
    {
        ChessGame cg {"8/8/8/8/8/8/8/8 w - - 0 1"};
        cg.board.sideToMove = InvalidArmy;
        ASSERT_EQ(cg.checkNotationMove("c1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("cxd1=Q"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("bxa4"), InvalidMove);
    }

    // Piece Movements
    TEST(ChessGameTester, NotationToMove_InitialPositionWhiteKnightMovements)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove("Nf3"), chessMove(Knight, g1, f3));
        ASSERT_EQ(cg.checkNotationMove("Nc3"), chessMove(Knight, b1, c3));
    }
    TEST(ChessGameTester, NotationToMove_InitialPositionBlackKnightMovements)
    {
        ChessGame cg {FENInitialStandardPosition};
        cg.addMove(chessMove(Pawn, e2, e4));
        ASSERT_EQ(cg.checkNotationMove("Nf6"), chessMove(Knight, g8, f6));
        ASSERT_EQ(cg.checkNotationMove("Nc6"), chessMove(Knight, b8, c6));
    }
    TEST(ChessGameTester, NotationToMove_InitialPositionWhiteAndBlackInvalidMovement)
    {
        ChessGame cg {FENInitialStandardPosition};
        ASSERT_EQ(cg.checkNotationMove("Nf4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nc6"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qd3"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rh2"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bg5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bc4"), InvalidMove);
        cg.addMove(chessMove(Pawn, e2, e4));
        ASSERT_EQ(cg.checkNotationMove("Nf4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nc3"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qd3"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rh2"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bg5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bc4"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_MiddleGamePositionWhitePiecesMovements)
    {
        ChessGame cg {"r1bq1rk1/ppp1n1bp/3p1np1/3PppN1/1PP1P3/2N5/P3BPPP/R1BQR1K1 w - - 2 12"};
        ASSERT_EQ(cg.checkNotationMove("Na4"), chessMove(Knight, c3, a4));
        ASSERT_EQ(cg.checkNotationMove("Nb5"), chessMove(Knight, c3, b5));
        ASSERT_EQ(cg.checkNotationMove("Nb1"), chessMove(Knight, c3, b1));
        ASSERT_EQ(cg.checkNotationMove("Rb1"), chessMove(Rook, a1, b1));
        ASSERT_EQ(cg.checkNotationMove("Bb2"), chessMove(Bishop, c1, b2));
        ASSERT_EQ(cg.checkNotationMove("Ba3"), chessMove(Bishop, c1, a3));
        ASSERT_EQ(cg.checkNotationMove("Bd2"), chessMove(Bishop, c1, d2));
        ASSERT_EQ(cg.checkNotationMove("Be3"), chessMove(Bishop, c1, e3));
        ASSERT_EQ(cg.checkNotationMove("Bf4"), chessMove(Bishop, c1, f4));
        ASSERT_EQ(cg.checkNotationMove("Bd3"), chessMove(Bishop, e2, d3));
        ASSERT_EQ(cg.checkNotationMove("Bf3"), chessMove(Bishop, e2, f3));
        ASSERT_EQ(cg.checkNotationMove("Bg4"), chessMove(Bishop, e2, g4));
        ASSERT_EQ(cg.checkNotationMove("Bh5"), chessMove(Bishop, e2, h5));
        ASSERT_EQ(cg.checkNotationMove("Rf1"), chessMove(Rook, e1, f1));
        ASSERT_EQ(cg.checkNotationMove("Kf1"), chessMove(King, g1, f1));
        ASSERT_EQ(cg.checkNotationMove("Kh1"), chessMove(King, g1, h1));
        ASSERT_EQ(cg.checkNotationMove("Qc2"), chessMove(Queen, d1, c2));
        ASSERT_EQ(cg.checkNotationMove("Qb3"), chessMove(Queen, d1, b3));
        ASSERT_EQ(cg.checkNotationMove("Qa4"), chessMove(Queen, d1, a4));
        ASSERT_EQ(cg.checkNotationMove("Qd2"), chessMove(Queen, d1, d2));
        ASSERT_EQ(cg.checkNotationMove("Qd3"), chessMove(Queen, d1, d3));
        ASSERT_EQ(cg.checkNotationMove("Qd4"), chessMove(Queen, d1, d4));

        // Invalid... (unnecessary "x")
        ASSERT_EQ(cg.checkNotationMove("Nxa4"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xNb5"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nbx1"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rxxb1"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxb2"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxa3"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxd2"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxe3"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxf4"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bd3xx"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xBf3x"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxgx4"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bxhx5"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xRxxxf1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Kf1xx"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qxc2"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qb3x"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qxxa4"),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qxd2"),    InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xxxQd3"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qdxxxx4"), InvalidMove);

        // Invalid... (too short)
        ASSERT_EQ(cg.checkNotationMove("Na"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("N5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("N"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("R"),  InvalidMove);

    }

    TEST(ChessGameTester, NotationToMove_MiddleGamePositionBlackPiecesMovements)
    {
        ChessGame cg {"r2Q1rk1/pp2n1b1/4P1pp/2B1p3/1P2p3/8/P4PPP/R3R1K1 b - - 0 20"};
        ASSERT_EQ(cg.checkNotationMove("Kh8"), chessMove(King, g8, h8));
        ASSERT_EQ(cg.checkNotationMove("Kh7"), chessMove(King, g8, h7));
        ASSERT_EQ(cg.checkNotationMove("Nd5"), chessMove(Knight, e7, d5));
        ASSERT_EQ(cg.checkNotationMove("Nc6"), chessMove(Knight, e7, c6));
        ASSERT_EQ(cg.checkNotationMove("Nc8"), chessMove(Knight, e7, c8));
        ASSERT_EQ(cg.checkNotationMove("Nf5"), chessMove(Knight, e7, f5));
        ASSERT_EQ(cg.checkNotationMove("Bf6"), chessMove(Bishop, g7, f6));
        ASSERT_EQ(cg.checkNotationMove("Rb8"), chessMove(Rook, a8, b8));
        ASSERT_EQ(cg.checkNotationMove("Rc8"), chessMove(Rook, a8, c8));
        ASSERT_EQ(cg.checkNotationMove("Re8"), chessMove(Rook, f8, e8));

        // Ambiguous...
        ASSERT_EQ(cg.checkNotationMove("Rxd8"), InvalidMove);

        // Invalid moves...
        ASSERT_EQ(cg.checkNotationMove("Kf7"), InvalidMove); // check!
        ASSERT_EQ(cg.checkNotationMove("Rf7"), InvalidMove); // check!
        ASSERT_EQ(cg.checkNotationMove("Rf6"), InvalidMove); // check!
        ASSERT_EQ(cg.checkNotationMove("Rf5"), InvalidMove); // check!
        ASSERT_EQ(cg.checkNotationMove("Rf4"), InvalidMove); // check!
        ASSERT_EQ(cg.checkNotationMove("Rf3"), InvalidMove); // check!

        // Ambiguous capture moves still not managed at the current point of the development
        //ASSERT_EQ(cg.checkNotationMove("Raxd8"), chessMove(Rook, a8, d8, Queen));
        //ASSERT_EQ(cg.checkNotationMove("Rfxd8"), chessMove(Rook, f8, d8, Queen));
    }

    TEST(ChessGameTester, NotationToMove_WhiteToMove_PiecesCaptureMovements)
    {
        ChessGame cg {"4rbk1/p1qn1ppp/b1p1p3/8/P1pPP3/2B1N1P1/2Q2P1P/1r2RBK1 w - - 0 24"};
        ASSERT_EQ(cg.checkNotationMove("Rxb1"), chessMove(Rook, e1, b1, Rook));
        ASSERT_EQ(cg.checkNotationMove("Qxb1"), chessMove(Queen, c2, b1, Rook));
        ASSERT_EQ(cg.checkNotationMove("Nxc4"), chessMove(Knight, e3, c4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Bxc4"), chessMove(Bishop, f1, c4, Pawn));

        // Invalid moves...
        ASSERT_EQ(cg.checkNotationMove("Qxc4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rb1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qb1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nc4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Bc4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rb1x"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xQb1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("xxxb1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Kxx"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qx1"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qxb"), InvalidMove);

    }

    TEST(ChessGameTester, NotationToMove_BlackToMove_PiecesCaptureMovements)
    {
        ChessGame cg {"5bk1/p4ppp/q3pn2/2p5/P1NPP3/4BPP1/2Q4P/6K1 b - - 1 31"};
        ASSERT_EQ(cg.checkNotationMove("Qxc4"), chessMove(Queen, a6, c4, Knight));
        ASSERT_EQ(cg.checkNotationMove("Qxa4"), chessMove(Queen, a6, a4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Nxe4"), chessMove(Knight, f6, e4, Pawn));

        // Invalid moves...
        ASSERT_EQ(cg.checkNotationMove("Qxc2"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qc4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Kxc4"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_WhiteToMove_AmbiguousPiecesMovements_File)
    {
        ChessGame cg {"8/6k1/5p2/1P2p3/P7/8/1KN3N1/8 w - - 0 1"};
        // correct unambiguous moves
        ASSERT_EQ(cg.checkNotationMove("Na1"), chessMove(Knight, c2, a1));
        ASSERT_EQ(cg.checkNotationMove("Na3"), chessMove(Knight, c2, a3));
        ASSERT_EQ(cg.checkNotationMove("Nb4"), chessMove(Knight, c2, b4));
        ASSERT_EQ(cg.checkNotationMove("Nd4"), chessMove(Knight, c2, d4));
        ASSERT_EQ(cg.checkNotationMove("Nf4"), chessMove(Knight, g2, f4));
        ASSERT_EQ(cg.checkNotationMove("Nh4"), chessMove(Knight, g2, h4));

        // Invalid (ambiguous) moves
        ASSERT_EQ(cg.checkNotationMove("Ne3"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne1"), InvalidMove);

        // Valid (unambiguous moves)
        ASSERT_EQ(cg.checkNotationMove("Nce3"), chessMove(Knight, c2, e3));
        ASSERT_EQ(cg.checkNotationMove("Nce1"), chessMove(Knight, c2, e1));
        ASSERT_EQ(cg.checkNotationMove("Nge3"), chessMove(Knight, g2, e3));
        ASSERT_EQ(cg.checkNotationMove("Nge1"), chessMove(Knight, g2, e1));
    }

    TEST(ChessGameTester, NotationToMove_BlackToMove_AmbiguousPiecesMovements_Rank)
    {
        ChessGame cg {"8/3r2k1/5p2/1P2p3/P7/8/1K6/3r4 b - - 0 1"};
        // correct unambiguous moves
        ASSERT_EQ(cg.checkNotationMove("Ra7"), chessMove(Rook, d7, a7));
        ASSERT_EQ(cg.checkNotationMove("Rb7"), chessMove(Rook, d7, b7));
        ASSERT_EQ(cg.checkNotationMove("Rc7"), chessMove(Rook, d7, c7));
        ASSERT_EQ(cg.checkNotationMove("Re7"), chessMove(Rook, d7, e7));
        ASSERT_EQ(cg.checkNotationMove("Rf7"), chessMove(Rook, d7, f7));
        ASSERT_EQ(cg.checkNotationMove("Ra1"), chessMove(Rook, d1, a1));
        ASSERT_EQ(cg.checkNotationMove("Rb1"), chessMove(Rook, d1, b1));
        ASSERT_EQ(cg.checkNotationMove("Rc1"), chessMove(Rook, d1, c1));
        ASSERT_EQ(cg.checkNotationMove("Re1"), chessMove(Rook, d1, e1));
        ASSERT_EQ(cg.checkNotationMove("Rf1"), chessMove(Rook, d1, f1));
        ASSERT_EQ(cg.checkNotationMove("Rg1"), chessMove(Rook, d1, g1));
        ASSERT_EQ(cg.checkNotationMove("Rh1"), chessMove(Rook, d1, h1));
        ASSERT_EQ(cg.checkNotationMove("Rd8"), chessMove(Rook, d7, d8));

        // Invalid (illegal) moves
        ASSERT_EQ(cg.checkNotationMove("Rd7"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rd1"), InvalidMove);

        // Invalid (ambiguous) moves
        ASSERT_EQ(cg.checkNotationMove("Rd6"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rd5"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rd4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rd3"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Rd2"), InvalidMove);

        // Valid (unambiguous moves)
        ASSERT_EQ(cg.checkNotationMove("R7d6"), chessMove(Rook, d7, d6));
        ASSERT_EQ(cg.checkNotationMove("R7d5"), chessMove(Rook, d7, d5));
        ASSERT_EQ(cg.checkNotationMove("R7d4"), chessMove(Rook, d7, d4));
        ASSERT_EQ(cg.checkNotationMove("R7d3"), chessMove(Rook, d7, d3));
        ASSERT_EQ(cg.checkNotationMove("R7d2"), chessMove(Rook, d7, d2));
        ASSERT_EQ(cg.checkNotationMove("R1d6"), chessMove(Rook, d1, d6));
        ASSERT_EQ(cg.checkNotationMove("R1d5"), chessMove(Rook, d1, d5));
        ASSERT_EQ(cg.checkNotationMove("R1d4"), chessMove(Rook, d1, d4));
        ASSERT_EQ(cg.checkNotationMove("R1d3"), chessMove(Rook, d1, d3));
        ASSERT_EQ(cg.checkNotationMove("R1d2"), chessMove(Rook, d1, d2));
    }

    TEST(ChessGameTester, NotationToMove_BlackToMove_AmbiguousPiecesMovementsWithCapture_File)
    {
        ChessGame cg {"6bk/r4Q1r/3n4/8/2R1P3/7P/1K1n4/8 b - - 0 1"};

        // Correct unambiguous moves
        ASSERT_EQ(cg.checkNotationMove("Bxf7"), chessMove(Bishop, g8, f7, Queen));
        ASSERT_EQ(cg.checkNotationMove("Ra1"), chessMove(Rook, a7, a1));
        ASSERT_EQ(cg.checkNotationMove("Ra2"), chessMove(Rook, a7, a2));
        ASSERT_EQ(cg.checkNotationMove("Ra3"), chessMove(Rook, a7, a3));
        ASSERT_EQ(cg.checkNotationMove("Ra4"), chessMove(Rook, a7, a4));
        ASSERT_EQ(cg.checkNotationMove("Ra5"), chessMove(Rook, a7, a5));
        ASSERT_EQ(cg.checkNotationMove("Ra6"), chessMove(Rook, a7, a6));
        ASSERT_EQ(cg.checkNotationMove("Ra8"), chessMove(Rook, a7, a8));
        ASSERT_EQ(cg.checkNotationMove("Rxh3"), chessMove(Rook, h7, h3, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Rh4"), chessMove(Rook, h7, h4));
        ASSERT_EQ(cg.checkNotationMove("Rh5"), chessMove(Rook, h7, h5));
        ASSERT_EQ(cg.checkNotationMove("Rh6"), chessMove(Rook, h7, h6));
        ASSERT_EQ(cg.checkNotationMove("Rb7"), chessMove(Rook, a7, b7));
        ASSERT_EQ(cg.checkNotationMove("Rc7"), chessMove(Rook, a7, c7));
        ASSERT_EQ(cg.checkNotationMove("Rd7"), chessMove(Rook, a7, d7));
        ASSERT_EQ(cg.checkNotationMove("Re7"), chessMove(Rook, a7, e7));
        ASSERT_EQ(cg.checkNotationMove("Nb1"), chessMove(Knight, d2, b1));
        ASSERT_EQ(cg.checkNotationMove("Nb3"), chessMove(Knight, d2, b3));
        ASSERT_EQ(cg.checkNotationMove("Nf3"), chessMove(Knight, d2, f3));
        ASSERT_EQ(cg.checkNotationMove("Nf1"), chessMove(Knight, d2, f1));
        ASSERT_EQ(cg.checkNotationMove("Nb5"), chessMove(Knight, d6, b5));
        ASSERT_EQ(cg.checkNotationMove("Nb7"), chessMove(Knight, d6, b7));
        ASSERT_EQ(cg.checkNotationMove("Nxf7"), chessMove(Knight, d6, f7, Queen));
        ASSERT_EQ(cg.checkNotationMove("Nf5"), chessMove(Knight, d6, f5));

        // Redundant, but still valid...
        ASSERT_EQ(cg.checkNotationMove("Raa1"), chessMove(Rook, a7, a1));
        ASSERT_EQ(cg.checkNotationMove("R7a1"), chessMove(Rook, a7, a1));
        ASSERT_EQ(cg.checkNotationMove("Rad7"), chessMove(Rook, a7, d7));
        ASSERT_EQ(cg.checkNotationMove("R7d7"), chessMove(Rook, a7, d7));
        ASSERT_EQ(cg.checkNotationMove("N6b5"), chessMove(Knight, d6, b5));
        ASSERT_EQ(cg.checkNotationMove("N2b3"), chessMove(Knight, d2, b3));

        // INVALID ambiguous capture moves...
        ASSERT_EQ(cg.checkNotationMove("Rxf7"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nxc4"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nxe4"), InvalidMove);

        // Correct disambiguated capture moves...
        ASSERT_EQ(cg.checkNotationMove("Raxf7"), chessMove(Rook, a7, f7, Queen));
        ASSERT_EQ(cg.checkNotationMove("Rhxf7"), chessMove(Rook, h7, f7, Queen));
        ASSERT_EQ(cg.checkNotationMove("N6xc4"), chessMove(Knight, d6, c4, Rook));
        ASSERT_EQ(cg.checkNotationMove("N2xc4"), chessMove(Knight, d2, c4, Rook));
        ASSERT_EQ(cg.checkNotationMove("N6xe4"), chessMove(Knight, d6, e4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("N2xe4"), chessMove(Knight, d2, e4, Pawn));

        // Invalid moves (redundant)
        ASSERT_EQ(cg.checkNotationMove("Ra7xf7"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Nd6xe4"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_Checks)
    {
        ChessGame cg {"3k4/8/3K4/8/6Q1/8/8/8 w - - 0 1"};

        // No check moves
        ASSERT_EQ(cg.checkNotationMove("Qa4"), chessMove(Queen, g4, a4));
        ASSERT_EQ(cg.checkNotationMove("Qb4"), chessMove(Queen, g4, b4));
        ASSERT_EQ(cg.checkNotationMove("Qc4"), chessMove(Queen, g4, c4));
        ASSERT_EQ(cg.checkNotationMove("Qd4"), chessMove(Queen, g4, d4));
        ASSERT_EQ(cg.checkNotationMove("Qe4"), chessMove(Queen, g4, e4));
        ASSERT_EQ(cg.checkNotationMove("Qf4"), chessMove(Queen, g4, f4));
        ASSERT_EQ(cg.checkNotationMove("Qg1"), chessMove(Queen, g4, g1));
        ASSERT_EQ(cg.checkNotationMove("Qg2"), chessMove(Queen, g4, g2));
        ASSERT_EQ(cg.checkNotationMove("Qg3"), chessMove(Queen, g4, g3));
        ASSERT_EQ(cg.checkNotationMove("Qg6"), chessMove(Queen, g4, g6));
        ASSERT_EQ(cg.checkNotationMove("Qg7"), chessMove(Queen, g4, g7));
        ASSERT_EQ(cg.checkNotationMove("Qd1"), chessMove(Queen, g4, d1));
        ASSERT_EQ(cg.checkNotationMove("Qe2"), chessMove(Queen, g4, e2));
        ASSERT_EQ(cg.checkNotationMove("Qf3"), chessMove(Queen, g4, f3));
        ASSERT_EQ(cg.checkNotationMove("Qh5"), chessMove(Queen, g4, h5));
        ASSERT_EQ(cg.checkNotationMove("Qh3"), chessMove(Queen, g4, h3));
        ASSERT_EQ(cg.checkNotationMove("Qf5"), chessMove(Queen, g4, f5));
        ASSERT_EQ(cg.checkNotationMove("Qe6"), chessMove(Queen, g4, e6));


        // Checks
        // We accept also the check move without the check annotation
        ASSERT_EQ(cg.checkNotationMove("Qh4"), chessMove(Queen, g4, h4));
        ASSERT_EQ(cg.checkNotationMove("Qg5"), chessMove(Queen, g4, g5));
        ASSERT_EQ(cg.checkNotationMove("Qc8"), chessMove(Queen, g4, c8));
        ASSERT_EQ(cg.checkNotationMove("Qh4+"), chessMove(Queen, g4, h4));
        ASSERT_EQ(cg.checkNotationMove("Qg5+"), chessMove(Queen, g4, g5));
        ASSERT_EQ(cg.checkNotationMove("Qc8+"), chessMove(Queen, g4, c8));

        // Checkmates
        // We accept also the checkmate move without the checkmate annotation
        // and we accet also the checkmate with only the check annotation
        // (questionable...)
        ASSERT_EQ(cg.checkNotationMove("Qd7"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qg8"), chessMove(Queen, g4, g8));
        ASSERT_EQ(cg.checkNotationMove("Qd7#"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qg8#"), chessMove(Queen, g4, g8));
        ASSERT_EQ(cg.checkNotationMove("Qd7+"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qg8+"), chessMove(Queen, g4, g8));

        // The '+#' and '#+' annotations are invalid and shall be refused
        ASSERT_EQ(cg.checkNotationMove("Qd7+#"), InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Qg8#+"), InvalidMove);

    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_BadMoves)
    {
        ChessGame cg {"rnb1k2r/pp3ppp/4p3/q2p4/1bPP4/2NB4/PPQN1PPP/R3K2R b KQkq - 0 10"};

        ASSERT_EQ(cg.checkNotationMove("dxc4"), chessMove(Pawn, d5, c4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("dxc4?"), chessMove(Pawn, d5, c4, Pawn));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_GoodMoves)
    {
        ChessGame cg {"r1b1k2r/pp3ppp/2n1p3/6q1/2NP4/2PB4/P1Q2PPP/R4RK1 w kq - 1 14"};
        ASSERT_EQ(cg.checkNotationMove("f4"), chessMove(Pawn, f2, f4));
        ASSERT_EQ(cg.checkNotationMove("f4!"), chessMove(Pawn, f2, f4));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_BrilliantMoves)
    {
        // Planinc - Velimirovic , Jugoslavia 1975
        ChessGame cg {"1q3rk1/1p1bppbp/r2p1np1/1N6/4P3/1PN1BP2/1PP1Q1PP/2KR3R b - - 0 16"};
        ASSERT_EQ(cg.checkNotationMove("d5"), chessMove(Pawn, d6, d5));
        ASSERT_EQ(cg.checkNotationMove("d5!"), chessMove(Pawn, d6, d5));
        ASSERT_EQ(cg.checkNotationMove("d5!!"), chessMove(Pawn, d6, d5));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_InterestingAndQuestionableMoves)
    {
        ChessGame cg {"rnbqkb1r/pppppppp/5n2/8/4P3/2N5/PPPP1PPP/R1BQKBNR b KQkq - 2 2"};
        ASSERT_EQ(cg.checkNotationMove("e6"), chessMove(Pawn, e7, e6));
        ASSERT_EQ(cg.checkNotationMove("e6!?"), chessMove(Pawn, e7, e6));
        ASSERT_EQ(cg.checkNotationMove("e6?!"), chessMove(Pawn, e7, e6));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_Blunder)
    {
        ChessGame cg {"rn1qkb1r/pQ2pppp/1np5/4Nb2/2BP4/4P3/PP3PPP/RNB1K2R b KQkq - 2 8"};
        ASSERT_EQ(cg.checkNotationMove("Bc8??"),   chessMove(Bishop, f5, c8));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_CompositeAnnotation)
    {
        ChessGame cg {"r6r/p4kbp/bq3np1/2pp2B1/6Q1/5N2/PPP2PPP/1R2R1K1 w - - 0 17"};
        ASSERT_EQ(cg.checkNotationMove("Ne5+"),   chessMove(Knight, f3, e5));
        ASSERT_EQ(cg.checkNotationMove("Ne5+?"),  chessMove(Knight, f3, e5));
        ASSERT_EQ(cg.checkNotationMove("Ne5+??"), chessMove(Knight, f3, e5));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_CheckmatesWithAdditionalAnnotations)
    {
        // Additional annotation on checkmates are superfluous if not wrong...
        // but we accect them (for the moment)

        // checkmate (in one...) cannot be a good/brilliant move
        ChessGame cg {"3k4/8/3K4/8/6Q1/8/8/8 w - - 0 1"};
        ASSERT_EQ(cg.checkNotationMove("Qd7#!"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qd7#!!"), chessMove(Queen, g4, d7));

        // A fortiori, Checkmate cannot be a bad move / blunder
        ASSERT_EQ(cg.checkNotationMove("Qd7#?"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qd7#??"), chessMove(Queen, g4, d7));

        // Finally, questionable / interesting does not make sense
        ASSERT_EQ(cg.checkNotationMove("Qd7#!?"), chessMove(Queen, g4, d7));
        ASSERT_EQ(cg.checkNotationMove("Qd7#?!"), chessMove(Queen, g4, d7));
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_InvalidAnnotations)
    {
        ChessGame cg {"r6r/p4kbp/bq3np1/2pp2B1/6Q1/5N2/PPP2PPP/1R2R1K1 w - - 0 17"};
        ASSERT_EQ(cg.checkNotationMove(""),   InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5?+"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5??+"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5!+"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5!!+"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5?!+"),  InvalidMove);
        ASSERT_EQ(cg.checkNotationMove("Ne5!?+"),  InvalidMove);

        ChessGame cgWithMate {"3k4/8/3K4/8/6Q1/8/8/8 w - - 0 1"};
        ASSERT_EQ(cgWithMate.checkNotationMove("Qd7!#"),  InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qg8!#"),  InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qd7!!#"), InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qg8!!#"), InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qd7?#"),  InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qg8?#"),  InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qd7??#"), InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qg8??#"), InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qd7!?#"), InvalidMove);
        ASSERT_EQ(cgWithMate.checkNotationMove("Qg8?!#"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_OtherInvalidCases)
    {
        // Too much '!'
        ChessGame cg {"1q3rk1/1p1bppbp/r2p1np1/1N6/4P3/1PN1BP2/1PP1Q1PP/2KR3R b - - 0 16"};
        ASSERT_EQ(cg.checkNotationMove("d5!!!"), InvalidMove);

        // Too much '?'
        ChessGame cg1 {"1q3rk1/1p1bppbp/r2p1np1/1N6/4P3/1PN1BP2/1PP1Q1PP/2KR3R b - - 0 16"};
        ASSERT_EQ(cg1.checkNotationMove("Bg4??"), chessMove(Bishop, d7, g4));
        ASSERT_EQ(cg1.checkNotationMove("Bg4???"), InvalidMove);

        // Too much '?' combined with '!'
        ASSERT_EQ(cg1.checkNotationMove("Bg4!??"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4?!?"), InvalidMove);

        // Note that '??!' is a trigraph
        ASSERT_EQ(cg1.checkNotationMove("Bg4\?\?!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4?!!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4!?!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4!!?"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4!!??"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4\?\?!!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4?!?!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4!?!?"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4!\?\?!"), InvalidMove);
        ASSERT_EQ(cg1.checkNotationMove("Bg4?!!?"), InvalidMove);
    }

    TEST(ChessGameTester, NotationToMove_MovesWithAnnotations_RefusesFalseCheckAndCheckMateAnnotations)
    {
        ChessGame cg {"1q3rk1/1p1bppbp/r2p1np1/1N6/4P3/1PN1BP2/1PP1Q1PP/2KR3R b - - 0 16"};

        ASSERT_EQ(cg.checkNotationMove("Nxe4"), chessMove(Knight, f6, e4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Bxb5"), chessMove(Bishop, d7, b5, Knight));
        ASSERT_EQ(cg.checkNotationMove("Ra2"),  chessMove(Rook, a6, a2));
        ASSERT_EQ(cg.checkNotationMove("Ra1+"), chessMove(Rook, a6, a1));

        // For the moment, we accept 'no check' moves annotated as check or checkmate
        ASSERT_EQ(cg.checkNotationMove("Nxe4+"), chessMove(Knight, f6, e4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Bxb5+"), chessMove(Bishop, d7, b5, Knight));
        ASSERT_EQ(cg.checkNotationMove("Ra2+"),  chessMove(Rook, a6, a2));
        ASSERT_EQ(cg.checkNotationMove("Nxe4#"), chessMove(Knight, f6, e4, Pawn));
        ASSERT_EQ(cg.checkNotationMove("Bxb5#"), chessMove(Bishop, d7, b5, Knight));
        ASSERT_EQ(cg.checkNotationMove("Ra2#"),  chessMove(Rook, a6, a2));

        // No checkmate move annotated as checkmate
        ASSERT_EQ(cg.checkNotationMove("Ra1#"), chessMove(Rook, a6, a1));

    }

} // namespace cSzd