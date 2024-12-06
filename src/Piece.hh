#ifndef Piece_HH__
#define Piece_HH__

#include <climits>

namespace KS{

    /**
     * @authors Kaleb Gebrehiwot and Sofonias Gebre
     * @brief An bit representation of chess pieces
     */
    const int NONE = 0;
    const int KING = 1;
    const int PAWN = 2;
    const int BISHOP = 3;
    const int KNIGHT = 5;
    const int ROOK = 6;
    const int QUEEN = 7;

    const int WHITE = 8;
    const int BLACK = 16;

    static const int pieceMask = 0b00111;
    static const int whiteMask = 0b01000;
    static const int blackMask = 0b10000;
    static const int colorMask = 0b11000;

    static bool isColor(int piece, int color){
        return (piece & colorMask) == color;
    }

    static int Color(int piece){
        return (piece & colorMask);
    }
    
    static int PieceType(int piece){
        return (piece & pieceMask);
    }

    static bool IsRookOrQueen (int piece) {
        return (piece & 0b110) == 0b110;
    }

    static bool IsBishopOrQueen (int piece) {
        return (piece & 0b101) == 0b101;
    }

    static bool IsSlidingPiece (int piece) {
        return (piece & 0b100) != 0;
    } 
}

#endif