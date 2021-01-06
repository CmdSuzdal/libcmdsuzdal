#include "cmdsuzdal/army.h"

namespace cSzd
{

    // --------------------------------------------------------
    Army::Army(ArmyColor c)
    {
        switch (c) {
            case WhiteArmy:
                color = WhiteArmy;
                pieces[King].setCell(e1);
                pieces[Queen].setCell(d1);
                pieces[Pawn] = BitBoard(RanksBB[r_2]);
                pieces[Bishop] = BitBoard({c1, f1});
                pieces[Knight] = BitBoard({b1, g1});
                pieces[Rook] = BitBoard({a1, h1});
                break;
            case BlackArmy:
                color = BlackArmy;
                pieces[King].setCell(e8);
                pieces[Queen].setCell(d8);
                pieces[Pawn] = BitBoard(RanksBB[r_7]);
                pieces[Bishop] = BitBoard({c8, f8});
                pieces[Knight] = BitBoard({b8, g8});
                pieces[Rook] = BitBoard({a8, h8});
                break;
            default:
                // invalid army.... init empty
                // FIXME: maybe an exception shall be generated?
                break;
        }
    }

    // --------------------------------------------------------
    unsigned int Army::numPieces() const
    {
        return  pieces[King].popCount()    +
                pieces[Queen].popCount()   +
                pieces[Pawn].popCount()    +
                pieces[Bishop].popCount()  +
                pieces[Knight].popCount()  +
                pieces[Rook].popCount();
    }

    // --------------------------------------------------------
    BitBoard Army::occupiedCells() const
    {
        return  pieces[King]    |
                pieces[Queen]   |
                pieces[Pawn]    |
                pieces[Bishop]  |
                pieces[Knight]  |
                pieces[Rook];
    }

    // Return the Piece type occupying the specified cell. If no
    // piece is occupying the cell, InvalidPiece is returned
    Piece Army::getPieceInCell(Cell c) const
    {
        BitBoard bb{c};
        int pieceNdx;
        for (pieceNdx = King; pieceNdx < InvalidPiece; pieceNdx++) {
            if (pieces[pieceNdx] & bb)
                break;
        }
        return static_cast<Piece>(pieceNdx);
    }

    Cell Army::getKingPosition() const
    {
        // Returns the position of the King of the Army. Note that the king is
        // the only piece type for which a method like this makes sense,
        // because it is the only piece type that has always a popCount() of 1
        return pieces[King].activeCell();
    }

    // --------------------------------------------------------
    // The interference board is provided to add a set of cell occupied by some
    // other pieces. This can further limit the view of the current army pieces.
    // The normal use of the interference board is to pass the position of the
    // pieces of the enemy army (see the ChessBoard class).
    // The interference board is not passed to pawns, king and knigths because
    // the cells controlled by these pieces are not effected to interference
    BitBoard Army::controlledCells(const BitBoard &intfBoard) const
    {
        return pawnsControlledCells() |
               knightsControlledCells(intfBoard) |
               bishopsControlledCells(intfBoard) |
               rooksControlledCells(intfBoard) |
               queensControlledCells(intfBoard) |
               kingControlledCells();
    }

    BitBoard Army::controlledCellsByPieceType(Piece pType, const BitBoard &intfBoard) const
    {
        switch (pType) {
            case King:
                return kingControlledCells();
                break;
            case Queen:
                return queensControlledCells(intfBoard);
                break;
            case Rook:
                return rooksControlledCells(intfBoard);
                break;
            case Bishop:
                return bishopsControlledCells(intfBoard);
                break;
            case Knight:
                return knightsControlledCells(intfBoard);
                break;
            case Pawn:
                return pawnsControlledCells();
                break;
            default:
                break;
        }
        return BitBoard(EmptyBB);
    }

    // ---------------------------------------------------------------
    // Returns a BitBoard with the cells controlled by the king of the army
    BitBoard Army::kingControlledCells() const
    {
        // The cell controlled by the king are the neighbour cells.
        // No check of cells occupancy by friends or foes is necessary
        return pieces[King].neighbourCells();
    }

