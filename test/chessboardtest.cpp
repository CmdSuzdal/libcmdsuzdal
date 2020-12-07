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

} // namespace cSzd
