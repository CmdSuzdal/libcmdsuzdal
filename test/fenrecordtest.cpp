#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "cmdsuzdal/fenrecord.h"

using namespace std;
using namespace testing;

#include "cmdsuzdal/fenrecord.h"

namespace cSzd
{
    constexpr std::string_view FENExampleE97Position
     {"r1bq1rk1/pp2n1b1/2ppNnpp/3Ppp2/1PP1P3/2N1BB2/P4PPP/R2QR1K1 b - - 1 14"};

    constexpr std::string_view FENExampleCastlingEnPassantTest
    {"rnbqkr2/ppp1ppbp/3p1n2/8/1PPPPPp1/P1N5/6PP/1RBQKBNR b Kq f3 0 8"};


    constexpr BitBoardState exampleE97Position           { 0x6D53FC381634E159ULL };
    constexpr BitBoardState exampleCastlingEnPassantTest { 0x3FF728007E05C0FEULL };

    TEST(FENRecordTester, DefaultCnstrPrepareInitialStandardBoard)
    {
        // Starting position:
        // "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
        FENRecord f;
        ASSERT_EQ(f.value(), FENInitialStandardPosition);
    }
    TEST(FENRecordTester, GenericPositionCnstrWithEmptyChessBoardIsNotOK)
    {
        FENRecord f {FENEmptyChessBoard};
        ASSERT_EQ(f.value(), FENEmptyChessBoard);
    }

    // Change position function
    TEST(FENRecordTester, ChangePositionToEmptyWorksOK)
    {
        FENRecord f;
        ASSERT_EQ(f.value(), FENInitialStandardPosition);
        f.loadPosition(FENEmptyChessBoard);
        ASSERT_EQ(f.value(), FENEmptyChessBoard);
    }

