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
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cb.sideToMove, WhiteArmy);
        ASSERT_EQ(cb.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cb.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb.halfMoveClock, 0);
        ASSERT_EQ(cb.fullMoves, 1);
    }

    TEST(ChessBoardTester, WholeWhiteArmyAtInitialStandardPositionOccupy1stAnd2ndRank)
    {
        ChessBoard cb {};
        ASSERT_EQ(cb.wholeArmyBitBoard(WhiteArmy), BitBoard(RanksBB[r_1] | RanksBB[r_2]));
        ASSERT_EQ(cb.wholeArmyBitBoard(BlackArmy), BitBoard(RanksBB[r_7] | RanksBB[r_8]));
        ASSERT_EQ(cb.wholeArmyBitBoard(), BitBoard(RanksBB[r_1] | RanksBB[r_2] |
                                                    RanksBB[r_7] | RanksBB[r_8]));
    }
    TEST(ChessBoardTester, CheckWholeArmyBitBoardForInvalidParameter)
    {
        ChessBoard cb {};
        ASSERT_EQ(cb.wholeArmyBitBoard(static_cast<ArmyColor>(3)), BitBoard(EmptyBB));
    }


    // Test on acquisition of position from a FEN Record
    // 1. Initial standard position
    TEST(ChessBoardTester, FENLoad_InitialStandardPosition)
    {
        ChessBoard cb {FENRecord(FENInitialStandardPosition)};
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
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
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[King],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Queen],  BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Rook],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[WhiteArmy].pieces[Pawn],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[King],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Queen],  BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Rook],   BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(cb.armies[BlackArmy].pieces[Pawn],   BitBoard(EmptyBB));
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

    // If pawns (of any color) in 1st or 8th rank, position is not valid
    TEST(ChessBoardTester, IfPawnsIn1stOr8thRankPositionIsNotValid)
    {
        ChessBoard cb { "p3k3/8/8/8/8/8/8/4K3 w - - 0 1" };
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("4k3/8/8/8/8/8/8/2p1K3 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("PP2kPPP/8/8/8/8/8/8/4K3 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("4k3/8/8/8/8/8/8/2PPK2P w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("PpPpPpPp/4k3/8/8/8/8/4K3/pPpPpPpP w - - 0 1");
        ASSERT_FALSE(cb.isValid());
    }

    // No more than 16 pieces (including pawns) per army can be on
    // the board. This rule take into account promotions.
    // Examples of other rules that shall be honored to have a
    // valid position (unfortunately not exaustive):
    // Num(pieces) <= 16
    // Num(Pawns) + Num(Queens) <= 9
    // Num(Pawns) + Num(Rooks) <= 10
    // Num(Pawns) + Num(Knights) <= 10
    // Num(Pawns) + Num(Bishops) <= 10
    // (is in any case really strange that a player promotes to
    // something different from a Queen and a Knight)
    // Additionally there are position that are impossible for
    // other reasons
    TEST(ChessBoardTester, InvalidPositionsDueToNumberOfPieces)
    {
        // too many white pieces (one additional pawn)
        ChessBoard cb {"rnbqkbnr/pppppppp/8/3P4/8/8/PPPPPPPP/RNBQKBNR w kq - 0 1"};
        ASSERT_FALSE(cb.isValid());
        // too many black pieces (three additional pawn)
        cb.loadPosition("rnbqkbnr/pppppppp/8/3ppp2/8/8/PPPPPPPP/RNBQKBNR w kq - 0 1");
        ASSERT_FALSE(cb.isValid());
    }

    // En passant check: a cell can be marked as an en passant target only if:
    //   - it is in the 3rd rank for white or in the 6th for black
    //   - if it is in the 3rd rank, the side to move shall be black
    //   - if it is in the 6th rank, the side to move shall be the white
    //   - if it is in the 3rd rank (file "x") the cell "x4" shall be
    //     occupied by a white pawn and the cell x2 shall be empty
    //   - if it is in the 6th rank (file "x") the cell "x5" shall be
    //     occupied by a black pawn and the cell x7 shall be empty
    //   - Additionally, Only one cell can be marked as en passant target
    TEST(ChessBoardTester, EnPassantMoveCanOnlyBeOn3rdOr6thRanks)
    {
        // initial position after e2-e4 has an e.p. target square in e3
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"};
        ASSERT_TRUE(cb.isValid());
        // sicilian defense: after first black move (c7-c5) e.p.t.s. is c6
        cb.loadPosition("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 1");
        ASSERT_TRUE(cb.isValid());

        // initial position with incorrectly placed en passant cell
        cb.loadPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e5 0 1");
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq d3 0 1");
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, IfEnPassantCellIsIn3rdRankActiveSideCannotBeTheWhite)
    {
        // initial position after e2-e4 has an e.p. target square in e3
        // but active side shall be black
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e3 0 1"};
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, IfEnPassantCellIsIn6thRankActiveSideCannotBeTheBlack)
    {
        // sicilian defense: after first black move (c7-c5) e.p.t.s. is c6
        // but active side shall be white
        ChessBoard cb {"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR b KQkq c6 0 1"};
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, EnPassantCellsCannotBeMoreThanOne)
    {
        // initial position after e2-e4 has an e.p. target square in e3
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"};
        ASSERT_TRUE(cb.isValid());
        // force an additional en passant square
        cb.enPassantTargetSquare.setCell(d3);
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, EnPassantBackCellShallBeEmpty)
    {
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/4P3/8/PPP1PPPP/RNBQKBNR b KQkq e3 0 1"};
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("rnbqkbnr/ppp1pppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 1");
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, EnPassantFrontCellShallBeOccupiedByAPawn)
    {
        ChessBoard cb {"rnbqkbnr/pppppppp/8/8/4N3/8/PPPPPPPP/R1BQKBNR b KQkq e3 0 1"};
        ASSERT_FALSE(cb.isValid());
        cb.loadPosition("rnbqkbnr/pp1ppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 1");
        ASSERT_FALSE(cb.isValid());

    }

    // ------------------------------------------------------------------------
    // Controlled Cells Tests
    TEST(ChessBoardTester, ChecksCellsControlledByWhiteKingInE5AndBlackKingInG7)
    {
        ChessBoard cb {"8/6k1/8/4K3/8/8/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({d4, e4, f4, d5, f5, d6, e6, f6}));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({f6, g6, h6, f7, h7, f8, g8, h8}));
    }
    TEST(ChessBoardTester, ChecksCellsControlledByWhiteKingInA1AndBlackKingInH8)
    {
        ChessBoard cb {"7k/8/8/8/8/8/8/K7 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({b1, a2, b2}));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({g7, h7, g8}));
    }

    TEST(ChessBoardTester, ComplexCaseControlledCells1)
    {
        // https://lichess.org/6ysOUWrw#31
        ChessBoard cb {"1k2r2r/1p1qbpp1/1B1pbn1p/1Pp1p3/Q1P5/3P1NP1/4PPBP/R4RK1 b - - 4 16"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({
            a8,         d8,
            a7,     c7,
            a6,     c6,
            a5, b5, c5, d5, e5,     g5,
            a4, b4, c4, d4, e4, f4,     h4,
            a3, b3,     d3, e3, f3, g3, h3,
            a2,     c2, d2,     f2, g2, h2,
            a1, b1, c1, d1, e1, f1, g1, h1
        }));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({
            a8, b8, c8, d8, e8, f8, g8, h8,
            a7, b7, c7, d7, e7, f7,     h7,
            a6, c6, c6, d6, e6, f6, g6, h6,
                b5, c5, d5, e5, f5, g5, h5,
                b4, c4, d4, e4, f4, g4,
                                        h3
        }));
    }

    TEST(ChessBoardTester, ComplexCaseControlledCells2)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb {"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({
            a7,     c7,                 h7,
                        d6,         g6,
                b5,             f5,
                    c4, d4, e4, f4,
            a3, b3, c3, d3,     f3, g3, h3,
                    c2, d2, e2, f2, g2, h2,
            a1, b1, c1,     e1, f1, g1, h1
        }));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({
            a8, b8, c8,     e8, f8, g8, h8,
                        d7,     f7, g7, h7,
            a6, b6, c6, d6, e6, f6, g6, h6,
                        d5, e5,
                        d4, e4,     g4,
                        d3, e3,         h3,
                                f2,     h2,
                        d1,             h1
        }));
    }

    // ----- Army in check Tests ------------------------------------
    TEST(ChessBoardTester, InInitialPositionTheKingsAreNotInCheck)
    {
        ChessBoard cb {};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
    }
    TEST(ChessBoardTester, BlackKingInCheckSimpleCase)
    {
        ChessBoard cb {"8/8/8/3Q4/2k1K3/8/8/8 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
    }
    TEST(ChessBoardTester, WhiteKingInCheckSimpleCase)
    {
        ChessBoard cb {"8/7b/1k6/8/4K3/8/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
    }
    TEST(ChessBoardTester, IfBothKingsAreInCheckArmyInCheckReturnsInvalidArmy)
    {
        ChessBoard cb {"8/7b/1k6/8/4K3/8/8/1R6 w - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
    }
    TEST(ChessBoardTester, IfBothKingsAreInCheckPositionIsNotValid)
    {
        ChessBoard cb {"8/7b/1k6/8/4K3/8/8/1R6 w - - 0 1"};
        ASSERT_FALSE(cb.isValid());
    }

    // ----- Additional validity consideration if a king is in check ---
    // If a king of an army is in check and move is assigned to other
    // army, position is not valid
    TEST(ChessBoardTester, IfWhiteKingInCheckAndMoveToBlackPositionIsNotValid)
    {

        ChessBoard cb {"8/7b/1k6/8/4K3/8/8/8 b - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_EQ(cb.sideToMove, BlackArmy);
        ASSERT_FALSE(cb.isValid());
    }
    TEST(ChessBoardTester, IfBlackKingInCheckAndMoveToWhitePositionIsNotValid)
    {

        ChessBoard cb {"8/8/8/3Q4/2k1K3/8/8/8 w - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
        ASSERT_EQ(cb.sideToMove, WhiteArmy);
        ASSERT_FALSE(cb.isValid());
    }

    // ---------------- generateLegalMoves() testing -------------------------
    // --- generateKingLegalMoves() method Testing
    TEST(ChessBoardTester, CheckLegalMovesOfKingsInE5AndA1WithNoInterference)
    {
        ChessBoard cb {"8/8/8/4k3/8/8/8/K7 b - - 0 1"};

        std::vector<ChessMove> blackKingMoves;
        cb.generateKingLegalMoves(blackKingMoves);
        ASSERT_EQ(blackKingMoves.size(), 8);
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, d4)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, e4)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, f4)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, d5)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, f5)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, d6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, e6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, e5, f6)) != blackKingMoves.end());

        cb.loadPosition("8/8/8/4k3/8/8/8/K7 w - - 0 1");
        std::vector<ChessMove> whiteKingMoves;
        cb.generateKingLegalMoves(whiteKingMoves);
        ASSERT_EQ(whiteKingMoves.size(), 3);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, b1)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, a2)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, b2)) != whiteKingMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfKingsInB4AndD5WithSomeInterferenceAndCaptures)
    {
        ChessBoard cb {"8/8/4N3/1p1k4/1K6/7r/1Q6/8 w - - 0 1"};

        std::vector<ChessMove> whiteKingMoves;
        cb.generateKingLegalMoves(whiteKingMoves);
        ASSERT_EQ(whiteKingMoves.size(), 2);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, b4, a5)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, b4, b5, Pawn)) != whiteKingMoves.end());

        cb.loadPosition("8/8/4N3/1p1k4/1K6/7r/1Q6/8 b - - 0 1");
        std::vector<ChessMove> blackKingMoves;
        cb.generateKingLegalMoves(blackKingMoves);
        ASSERT_EQ(blackKingMoves.size(), 4);
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, c6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, d6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, e6, Knight)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, e4)) != blackKingMoves.end());
    }

} // namespace cSzd
