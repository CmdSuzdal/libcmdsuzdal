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
    BitBoard Army::controlledCells() const
    {
        return pawnsControlledCells() |
               knightsControlledCells() |
               bishopsControlledCells() |
               rooksControlledCells() |
               queensControlledCells() |
               kingControlledCells();
    }

    // ---------------------------------------------------------------
    // Returns a BitBoard with the cells controlled by the king of the army
    BitBoard Army::kingControlledCells() const
    {
        // The cell controlled by the king are the neighbour cells.
        // No check of cells occupancy by friends or foes is necessary
        return pieces[King].neighbourCells();
    }

    // Returns a BitBoard with the cells controlled by the pawns of the army
    BitBoard Army::pawnsControlledCells() const
    {
        // The cell controlled by pawns are the front left and front right
        // of each pawn. Front is north for white army, and south for black
        BitBoard bb;
        auto foundCells = 0;
        for (auto ndx = 0; (ndx < 64) && (foundCells < pieces[Pawn].popCount()); ndx++) {
            if (pieces[Pawn].bbs[ndx] != 0) {
                // pawn in position ndx
                foundCells++;
                if (color == WhiteArmy) {
                    bb |= BitBoard(BitBoard::ne(static_cast<const Cell>(ndx)));
                    bb |= BitBoard(BitBoard::nw(static_cast<const Cell>(ndx)));
                }
                else if (color == BlackArmy) {
                    bb |= BitBoard(BitBoard::se(static_cast<const Cell>(ndx)));
                    bb |= BitBoard(BitBoard::sw(static_cast<const Cell>(ndx)));
                }
            }
        }
        return bb;
    }

    // Returns a BitBoard with the cells controlled by the knights of the army
    BitBoard Army::knightsControlledCells() const
    {
        return BitBoard(EmptyBB);
    }

    // Returns a BitBoard with the cells controlled by the bishops of the army
    BitBoard Army::bishopsControlledCells() const
    {
        return BitBoard(EmptyBB);
    }

    // Returns a BitBoard with the cells controlled by the rooks of the army
    BitBoard Army::rooksControlledCells() const
    {
        return BitBoard(EmptyBB);
    }

    // Returns a BitBoard with the cells controlled by the queens of the army
    BitBoard Army::queensControlledCells() const
    {
        return BitBoard(EmptyBB);
    }

} // namespace cSzd