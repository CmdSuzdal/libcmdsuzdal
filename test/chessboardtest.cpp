#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessboard.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    TEST(ChessBoardTester, DefaultConstructorPrepareInitialStandardPosition)
    {
        ChessBoard cb {};
        ASSERT_EQ(cb.whiteArmy.pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb.blackArmy.pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb.blackArmy.pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb.blackArmy.pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb.blackArmy.pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb.blackArmy.pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb.blackArmy.pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cb.sideToMove, WhiteArmy);
        ASSERT_EQ(cb.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cb.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb.halfMoveClock, 0);
        ASSERT_EQ(cb.fullMoves, 1);
    }

    // Test on acquisition of position from a FEN Record
    // 1. Initial standard position
    TEST(ChessBoardTester, FENLoad_InitialStandardPosition)
    {
        ChessBoard cb {FENRecord(FENInitialStandardPosition)};
        ASSERT_EQ(cb.whiteArmy.pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb.whiteArmy.pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb.blackArmy.pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb.blackArmy.pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb.blackArmy.pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb.blackArmy.pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb.blackArmy.pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb.blackArmy.pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cb.sideToMove, WhiteArmy);
        ASSERT_EQ(cb.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cb.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb.halfMoveClock, 0);
        ASSERT_EQ(cb.fullMoves, 1);
    }

    // 2. Empty Board
    TEST(ChessBoardTester, FENLoad_EmptyBoard)
    {
        ChessBoard cb {FENRecord(FENEmptyChessBoard)};
        ASSERT_EQ(cb.whiteArmy.pieces[King],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.whiteArmy.pieces[Queen],  BitBoard(EmptyBB));
        ASSERT_EQ(cb.whiteArmy.pieces[Rook],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.whiteArmy.pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(cb.whiteArmy.pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(cb.whiteArmy.pieces[Pawn],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[King],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[Queen],  BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[Rook],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(cb.blackArmy.pieces[Pawn],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.sideToMove, InvalidArmy);
        ASSERT_EQ(cb.castlingAvailability, BitBoard(EmptyBB));
        ASSERT_EQ(cb.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb.halfMoveClock, 0);
        ASSERT_EQ(cb.fullMoves, 1);
    }

    // ---- Chess board validity tests ------------------------------------
    // After default constructor position is valid
    TEST(ChessBoardTester, AfterDefaultConstructurPositionIsValid)
    {
        ChessBoard cb;
        ASSERT_TRUE(cb.isValid());
    }

    // An empty chessboard is not valid
    TEST(ChessBoardTester, AnEmptyChessBoardIsNotValid)
    {
        ChessBoard cb {FENEmptyChessBoard};
        ASSERT_FALSE(cb.isValid());
    }

    // If one king is missing position is not valid
    TEST(ChessBoardTester, IfKingsAreMissingPositionIsNotValid)
    {
        // Initial position, missing white king
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQ1BNR w kq - 0 1"};
        ASSERT_FALSE(cb.isValid());
        // Initial position, missing black king
        cb.loadPosition("rnbq1bnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQ - 0 1");
        ASSERT_FALSE(cb.isValid());
        // Initial position, missing both kings
        cb.loadPosition("rnbq1bnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQ1BNR w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        // only kings in initial position, everything ok
        cb.loadPosition("4k3/8/8/8/8/8/8/4K3 w - - 0 1");
        ASSERT_TRUE(cb.isValid());
    }

    // If more that one king per side are present, position is not valid
    TEST(ChessBoardTester, IsMoreThanOneArmyKingIsPresentPositionIsNotValid)
    {
        // Initial position with one additional white king
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/8/8/PPKPPPPP/RNBQKBNR w KQkq - 0 1"};
        ASSERT_FALSE(cb.isValid());
        // Initial position with one additional black king
        cb.loadPosition("rnbqkbnr/pppppppp/8/1k6/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        ASSERT_FALSE(cb.isValid());
        // Initial position with one additional king per side
        cb.loadPosition("rnbqkbnr/pppppppp/8/1k6/2K2k2/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        ASSERT_FALSE(cb.isValid());
    }

    // If kings are "in contact" position is not valid
    TEST(ChessBoardTester, IfKingsAreInContactPositionIsNotValid)
    {
        ChessBoard cb { "kK6/8/8/8/8/8/8/8 w - - 0 1" };
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("k7/K7/8/8/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("k7/1K6/8/8/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("k7/2K5/8/8/8/8/8/8 w - - 0 1");
        ASSERT_TRUE(cb.isValid());

        cb.loadPosition("8/8/8/2kK4/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/8/3Kk3/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/2k5/3K4/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/3k4/3K4/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/4k3/3K4/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/8/3K4/2k5/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/8/3K4/3k4/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("8/8/8/3K4/4k3/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
    }

} // namespace cSzd
