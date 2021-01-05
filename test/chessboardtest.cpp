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
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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

    // Copy Constructor
    TEST(ChessBoardTester, CheckCopyConstructorOfStandardInitialPosition)
    {
        ChessBoard cb {};
        ChessBoard cb2 = cb;
        cb.loadPosition("8/8/8/8/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        ASSERT_TRUE(cb2.isValid());
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cb2.sideToMove, WhiteArmy);
        ASSERT_EQ(cb2.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cb2.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb2.halfMoveClock, 0);
        ASSERT_EQ(cb2.fullMoves, 1);
        ASSERT_EQ(cb2.wholeArmyBitBoard(WhiteArmy), BitBoard(RanksBB[r_1] | RanksBB[r_2]));
        ASSERT_EQ(cb2.wholeArmyBitBoard(BlackArmy), BitBoard(RanksBB[r_7] | RanksBB[r_8]));
        ASSERT_EQ(cb2.wholeArmyBitBoard(), BitBoard(RanksBB[r_1] | RanksBB[r_2] |
                                                    RanksBB[r_7] | RanksBB[r_8]));
    }

    // Assignment Operator
    TEST(ChessBoardTester, CheckAssignmentOperatorOfStandardInitialPosition)
    {
        ChessBoard cb {};
        ChessBoard cb2{"8/8/8/8/8/8/8/8 w - - 0 1"};

        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb2.isValid());

        cb2 = cb;

        cb.loadPosition("8/8/8/8/8/8/8/8 w - - 0 1");
        ASSERT_FALSE(cb.isValid());
        ASSERT_TRUE(cb2.isValid());
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[King], BitBoard({e1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Queen], BitBoard({d1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(cb2.armies[WhiteArmy].pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[King], BitBoard({e8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Queen], BitBoard({d8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(cb2.armies[BlackArmy].pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(cb2.sideToMove, WhiteArmy);
        ASSERT_EQ(cb2.castlingAvailability, BitBoard({b1, g1, b8, g8}));
        ASSERT_EQ(cb2.enPassantTargetSquare, BitBoard(EmptyBB));
        ASSERT_EQ(cb2.halfMoveClock, 0);
        ASSERT_EQ(cb2.fullMoves, 1);
        ASSERT_EQ(cb2.wholeArmyBitBoard(WhiteArmy), BitBoard(RanksBB[r_1] | RanksBB[r_2]));
        ASSERT_EQ(cb2.wholeArmyBitBoard(BlackArmy), BitBoard(RanksBB[r_7] | RanksBB[r_8]));
        ASSERT_EQ(cb2.wholeArmyBitBoard(), BitBoard(RanksBB[r_1] | RanksBB[r_2] |
                                                    RanksBB[r_7] | RanksBB[r_8]));
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
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
        // sicilian defense: after first black move (c7-c5) e.p.t.s. is c6
        cb.loadPosition("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        // initial position with incorrectly placed en passant cell
        cb.loadPosition("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq e5 0 1");
        ASSERT_FALSE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
        cb.loadPosition("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq d3 0 1");
        ASSERT_FALSE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({d4, e4, f4, d5, f5, d6, e6, f6}));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({f6, g6, h6, f7, h7, f8, g8, h8}));
    }
    TEST(ChessBoardTester, ChecksCellsControlledByWhiteKingInA1AndBlackKingInH8)
    {
        ChessBoard cb {"7k/8/8/8/8/8/8/K7 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
        ASSERT_EQ(cb.controlledCells(WhiteArmy), BitBoard({b1, a2, b2}));
        ASSERT_EQ(cb.controlledCells(BlackArmy), BitBoard({g7, h7, g8}));
    }

    TEST(ChessBoardTester, ComplexCaseControlledCells1)
    {
        // https://lichess.org/6ysOUWrw#31
        ChessBoard cb {"1k2r2r/1p1qbpp1/1B1pbn1p/1Pp1p3/Q1P5/3P1NP1/4PPBP/R4RK1 b - - 4 16"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessBoardTester, BlackKingInCheckSimpleCase)
    {
        ChessBoard cb {"8/8/8/3Q4/2k1K3/8/8/8 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessBoardTester, WhiteKingInCheckSimpleCase)
    {
        ChessBoard cb {"8/7b/1k6/8/4K3/8/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());
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

    // --- KING ---
    TEST(ChessBoardTester, CheckLegalMovesOfKingsInE5AndA1WithNoInterference)
    {
        ChessBoard cb {"8/8/8/4k3/8/8/8/K7 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackKingMoves;
        cb.generateLegalMoves(blackKingMoves, King);
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
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteKingMoves;
        cb.generateLegalMoves(whiteKingMoves, King);
        ASSERT_EQ(whiteKingMoves.size(), 3);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, b1)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, a2)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, a1, b2)) != whiteKingMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfKingsInB4AndD5WithSomeInterferenceAndCaptures)
    {
        ChessBoard cb {"8/8/4N3/1p1k4/1K6/7r/1Q6/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteKingMoves;
        cb.generateLegalMoves(whiteKingMoves, King);
        ASSERT_EQ(whiteKingMoves.size(), 2);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, b4, a5)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, b4, b5, Pawn)) != whiteKingMoves.end());

        cb.loadPosition("8/8/4N3/1p1k4/1K6/7r/1Q6/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackKingMoves;
        cb.generateLegalMoves(blackKingMoves, King);
        ASSERT_EQ(blackKingMoves.size(), 4);
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, c6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, d6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, e6, Knight)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, d5, e4)) != blackKingMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfKingsInOpposition)
    {
        // https://lichess.org/editor/8/8/8/2k5/8/2K5/8/8_w_-_-_0_1
        ChessBoard cb {"8/8/8/2k5/8/2K5/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteKingMoves;
        cb.generateLegalMoves(whiteKingMoves, King);
        ASSERT_EQ(whiteKingMoves.size(), 5);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, c3, b2)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, c3, c2)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, c3, d2)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, c3, b3)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, c3, d3)) != whiteKingMoves.end());

        cb.loadPosition("8/8/8/2k5/8/2K5/8/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackKingMoves;
        cb.generateLegalMoves(blackKingMoves, King);
        ASSERT_EQ(blackKingMoves.size(), 5);
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c5, b5)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c5, d5)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c5, b6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c5, c6)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c5, d5)) != blackKingMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfKingsInDiagonalOppositionWithCaptures)
    {
        // https://lichess.org/editor/8/1R1N4/1BkP4/1NP1pn2/3pKb2/3n1r2/8/8_w_-_-_0_1
        ChessBoard cb {"8/1R1N4/1BkP4/1NP1pn2/3pKb2/3n1r2/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteKingMoves;
        cb.generateLegalMoves(whiteKingMoves, King);
        ASSERT_EQ(whiteKingMoves.size(), 2);
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, e4, f5, Knight)) != whiteKingMoves.end());
        ASSERT_TRUE(std::find(whiteKingMoves.begin(), whiteKingMoves.end(), chessMove(King, e4, f3, Rook)) != whiteKingMoves.end());

        cb.loadPosition("8/1R1N4/1BkP4/1NP1pn2/3pKb2/3n1r2/8/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackKingMoves;
        cb.generateLegalMoves(blackKingMoves, King);
        ASSERT_EQ(blackKingMoves.size(), 2);
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c6, b7, Rook)) != blackKingMoves.end());
        ASSERT_TRUE(std::find(blackKingMoves.begin(), blackKingMoves.end(), chessMove(King, c6, b5, Knight)) != blackKingMoves.end());
    }

    // --- KNIGHTS ---
    TEST(ChessBoardTester, CheckLegalMovesOfKnightsInC6AndF3WithNoInterference)
    {
        // https://lichess.org/editor/7k/8/2N5/8/8/5n2/8/K7_w_-_-_0_1
        ChessBoard cb {"7k/8/2N5/8/8/5n2/8/K7 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Knight);
        ASSERT_EQ(whiteMoves.size(), 8);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, b8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, d8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, e7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, e5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, d4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, a5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c6, a7)) != whiteMoves.end());

        cb.loadPosition("7k/8/2N5/8/8/5n2/8/K7 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Knight);
        ASSERT_EQ(blackMoves.size(), 8);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, e5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, g5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, h4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, h2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, g1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, e1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, d2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, f3, d4)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfWhiteKnightAndKingThatHasToRemoveCheckCondition)
    {
        // https://lichess.org/editor/7k/8/8/2N5/8/1n6/8/K7_w_-_-_0_1
        ChessBoard cb {"7k/8/8/2N5/8/1n6/8/K7 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, c5, b3, Knight)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, a1, b1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, a1, a2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, a1, b2)) != whiteMoves.end());
    }

    // --- BISHOPS ---
    TEST(ChessBoardTester, CheckLegalMovesOfBishopsSimpleCase)
    {
        // https://lichess.org/editor/8/4k3/8/4bb2/K1B5/8/3B4/8_w_-_-_0_1
        ChessBoard cb {"8/4k3/8/4bb2/K1B5/8/3B4/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Bishop);
        ASSERT_EQ(whiteMoves.size(), 20);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, a2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, b3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, d5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, f7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, g8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, f1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, e2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, d3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, b5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, c4, a6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, c1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, e3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, g5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, h6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, e1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, c3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, d2, a5)) != whiteMoves.end());

        cb.loadPosition("8/4k3/8/4bb2/K1B5/8/3B4/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Bishop);
        ASSERT_EQ(blackMoves.size(), 24);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, a1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, b2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, c3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, d4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, g7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, h8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, h2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, g3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, f4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, d6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, c7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e5, b8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, b1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, c2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, d3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, e4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, g6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, h7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, h3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, g4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, e6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, d7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f5, c8)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfBishopsComplexCase)
    {
        // https://lichess.org/editor/4b3/4k3/5b2/1B5N/K6B/8/5r2/8_w_-_-_0_1
        ChessBoard cb {"4b3/4k3/5b2/1B5N/K6B/8/5r2/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Bishop);
        ASSERT_EQ(whiteMoves.size(), 7);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, b5, c6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, b5, d7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, b5, e8, Bishop)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, h4, g5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, h4, f6, Bishop)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, h4, f2, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Bishop, h4, g3)) != whiteMoves.end());

        cb.loadPosition("4b3/4k3/5b2/1B5N/K6B/8/5r2/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Bishop);
        ASSERT_EQ(blackMoves.size(), 8);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, b5, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, c6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, d7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, f7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, g6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e8, h5, Knight)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f6, g5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, f6, h4, Bishop)) != blackMoves.end());
    }

    // --- ROOKS ---
    TEST(ChessBoardTester, CheckLegalMovesOfRooksSimpleCase)
    {
        // https://lichess.org/editor/8/5r2/6k1/1K6/2R5/8/8/8_w_-_-_0_1
        ChessBoard cb {"8/5r2/6k1/1K6/2R5/8/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Rook);
        ASSERT_EQ(whiteMoves.size(), 14);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, a4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, d4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, e4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, g4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, h4)) != whiteMoves.end());

        cb.loadPosition("8/5r2/6k1/1K6/2R5/8/8/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Rook);
        ASSERT_EQ(blackMoves.size(), 14);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, f8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, a7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, b7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, c7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, d7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, e7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, g7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, f7, h7)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfRooksComplexCase)
    {
        // https://lichess.org/editor/8/6p1/1kr3R1/8/2R3r1/2K3P1/8/8_w_-_-_0_1
        ChessBoard cb {"8/6p1/1kr3R1/8/2R3r1/2K3P1/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Rook);
        ASSERT_EQ(whiteMoves.size(), 10);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, c4, c6, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, h6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, f6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, d6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, c6, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, g5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, g4, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Rook, g6, g7, Pawn)) != whiteMoves.end());

        cb.loadPosition("8/6p1/1kr3R1/8/2R3r1/2K3P1/8/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Rook);
        ASSERT_EQ(blackMoves.size(), 12);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, c6, d6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, c6, e6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, c6, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, c6, g6, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, g3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, g5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, g6, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, h4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, f4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, e4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, d4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, g4, c4, Rook)) != blackMoves.end());
    }

    // --- QUEENS ---
    TEST(ChessBoardTester, CheckLegalMovesOfQueensSimpleCase)
    {
        // https://lichess.org/editor/8/k7/8/8/4Q3/2q5/7K/8_w_-_-_0_1
        ChessBoard cb {"8/k7/8/8/4Q3/2q5/7K/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Queen);
        ASSERT_EQ(whiteMoves.size(), 27);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, e8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, a4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, c4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, d4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, g4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, h4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, b1)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, c2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, d3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, f5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, g6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, h7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, a8)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, b7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, c6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, d5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, f3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, g2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, e4, h1)) != whiteMoves.end());

        cb.loadPosition("8/k7/8/8/4Q3/2q5/7K/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Queen);
        ASSERT_EQ(blackMoves.size(), 25);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, c8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, a3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, b3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, d3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, e3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, f3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, g3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, h3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, a1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, b2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, d4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, e5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, g7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, h8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, e1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, d2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, b4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c3, a5)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfQueensComplexCase)
    {
        // https://lichess.org/editor/k7/1q2p3/8/8/8/6R1/1r3PQ1/7K_w_-_-_0_1
        ChessBoard cb {"k7/1q2p3/8/8/8/6R1/1r3PQ1/7K w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Queen);
        ASSERT_EQ(whiteMoves.size(), 5);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, g2, f3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, g2, e4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, g2, d5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, g2, c6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Queen, g2, b7, Queen)) != whiteMoves.end());

        cb.loadPosition("k7/1q2p3/8/8/8/6R1/1r3PQ1/7K b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Queen);
        ASSERT_EQ(blackMoves.size(), 5);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, b7, c6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, b7, d5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, b7, e4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, b7, f3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, b7, g2, Queen)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfBlackWithTwoOppositeQueensAndCheckToCover)
    {
        // https://lichess.org/editor/k4Q2/2q5/b7/2b5/3Q4/8/8/7K_b_-_-_0_1
        ChessBoard cb {"k4Q2/2q5/b7/2b5/3Q4/8/8/7K b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 7);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, a8, a7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, a8, b7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, a6, c8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, c5, f8, Queen)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c7, b8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c7, c8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, c7, d8)) != blackMoves.end());
    }

    // --- PAWNS ---
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsFromLineDifferentFromStartNoCapturesAndNoCheckConsiderations)
    {
        // https://lichess.org/editor/4k3/8/1p4p1/p4p2/3P3P/1P3P2/8/4K3_w_-_-_0_1
        ChessBoard cb {"4k3/8/1p4p1/p4p2/3P3P/1P3P2/8/4K3 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, b3, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d4, d5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, f3, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, h4, h5)) != whiteMoves.end());

        cb.loadPosition("4k3/8/1p4p1/p4p2/3P3P/1P3P2/8/4K3 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 4);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a5, a4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b6, b5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f5, f4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g6, g5)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsFromLineDifferentFromStartWithCapturesAndNoCheckConsiderations)
    {
        // https://lichess.org/editor/4k3/8/8/2p3p1/p2Pp2P/1P3P2/8/4K3_w_-_-_0_1
        ChessBoard cb {"4k3/8/8/2p3p1/p2Pp2P/1P3P2/8/4K3 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 8);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, b3, a4, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, b3, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d4, c5, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d4, d5)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, f3, e4, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, f3, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, h4, g5, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, h4, h5)) != whiteMoves.end());

        cb.loadPosition("4k3/8/8/2p3p1/p2Pp2P/1P3P2/8/4K3 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 8);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a4, a3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a4, b3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c5, c4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c5, d4, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, e3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, f3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g5, g4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g5, h4, Pawn)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsFromLineDifferentFromStartWithCapturesAndDiscoverCheckConsiderations)
    {
        // https://lichess.org/editor/8/8/8/R1pk2pb/p2Pp2P/1P3P2/4K3/8_w_-_-_0_1
        ChessBoard cb {"8/8/8/R1pk2pb/p2Pp2P/1P3P2/4K3/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, b3, a4, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, b3, b4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d4, c5, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, h4, g5, Pawn)) != whiteMoves.end());

        cb.loadPosition("8/8/8/R1pk2pb/p2Pp2P/1P3P2/4K3/8 b - - 0 1");
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 6);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a4, a3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a4, b3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, e3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, f3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g5, g4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g5, h4, Pawn)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsFromStartLine1)
    {
        // https://lichess.org/editor/4k3/8/8/8/1r6/7n/2P3P1/4K3_w_-_-_0_1
        ChessBoard cb {"4k3/8/8/8/1r6/7n/2P3P1/4K3 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 5);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, c2, c3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, c2, c4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g2, g3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g2, g4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g2, h3, Knight)) != whiteMoves.end());

    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsFromStartLine2)
    {
        // https://lichess.org/editor/4k3/1pp3p1/7R/1P6/8/8/8/4K3_b_-_-_0_1
        ChessBoard cb {"4k3/1pp3p1/7R/1P6/8/8/8/4K3 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 6);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b7, b6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c7, c6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c7, c5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g7, g6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g7, g5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g7, h6, Rook)) != blackMoves.end());
    }

    TEST(ChessBoardTester, CheckLegalMovesOfPawnsEnPassantCase_LeftOfWhitePawn)
    {
        // https://lichess.org/editor/8/8/8/2pP2k1/8/1K6/8/8_w_-_c6_0_1
        ChessBoard cb {"8/8/8/2pP2k1/8/1K6/8/8 w - c6 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 2);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d5, d6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, d5, c6, Pawn)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsEnPassantCase_RightOfWhitePawn)
    {
        // https://lichess.org/editor/3k4/8/2p5/4Pp2/8/1K6/P7/8_w_-_f6_0_1
        ChessBoard cb {"3k4/8/2p5/4Pp2/8/1K6/P7/8 w - f6 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, e5, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, e5, f6, Pawn)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, a2, a3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, a2, a4)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsEnPassantCase_RightOfBlackPawn)
    {
        // https://lichess.org/editor/8/8/2k5/8/1Pp5/8/8/4K3_b_-_b3_0_1
        ChessBoard cb {"8/8/2k5/8/1Pp5/8/8/4K3 b - b3 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 2);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c4, c3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c4, b3, Pawn)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckLegalMovesOfPawnsEnPassantCase_LeftOfBlackPawn)
    {
        // https://lichess.org/editor/3k4/8/8/2p5/4pP2/8/8/4K3_b_-_f3_0_1
        ChessBoard cb {"3k4/8/8/2p5/4pP2/8/8/4K3 b - f3 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 3);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, e3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e4, f3, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, c5, c4)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckPromotionMovesOfPawn_WhiteCaseNoCapture)
    {
        // https://lichess.org/editor/8/4k1P1/8/8/2K5/8/8/8_w_-_-_0_1
        ChessBoard cb {"8/4k1P1/8/8/2K5/8/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, g8, InvalidPiece, Queen)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, g8, InvalidPiece, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, g8, InvalidPiece, Bishop)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, g8, InvalidPiece, Knight)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, CheckPromotionMovesOfPawn_WhiteCaseWithCapture)
    {
        // https://lichess.org/editor/5bb1/3k2P1/7R/8/8/6K1/8/8_w_-_-_0_1
        ChessBoard cb {"5bb1/3k2P1/7R/8/8/6K1/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves, Pawn);
        ASSERT_EQ(whiteMoves.size(), 4);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, f8, Bishop, Queen)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, f8, Bishop, Rook)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, f8, Bishop, Bishop)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Pawn, g7, f8, Bishop, Knight)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, CheckPromotionMovesOfPawn_BlackCaseNoCapture)
    {
        // https://lichess.org/editor/8/8/8/5K2/1k6/8/1p2p3/8_b_-_-_0_1
        ChessBoard cb {"8/8/8/5K2/1k6/8/1p2p3/8 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 8);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b2, b1, InvalidPiece, Queen)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b2, b1, InvalidPiece, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b2, b1, InvalidPiece, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, b2, b1, InvalidPiece, Knight)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, e1, InvalidPiece, Queen)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, e1, InvalidPiece, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, e1, InvalidPiece, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, e1, InvalidPiece, Knight)) != blackMoves.end());
    }
    TEST(ChessBoardTester, CheckPromotionMovesOfPawn_BlackCaseWithCapture)
    {
        // https://lichess.org/editor/8/8/6p1/8/1k6/6K1/4p3/3NN3_b_-_-_0_1
        ChessBoard cb {"8/8/6p1/8/1k6/6K1/4p3/3NN3 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves, Pawn);
        ASSERT_EQ(blackMoves.size(), 5);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, d1, Knight, Queen)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, d1, Knight, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, d1, Knight, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, e2, d1, Knight, Knight)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g6, g5)) != blackMoves.end());
    }

    // --- isCheckMate() method testing ---
    TEST(ChessBoardTester, IsCheckMateForWhiteNegativeCaseInCaseOfNoCheckTesting)
    {
        // https://lichess.org/editor/3N4/1q6/6p1/6N1/pk6/6K1/8/8_w_-_-_0_1
        ChessBoard cb {"3N4/1q6/6p1/6N1/pk6/6K1/8/8 w - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 16);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, d8, b7, Queen)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, d8, c6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, d8, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, d8, f7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, f7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, h7)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, h3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, f3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, e4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, g5, e6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, f2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, h2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, h3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, f4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, g4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, h4)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, IsCheckMateForWhiteNegativeCaseInCaseOfCheckTesting)
    {
        // https://lichess.org/editor/4N3/2q5/6p1/6N1/pk6/6K1/8/8_w_-_-_0_1
        ChessBoard cb {"4N3/2q5/6p1/6N1/pk6/6K1/8/8 w - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 8);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, e8, c7, Queen)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(Knight, e8, d6)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, f2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, g2)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, f3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, h3)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, g4)) != whiteMoves.end());
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, g3, h4)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, IsCheckMateForWhitePositiveCaseTesting)
    {
        // https://lichess.org/editor/8/2B5/p7/3p2N1/1k6/8/5PPP/1q4K1_w_-_-_0_1
        ChessBoard cb {"8/2B5/p7/3p2N1/1k6/8/5PPP/1q4K1 w - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_TRUE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 0);
    }

    TEST(ChessBoardTester, IsCheckMateForBlackNegativeCaseInCaseOfNoCheckTesting)
    {
        // https://lichess.org/editor/2K5/p3B3/8/8/7R/1k6/4rp2/8_b_-_-_0_1
        ChessBoard cb {"2K5/p3B3/8/8/7R/1k6/4rp2/8 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 20);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, c3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, a2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, b2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, c2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e1)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e7, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, d2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, c2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, b2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, a2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a7, a6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, a7, a5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f2, f1, InvalidPiece, Queen)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f2, f1, InvalidPiece, Rook)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f2, f1, InvalidPiece, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f2, f1, InvalidPiece, Knight)) != blackMoves.end());
    }
    TEST(ChessBoardTester, IsCheckMateForBlackNegativeCaseInCaseOfCheckTesting)
    {
        // https://lichess.org/editor/2K5/p3B3/8/8/8/1k4R1/4rp2/8_b_-_-_0_1
        ChessBoard cb {"2K5/p3B3/8/8/8/1k4R1/4rp2/8 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 6);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, a4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, c4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, a2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, b2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, b3, c2)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, e2, e3)) != blackMoves.end());
    }
    TEST(ChessBoardTester, IsCheckMateForBlackPositiveCaseTesting)
    {
        // https://lichess.org/editor/8/8/8/knN5/1nN5/8/8/5K2_b_-_-_0_1
        ChessBoard cb {"8/8/8/knN5/1nN5/8/8/5K2 b - - 0 1"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), BlackArmy);
        ASSERT_TRUE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 0);
    }

    // --- isStaleMate() method testing ---
    TEST(ChessBoardTester, IsStaleMateForBlackNegativeCaseInCaseOfNoCheck)
    {
        // https://lichess.org/editor/3qnrk1/4bppp/3p4/4nPP1/r2BP2P/Np6/1P1Q4/1K1R1B1R_b_-_-_2_23
        ChessBoard cb {"3qnrk1/4bppp/3p4/4nPP1/r2BP2P/Np6/1P1Q4/1K1R1B1R b - - 2 23"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 32);
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, a3, Knight)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, a5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, a6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, a7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, a8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, b4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, c4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Rook, a4, d4, Bishop)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, d7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, g6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, g4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, f3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, d3)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, c4)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e5, c6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, d6, d5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e7, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Bishop, e7, g5, Pawn)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, f7, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, g7, g6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, h7, h6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Pawn, h7, h5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, c8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, b8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, a8)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, c7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, b6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, a5)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Queen, d8, d7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e8, c7)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(Knight, e8, f6)) != blackMoves.end());
        ASSERT_TRUE(std::find(blackMoves.begin(), blackMoves.end(), chessMove(King, g8, h8)) != blackMoves.end());
    }

    TEST(ChessBoardTester, IsNotStaleMateForWhiteNegativeCaseInCaseOfCheck)
    {
        // https://lichess.org/editor/8/8/8/1R4P1/1P1pk3/P3p3/8/r3K3_w_-_-_1_46
        ChessBoard cb {"8/8/8/1R4P1/1P1pk3/P3p3/8/r3K3 w - - 1 46"};
        ASSERT_EQ(cb.armyInCheck(), WhiteArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_FALSE(cb.drawnCanBeCalledAndCannotBeRefused());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 1);
        ASSERT_TRUE(std::find(whiteMoves.begin(), whiteMoves.end(), chessMove(King, e1, e2)) != whiteMoves.end());
    }
    TEST(ChessBoardTester, IsStaleMateForBlackPositiveCase)
    {
        // https://lichess.org/editor/7k/5Q2/4K3/3p4/p2P4/P7/8/8_b_-_-_0_1
        ChessBoard cb {"7k/5Q2/4K3/3p4/p2P4/P7/8/8 b - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_TRUE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 0);
    }

    TEST(ChessBoardTester, IsStaleMateForWhitePositiveCase)
    {
        // https://lichess.org/editor/8/kp6/p7/P1b3p1/6Pp/7P/2r5/7K_w_-_-_0_3
        ChessBoard cb {"8/kp6/p7/P1b3p1/6Pp/7P/2r5/7K w - - 0 3"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_TRUE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 0);
    }
    TEST(ChessBoardTester, AnotherStaleMateForWhitePositiveCase)
    {
        // https://lichess.org/editor/3K4/8/1n1k4/1PnP3b/2P4P/8/8/8_w_-_-_0_1
        ChessBoard cb {"3K4/8/1n1k4/1PnP3b/2P4P/8/8/8 w - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_TRUE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());

        std::vector<ChessMove> whiteMoves;
        cb.generateLegalMoves(whiteMoves);
        ASSERT_EQ(whiteMoves.size(), 0);
    }
    TEST(ChessBoardTester, AnotherStaleMateForBlackPositiveCase)
    {
        // https://lichess.org/editor/7k/1Q4rp/7P/8/2BB4/p7/p7/K7_b_-_-_0_1
        ChessBoard cb {"7k/1Q4rp/7P/8/2BB4/p7/p7/K7 b - - 0 1"};
        ASSERT_EQ(cb.armyInCheck(), InvalidArmy);
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_TRUE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());

        std::vector<ChessMove> blackMoves;
        cb.generateLegalMoves(blackMoves);
        ASSERT_EQ(blackMoves.size(), 0);
    }

    TEST(ChessBoardTester, NoStaleMateForFiftyFiveMovesRules)
    {
        // 50-moves rules: If fifty moves are made without a pawn move or capture being made,
        // the game is NOT automatically drawn: a player shall claim explicitly the draw
        // (the draw can be claim).
        // https://lichess.org/editor/3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q_w_-_-_100_71
        ChessBoard cb {"3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q w - - 100 71"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_TRUE(cb.drawnCanBeCalledAndCannotBeRefused());
        cb.loadPosition("3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q b - - 101 71");
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_TRUE(cb.drawnCanBeCalledAndCannotBeRefused());
        cb.loadPosition("3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q b - - 149 95");
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_FALSE(cb.isDrawnPosition());
        ASSERT_TRUE(cb.drawnCanBeCalledAndCannotBeRefused());
    }
    TEST(ChessBoardTester, StaleMateForSeventyFiveMovesRules)
    {
        // 75-moves rules: If seventy-five moves are made without a pawn move or capture being made,
        // the game is drawn unless the seventy-fifth move delivers a checkmate. No claim needs to
        // be made by either player, the draw is mandatorily applied by the arbiter. 
        // https://lichess.org/editor/3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q_w_-_-_150_96
        ChessBoard cb {"3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q w - - 150 96"};
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());
        cb.loadPosition("3r4/r1b1qnk1/1pb1p1p1/p1pnPp1p/P2p1P1P/NP1P1BPN/2PB3K/R3R2Q b - - 151 96");
        ASSERT_TRUE(cb.isValid());
        ASSERT_FALSE(cb.isCheckMate());
        ASSERT_FALSE(cb.isStaleMate());
        ASSERT_TRUE(cb.isDrawnPosition());
    }

    // --- Equality operators testing ---
    TEST(ChessBoardTester, TwoChessBoardsBuiltWithDefaultConstructorAreEqual)
    {
        ChessBoard cb1{};
        ChessBoard cb2{};
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingTheInitialPositionBuiltInDifferentWaysAreEqual)
    {
        ChessBoard cb1{};
        ChessBoard cb2 {FENRecord(FENInitialStandardPosition)};
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingTwoDifferentPositionsAreNotEqual)
    {
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2 {FENRecord(FENInitialStandardPosition)};
        ASSERT_TRUE(cb1 != cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingTheSamePositionDifferentFromInitialAreEqual)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"8/8/8/8/8/8/8/8 w - - 0 1"};
        cb2.armies[WhiteArmy].color = WhiteArmy;
        cb2.armies[WhiteArmy].pieces[King] = BitBoard{g1};
        cb2.armies[WhiteArmy].pieces[Queen] = BitBoard(EmptyBB);
        cb2.armies[WhiteArmy].pieces[Rook] = BitBoard{d1};
        cb2.armies[WhiteArmy].pieces[Knight] = BitBoard{b5};
        cb2.armies[WhiteArmy].pieces[Bishop] = BitBoard{d3};
        cb2.armies[WhiteArmy].pieces[Pawn] = BitBoard({a2, b2, c2, e3, g2, h2});
        cb2.armies[BlackArmy].color = BlackArmy;
        cb2.armies[BlackArmy].pieces[King] = BitBoard{g8};
        cb2.armies[BlackArmy].pieces[Queen] = BitBoard(EmptyBB);
        cb2.armies[BlackArmy].pieces[Rook] = BitBoard{d8};
        cb2.armies[BlackArmy].pieces[Knight] = BitBoard({f2, g4});
        cb2.armies[BlackArmy].pieces[Bishop] = BitBoard(EmptyBB);
        cb2.armies[BlackArmy].pieces[Pawn] = BitBoard({a7, b7, c7, f7, g7, h7});
        cb2.sideToMove = WhiteArmy;
        cb2.castlingAvailability = BitBoard(EmptyBB);
        cb2.enPassantTargetSquare = BitBoard(EmptyBB);
        cb2.halfMoveClock = 3;
        cb2.fullMoves = 19;
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyColorDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].color = InvalidArmy;
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].color = WhiteArmy;
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyKingPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[King] ^= BitBoard({g1, f1});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[King] ^= BitBoard({g1, f1});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyQueenPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[Queen] ^= BitBoard(d2);
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[Queen] ^= BitBoard(d2);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyRookPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[Rook] ^= BitBoard({d1, c5});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[Rook] ^= BitBoard({d1, c5});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyBishopPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[Bishop] ^= BitBoard({d3, c4});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[Bishop] ^= BitBoard({d3, c4});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyKnightPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[Knight] ^= BitBoard({b5, d4});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[Knight] ^= BitBoard({b5, d4});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FirstArmyPawnPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[WhiteArmy].pieces[Pawn] ^= BitBoard({b2, b3});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[WhiteArmy].pieces[Pawn] ^= BitBoard({b2, b3});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyKingPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[King] ^= BitBoard({g8, h8});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[King] ^= BitBoard({g8, h8});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyQueenPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[Queen] = BitBoard(g5);
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[Queen] = BitBoard(EmptyBB);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyRookPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[Rook] ^= BitBoard({d8, e8});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[Rook] ^= BitBoard({d8, e8});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyBishopPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[Bishop] = BitBoard(g4);
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[Bishop] = BitBoard(EmptyBB);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyKnightPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[Knight] ^= BitBoard({g4, e4});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[Knight] = BitBoard({g4, f2});
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SecondArmyPawnPositionDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.armies[BlackArmy].pieces[Pawn] ^= BitBoard({c7, c6});
        ASSERT_TRUE(cb1 != cb2);
        cb2.armies[BlackArmy].pieces[Pawn].setCell(c7);
        cb2.armies[BlackArmy].pieces[Pawn].resetCell(c6);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_SideToMoveDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.sideToMove = BlackArmy;
        ASSERT_TRUE(cb1 != cb2);
        cb2.sideToMove = WhiteArmy;
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_CastlingAvailabilityDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.castlingAvailability = BitBoard({g1, g8});
        ASSERT_TRUE(cb1 != cb2);
        cb2.castlingAvailability = BitBoard(EmptyBB);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_EnPassantTargetSquareDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        cb2.enPassantTargetSquare = BitBoard(c3);
        ASSERT_TRUE(cb1 != cb2);
        cb2.enPassantTargetSquare = BitBoard(EmptyBB);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_HalfMoveClockDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        ++(cb2.halfMoveClock);
        ASSERT_EQ(cb2.halfMoveClock, 4);
        ASSERT_TRUE(cb1 != cb2);
        --(cb2.halfMoveClock);
        ASSERT_TRUE(cb1 == cb2);
    }
    TEST(ChessBoardTester, TwoChessBoardsContainingQuiteTheSamePositionAreNotEqual_FullMovesDifferent)
    {
        // https://lichess.org/WqXdBTUg#36
        ChessBoard cb1{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ChessBoard cb2{"3r2k1/ppp2ppp/8/1N6/6n1/3BP3/PPP2nPP/3R2K1 w - - 3 19"};
        ASSERT_TRUE(cb1 == cb2);
        ++(cb2.fullMoves);
        ASSERT_EQ(cb2.fullMoves, 20);
        ASSERT_TRUE(cb1 != cb2);
        --(cb2.fullMoves);
        ASSERT_TRUE(cb1 == cb2);
    }

    // -------------------------------------------------------------------------------------
    // DO MOVE TESTING ---
    TEST(ChessBoardTester, TestSequenceOfMoves_GiuocoPiano)
    {
        ChessBoard cb;
        ASSERT_EQ(cb, ChessBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"));
        cb.doMove(chessMove(Pawn, e2, e4));
        ASSERT_EQ(cb, ChessBoard("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"));
        cb.doMove(chessMove(Pawn, e7, e5));
        ASSERT_EQ(cb, ChessBoard("rnbqkbnr/pppp1ppp/8/4p3/4P3/8/PPPP1PPP/RNBQKBNR w KQkq e6 0 2"));
        cb.doMove(chessMove(Knight, g1, f3));
        ASSERT_EQ(cb, ChessBoard("rnbqkbnr/pppp1ppp/8/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"));
        cb.doMove(chessMove(Knight, b8, c6));
        ASSERT_EQ(cb, ChessBoard("r1bqkbnr/pppp1ppp/2n5/4p3/4P3/5N2/PPPP1PPP/RNBQKB1R w KQkq - 2 3"));
        cb.doMove(chessMove(Bishop, f1, c4));
        ASSERT_EQ(cb, ChessBoard("r1bqkbnr/pppp1ppp/2n5/4p3/2B1P3/5N2/PPPP1PPP/RNBQK2R b KQkq - 3 3"));
        cb.doMove(chessMove(Bishop, f8, c5));
        ASSERT_EQ(cb, ChessBoard("r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQkq - 4 4"));
        cb.doMove(chessMove(Pawn, c2, c3));
        ASSERT_EQ(cb, ChessBoard("r1bqk1nr/pppp1ppp/2n5/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R b KQkq - 0 4"));
        cb.doMove(chessMove(Queen, d8, e7));
        ASSERT_EQ(cb, ChessBoard("r1b1k1nr/ppppqppp/2n5/2b1p3/2B1P3/2P2N2/PP1P1PPP/RNBQK2R w KQkq - 1 5"));
        cb.doMove(chessMove(Pawn, d2, d4));
        ASSERT_EQ(cb, ChessBoard("r1b1k1nr/ppppqppp/2n5/2b1p3/2BPP3/2P2N2/PP3PPP/RNBQK2R b KQkq d3 0 5"));
        cb.doMove(chessMove(Bishop, c5, b6));
        ASSERT_EQ(cb, ChessBoard("r1b1k1nr/ppppqppp/1bn5/4p3/2BPP3/2P2N2/PP3PPP/RNBQK2R w KQkq - 1 6"));
        //cb.doMove(chessMove(King, e1, g1));
        //ASSERT_EQ(cb, ChessBoard("r1b1k1nr/ppppqppp/1bn5/4p3/2BPP3/2P2N2/PP3PPP/RNBQ1RK1 b kq - 2 6"));
        // FIXME --- TO BE COMPLETED ---
    }


    // -------------------------------------------------------------------------------------


} // namespace cSzd
