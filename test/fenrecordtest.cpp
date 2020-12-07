#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "cmdsuzdal/fenrecord.h"

// From Wikipedia (https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation):
// Forsyth–Edwards Notation (FEN) is a standard notation for describing a particular board
// position of a chess game. The purpose of FEN is to provide all the necessary information
// to restart a game from a particular position.
//
// FEN is based on a system developed by Scottish newspaper journalist David Forsyth.
// Forsyth's system became popular in the 19th century; Steven J. Edwards extended it
// to support use by computers. FEN is defined in the "Portable Game Notation
// Specification and Implementation Guide" (see documentation area). In the Portable
// Game Notation for chess games, FEN is used to define initial positions other than
// the standard one.[3] FEN does not provide sufficient information to decide whether
// a draw by threefold repetition may be legally claimed or a draw offer may be
// accepted; for that, a different format such as Extended Position Description is needed.
//
// A FEN "record" defines a particular game position, all in one text line and using
//only the ASCII character set. A text file with only FEN data records should have the
// file extension ".fen".[4]
//
// A FEN record contains six fields. The separator between fields is a space.
// The fields are:
//
// 1. Piece placement (from White's perspective). Each rank is described, starting with
//    rank 8 and ending with rank 1; within each rank, the contents of each square are
//    described from file "a" through file "h". Following the Standard Algebraic
//    Notation (SAN), each piece is identified by a single letter taken from the
//    standard English names (pawn = "P", knight = "N", bishop = "B", rook = "R",
//    queen = "Q" and king = "K"). White pieces are designated using upper-case letters
//    ("PNBRQK") while black pieces use lowercase ("pnbrqk"). Empty squares are noted
//    using digits 1 through 8 (the number of empty squares), and "/" separates ranks.
// 2. Active color. "w" means White moves next, "b" means Black moves next.
// 3. Castling availability. If neither side can castle, this is "-". Otherwise, this
//    has one or more letters: "K" (White can castle kingside), "Q" (White can castle
//    queenside), "k" (Black can castle kingside), and/or "q" (Black can castle
//    queenside). A move that temporarily prevents castling does not negate this
//    notation.
// 4. En passant target square in algebraic notation. If there's no en passant target
//    square, this is "-". If a pawn has just made a two-square move, this is the
//    position "behind" the pawn. This is recorded regardless of whether there is a
//    pawn in position to make an en passant capture.
// 5. Halfmove clock: This is the number of halfmoves since the last capture or pawn
//    advance. The reason for this field is that the value is used in the fifty-move
//    rule.
// 6. Fullmove number: The number of the full move. It starts at 1, and is incremented
//    after Black's move.
//

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

} // namespace cSzd
