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
        //      0 1000000 010100 001100 0110 0110 0101 = 0x4050C665
        ASSERT_EQ(chessMove(Pawn, e2, e3), static_cast<ChessMove>(0x4050C665));
    }
    TEST(ChessMoveTester, PawnE4ToF5WithPawnTakenMove)
    {
        //    - Pawn (5 = 101) from e4 (28 = 011100) to f5 (37 = 100101) with Pawn (5 = 101) taken
        //      0 1000000 100101 011100 0110 0101 0101
        //      0100 0000 1001 0101 1100 0110 0101 0101 = 0x4095C655
        ASSERT_EQ(chessMove(Pawn, e4, f5, Pawn), static_cast<ChessMove>(0x4095C655));
    }
    TEST(ChessMoveTester, KnightD2ToB3WithPawnTakenMove)
    {
        //    - Knight (3 = 011) from d2 (11 = 001011) to b3 (17 = 010001) with Pawn (5 = 101) taken
        //      0 1000000 010001 001011 0110 0101 0011
        //      0100 0000 0100 0100 1011 0110 0101 0011 = 0x4044B653
        ASSERT_EQ(chessMove(Knight, d2, b3, Pawn), static_cast<ChessMove>(0x4044B653));
    }
    TEST(ChessMoveTester, BishopA1ToH8WithQueenTakenMove)
    {
        //    - Bishop (2 = 010) from a1 (0 = 000000) to h8 (63 = 111111) with Queen (1 = 001) taken
        //      0 1000000 111111 000000 0110 0001 0010
        //      0100 0000 1111 1100 0000 0110 0001 0010 = 0x40FC0612
        ASSERT_EQ(chessMove(Bishop, a1, h8, Queen), static_cast<ChessMove>(0x40FC0612));
    }
    TEST(ChessMoveTester, RookG7ToA7WithBishopTakenMove)
    {
        //    - Rook (4 = 100) from g7 (54 = 110110) to a7 (48 = 110000) with Bishop (2 = 010) taken
        //      0 1000000 110000 110110 0110 0010 0100
        //      0100 0000 1100 0011 0110 0110 0010 0100 = 0x40C36624
        ASSERT_EQ(chessMove(Rook, g7, a7, Bishop), static_cast<ChessMove>(0x40C36624));
    }
    TEST(ChessMoveTester, QueenE1ToE8WithQueenTakenMove)
    {
        //    - Queen (1 = 001) from e1 (4 = 000100) to e8 (60 = 111100) with Queen (1 = 001) taken
        //      0 1000000 111100 000100 0110 0001 0001
        //      0100 0000 1111 0000 0100 0110 0001 0001 = 0x40F04611
        ASSERT_EQ(chessMove(Queen, e1, e8, Queen), static_cast<ChessMove>(0x40F04611));
    }
    TEST(ChessMoveTester, KingD3ToE4WithPawnTakenMove)
    {
        //    - King (0 = 000) from d3 (19 = 010011) to e4 (28 = 011100) with Pawn (5 = 101) taken
        //      0 1000000 011100 010011 0110 0101 0000
        //      0100 0000 0111 0001 0011 0110 0101 0000 = 0x40713650
        ASSERT_EQ(chessMove(King, d3, e4, Pawn), static_cast<ChessMove>(0x40713650));
    }

    // Promotions testing
    TEST(ChessMoveTester, PawnFromB7ToB8WithPromotionToQueen)
    {
        // Pawn (5 = 101) from b7 (49 = 110001) to b8 (57 = 111001) with no piece taken and promotion to Queen (1 = 001)
        //      0 1000000 111001 110001 0001 0110 0101
        //      0100 0000 1110 0111 0001 0001 0110 0101 = 0x40E71165
        ASSERT_EQ(chessMove(Pawn, b7, b8, InvalidPiece, Queen), static_cast<ChessMove>(0x40E71165));
    }
    TEST(ChessMoveTester, PawnFromG2ToH1WithRookTakenAndPromotionToKnight)
    {
        // Pawn (5 = 101) from g2 (14 = 001110) to h1 (7 = 000111) with Rook (4 = 0100) taken and promotion to Knigh (3 = 011)
        //      0 1000000 000111 001110 0011 0100 0101
        //      0100 0000 0001 1100 1110 0011 0100 0101 = 0x401CE345
        ASSERT_EQ(chessMove(Pawn, g2, h1, Rook, Knight), static_cast<ChessMove>(0x401CE345));
    }
}
