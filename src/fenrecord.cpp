#include <iostream>
#include <sstream>

#include "cmdsuzdal/fenrecord.h"

namespace cSzd
{

    // -------------------------------------------------------------
    FENRecord::FENRecord() : FENRecord(FENInitialStandardPosition) {}

    // -------------------------------------------------------------
    FENRecord::FENRecord(const std::string_view f)
    {
        if (f != "")
            loadPosition(f);
        else
            loadPosition(FENEmptyChessBoard);
    }

    // -------------------------------------------------------------
    void FENRecord::loadPosition(const std::string_view f)
    {
        fen = f;
        activeArmy = InvalidArmy;
        cstlAvail = BitBoard(EmptyBB);
        enPassantCell = BitBoard(EmptyBB);

        // extracts the subfields
        std::istringstream ss(fen);
        std::string fld;

        // pieces placement
        pPlacement = std::string_view {fen.c_str(), fen.find_first_of(FENDelim)};

        // active army
        ss >> fld;  // skip first field
        ss >> fld;
        if (fld == "w") {
            activeArmy = WhiteArmy;
        }
        else if (fld == "b") {
            activeArmy = BlackArmy;
        }

        // castling availability
        ss >> fld;
        if (fld.find('Q') != std::string::npos) {
            cstlAvail.setCell(c1);
        }
        if (fld.find('K') != std::string::npos) {
            cstlAvail.setCell(g1);
        }
        if (fld.find('q') != std::string::npos) {
            cstlAvail.setCell(c8);
        }
        if (fld.find('k') != std::string::npos) {
            cstlAvail.setCell(g8);
        }

        // En passant target cell
        ss >> fld;
        if (fld.size() == 2) {
            // FIXME --- TODO Improve the check!
            enPassantCell.setCell(
                static_cast<File>(fld[0] - 'a'),
                static_cast<Rank>(fld[1] - '1'));
        }

        // half move clock
        ss >> fld;
        // FIXME --- TODO --- Check for exceptions
        hmc = std::stoul(fld);;

        // full move number
        ss >> fld;
        // FIXME --- TODO --- Check for exceptions
        fm = std::stoul(fld);;
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