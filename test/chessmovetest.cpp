#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/chessmove.h"

using namespace std;
using namespace testing;

namespace cSzd
{
    TEST(ChessMoveTester, PawnE2ToE3Move)
    {
        //    - Pawn (5 = 101) e2 (12 = 001100) to e3 (20 010100)
        //      0 1000000 010100 001100 000 110 110 101
        //      0100 0000 0101 0000 1100 0001 1011 0101 = 0x4050C1B5
        ASSERT_EQ(chessMove(Pawn, e2, e3), static_cast<ChessMove>(0x4050C1B5));
    }
    TEST(ChessMoveTester, PawnE4ToF5WithPawnTakenMove)
    {
        //    - Pawn (5 = 101) from e4 (28 = 011100) to f5 (37 = 100101) with Pawn (5 = 101) taken
        //      0 1000000 100101 011100 000 110 101 101
        //      0100 0000 1001 0101 1100 0001 1010 1101 = 0x4095 C1AD
        ASSERT_EQ(chessMove(Pawn, e4, f5, Pawn), static_cast<ChessMove>(0x4095C1AD));
    }
    TEST(ChessMoveTester, KnightD2ToB3WithPawnTakenMove)
    {
        //    - Knight (3 = 011) from d2 (11 = 001011) to b3 (17 = 010001) with Pawn (5 = 101) taken
        //      0 1000000 010001 001011 000 110 101 011
        //      0100 0000 0100 0100 1011 0001 1010 1011 = 0x4044B1AB
        ASSERT_EQ(chessMove(Knight, d2, b3, Pawn), static_cast<ChessMove>(0x4044B1AB));
    }
    TEST(ChessMoveTester, BishopA1ToH8WithQueenTakenMove)
    {
        //    - Bishop (2 = 010) from a1 (0 = 000000) to h8 (63 = 111111) with Queen (1 = 001) taken
        //      0 1000000 111111 000000 000 110 001 010
        //      0100 0000 1111 1100 0000 0001 1000 1010 = 0x40FC018A
        ASSERT_EQ(chessMove(Bishop, a1, h8, Queen), static_cast<ChessMove>(0x40FC018A));
    }
    TEST(ChessMoveTester, RookG7ToA7WithBishopTakenMove)
    {
        //    - Rook (4 = 100) from g7 (54 = 110110) to a7 (48 = 110000) with Bishop (2 = 010) taken
        //      0 1000000 110000 110110 000 110 010 100
        //      0100 0000 1100 0011 0110 0001 1001 0100 = 0x40C36194
        ASSERT_EQ(chessMove(Rook, g7, a7, Bishop), static_cast<ChessMove>(0x40C36194));
    }
    TEST(ChessMoveTester, QueenE1ToE8WithQueenTakenMove)
    {
        //    - Queen (1 = 001) from e1 (4 = 000100) to e8 (60 = 111100) with Queen (1 = 001) taken
        //      0 1000000 111100 000100 000 110 001 001
        //      0100 0000 1111 0000 0100 0001 1000 1001 = 0x40F04189
        ASSERT_EQ(chessMove(Queen, e1, e8, Queen), static_cast<ChessMove>(0x40F04189));
    }
    TEST(ChessMoveTester, KingD3ToE4WithPawnTakenMove)
    {
        //    - King (0 = 000) from d3 (19 = 010011) to e4 (28 = 011100) with Pawn (5 = 101) taken
        //      0 1000000 011100 010011 000 110 101 000
        //      0100 0000 0111 0001 0011 0001 1010 1000 = 0x407131A8
        ASSERT_EQ(chessMove(King, d3, e4, Pawn), static_cast<ChessMove>(0x407131A8));
    }

    // Promotions testing
    TEST(ChessMoveTester, PawnFromB7ToB8WithPromotionToQueen)
    {
        // Pawn (5 = 101) from b7 (49 = 110001) to b8 (57 = 111001) with no piece taken and promotion to Queen (1 = 001)
        //      0 1000000 111001 110001 000 001 110 101
        //      0100 0000 1110 0111 0001 0000 0111 0101 = 0x40E71075
        ASSERT_EQ(chessMove(Pawn, b7, b8, InvalidPiece, Queen), static_cast<ChessMove>(0x40E71075));
    }
    TEST(ChessMoveTester, PawnFromG2ToH1WithRookTakenAndPromotionToKnight)
    {
        // Pawn (5 = 101) from g2 (14 = 001110) to h1 (7 = 000111) with Rook (4 = 0100) taken and promotion to Knigh (3 = 011)
        //      0 1000000 000111 001110 000 011 100 101
        //      0100 0000 0001 1100 1110 0000 1110 0101 = 0x401CE0E5
        ASSERT_EQ(chessMove(Pawn, g2, h1, Rook, Knight), static_cast<ChessMove>(0x401CE0E5));
    }

