#if !defined CSZD_CHESSDEFINES_HEADER
#define CSZD_CHESSDEFINES_HEADER

    enum ArmyColor : unsigned int { WhiteArmy, BlackArmy, InvalidArmy };

    constexpr unsigned int NumPieceTypes = 6;
    enum Piece : unsigned int { King = 0, Queen = 1, Bishop = 2,
                 Knight = 3, Rook = 4 , Pawn = 5, InvalidPiece };

#endif // #if !defined CSZD_CHESSDEFINES_HEADER
