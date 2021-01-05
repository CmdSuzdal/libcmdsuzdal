#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cmdsuzdal/army.h"

using namespace std;
using namespace testing;

namespace cSzd
{

    TEST(ArmyTester, AfterInitWithInvalidArmyThereIsNobody)
    {
        Army army { InvalidArmy };
        ASSERT_EQ(army.color, InvalidArmy);
        ASSERT_EQ(army.pieces[King].popCount(), 0);
        ASSERT_EQ(army.pieces[Queen].popCount(), 0);
        ASSERT_EQ(army.pieces[Rook].popCount(), 0);
        ASSERT_EQ(army.pieces[Bishop].popCount(), 0);
        ASSERT_EQ(army.pieces[Knight].popCount(), 0);
        ASSERT_EQ(army.pieces[Pawn].popCount(), 0);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasOneKingInE1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(e1));
        ASSERT_EQ(army.pieces[King].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasEightPawnInTheSecondRank)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Pawn], BitBoard(RanksBB[r_2]));
        ASSERT_EQ(army.pieces[Pawn].popCount(), 8);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasOneKingInE8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(e8));
        ASSERT_EQ(army.pieces[King].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasEightPawnInTheSeventhRank)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Pawn], BitBoard(RanksBB[r_7]));
        ASSERT_EQ(army.pieces[Pawn].popCount(), 8);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasOneQueenInD1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Queen], BitBoard(d1));
        ASSERT_EQ(army.pieces[Queen].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasOneQueenInD8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Queen], BitBoard(d8));
        ASSERT_EQ(army.pieces[Queen].popCount(), 1);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoBishopsInC1AndF1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Bishop], BitBoard({c1, f1}));
        ASSERT_EQ(army.pieces[Bishop].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoBishopsInC8AndF8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Bishop], BitBoard({c8, f8}));
        ASSERT_EQ(army.pieces[Bishop].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoKnightsInB1AndG1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Knight], BitBoard({b1, g1}));
        ASSERT_EQ(army.pieces[Knight].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoKnightsInB8AndG8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Knight], BitBoard({b8, g8}));
        ASSERT_EQ(army.pieces[Knight].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitWhiteArmyHasTwoRooksInA1AndH1)
    {
        Army army { WhiteArmy };
        ASSERT_EQ(army.color, WhiteArmy);
        ASSERT_EQ(army.pieces[Rook], BitBoard({a1, h1}));
        ASSERT_EQ(army.pieces[Rook].popCount(), 2);
    }
    TEST(ArmyTester, AfterInitBlackArmyHasTwoRooksInA8AndH8)
    {
        Army army { BlackArmy };
        ASSERT_EQ(army.color, BlackArmy);
        ASSERT_EQ(army.pieces[Rook], BitBoard({a8, h8}));
        ASSERT_EQ(army.pieces[Rook].popCount(), 2);
    }
    TEST(ArmyTester, AfterDefaultInitThereIsNoArmy)
    {
        Army army {};
        ASSERT_EQ(army.color, InvalidArmy);
        ASSERT_EQ(army.pieces[King], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Queen], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Bishop], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Knight], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Rook], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[Pawn], BitBoard(EmptyBB));
        ASSERT_EQ(army.pieces[King].popCount(), 0);
        ASSERT_EQ(army.pieces[Queen].popCount(), 0);
        ASSERT_EQ(army.pieces[Bishop].popCount(), 0);
        ASSERT_EQ(army.pieces[Knight].popCount(), 0);
        ASSERT_EQ(army.pieces[Rook].popCount(), 0);
        ASSERT_EQ(army.pieces[Pawn].popCount(), 0);
    }

    // numPieces() method testing
    TEST(ArmyTester, AfterDefaultInitThereAreNoPieces)
    {
        Army a {};
        ASSERT_EQ(a.numPieces(), 0);
    }
    TEST(ArmyTester, AfterWhiteArmyInitThereAre16Pieces)
    {
        Army a { WhiteArmy };
        ASSERT_EQ(a.numPieces(), 16);
    }
    TEST(ArmyTester, AfterBlackArmyInitThereAre16Pieces)
    {
        Army a { BlackArmy };
        ASSERT_EQ(a.numPieces(), 16);
    }

    // ------------------------------------------------------------------------
    // --- Controlled Cells Tests --- Without interference board

    // King alone ---
    TEST(ArmyTester, ControlledCellsOfAnEmptyArmyIsEmpty)
    {
        Army a {};
        ASSERT_EQ(a.controlledCells(), BitBoard(EmptyBB));
    }

    TEST(ArmyTester, ChecksCellsControlledByWhiteKingInE5)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[King] = BitBoard{e5};
        ASSERT_EQ(a.controlledCells(), BitBoard({d4, e4, f4, d5, f5, d6, e6, f6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKingInG7)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[King] = BitBoard{g7};
        ASSERT_EQ(a.controlledCells(), BitBoard({f6, g6, h6, f7, h7, f8, g8, h8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKingInA1)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[King] = BitBoard{a1};
        ASSERT_EQ(a.controlledCells(), BitBoard({b1, a2, b2}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKingInH8)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[King] = BitBoard{h8};
        ASSERT_EQ(a.controlledCells(), BitBoard({g7, h7, g8}));
    }

    // Pawns alone ---
    TEST(ArmyTester, ChecksCellsControlledByInitialRowOfWhitePawns)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({a2, b2, c2, d2, e2, f2, g2, h2});
        ASSERT_EQ(a.controlledCells(), BitBoard({a3, b3, c3, d3, e3, f3, g3, h3}));
    }
    TEST(ArmyTester, ChecksCellsControlledByInitialRowOfBlackPawns)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({a7, b7, c7, d7, e7, f7, g7, h7});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, b6, c6, d6, e6, f6, g6, h6}));
    }

    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns1)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({a4});
        ASSERT_EQ(a.controlledCells(), BitBoard({b5}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns2)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({a4});
        ASSERT_EQ(a.controlledCells(), BitBoard({b3}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns3)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({b5, h7});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, c6, g8}));
    }
    TEST(ArmyTester, AdditionalTestsForCellsControlledByPawns4)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({f6, h2});
        ASSERT_EQ(a.controlledCells(), BitBoard({e5, g5, g1}));
    }

    // Knights ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({b1, g1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a3, c3, d2, e2, f3, h3}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackKnightsInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({b8, g8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a6, c6, d7, e7, f6, h6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInD4)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({d4});
        ASSERT_EQ(a.controlledCells(), BitBoard({e6, f5, f3, e2, c2, b3, b5, c6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsInH8)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Knight] = BitBoard({h8});
        ASSERT_EQ(a.controlledCells(), BitBoard({f7, g6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByWhiteKnightsOnAllTheCellsOfTheDiagonal)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Knight] = BitBoard({a1, b2, c3, d4, e5, f6, g7, h8});
        ASSERT_EQ(a.controlledCells(), BitBoard(
            {b1, d1, a2, c2, e2, b3, d3, f3, a4, c4, e4, g4,
             b5, d5, f5, h5, c6, e6, g6, d7, f7, h7, e8, g8}));
    }

    // Bishops simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteBishopsAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Bishop] = BitBoard({c1, f1});
        ASSERT_EQ(a.controlledCells(), BitBoard({b2, d2, e2, g2, a3, d3, e3, h3, c4, f4, b5, g5, a6, h6}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackBishopsAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({c8, f8});
        ASSERT_EQ(a.controlledCells(), BitBoard({b7, d7, e7, g7, a6, d6, e6, h6, c5, f5, b4, g4, a3, h3}));
    }

    // Rooks simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteRooksAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({a1, h1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, b1, c1, d1, e1, f1, g1, h1, a2, h2, a3, h3, a4, h4, a5, h5, a6, h6, a7, h7, a8, h8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackRookAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({a8, h8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, h1, a2, h2, a3, h3, a4, h4, a5, h5, a6, h6, a7, h7, a8, b8, c8, d8, e8, f8, g8, h8}));
    }

    // Queens simple cases ---
    TEST(ArmyTester, ChecksCellsControlledByWhiteQueenAloneInInitialPosition)
    {
        Army a {};
        a.color = WhiteArmy;
        a.pieces[Queen] = BitBoard({d1});
        ASSERT_EQ(a.controlledCells(), BitBoard({a1, b1, c1, e1, f1, g1, h1, c2, d2, e2, b3, d3, f3, a4, d4, g4, d5, h5, d6, d7, d8}));
    }
    TEST(ArmyTester, ChecksCellsControlledByBlackQueenAloneInInitialPosition)
    {
        Army a {};
        a.color = BlackArmy;
        a.pieces[Queen] = BitBoard({d8});
        ASSERT_EQ(a.controlledCells(), BitBoard({a8, b8, c8, e8, f8, g8, h8, c7, d7, e7, b6, d6, f6, a5, d5, g5, d4, h4, d3, d2, d1}));
    }

    // To manage complex case of controlled cells with interferences,
    // we need a function that returns the Bitboard with all the cells
    // occupied by the army. We firstly test this function
    TEST(ArmyTester, WhiteArmyInInitialPositionOccupyTheRanks1and2)
    {
        Army a { WhiteArmy };
        ASSERT_EQ(a.occupiedCells(), BitBoard(RanksBB[r_1] | RanksBB[r_2]));
    }
    TEST(ArmyTester, BlackArmyInInitialPositionOccupyTheRanks7and8)
    {
        Army a { BlackArmy };
        ASSERT_EQ(a.occupiedCells(), BitBoard(RanksBB[r_7] | RanksBB[r_8]));
    }

    // --- getPieceInCell() method Testing
    TEST(ArmyTester, CheckThatGetPieceInCellReturnsCorrectValues)
    {
        Army a{WhiteArmy};
        ASSERT_EQ(a.getPieceInCell(e1), King);
        ASSERT_EQ(a.getPieceInCell(d1), Queen);
        ASSERT_EQ(a.getPieceInCell(c1), Bishop);
        ASSERT_EQ(a.getPieceInCell(f1), Bishop);
        ASSERT_EQ(a.getPieceInCell(b1), Knight);
        ASSERT_EQ(a.getPieceInCell(g1), Knight);
        ASSERT_EQ(a.getPieceInCell(a1), Rook);
        ASSERT_EQ(a.getPieceInCell(h1), Rook);
        ASSERT_EQ(a.getPieceInCell(a2), Pawn);
        ASSERT_EQ(a.getPieceInCell(b2), Pawn);
        ASSERT_EQ(a.getPieceInCell(c2), Pawn);
        ASSERT_EQ(a.getPieceInCell(d2), Pawn);
        ASSERT_EQ(a.getPieceInCell(e2), Pawn);
        ASSERT_EQ(a.getPieceInCell(f2), Pawn);
        ASSERT_EQ(a.getPieceInCell(g2), Pawn);
        ASSERT_EQ(a.getPieceInCell(h2), Pawn);
        ASSERT_EQ(a.getPieceInCell(a3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(b3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(c3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(d3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(e3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(f3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(g3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(h3), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(a4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(b4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(c4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(d4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(e4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(f4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(g4), InvalidPiece);
        ASSERT_EQ(a.getPieceInCell(h4), InvalidPiece);
    }

    // --- getKingPosition() method Testing
    TEST(ArmyTester, getKingPositionWorksOk)
    {
        Army w{WhiteArmy};
        ASSERT_EQ(w.getKingPosition(), e1);
        Army b{BlackArmy};
        ASSERT_EQ(b.getKingPosition(), e8);
    }

    // --- Test the controlledCellsByPieceType() method for kings, pawns and invalid pieces.
    // (this is done to complete the coverage of the function)
    TEST(ArmyTester, controlledCellsByPieceType_CheckKing)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[King] = BitBoard(g4);
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(b6);
        ASSERT_EQ(w.controlledCellsByPieceType(King, b.occupiedCells()), BitBoard({f3, g3, h3, f4, h4, f5, g5, h5}));
        ASSERT_EQ(b.controlledCellsByPieceType(King, w.occupiedCells()), BitBoard({a5, b5, c5, a6, c6, a7, b7, c7}));
    }
    TEST(ArmyTester, controlledCellsByPieceType_CheckInvalidPiece)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[King] = BitBoard(g4);
        Army b{};
        b.color = BlackArmy;
        b.pieces[King] = BitBoard(b6);
        ASSERT_EQ(w.controlledCellsByPieceType(InvalidPiece, b.occupiedCells()), BitBoard(EmptyBB));
        ASSERT_EQ(b.controlledCellsByPieceType(InvalidPiece, w.occupiedCells()), BitBoard(EmptyBB));
    }
    TEST(ArmyTester, controlledCellsByPieceType_CheckPawn)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard({c2, g3});
        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard({c7, h6});
        ASSERT_EQ(w.controlledCellsByPieceType(Pawn, b.occupiedCells()), BitBoard({b3, d3, f4, h4}));
        ASSERT_EQ(b.controlledCellsByPieceType(Pawn, w.occupiedCells()), BitBoard({b6, d6, g5}));
    }


    // --- OCCUPIED CELLS COMPLEX CASES (with interference) ----------------------------------------
    // Rooks ---
    TEST(ArmyTester, CheckCellsControlledByRookInA1WithPawnInA2)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({a1});
        a.pieces[Pawn] = BitBoard({a2});
        ASSERT_EQ(a.controlledCellsByPieceType(Rook), BitBoard({b1, c1, d1, e1, f1, g1, h1, a2}));
    }
    TEST(ArmyTester, CheckCellsControlledByARookInD4SurroundedByPawns)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({d4});
        a.pieces[Pawn] = BitBoard({d3, c4, e4, d5});
        ASSERT_EQ(a.controlledCellsByPieceType(Rook), BitBoard({d3, c4, e4, d5}));
    }
    TEST(ArmyTester, CheckCellsControlledByRooksComplex1)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Rook] = BitBoard({d4, g7});
        a.pieces[Pawn] = BitBoard({d5});
        a.pieces[Knight] = BitBoard({g6});
        a.pieces[King] = BitBoard({f6});
        ASSERT_EQ(a.controlledCellsByPieceType(Rook), BitBoard({d1, d2, d3, a4, b4, c4, e4, f4, g4, h4, d5, g6, a7, b7, c7, d7, e7, f7, h7, g8}));
    }
    TEST(ArmyTester, CheckCellsControlledByRooksComplex2)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Rook] = BitBoard({c4, c5});
        ASSERT_EQ(a.controlledCellsByPieceType(Rook), BitBoard({c1, c2, c3, a4, b4, c4, d4, e4, f4, g4, h4, a5, b5, c5, d5, e5, f5, g5, h5, c6, c7, c8}));
    }

    // Bishops ---
    TEST(ArmyTester, CheckCellsControlledByBishopInH8WithPawnInG7)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({h8});
        a.pieces[Pawn] = BitBoard({g7});
        ASSERT_EQ(a.controlledCellsByPieceType(Bishop), BitBoard({g7}));
    }
    TEST(ArmyTester, CheckCellsControlledByBishopComplexCase1)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Bishop] = BitBoard({d4, g6});
        a.pieces[Pawn] = BitBoard({b2,c2,d2,e2,f2});
        a.pieces[King] = BitBoard({f6});
        ASSERT_EQ(a.controlledCellsByPieceType(Bishop), BitBoard({b2, c2, f2, c3, d3, e3, e4, c5, e5, f5, h5, b6, f6, a7, f7, h7, e8}));
    }
    TEST(ArmyTester, CheckCellsControlledByBishopComplexCase2)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Bishop] = BitBoard({b5, g3});
        a.pieces[Pawn] = BitBoard({d3, d7});
        a.pieces[King] = BitBoard({e5});
        a.pieces[Queen] = BitBoard({f1});
        ASSERT_EQ(a.controlledCellsByPieceType(Bishop), BitBoard({e1, f2, h2, d3, a4, c4, f4, h4, e5, a6, c6, d7}));
    }

    // Queens ---
    TEST(ArmyTester, CheckCellsControlledByWhiteQueenInInitialPositionOfACompleteArmy)
    {
        Army a {WhiteArmy};
        ASSERT_EQ(a.controlledCellsByPieceType(Queen), BitBoard({c1, e1, c2, d2, e2}));
    }
    TEST(ArmyTester, CheckCellsControlledByBlackQueenInInitialPositionOfACompleteArmy)
    {
        Army a {BlackArmy};
        ASSERT_EQ(a.controlledCellsByPieceType(Queen), BitBoard({c8, e8, c7, d7, e7}));
    }
    TEST(ArmyTester, CheckCellsControlledByQueensComplexCase1)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Queen] = BitBoard({b5, g3});
        a.pieces[Pawn] = BitBoard({d3, d7});
        a.pieces[King] = BitBoard({e5});
        a.pieces[Knight] = BitBoard({f1});
        ASSERT_EQ(a.controlledCellsByPieceType(Queen), BitBoard({b1, e1, g1, b2, f2, g2, h2, b3, d3, e3, f3, h3,
                                                        a4, b4, c4, f4, g4, h4, a5, c5, d5, e5, g5,
                                                        a6, b6, c6, g6, b7, d7, g7, b8, g8}));
    }
    TEST(ArmyTester, CheckCellsControlledByQueensComplexCase2)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Queen] = BitBoard({d4, g7});
        a.pieces[Pawn] = BitBoard({c5, d5});
        a.pieces[Knight] = BitBoard({g6});
        a.pieces[King] = BitBoard({f6});
        ASSERT_EQ(a.controlledCellsByPieceType(Queen), BitBoard({a1, d1, g1, b2, d2, f2, c3, d3, e3,
                                                     a4, b4, c4, e4, f4, g4, h4, c5, d5, e5, f6, g6, h6,
                                                     a7, b7, c7, d7, e7, f7, h7, f8, g8, h8}));
    }

    // ------------------------------------------------------------------------
    // --- Controlled Cells Tests --- With interference board
    // ... Check the ChessBoard class for additional tests ...

    TEST(ArmyTester, CheckCellControlledByWhiteRooksInInitialPositionWithTheBlackArmyInTheOppositeSide)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Rook] = BitBoard({a1, h1});
        Army b {BlackArmy};
        ASSERT_EQ(w.controlledCells(b.occupiedCells()), BitBoard({a1, b1, c1, d1, e1, f1, g1, h1, a2, h2, a3, h3, a4, h4, a5, h5, a6, h6, a7, h7}));
    }
    TEST(ArmyTester, CheckCellControlledByBlackBishopsInInitialPositionWithTheBlackArmyInTheOppositeSide)
    {
        // The opposite army does not really causes interference to bishops
        Army b{};
        b.color = BlackArmy;
        b.pieces[Bishop] = BitBoard({c8, f8});
        Army w {WhiteArmy};
        ASSERT_EQ(b.controlledCells(w.occupiedCells()), BitBoard({b7, d7, e7, g7, a6, d6, e6, h6, c5, f5, b4, g4, a3, h3}));
    }

    // ------------------------------------------------------------------------
    // --- Possible Moves Tests ---

    // --- King
    TEST(ArmyTester, CheckThatKingsAloneInE5AndA1CanMoveInTheWholeNeighbour)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[King] = BitBoard(e5);
        Army b{};
        b.color = BlackArmy;
        b.pieces[King] = BitBoard(a1);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(King, w.getKingPosition(), b.occupiedCells()),
            w.pieces[King].neighbourCells());
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(King, b.getKingPosition(), w.occupiedCells()),
            b.pieces[King].neighbourCells());
    }
    TEST(ArmyTester, CheckPossibleMovesOfKingInOpposition)
    {
        // remember that the kingPossibleMovesCells does not check
        // for validity and returns all the possible moves
        Army w{};
        w.color = WhiteArmy;
        w.pieces[King] = BitBoard(e5);
        Army b{};
        b.color = BlackArmy;
        b.pieces[King] = BitBoard(e7);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(King, w.getKingPosition(), b.occupiedCells()),
                    BitBoard({d4, e4, f4, d5, f5, d6, e6, f6 }));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(King, b.getKingPosition(), w.occupiedCells()),
                    BitBoard({d6, e6, f6, d7, f7, d8, e8, f8}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfKingsObstructedByFriends)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[King] = BitBoard(b2);
        w.pieces[Queen] = BitBoard(a2);
        w.pieces[Rook] = BitBoard(a1);
        w.pieces[Knight] = BitBoard({c1, a3});
        w.pieces[Pawn] = BitBoard({b3, c3, d3});
        Army b{};
        b.color = BlackArmy;
        b.pieces[King] = BitBoard(h8);
        b.pieces[Pawn] = BitBoard({g7, f6, e6});
        b.pieces[Rook] = BitBoard(h7);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(King, w.getKingPosition(), b.occupiedCells()),
                    BitBoard({b1, c2}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(King, b.getKingPosition(), w.occupiedCells()),
                    BitBoard(g8));
    }

    // --- Knights
    TEST(ArmyTester, CheckPossibleMovesOfAKnightInF3WithNoOtherFriendPiecesInDestinationCells)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Knight] = BitBoard(f3);
        w.pieces[Pawn] = BitBoard(g2);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Knight, g2), BitBoard(EmptyBB));  // No knights in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Knight, f3), BitBoard({e1, g1, d2, h2, d4, h4, e5, g5}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfKnightsWithComplexInteraction)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Knight] = BitBoard(d3);
        w.pieces[King] = BitBoard(f2);
        w.pieces[Bishop] = BitBoard(h5);
        w.pieces[Pawn] = BitBoard({a4, b4, c5, a6});
        Army b{};
        b.color = BlackArmy;
        b.pieces[Knight] = BitBoard(f4);
        b.pieces[King] = BitBoard(d5);
        b.pieces[Rook] = BitBoard(h3);
        b.pieces[Queen] = BitBoard(b2);
        b.pieces[Pawn] = BitBoard({e6, f7, g6, h7});
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Knight, f4, b.occupiedCells()), BitBoard(EmptyBB));  // No white knight in g2
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Knight, d3, w.occupiedCells()), BitBoard(EmptyBB));  // No black knight in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Knight, d3, b.occupiedCells()), BitBoard({c1, b2, e5, f4, e1}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Knight, f4, w.occupiedCells()), BitBoard({d3, h5, g2, e2}));
    }

    // --- Bishops
    TEST(ArmyTester, CheckPossibleMovesOfABishopInF3WithNoOtherFriendPiecesInDestinationCells)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Bishop] = BitBoard(e6);
        w.pieces[Pawn] = BitBoard(g2);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Bishop, g2), BitBoard(EmptyBB));  // No bishop in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Bishop, e6), BitBoard({a2, b3, c4, d5, f7, g8, h3, g4, f5, d7, c8}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfBishopsWithComplexInteraction)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Bishop] = BitBoard(d5);
        w.pieces[King] = BitBoard(c4);
        w.pieces[Knight] = BitBoard(g3);
        w.pieces[Pawn] = BitBoard({e6, f6});
        Army b{};
        b.color = BlackArmy;
        b.pieces[Bishop] = BitBoard(f4);
        b.pieces[King] = BitBoard(g5);
        b.pieces[Knight] = BitBoard(b7);
        b.pieces[Pawn] = BitBoard({e3, f3});
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Bishop, c4, b.occupiedCells()), BitBoard(EmptyBB));  // No white bishop in g2
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Bishop, e3, w.occupiedCells()), BitBoard(EmptyBB));  // No black bishop in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Bishop, d5, b.occupiedCells()), BitBoard({b7, c6, e4, f3}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Bishop, f4, w.occupiedCells()), BitBoard({b8, c7, d6, e5, g3}));
    }

    // --- Rooks
    TEST(ArmyTester, CheckPossibleMovesOfARookInB2WithNoOtherFriendPiecesInDestinationCells)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Rook] = BitBoard(b2);
        w.pieces[Pawn] = BitBoard(g3);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Rook, g3), BitBoard(EmptyBB));  // No rook in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Rook, b2), BitBoard(FilesBB[f_b] ^ RanksBB[r_2]));
    }

    TEST(ArmyTester, CheckPossibleMovesOfRooksWithComplexInteraction)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Rook] = BitBoard({c3, d3});
        w.pieces[King] = BitBoard(a3);
        w.pieces[Pawn] = BitBoard({e2, h3});
        Army b{};
        b.color = BlackArmy;
        b.pieces[Rook] = BitBoard({g3, d5});
        b.pieces[King] = BitBoard(d8);
        b.pieces[Pawn] = BitBoard({c6, h4});
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Rook, e2, b.occupiedCells()), BitBoard(EmptyBB));  // No white rook in g2
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Rook, c3, b.occupiedCells()), BitBoard({b3, c1, c2, c4, c5, c6}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Rook, d3, b.occupiedCells()), BitBoard({e3, f3, g3, d1, d2, d4, d5}));

        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Rook, c6, w.occupiedCells()), BitBoard(EmptyBB));  // No black rook in g2
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Rook, g3, w.occupiedCells()), BitBoard({d3, e3, f3, h3, g1, g2, g4, g5, g6, g7, g8}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Rook, d5, w.occupiedCells()), BitBoard({d3, d4, d6, d7, a5, b5, c5, e5, f5, g5, h5}));
    }

    // --- Queens
    TEST(ArmyTester, CheckPossibleMovesOfAQueenInE6WithNoOtherFriendPiecesInDestinationCells)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Queen] = BitBoard(e6);
        w.pieces[King] = BitBoard(f4);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Queen, f4), BitBoard(EmptyBB));  // No queen in f4
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Queen, e6),
                                            BitBoard(FilesBB[f_e] | RanksBB[r_6] |
                                            DiagsBB[d_6] | AntiDiagsBB[a_9]) ^ BitBoard(e6));
    }

    TEST(ArmyTester, CheckPossibleMovesOfQueensWithComplexInteraction)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Queen] = BitBoard(c6);
        w.pieces[King] = BitBoard(b6);
        w.pieces[Knight] = BitBoard(e8);
        w.pieces[Bishop] = BitBoard(f6);
        w.pieces[Pawn] = BitBoard({b5, c5});
        Army b{};
        b.color = BlackArmy;
        b.pieces[Queen] = BitBoard(f3);
        b.pieces[King] = BitBoard(g2);
        b.pieces[Rook] = BitBoard(h5);
        b.pieces[Pawn] = BitBoard({c3, h7});
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Queen, f6, b.occupiedCells()), BitBoard(EmptyBB));  // No white queen in f6
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Queen, c6, b.occupiedCells()), BitBoard({a8, b7, d5, e4, f3, d7, d6, e6, c7, c8}));

        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Queen, h5, w.occupiedCells()), BitBoard(EmptyBB));  // No black queen in h5
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Queen, f3, w.occupiedCells()), BitBoard({d3, e3, g3, h3, f1, f2, f4, f5, f6, d1, e2, g4, e4, d5, c6}));
    }

    // --- Pawns
    TEST(ArmyTester, CheckPossibleMovesOfPawn1_OnlySingleStepIsPossibleFromRankDifferentFromStartRankAndNoCapture_WhiteSide)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({a3, e4, g6});
        a.pieces[King] = BitBoard(e1);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, e1), BitBoard(EmptyBB));  // No pawn in e1
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, b3), BitBoard(EmptyBB));  // No pawn in b3
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, a3), BitBoard(a4));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, e4), BitBoard(e5));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, g6), BitBoard(g7));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn1_OnlySingleStepIsPossibleFromRankDifferentFromStartRankAndNoCapture_BlackSide)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({b6, c5, h3});
        a.pieces[King] = BitBoard(e8);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, e8), BitBoard(EmptyBB));  // No pawn in e8
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, d4), BitBoard(EmptyBB));  // No pawn in d4
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, b6), BitBoard(b5));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, c5), BitBoard(c4));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, h3), BitBoard(h2));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn2_OneOrTwoRanksStepPossibleFromSecondRankForWhite)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({c2, f2});
        a.pieces[King] = BitBoard(e1);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, a2), BitBoard(EmptyBB));  // No pawn in a2
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, c2), BitBoard({c3, c4}));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, f2), BitBoard({f3, f4}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn2_OneOrTwoRanksStepPossibleFromSeventhRankForBlack)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({d7, h7});
        a.pieces[King] = BitBoard(e1);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, b7), BitBoard(EmptyBB));  // No pawn in b7
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, d7), BitBoard({d6, d5}));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, h7), BitBoard({h6, h5}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn3_FromRankDifferentFromStartWithBlockingPieceOfTheSameArmy_WhiteCase)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard(d3);
        a.pieces[King] = BitBoard(d4);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, d3), BitBoard(EmptyBB));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn3_FromRankDifferentFromStartWithBlockingPieceOfTheSameArmy_BlackCase)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard(g5);
        a.pieces[King] = BitBoard(g4);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, g5), BitBoard(EmptyBB));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn4_FromStartRankWithBlockingPieceOfTheSameArmy_WhiteCase)
    {
        Army a{};
        a.color = WhiteArmy;
        a.pieces[Pawn] = BitBoard({b2, g2, h2});
        a.pieces[King] = BitBoard(b3);
        a.pieces[Knight] = BitBoard(g4);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, b2), BitBoard(EmptyBB));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, g2), BitBoard(g3));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, h2), BitBoard({h3, h4}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn4_FromStartRankWithBlockingPieceOfTheSameArmy_BlackCase)
    {
        Army a{};
        a.color = BlackArmy;
        a.pieces[Pawn] = BitBoard({a7, b7, e7});
        a.pieces[King] = BitBoard(a6);
        a.pieces[Knight] = BitBoard(b5);
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, a7), BitBoard(EmptyBB));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, b7), BitBoard(b6));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, e7), BitBoard({e6, e5}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn5_FromNonStartRankWithBlockingPieceOfTheOppositeArmy_WhiteCase)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard({c3, g7});
        w.pieces[King] = BitBoard(g1);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, c3), BitBoard(c4));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, g7), BitBoard(g8));
        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard(c4);
        b.pieces[King] = BitBoard(g8);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, c3, b.occupiedCells()), BitBoard(EmptyBB));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, g7, b.occupiedCells()), BitBoard(EmptyBB));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn5_FromNonStartRankWithBlockingPieceOfTheOppositeArmy_BlackCase)
    {
        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard({c5, f3});
        b.pieces[King] = BitBoard(g8);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, c5), BitBoard(c4));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, f3), BitBoard(f2));
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard(c4);
        w.pieces[King] = BitBoard(f2);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, c4, w.occupiedCells()), BitBoard(EmptyBB));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, f3, w.occupiedCells()), BitBoard(EmptyBB));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn6_FromStartRankWithBlockingPieceOfTheOppositeArmy_WhiteCase)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard({b2, e2, h2});
        w.pieces[King] = BitBoard(g1);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, b2), BitBoard({b3, b4}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, e2), BitBoard({e3, e4}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, h2), BitBoard({h3, h4}));

        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard(e3);
        b.pieces[King] = BitBoard(b4);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, b2, b.occupiedCells()), BitBoard(b3));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, e2, b.occupiedCells()), BitBoard(EmptyBB));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, h2, b.occupiedCells()), BitBoard({h3, h4}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn6_FromStartRankWithBlockingPieceOfTheOppositeArmy_BlackCase)
    {
        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard({b7,d7, h7});
        b.pieces[King] = BitBoard(g8);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, b7), BitBoard({b6, b5}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, d7), BitBoard({d6, d5}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, h7), BitBoard({h6, h5}));

        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard(b6);
        w.pieces[King] = BitBoard(d5);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, b7, w.occupiedCells()), BitBoard({EmptyBB}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, d7, w.occupiedCells()), BitBoard(d6));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, h7, w.occupiedCells()), BitBoard({h6, h5}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn7_FromNonStartLineWithEnemyToCaptureOnOneSide)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard(d4);
        w.pieces[King] = BitBoard(c5);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, d4), BitBoard(d5));

        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard(e5);
        b.pieces[King] = BitBoard(e6);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, e5), BitBoard(e4));

        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, d4, b.occupiedCells()), BitBoard({d5, e5}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, e5, w.occupiedCells()), BitBoard({e4, d4}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn7_FromNonStartLineWithEnemyToCaptureOnBothSides)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard(b5);
        w.pieces[King] = BitBoard(b4);
        w.pieces[Queen] = BitBoard(d5);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, b5), BitBoard(b6));

        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard(c6);
        b.pieces[King] = BitBoard(c7);
        b.pieces[Bishop] = BitBoard(a6);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, c6), BitBoard(c5));

        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, b5, b.occupiedCells()), BitBoard({a6, b6, c6}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, c6, w.occupiedCells()), BitBoard({b5, c5, d5}));
    }
    TEST(ArmyTester, CheckPossibleMovesOfPawn7_FromStartLineWithEnemyToCaptureOnBothSides)
    {
        Army w{};
        w.color = WhiteArmy;
        w.pieces[Pawn] = BitBoard({c2, d2, h5});
        w.pieces[King] = BitBoard(e1);
        w.pieces[Knight] = BitBoard({c6, e6});
        w.pieces[Bishop] = BitBoard({c5, e5});
        w.pieces[Rook] = BitBoard({f6, h6});
        w.pieces[Queen] = BitBoard(f5);
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, c2), BitBoard({c3, c4}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, d2), BitBoard({d3, d4}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, h5), BitBoard(EmptyBB));

        Army b{};
        b.color = BlackArmy;
        b.pieces[Pawn] = BitBoard({d7, g7});
        b.pieces[King] = BitBoard(e8);
        b.pieces[Knight] = BitBoard({b3, e3});
        b.pieces[Bishop] = BitBoard(b4);
        b.pieces[Queen] = BitBoard(e4);
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, d7), BitBoard({d6, d5}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, g7), BitBoard({g6, g5}));

        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, c2, b.occupiedCells()), BitBoard({c3, c4, b3}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, d2, b.occupiedCells()), BitBoard({d3, d4, e3}));
        ASSERT_EQ(w.possibleMovesCellsByPieceTypeAndPosition(Pawn, h5, b.occupiedCells()), BitBoard(EmptyBB));

        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, d7, w.occupiedCells()), BitBoard({d6, d5, c6, e6}));
        ASSERT_EQ(b.possibleMovesCellsByPieceTypeAndPosition(Pawn, g7, w.occupiedCells()), BitBoard({g6, g5, f6, h6}));
    }

    // These tests are mainly added to complete Coverage
    TEST(ArmyTester, IfArmyColorIsNotSetSinglePawnControllingCellsReturnsEmptyBB)
    {
        Army a{};
        a.pieces[Pawn] = BitBoard({c2, d2, h5});
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, c2), BitBoard(EmptyBB));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, d2), BitBoard(EmptyBB));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(Pawn, h5), BitBoard(EmptyBB));

    }

    TEST(ArmyTester, IfInvalidPieceTypeIsSpecifiedPossibleMoveCellReturnsEmptyBB)
    {
        Army a{WhiteArmy};
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(InvalidPiece, a1), BitBoard(EmptyBB));
        ASSERT_EQ(a.possibleMovesCellsByPieceTypeAndPosition(static_cast<Piece>(42), a1), BitBoard(EmptyBB));
    }

    // --- Tests for equality operator
    TEST(ArmyTester, WhiteArmyAndBlackArmyAreNotEqual)
    {
        Army w{WhiteArmy};
        Army b{BlackArmy};
        ASSERT_TRUE(w != b);
    }
    TEST(ArmyTester, WhiteAndBlackArmiesAndDefaultArmyAreNotEqual)
    {
        Army w{WhiteArmy};
        Army b{WhiteArmy};
        Army a{};
        ASSERT_TRUE(w != a);
        ASSERT_TRUE(b != a);
    }
    TEST(ArmyTester, WhiteArmiesBuiltInDifferentWaysAreEqual)
    {
        Army w1{WhiteArmy};
        Army w2{};
        w2.color = WhiteArmy;
        w2.pieces[King] = BitBoard(e1);
        w2.pieces[Queen] = BitBoard(d1);
        w2.pieces[Rook] = BitBoard({a1, h1});
        w2.pieces[Knight] = BitBoard({b1, g1});
        w2.pieces[Bishop] = BitBoard({c1, f1});
        w2.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(w1 == w2);
    }
    TEST(ArmyTester, BlackArmiesBuiltInDifferentWaysAreEqual)
    {
        Army b1{BlackArmy};
        Army b2{};
        b2.color = BlackArmy;
        b2.pieces[King] = BitBoard(e8);
        b2.pieces[Queen] = BitBoard(d8);
        b2.pieces[Rook] = BitBoard({a8, h8});
        b2.pieces[Knight] = BitBoard({b8, g8});
        b2.pieces[Bishop] = BitBoard({c8, f8});
        b2.pieces[Pawn] = BitBoard(RanksBB[r_7]);
        ASSERT_TRUE(b1 == b2);
    }
    TEST(ArmyTester, ArmiesWithAKingInDifferentPositionsAreNotEqual)
    {
        Army a{WhiteArmy};
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(e3);  // <---
        b.pieces[Queen] = BitBoard(d1);
        b.pieces[Rook] = BitBoard({a1, h1});
        b.pieces[Knight] = BitBoard({b1, g1});
        b.pieces[Bishop] = BitBoard({c1, f1});
        b.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(a != b);
    }
    TEST(ArmyTester, ArmiesWithAQueenInDifferentPositionsAreNotEqual)
    {
        Army a{WhiteArmy};
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(e1);
        b.pieces[Queen] = BitBoard(g5);  // <---
        b.pieces[Rook] = BitBoard({a1, h1});
        b.pieces[Knight] = BitBoard({b1, g1});
        b.pieces[Bishop] = BitBoard({c1, f1});
        b.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(a != b);
    }
    TEST(ArmyTester, ArmiesWithARookInDifferentPositionsAreNotEqual)
    {
        Army a{WhiteArmy};
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(e1);
        b.pieces[Queen] = BitBoard(d1);
        b.pieces[Rook] = BitBoard({f4, h1}); // <---
        b.pieces[Knight] = BitBoard({b1, g1});
        b.pieces[Bishop] = BitBoard({c1, f1});
        b.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(a != b);
    }
    TEST(ArmyTester, ArmiesWithAKnightInDifferentPositionsAreNotEqual)
    {
        Army a{WhiteArmy};
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(e1);
        b.pieces[Queen] = BitBoard(d1);
        b.pieces[Rook] = BitBoard({a1, h1});
        b.pieces[Knight] = BitBoard({b1, f3}); // <---
        b.pieces[Bishop] = BitBoard({c1, f1});
        b.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(a != b);
    }
    TEST(ArmyTester, ArmiesWithABishopInDifferentPositionsAreNotEqual)
    {
        Army a{WhiteArmy};
        Army b{};
        b.color = WhiteArmy;
        b.pieces[King] = BitBoard(e1);
        b.pieces[Queen] = BitBoard(d1);
        b.pieces[Rook] = BitBoard({a1, h1});
        b.pieces[Knight] = BitBoard({b1, g1});
        b.pieces[Bishop] = BitBoard({h6, f1}); // <---
        b.pieces[Pawn] = BitBoard(RanksBB[r_2]);
        ASSERT_TRUE(a != b);
    }
    TEST(ArmyTester, ArmiesWithAPawnInDifferentPositionsAreNotEqual)
    {
        Army a{BlackArmy};
        Army b{};
        b.color = BlackArmy;
        b.pieces[King] = BitBoard(e8);
        b.pieces[Queen] = BitBoard(d8);
        b.pieces[Rook] = BitBoard({a8, h8});
        b.pieces[Knight] = BitBoard({b8, g8});
        b.pieces[Bishop] = BitBoard({c8, f8});
        b.pieces[Pawn] = BitBoard({a7, b7, c7, d7, e7, f7, g7, h7});
        ASSERT_TRUE(a == b);
        b.pieces[Pawn] = BitBoard({a7, b7, c7, d5, e7, f7, g7, h7});
        ASSERT_TRUE(a != b);
        a.pieces[Pawn] = BitBoard({a7, b7, c7, d5, e7, f7, g7, h7});
        ASSERT_TRUE(a == b);
    }

} // namespace cSzd
