/**
 * @authors Kaleb Gebrehiwot and Sofonias Gebre
 * @brief An bit representation of chess pieces
 *        and other helper functions.
 */
#ifndef Piece_HH__
#define Piece_HH__

#include <cmath>
#include <map>
#include <climits>
#include <array>

namespace KS{

    
    const int NONE = 0;
    const int KING = 1;
    const int PAWN = 2;
    const int KNIGHT = 3;
    const int BISHOP = 4;
    const int ROOK = 5;
    const int QUEEN = 6;

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
        return PieceType(piece) == BISHOP || PieceType(piece) == ROOK || PieceType(piece) == QUEEN;
    } 
    // ---------- Move Rules --------------

    // Hard coding knight moves for now
    //const std::array<int, 8> knightMoves = {-17, -15, -10, -6, 6, 10, 15, 17};
    const std::array<int, 8> directions = { 8, -8, -1, 1, 7, -7, 9, -9};
    std::array<std::array<int, 8>, 8> numToEdges;

    void populateNumToEdges(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){

                int numNorth = 7 - j;
                int numSouth = j;
                int numWest = i;
                int numEast = 7 - i;

                int squareIndex = j * 8 + i;
                numToEdges[squareIndex] = {
                    numNorth,
                    numSouth,
                    numWest,
                    numEast,
                    std::min(numNorth, numWest),
                    std::min(numSouth, numEast),
                    std::min(numNorth, numEast),
                    std::min(numSouth, numWest)
                };
            }
        }
    }
}

#endif