    // Sub-FEN extraction functions
    TEST(FENRecordTester, ExtractFENFieldsFromVariousPositionsIsOK)
    {
        FENRecord f;
        ASSERT_EQ(f.piecePlacement(), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
        ASSERT_EQ(f.sideToMove(), WhiteArmy);
        ASSERT_EQ(f.castlingAvailability(), BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(f.enPassantTargetSquare(), BitBoard(EmptyBB));
        ASSERT_EQ(f.halfMoveClock(), 0);
        ASSERT_EQ(f.fullMoves(), 1);
        f.loadPosition(FENEmptyChessBoard);
        ASSERT_EQ(f.piecePlacement(), "8/8/8/8/8/8/8/8");
        ASSERT_EQ(f.sideToMove(), InvalidArmy);
        ASSERT_EQ(f.castlingAvailability(), BitBoard(EmptyBB));
        ASSERT_EQ(f.enPassantTargetSquare(), BitBoard(EmptyBB));
        ASSERT_EQ(f.halfMoveClock(), 0);
        ASSERT_EQ(f.fullMoves(), 1);
        f.loadPosition(FENExampleE97Position);
        ASSERT_EQ(f.piecePlacement(), "r1bq1rk1/pp2n1b1/2ppNnpp/3Ppp2/1PP1P3/2N1BB2/P4PPP/R2QR1K1");
        ASSERT_EQ(f.sideToMove(), BlackArmy);
        ASSERT_EQ(f.castlingAvailability(), BitBoard(EmptyBB));
        ASSERT_EQ(f.enPassantTargetSquare(), BitBoard(EmptyBB));
        ASSERT_EQ(f.halfMoveClock(), 1);
        ASSERT_EQ(f.fullMoves(), 14);
        f.loadPosition(FENExampleCastlingEnPassantTest);
        ASSERT_EQ(f.piecePlacement(), "rnbqkr2/ppp1ppbp/3p1n2/8/1PPPPPp1/P1N5/6PP/1RBQKBNR");
        ASSERT_EQ(f.sideToMove(), BlackArmy);
        ASSERT_EQ(f.castlingAvailability(), BitBoard({g1, b8}));
        ASSERT_EQ(f.enPassantTargetSquare(), BitBoard({f3}));
        ASSERT_EQ(f.halfMoveClock(), 0);
        ASSERT_EQ(f.fullMoves(), 8);
    }

    TEST(FENRecordTester, ExtractBitBoardWithIllegalParametersReturnsEmptyBitBoard)
    {
        FENRecord f; // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3)), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), King), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), Queen), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), Bishop), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), Knight), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), Rook), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(static_cast<ArmyColor>(3), Pawn), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, static_cast<Piece>(42)), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, static_cast<Piece>(42)), BitBoard(EmptyBB));
    }


    TEST(FENRecordTester, ExtractArmyPlacementFromVariousPositionIsOK)
    {
        FENRecord f; // rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR
        ASSERT_EQ(f.extractBitBoard(), BitBoard(RanksBB[r_1] | RanksBB[r_2] | RanksBB[r_7] | RanksBB[r_8]));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy),         BitBoard(RanksBB[r_1] | RanksBB[r_2]));
        ASSERT_EQ(f.extractBitBoard(BlackArmy),         BitBoard(RanksBB[r_7] | RanksBB[r_8]));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, King),   BitBoard({e1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Queen),  BitBoard({d1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Bishop), BitBoard({c1, f1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Knight), BitBoard({b1, g1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Rook),   BitBoard({a1, h1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Pawn),   BitBoard(RanksBB[r_2]));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, King),   BitBoard({e8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Queen),  BitBoard({d8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Bishop), BitBoard({c8, f8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Knight), BitBoard({b8, g8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Rook),   BitBoard({a8, h8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Pawn),   BitBoard(RanksBB[r_7]));

        f.loadPosition(FENEmptyChessBoard);    // 8/8/8/8/8/8/8/8
        ASSERT_EQ(f.extractBitBoard(), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy),         BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy),         BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, King),   BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Queen),  BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Bishop), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Knight), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Rook),   BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Pawn),   BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, King),   BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Queen),  BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Bishop), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Knight), BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Rook),   BitBoard(EmptyBB));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Pawn),   BitBoard(EmptyBB));

        f.loadPosition(FENExampleE97Position);
        ASSERT_EQ(f.extractBitBoard(), BitBoard(exampleE97Position));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy),         BitBoard({g1, d1, e3, f3, c3, e6, a1, e1, a2, b4, c4, d5, e4, f2, g2, h2}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy),         BitBoard({g8, d8, c8, g7, e7, f6, a8, f8, a7, b7, c6, d6, e5, f5, g6, h6}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, King),   BitBoard({g1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Queen),  BitBoard({d1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Bishop), BitBoard({e3, f3}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Knight), BitBoard({c3, e6}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Rook),   BitBoard({a1, e1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Pawn),   BitBoard({a2, b4, c4, d5, e4, f2, g2, h2}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, King),   BitBoard({g8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Queen),  BitBoard({d8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Bishop), BitBoard({c8, g7}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Knight), BitBoard({e7, f6}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Rook),   BitBoard({a8, f8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Pawn),   BitBoard({a7, b7, c6, d6, e5, f5, g6, h6}));

        f.loadPosition(FENExampleCastlingEnPassantTest);
        ASSERT_EQ(f.extractBitBoard(), BitBoard(exampleCastlingEnPassantTest));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy),         BitBoard({e1, d1, c1, f1, c3, g1, b1, h1, a3, b4, c4, d4, e4, f4, g2, h2}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy),         BitBoard({e8, d8, c8, g7, b8, f6, a8, f8, a7, b7, c7, d6, e7, f7, g4, h7}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, King),   BitBoard({e1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Queen),  BitBoard({d1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Bishop), BitBoard({c1, f1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Knight), BitBoard({c3, g1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Rook),   BitBoard({b1, h1}));
        ASSERT_EQ(f.extractBitBoard(WhiteArmy, Pawn),   BitBoard({a3, b4, c4, d4, e4, f4, g2, h2}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, King),   BitBoard({e8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Queen),  BitBoard({d8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Bishop), BitBoard({c8, g7}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Knight), BitBoard({b8, f6}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Rook),   BitBoard({a8, f8}));
        ASSERT_EQ(f.extractBitBoard(BlackArmy, Pawn),   BitBoard({a7, b7, c7, d6, e7, f7, g4, h7}));
    }

    // --- Equality operator testing ---
    TEST(FENRecordTester,TwoFENRecordsBuiltWithDefaultConstructorAreEqual)
    {
        FENRecord fr1{};
        FENRecord fr2{};
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAreEqual)
    {
        FENRecord fr1{FENEmptyChessBoard};
        FENRecord fr2{FENEmptyChessBoard};
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithDifferentStringAreNotEqual)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENEmptyChessBoard};
        ASSERT_TRUE(fr1 != fr2);
        fr2.loadPosition(FENInitialStandardPosition);
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_FENString)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        fr2.fen = "rnbqkbnr/1ppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        ASSERT_TRUE(fr1 != fr2);
        fr2.fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_PiecePlacementView)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        fr2.pPlacement = "rnbqkbnr/1ppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
        ASSERT_TRUE(fr1 != fr2);
        fr2.pPlacement = std::string_view {fr2.fen.c_str(), fr2.fen.find_first_of(FENDelim)};
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_ActiveArmy)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        fr2.activeArmy = BlackArmy;
        ASSERT_TRUE(fr1 != fr2);
        fr2.activeArmy = WhiteArmy;
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_CastlingAvailability)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        fr2.cstlAvail ^= BitBoard(b1);
        ASSERT_TRUE(fr1 != fr2);
        fr2.cstlAvail ^= BitBoard(b1);
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_EnPassantCell)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        fr2.enPassantCell ^= BitBoard(e3);
        ASSERT_TRUE(fr1 != fr2);
        fr2.enPassantCell = BitBoard(EmptyBB);
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_HalfMoveClock)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        ++(fr2.hmc);
        ASSERT_TRUE(fr1 != fr2);
        --(fr2.hmc);
        ASSERT_TRUE(fr1 == fr2);
        fr2.hmc -= 33;
        ASSERT_TRUE(fr1 != fr2);
        fr2.hmc += 33;
        ASSERT_TRUE(fr1 == fr2);
    }
    TEST(FENRecordTester,TwoFENRecordsBuiltWithTheSameStringAndThenChangedAreNotEqual_FullMove)
    {
        FENRecord fr1{FENInitialStandardPosition};
        FENRecord fr2{FENInitialStandardPosition};
        ASSERT_TRUE(fr1 == fr2);
        ++(fr2.fm);
        ASSERT_TRUE(fr1 != fr2);
        --(fr2.fm);
        ASSERT_TRUE(fr1 == fr2);
        fr2.fm -= 42;
        ASSERT_TRUE(fr1 != fr2);
        fr2.fm += 42;
        ASSERT_TRUE(fr1 == fr2);
    }

} // namespace cSzd
