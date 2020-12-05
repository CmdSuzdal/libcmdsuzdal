#include <iostream>

#include "cmdsuzdal/fenrecord.h"

namespace cSzd
{
    const std::string_view FENRecord::piecePlacement() const
    {
        return std::string_view {fen.c_str(), fen.find_first_of(FENDelim)};
    }

    const BitBoard FENRecord::extractBitBoard(ArmyColor c, Piece p) const
    {
        BitBoard bb;
        std::string allValidPieces = "BKNPQRbknpqr";
        std::string piecesToSearch = "";
        std::string skipList = "12345678";
        std::string_view pp = piecePlacement();

        // Build the list of pieces to search, depending on arguments
        switch (c) {
            case WhiteArmy:
                // searches white army
                switch (p) {
                    case King:
                        piecesToSearch = "K";
                        break;
                    case Queen:
                        piecesToSearch = "Q";
                        break;
                    case Bishop:
                        piecesToSearch = "B";
                        break;
                    case Knight:
                        piecesToSearch = "N";
                        break;
                    case Rook:
                        piecesToSearch = "R";
                        break;
                    case Pawn:
                        piecesToSearch = "P";
                        break;
                    case InvalidPiece:
                        // search all white pieces
                        piecesToSearch = "BKNPQR";
                        break;
                    default:
                        // invalid arg, return empty bitboard
                        return BitBoard(EmptyBB);
                        break;
                }
                break;
            case BlackArmy:
                // searches black army
                switch (p) {
                    case King:
                        piecesToSearch = "k";
                        break;
                    case Queen:
                        piecesToSearch = "q";
                        break;
                    case Bishop:
                        piecesToSearch = "b";
                        break;
                    case Knight:
                        piecesToSearch = "n";
                        break;
                    case Rook:
                        piecesToSearch = "r";
                        break;
                    case Pawn:
                        piecesToSearch = "p";
                        break;
                    case InvalidPiece:
                        // search all black pieces
                        piecesToSearch = "bknpqr";
                        break;
                    default:
                        // invalid arg, return empty bitboard
                        return BitBoard(EmptyBB);
                        break;
                }
                break;
                break;
            case InvalidArmy:
                // searches any army
                piecesToSearch = "BKNPQRbknpqr";
                break;
            default:
                // invalid arg, return empty bitboard
                return BitBoard(EmptyBB);
                break;
        }

        Cell bbCell = a8;
        for (auto c: pp) {
            if (piecesToSearch.find(c) != std::string::npos) {
                bb.setCell(bbCell);
                bbCell = static_cast<Cell>(bbCell + 1);
            }
            else if (allValidPieces.find(c) != std::string::npos) {
                // all the other valid pieces shall be skipped
                bbCell = static_cast<Cell>(bbCell + 1);
            }
            else if (skipList.find(c) != std::string::npos) {
                unsigned int posToSkip = c - '1' + 1;
                bbCell = static_cast<Cell>(bbCell + posToSkip);
            }
            else if (c == '/') {
                // end of rank: restart from previous rank
                bbCell = static_cast<Cell>(bbCell - 16);
            }
        }
        return bb;
    }

} // namespace cSzd