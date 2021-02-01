#include "cmdsuzdal/chessdefines.h"

namespace cSzd
{
    Piece toPiece(const char &c)
    {
        Piece p = InvalidPiece;
        switch (c) {
            case 'K':
                p = King;
                break;
            case 'Q':
                p = Queen;
                break;
            case 'N':
                p = Knight;
                break;
            case 'R':
                p = Rook;
                break;
            case 'B':
                p = Bishop;
                break;
            default:
                break;
        }
        return p;
    }

} // namespace cSzd
