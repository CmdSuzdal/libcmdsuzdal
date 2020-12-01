#include <iostream>
#include "cmdsuzdal/army.h"

namespace cSzd
{

    Army::Army(ArmyColor c)
    {
        switch (c) {
            case WhiteArmy:
                king.setCell(e1);
                pawns = BitBoard(RanksBB[r_2]);
                break;
            case BlackArmy:
                king.setCell(e8);
                pawns = BitBoard(RanksBB[r_7]);
                break;
            default:
                // invalid army.... init empty
                // FIXME: maybe an exception shall be generated?
                break;
        }
    }



} // namespace cSzd