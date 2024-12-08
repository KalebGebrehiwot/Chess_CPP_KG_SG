/**
 * @authors Kaleb Gebrehiwot and Sofonias Gebre
 * @brief An bit representation of chess pieces
 *        and other helper functions.
 */
#ifndef Piece_HH__
#define Piece_HH__

#include "Point.hh"

#include <FL/Fl_PNG_Image.H>

#include <climits>
#include <array>

namespace KS{

    
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

    // ---------- Move Rules --------------

    // Figured hard coding these values for pawns would result in less code
    //std::array<int, 4> whitePawnMoves = {-8,-16,-7,-9};
    //std::array<int, 4> blackPawnMoves = {8,16,7,9};

    std::array<int, 8> knightMoves = {-17, -15, -10, -6, 6, 10, 15, 17};
    std::array<int, 8> kingMoves = {-9, -8, -7, -1, 1, 7, 8, 9};
    
    std::array<int, 4> rookDirections = {-1, 1, -8, 8};
    std::array<int, 4> bishopDirections = {-9, 9, -7, 7};
    std::array<int, 8> queenDirections = {-1, 1, -8, 8, -9, 9, -7, 7};

    // -------------- GUI -------------------

    class PieceGUI{
        public:
            PieceGUI(Fl_PNG_Image *img, const AUGL::Point& initPos) : piece_IMG(img), position(initPos){
            
            }

            void setPosition(const AUGL::Point& newPos){
                position = newPos;
            }
            void setImage(Fl_PNG_Image *img){
                piece_IMG = img;
            }

            ~PieceGUI(){};
        private:
            Fl_PNG_Image *piece_IMG;
            AUGL::Point position;
    };

}

#endif