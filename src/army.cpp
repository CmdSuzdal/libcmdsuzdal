#include <iostream>
#include "cmdsuzdal/army.h"

namespace cSzd
{

    Army::Army(ArmyColor c)
    {
        switch (c) {
            case WhiteArmy:
                pieces[King].setCell(e1);
                pieces[Pawn] = BitBoard(RanksBB[r_2]);
                break;
            case BlackArmy:
                pieces[King].setCell(e8);
                pieces[Pawn] = BitBoard(RanksBB[r_7]);
                break;
            default:
                // invalid army.... init empty
                // FIXME: maybe an exception shall be generated?
                break;
        }
    }



} // namespace cSzd