    // En-passant testing
    TEST(ChessMoveTester, PawnFromC2ToC4WithImplicitEnPassantInC3)
    {
        // Pawn (5 = 101) from c2 (10 = 001010) to c4 (26 = 011010) with en passant in c3 (18 = 010010)
        //      0 0010010 011010 001010 000 110 110 101
        //      0001 0010 0110 1000 1010 0001 1011 0101 = 0x1268A1B5
        ASSERT_EQ(chessMove(Pawn, c2, c4), static_cast<ChessMove>(0x1268A1B5));
    }
    TEST(ChessMoveTester, PawnFromD7ToD5WithImplicitEnPassantInD6)
    {
        // Pawn (5 = 101) from d7 (51 = 110011) to d5 (35 = 100011) with en passant in d6 (43 = 101011)
        //      0 0101011 100011 110011 000 110 110 101
        //      0010 1011 1000 1111 0011 0001 1011 0101 = 0x2B8F31B5
        ASSERT_EQ(chessMove(Pawn, d7, d5), static_cast<ChessMove>(0x2B8F31B5));
    }
    TEST(ChessMoveTester, QueenFromE2ToE4DoesNotGenerateEnPassantInE3)
    {
        // Queen (1 = 001) from e2 (12 = 001100) to e4 (28 = 011100) does not generate en passant
        //      0 1000000 011100 001100 000 110 110 001
        //      0100 0000 0111 0000 1100 0001 1011 0001 = 0x4070C1B1
        ASSERT_EQ(chessMove(Queen, e2, e4), static_cast<ChessMove>(0x4070C1B1));
    }
    TEST(ChessMoveTester, RookFromD7ToD5DoesNotGenerateEnPassantInD6)
    {
        // Rook (4 = 100) from d7 (51 = 110011) to d5 (35 = 100011) does not generate en passant
        //      0 1000000 100011 110011 000 110 110 100
        //      0100 0000 1000 1111 0011 0001 1011 0100 = 0x408F31B4
        ASSERT_EQ(chessMove(Rook, d7, d5), static_cast<ChessMove>(0x408F31B4));
    }

    // --- Get sub-elements helpers method testing
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_PawnE2toE4)
    {
        ChessMove cm = chessMove(Pawn, e2, e4);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Pawn);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), e2);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), e4);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), e3);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_PawnB4toC5TakingAKnight)
    {
        ChessMove cm = chessMove(Pawn, b4, c5, Knight);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Pawn);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), Knight);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), b4);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), c5);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_PawnF7toF8PromotingToQueen)
    {
        ChessMove cm = chessMove(Pawn, f7, f8, InvalidPiece, Queen);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Pawn);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), Queen);
        ASSERT_EQ(chessMoveGetStartingCell(cm), f7);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), f8);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_PawnB2toC1TakingABishopPromotingToKnight)
    {
        ChessMove cm = chessMove(Pawn, b2, c1, Bishop, Knight);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Pawn);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), Bishop);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), Knight);
        ASSERT_EQ(chessMoveGetStartingCell(cm), b2);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), c1);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_RookG3toB3)
    {
        ChessMove cm = chessMove(Rook, g3, b3);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Rook);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), g3);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), b3);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_KnightE4toC5TakingPawn)
    {
        ChessMove cm = chessMove(Knight, e4, c5, Pawn);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Knight);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), Pawn);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), e4);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), c5);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_BishopA3toF8TakingQueen)
    {
        ChessMove cm = chessMove(Bishop, a3, f8, Queen);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Bishop);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), Queen);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), a3);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), f8);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_QueenA6toE2)
    {
        ChessMove cm = chessMove(Queen, a6, e2);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), Queen);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), a6);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), e2);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }
    TEST(ChessMoveTester, TestThatTheGetElementHelpersWorksGood_KingD5toE4TakingRook)
    {
        ChessMove cm = chessMove(King, d5, e4, Rook);
        ASSERT_EQ(chessMoveGetMovedPiece(cm), King);
        ASSERT_EQ(chessMoveGetTakenPiece(cm), Rook);
        ASSERT_EQ(chessMoveGetPromotedPiece(cm), InvalidPiece);
        ASSERT_EQ(chessMoveGetStartingCell(cm), d5);
        ASSERT_EQ(chessMoveGetDestinationCell(cm), e4);
        ASSERT_EQ(chessMoveGetEnPassantCell(cm), InvalidCell);
    }

    // --- isACastlingMove() method testing ---
    TEST(ChessMoveTester, White_00_IsACastlingMove)
    {
        ChessMove cm = chessMove(King, e1, g1);
        ASSERT_TRUE(isACastlingMove(cm));
    }
    TEST(ChessMoveTester, White_000_IsACastlingMove)
    {
        ChessMove cm = chessMove(King, e1, c1);
        ASSERT_TRUE(isACastlingMove(cm));
    }
    TEST(ChessMoveTester, Black_00_IsACastlingMove)
    {
        ChessMove cm = chessMove(King, e8, g8);
        ASSERT_TRUE(isACastlingMove(cm));
    }
    TEST(ChessMoveTester, Black_000_IsACastlingMove)
    {
        ChessMove cm = chessMove(King, e8, c8);
        ASSERT_TRUE(isACastlingMove(cm));
    }
    TEST(ChessMoveTester, CheckThatOtherKingMovesAreNotCastlingMove)
    {
        ChessMove cm = chessMove(King, e1, f1);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, e1, d1);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, e8, e7);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, e8, d7);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, f5, f4);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, c3, d4);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(King, g7, h8);
        ASSERT_FALSE(isACastlingMove(cm));
    }
    TEST(ChessMoveTester, CheckThatOtherPiecesMovesAreNotCastlingMove)
    {
        ChessMove cm = chessMove(Rook, h1, f1);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Rook, a1, d1);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Rook, a8, d8);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Rook, a8, f8);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Knight, d3, e5, Pawn);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Bishop, f6, a1, Rook);
        ASSERT_FALSE(isACastlingMove(cm));
        cm = chessMove(Bishop, f6, a1, Rook);
        ASSERT_FALSE(isACastlingMove(cm));
    }
}
