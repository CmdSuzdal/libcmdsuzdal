#if !defined CSZD_CHESSMOVE_HEADER
#define CSZD_CHESSMOVE_HEADER

#include <bitset>
#include "cmdsuzdal/bbdefines.h"
#include "cmdsuzdal/chessdefines.h"

namespace cSzd
{

    // Chess Move. 32-bits wide bitset with the following format:
    //
    //  bits[0..2]   = the moved piece (0..5, cannot be invalid)
    //  bits[3..5]   = in case of opposite army piece taken, the taken piece
    //                 (InvalidPiece if no piece taken)
    //  bits[6..8]   = in case of promotion, the piece chosen after promotion
    //                 (InvalidPiece if no promotion)
    //  bits[9]      = move is a check
    //  bits[10]     = move is a checkmate
    //  bits[11]     = move is a stalemate
    //  bits[12..17] = the start Cell (0...63, cannot be invalid)
    //  bits[18..23] = the destination Cell (0...63, cannot be invalid)
    //  bits[24..30] = the en passant Cell (InvalidCell if no en-passant)
    //  bits[31]     = invalid move flag (1 = invalid)
    //
    //  Examples:
    //    - Pawn e2 to e3
    //      0 1000000 010100 001100 0001 1011 0101 = 0x4050C1B5
    using ChessMove = std::bitset<32>;
    constexpr ChessMove InvalidMove = 0x80000000;

    constexpr unsigned int MovedPieceOffset = 0;
    constexpr unsigned int TakenPieceOffset = 3;
    constexpr unsigned int PromotedPieceOffset = 6;
    constexpr unsigned int CheckFlagOffset = 9;
    constexpr unsigned int CheckMateFlagOffset = 10;
    constexpr unsigned int StaleMateFlagOffset = 11;
    constexpr unsigned int StartCellOffset = 12;
    constexpr unsigned int DestinationCellOffset = 18;
    constexpr unsigned int EnPassantCellOffset = 24;

    constexpr unsigned int PieceMask = 0x0007;
    constexpr unsigned int ValidCellMask = 0x003F;
    constexpr unsigned int ValidAndInvalidCellMask = 0x007F;

    struct CheckCondition {
        bool isCheck;
        bool isMate;
        bool isStale;
    };


    ChessMove chessMove(Piece movedPiece, Cell startCell, Cell destCell,
                        Piece takenPiece = InvalidPiece,
                        Piece promotedPiece = InvalidPiece,
                        const struct CheckCondition &cc = {false, false, false});

    Cell computeEnPassant(Cell from, Cell to);
    inline Piece chessMoveGetMovedPiece(ChessMove cm) { return static_cast<Piece>((cm.to_ullong() >> MovedPieceOffset)  & PieceMask); }
    inline Piece chessMoveGetTakenPiece(ChessMove cm) { return static_cast<Piece>((cm.to_ullong() >> TakenPieceOffset)  & PieceMask); }
    inline Piece chessMoveGetPromotedPiece(ChessMove cm) { return static_cast<Piece>((cm.to_ullong() >> PromotedPieceOffset)  & PieceMask); }
    inline Cell chessMoveGetStartingCell(ChessMove cm) { return static_cast<Cell>((cm.to_ullong() >> StartCellOffset)  & ValidCellMask); }
    inline Cell chessMoveGetDestinationCell(ChessMove cm) { return static_cast<Cell>((cm.to_ullong() >> DestinationCellOffset)  & ValidCellMask); }
    inline Cell chessMoveGetEnPassantCell(ChessMove cm) { return static_cast<Cell>((cm.to_ullong() >> EnPassantCellOffset)  & ValidAndInvalidCellMask); }
    inline bool isACastlingMove(ChessMove cm)
    {
        // It is (maybe) a castling move if moved piece is king and there is one of the following movements:
        //    e1 --> g1 or e1 --> c1 or e8 --> g8 or e8 --> c8
        if ((chessMoveGetMovedPiece(cm) == King) && (
                 (chessMoveGetStartingCell(cm) == e1 &&
                    ((chessMoveGetDestinationCell(cm) == g1) || (chessMoveGetDestinationCell(cm) == c1))) ||
                 (chessMoveGetStartingCell(cm) == e8 &&
                    ((chessMoveGetDestinationCell(cm) == g8) || (chessMoveGetDestinationCell(cm) == c8)))))
            return true;
        return false;
    }

    inline bool chessMoveIsACheck(ChessMove cm) { return static_cast<bool>((cm.to_ullong() >> CheckFlagOffset) & 0x00000001); }
    inline bool chessMoveIsACheckMate(ChessMove cm) { return static_cast<bool>((cm.to_ullong() >> CheckMateFlagOffset) & 0x00000001); }
    inline bool chessMoveIsAStaleMate(ChessMove cm) { return static_cast<bool>((cm.to_ullong() >> StaleMateFlagOffset) & 0x00000001); }

}

#endif // #if !defined CSZD_CHESSMOVE_HEADER