    // Returns a BitBoard with the cells controlled by all the pawns of the army
    BitBoard Army::pawnsControlledCells() const
    {
        // The cell controlled by pawns are the front left and front right
        // of each pawn. Front is north for white army, and south for black
        BitBoard bb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < pieces[Pawn].popCount()); ndx++) {
            if (pieces[Pawn][ndx] != 0) {
                // pawn in position ndx
                foundCells++;
                bb |= singlePawnControlledCells(static_cast<Cell>(ndx));
            }
        }
        return bb;
    }
    // Returns the cell controlled by a pawn in the given position
    // N.B. This function does not check for presence of the pawn
    // in that position, so the caller knows what it is doing...
    BitBoard Army::singlePawnControlledCells(Cell nPos) const
    {
        if (color == WhiteArmy) {
            return BitBoard({ne(nPos), nw(nPos)});
        }
        else if (color == BlackArmy) {
            return BitBoard({se(nPos), sw(nPos)});
        }
        return BitBoard(EmptyBB);
    }

    // Returns a BitBoard with the cells controlled by the knights of the army
    BitBoard Army::knightsControlledCells(const BitBoard &intfBoard) const
    {
        BitBoard bb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < pieces[Knight].popCount()); ndx++) {
            if (pieces[Knight][ndx] != 0) {
                // knight in position ndx
                foundCells++;
                // FIXME --- This can be do probably better using the BitBoard shift functions
                Cell c = static_cast<const Cell>(ndx);
                bb |= BitBoard({calcCellAfterSteps(c,  2,  1),
                                calcCellAfterSteps(c,  1,  2),
                                calcCellAfterSteps(c, -1,  2),
                                calcCellAfterSteps(c, -2,  1),
                                calcCellAfterSteps(c, -2, -1),
                                calcCellAfterSteps(c, -1, -2),
                                calcCellAfterSteps(c,  1, -2),
                                calcCellAfterSteps(c,  2, -1)});
            }
        }
        return bb;
    }

    // Returns a BitBoard with the cells controlled by the bishops of the army
    // The interference board is provided to add a set of cell occupied by some
    // other pieces. This can further limit the view of the current army pieces.
    // The normal use of the interference board is to pass the position of the
    // pieces of the enemy army (see the ChessBoard class)
    BitBoard Army::bishopsControlledCells(const BitBoard &intfBoard) const
    {
        BitBoard bb;
        BitBoard busyCells = occupiedCells() | intfBoard;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < pieces[Bishop].popCount()); ndx++) {
            if (pieces[Bishop][ndx] != 0) {
                foundCells++;
                auto r = rank(static_cast<Cell>(ndx));
                auto f = file(static_cast<Cell>(ndx));
                // Bishop found in position ndx, (rank r, file f)
                // Eplore left-lower side of the diagonal for controlled
                // cells. The cells are controlled until a busy cell
                // is found: the busy cell is the last controlled one
                int cFile = f - 1;
                int cRank = r - 1;
                while (cFile >= 0 && cRank >= 0) {
                    bb.setCell(static_cast<File>(cFile), static_cast<Rank>(cRank));
                    if (busyCells.isActive(static_cast<File>(cFile), static_cast<Rank>(cRank))) {
                        break;
                    }
                    --cFile;
                    --cRank;
                }
                // Explore the right-upper side of the diagonal (same algo above)
                cFile = f + 1;
                cRank = r + 1;
                while (cFile < 8 && cRank < 8) {
                    bb.setCell(static_cast<File>(cFile), static_cast<Rank>(cRank));
                    if (busyCells.isActive(static_cast<File>(cFile), static_cast<Rank>(cRank))) {
                        break;
                    }
                    ++cFile;
                    ++cRank;
                }
                // Explore the right-lower side of the antidiagonal (same algo above)
                cFile = f + 1;
                cRank = r - 1;
                while (cFile < 8 && cRank >= 0) {
                    bb.setCell(static_cast<File>(cFile), static_cast<Rank>(cRank));
                    if (busyCells.isActive(static_cast<File>(cFile), static_cast<Rank>(cRank))) {
                        break;
                    }
                    ++cFile;
                    --cRank;
                }
                // Explore the left-upper side of the antidiagonal (same algo above)
                cFile = f - 1;
                cRank = r + 1;
                while (cFile >= 0 && cRank < 8) {
                    bb.setCell(static_cast<File>(cFile), static_cast<Rank>(cRank));
                    if (busyCells.isActive(static_cast<File>(cFile), static_cast<Rank>(cRank))) {
                        break;
                    }
                    --cFile;
                    ++cRank;
                }
            }
        }
        return bb;
    }

    // Returns a BitBoard with the cells controlled by the rooks of the army
    // This algorithm take into account occupied cells that can obstruct
    // the rooks "view".
    // The interference board is provided to add a set of cell occupied by some
    // other pieces. This can further limit the view of the current army pieces.
    // The normal use of the interference board is to pass the position of the
    // pieces of the enemy army (see the ChessBoard class)
    BitBoard Army::rooksControlledCells(const BitBoard &intfBoard) const
    {
        BitBoard bb;
        BitBoard busyCells = occupiedCells() | intfBoard;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < pieces[Rook].popCount()); ndx++) {
            if (pieces[Rook][ndx] != 0) {
                // rook in position ndx
                foundCells++;
                auto r = rank(static_cast<Cell>(ndx));
                auto f = file(static_cast<Cell>(ndx));
                // Rook found in position ndx, (rank r, file f)

                // Eplore left side of the rank for controlled
                // cells. The cells are controlled until a busy cell
                // is found: the busy cell is the last controlled one
                int cFile = f - 1;
                while (cFile >= 0) {
                    bb.setCell(static_cast<File>(cFile), r);
                    if (busyCells.isActive(static_cast<File>(cFile), r)) {
                        break;
                    }
                    --cFile;
                }
                // Explore the right side of the rank (same algo above)
                cFile = f + 1;
                while (cFile < 8) {
                    bb.setCell(static_cast<File>(cFile), r);
                    if (busyCells.isActive(static_cast<File>(cFile), r)) {
                        break;
                    }
                    ++cFile;
                }
                // Explore the lower side of the file (same algo above)
                int cRank = r - 1;
                while (cRank >= 0) {
                    bb.setCell(f, static_cast<Rank>(cRank));
                    if (busyCells.isActive(f, static_cast<Rank>(cRank))) {
                        break;
                    }
                    --cRank;
                }
                // Explore the upper side of the file (same algo above)
                cRank = r + 1;
                while (cRank < 8) {
                    bb.setCell(f, static_cast<Rank>(cRank));
                    if (busyCells.isActive(f, static_cast<Rank>(cRank))) {
                        break;
                    }
                    ++cRank;
                }
            }
        }
        return bb;
    }

    // Returns a BitBoard with the cells controlled by the queens of the army
    // The interference board is provided to add a set of cell occupied by some
    // other pieces. This can further limit the view of the current army pieces.
    // The normal use of the interference board is to pass the position of the
    // pieces of the enemy army (see the ChessBoard class)
    BitBoard Army::queensControlledCells(const BitBoard &intfBoard) const
    {
        // Cells controlled by Queens is the union of the cells
        // controlled by rooks and bishops in the same position
        // of the queens. The code below is quite tricky... we have
        // to convert bishops and rooks in pawn to mantain interference
        // and avoid to signal wrong controlled cells
        Army fakeArmy = *this;
        fakeArmy.pieces[Pawn] |= fakeArmy.pieces[Bishop];
        fakeArmy.pieces[Pawn] |= fakeArmy.pieces[Rook];
        fakeArmy.pieces[Bishop] = pieces[Queen];
        fakeArmy.pieces[Rook] = pieces[Queen];
        // IMPORTANT: Please note that we cannot call directly the fakeArmy.controlledCells()
        // method because not only it returns the wrong value in case of comples army
        // with interferences, but also generate an infinite recursion...
        // This is wrong:
        //   return fakeArmy.controlledCells();
        // This is OK:
        return fakeArmy.bishopsControlledCells(intfBoard) |
                fakeArmy.rooksControlledCells(intfBoard);
    }

    BitBoard Army::possibleMovesCellsByPieceTypeAndPosition(Piece pType,
                                        Cell c, const BitBoard &intfBoard) const
    {
        switch (pType) {
            case King:
                return kingPossibleMovesCells();
                break;
            case Queen:
                return queenPossibleMovesCells(c, intfBoard);
                break;
            case Rook:
                return rookPossibleMovesCells(c, intfBoard);
                break;
            case Bishop:
                return bishopPossibleMovesCells(c, intfBoard);
                break;
            case Knight:
                return knightPossibleMovesCells(c, intfBoard);
                break;
            case Pawn:
                return pawnPossibleMovesCells(c, intfBoard);
                break;
            default:
                break;
        }
        return BitBoard(EmptyBB);
    }



    BitBoard Army::kingPossibleMovesCells() const
    {
        // The king can move in any of its controlled cells that is not
        // occupied by a piece of its army. As for other pieces we do not
        // checks here for validity of moves (placing the king under check),
        // the "possible moves" functions return the possible moves and not
        // the valid ones. Check for validity shall be done from caller
        return ((kingControlledCells() | occupiedCells()) ^ occupiedCells());
    }

    BitBoard Army::knightPossibleMovesCells(Cell c, const BitBoard &intfBoard) const
    {
        // Returns the bitboard with all the possible
        // moves of the knight in position c
        return piecePossibleMovesCells(Knight, c, intfBoard);
    }

    BitBoard Army::bishopPossibleMovesCells(Cell c, const BitBoard &intfBoard) const
    {
        // Returns the bitboard with all the possible
        // moves of the bishop in position c
        return piecePossibleMovesCells(Bishop, c, intfBoard);
    }

    BitBoard Army::rookPossibleMovesCells(Cell c, const BitBoard &intfBoard) const
    {
        // Returns the bitboard with all the possible
        // moves of a rook in position c
        return piecePossibleMovesCells(Rook, c, intfBoard);
    }

    BitBoard Army::queenPossibleMovesCells(Cell c, const BitBoard &intfBoard) const
    {
        // Returns the bitboard with all the possible
        // moves of a queen in position c
        return piecePossibleMovesCells(Queen, c, intfBoard);
    }

    BitBoard Army::pawnPossibleMovesCells(Cell c, const BitBoard &intfBoard) const
    {
        BitBoard bb {};
        Cell tentativeCell;
        if (!(pieces[Pawn] & BitBoard(c)))
            return bb;

        if (color == WhiteArmy) {
            tentativeCell = static_cast<Cell>(c + 8);
            if (!((occupiedCells() | intfBoard) & BitBoard(tentativeCell))) {
                // the tentative cell is free. Add to the BitBoard of possible moves
                bb.setCell(tentativeCell);
                if (rank(c) == r_2) {
                    tentativeCell = static_cast<Cell>(c + 16);
                    if (!((occupiedCells() | intfBoard) & BitBoard(tentativeCell))) {
                        // the tentative cell is free. Add to the BitBoard of possible moves
                        bb.setCell(tentativeCell);
                    }
                }
            }
        }
        else if (color == BlackArmy) {
            tentativeCell = static_cast<Cell>(c - 8);
            if (!((occupiedCells() | intfBoard) & BitBoard(tentativeCell))) {
                // the tentative cell is free. Add to the BitBoard of possible moves
                bb.setCell(tentativeCell);
                if (rank(c) == r_7) {
                    tentativeCell = static_cast<Cell>(c - 16);
                    if (!((occupiedCells() | intfBoard) & BitBoard(tentativeCell))) {
                        // the tentative cell is free. Add to the BitBoard of possible moves
                        bb.setCell(tentativeCell);
                    }
                }
            }
        }
        bb |= singlePawnControlledCells(c) & intfBoard;
        return bb;
    }

    // --------------------------------------------------------------------------------------------
    BitBoard Army::piecePossibleMovesCells(Piece pType, Cell c, const BitBoard &intfBoard) const
    {
        // Returns the bitboard with all the possible moves of a piece
        // of type pType in position qPos (if the army does not have a piece
        // of that type in this position, empty BB is returned).
        // This functions works only for "normal pieces":
        //   - Knights
        //   - Bishops
        //   - Rooks
        //   - Queens
        if (!(pieces[pType] & BitBoard(c)))
            return BitBoard(EmptyBB);
        Army fakeArmy = *this;
        fakeArmy.pieces[Pawn] |= (pieces[pType] ^ BitBoard(c));
        fakeArmy.pieces[pType] = BitBoard(c);
        return ((fakeArmy.controlledCellsByPieceType(pType, intfBoard) | occupiedCells()) ^ occupiedCells());
    }

    std::ostream &operator<<(std::ostream &os, const Army &a)
    {
        // We want to represent an Army like a Bitboard, with piece symbols
        // instead of the 'x' in the active cells
        // We use "K Q B N R P" for white and "k q b n r p" for black
        //
        // Examples:
        //  - White in initial position:
        //   _ _ _ _ _ _ _ _
        // 8| | | | | | | | |
        // 7| | | | | | | | |
        // 6| | | | | | | | |
        // 5| | | | | | | | |
        // 4| | | | | | | | |
        // 3| | | | | | | | |
        // 2|P|P|P|P|P|P|P|P|
        // 1|R|N|B|Q|K|B|N|R|
        //   a b c d e f g h
        //
        //  - Black in initial position:
        //   _ _ _ _ _ _ _ _
        // 8|r|n|b|q|k|b|n|r|
        // 7|p|p|p|p|p|p|p|p|
        // 6| | | | | | | | |
        // 5| | | | | | | | |
        // 4| | | | | | | | |
        // 3| | | | | | | | |
        // 2| | | | | | | | |
        // 1|_|_|_|_|_|_|_|_|
        //   a b c d e f g h
        //

        os << std::endl << "  _ _ _ _ _ _ _ _";
        auto fillchar = ' ';
        for (auto rank = 7; rank >= 0; rank--) {
            os << std::endl << rank+1 << '|';
            auto startPos = rank * 8;
            if (rank == 0) fillchar = '_';
            for (auto file = 0; file < 8; file++) {
                if (a.color == WhiteArmy) {
                    if (a.pieces[King][startPos + file] != 0)
                       os << 'K' << '|';
                    else if (a.pieces[Queen][startPos + file] != 0)
                       os << 'Q' << '|';
                    else if (a.pieces[Bishop][startPos + file] != 0)
                       os << 'B' << '|';
                    else if (a.pieces[Knight][startPos + file] != 0)
                       os << 'N' << '|';
                    else if (a.pieces[Rook][startPos + file] != 0)
                       os << 'R' << '|';
                    else if (a.pieces[Pawn][startPos + file] != 0)
                       os << 'P' << '|';
                    else
                       os << fillchar << '|';
                }
                else if (a.color == BlackArmy) {
                    if (a.pieces[King][startPos + file] != 0)
                       os << 'k' << '|';
                    else if (a.pieces[Queen][startPos + file] != 0)
                       os << 'q' << '|';
                    else if (a.pieces[Bishop][startPos + file] != 0)
                       os << 'b' << '|';
                    else if (a.pieces[Knight][startPos + file] != 0)
                       os << 'n' << '|';
                    else if (a.pieces[Rook][startPos + file] != 0)
                       os << 'r' << '|';
                    else if (a.pieces[Pawn][startPos + file] != 0)
                       os << 'p' << '|';
                    else
                       os << fillchar << '|';
                }
            }
        }
        os << std::endl << "  a b c d e f g h" << std::endl;
        return os;
    }

} // namespace cSzd