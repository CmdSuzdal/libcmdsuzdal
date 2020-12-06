#include <iostream>

#include "cmdsuzdal/fenrecord.h"

namespace cSzd
{

    // -------------------------------------------------------------
    // Returns the Piece Placement section of the FEN Record
    const std::string_view FENRecord::piecePlacement() const
    {
        return std::string_view {fen.c_str(), fen.find_first_of(FENDelim)};
    }

    // -------------------------------------------------------------
    // Evaluates if the FEN string represent a valid chess position
    bool FENRecord::isValid() const
    {
        if (extractBitBoard() == BitBoard(EmptyBB)) { return false; }
        return true;
    }

    // -------------------------------------------------------------
    // Returns the bitboard with the placement of the specified pieces
    // For example, if Army = WhiteArmy and Piece = King, returns
    // the bitboard with the position of the white King.
    // If Piece is Invalid (default) the BitBoard of all the pieces of
    // the specified Army is returned, if also the Army is invalid, the
    // BitBoard with all the pieces is returned
    const BitBoard FENRecord::extractBitBoard(ArmyColor c, Piece p) const
    {
        BitBoard bb;
        std::string skipList = "12345678";
        std::string_view pp = piecePlacement();

        // Build the list of pieces to search, depending on arguments
        std::string piecesToSearch = pieceSetFENCharacters(c, p);
        Cell bbCell = a8;
        for (auto c: pp) {
            if (c == '/') {
                // end of rank: restart from previous rank
                bbCell = static_cast<Cell>(bbCell - 16);
            }
            else {
                if (piecesToSearch.find(c) != std::string::npos) {
                    // Found a "target" piece: set the position
                    // in the bitboard
                    bb.setCell(bbCell);
                }
                else if (skipList.find(c) != std::string::npos) {
                    // found empty cell(s), skip them
                    bbCell = static_cast<Cell>(bbCell + (c -'1'));
                }
                bbCell = static_cast<Cell>(bbCell + 1);
            }
        }
        return bb;
    }

    // ----------------------------------------------------------
    // Build a string with the FEN characters of the specified pieces.
    // Used by extractBitBoard()
    const std::string FENRecord::pieceSetFENCharacters(ArmyColor c, Piece p)
    {
        switch (c) {
            case WhiteArmy:
                // searches white army
                switch (p) {
                    case King:
                        return "K";
                        break;
                    case Queen:
                        return "Q";
                        break;
                    case Bishop:
                        return "B";
                        break;
                    case Knight:
                        return "N";
                        break;
                    case Rook:
                        return "R";
                        break;
                    case Pawn:
                        return "P";
                        break;
                    case InvalidPiece:
                        // search all white pieces
                        return "BKNPQR";
                        break;
                    default:
                        // invalid arg, return empty bitboard
                        return "";
                        break;
                }
                break;
            case BlackArmy:
                // searches black army
                switch (p) {
                    case King:
                        return "k";
                        break;
                    case Queen:
                        return "q";
                        break;
                    case Bishop:
                        return "b";
                        break;
                    case Knight:
                        return "n";
                        break;
                    case Rook:
                        return "r";
                        break;
                    case Pawn:
                        return "p";
                        break;
                    case InvalidPiece:
                        // search all black pieces
                        return "bknpqr";
                        break;
                    default:
                        // invalid arg, return empty bitboard
                        return "";
                        break;
                }
                break;
            case InvalidArmy:
                // searches any army
                return "BKNPQRbknpqr";
                break;
            default:
                // invalid arg, return empty bitboard
                return "";
                break;
        }
        return "";
    }

} // namespace cSzd