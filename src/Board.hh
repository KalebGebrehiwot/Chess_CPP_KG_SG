/**
 * A collection of free functions for the functionalities like initializing the board, checking for check, and checking available moves.
 * @author Kaleb Gebrehiwot and Sofonias Gebre
 * @date 12/06/2024
*/
#ifndef BOARD_HH__
#define BOARD_HH__

#include "Point.hh"
#include "Piece.hh"
#include <array>

namespace KS{
    
    // Representation of a chess board as an array of 64 ints. 0 = empty square.
    struct Board{
        std::array<int, 64> setup;

        //Default Constructor 
        Board(){
            for(int i = 0;i < 64; i++){
                setup[i] = 0;
            }
            // White pieces
            setup[56] = ROOK | WHITE;      // A1
            setup[57] = KNIGHT | WHITE;    // B1
            setup[58] = BISHOP | WHITE;    // C1
            setup[59] = QUEEN | WHITE;     // D1
            setup[60] = KING | WHITE;      // E1
            setup[61] = BISHOP | WHITE;    // F1
            setup[62] = KNIGHT | WHITE;    // G1
            setup[63] = ROOK | WHITE;      // H1
            for (int i = 48; i < 56; ++i) setup[i] = PAWN | WHITE;  // White pawns

            // Black pieces
            setup[0] = ROOK | BLACK;     // A8
            setup[1] = KNIGHT | BLACK;   // B8
            setup[2] = BISHOP | BLACK;   // C8
            setup[3] = QUEEN | BLACK;    // D8
            setup[4] = KING | BLACK;     // E8
            setup[5] = BISHOP | BLACK;   // F8
            setup[6] = KNIGHT | BLACK;   // G8
            setup[7] = ROOK | BLACK;     // H8
            for (int i = 8; i < 16; ++i) setup[i] = PAWN | BLACK;  // Black pawns
        }
        // Copy constructors
        Board(const Board& other) = default;
        Board(const std::array<int, 64>& other){
            setup = other;
        }
    };
    
    
    int intCoordinates_toIndex(const AUGL::Point& point){
        int index = point.x + point.y;
        return index;
    }

    AUGL::Point index_toCoordinates(int index){
        AUGL::Point coordinates = {index % 8, index / 8};
        return coordinates;
    }

    bool isOnBoard(int index, int offset){
        int targetIndex = index + offset;
        return !(targetIndex < 0 || targetIndex >= 64);
    }

    /// @return True if the specified color king is checked
    bool isChecked(int color, const Board& board){
        int oppColor = (color == WHITE)? BLACK : WHITE;
        // Find the index of the King
        int kingIndex = 0;
        for(int i = 0; i < 64; i++){
            if(board.setup[i] == (color | KING)){
                kingIndex = i;
                break;
            }
        }
        // Check for opponent pawns
        int oppPawnDir = (color == WHITE) ? -1 : 1; 
        if(isOnBoard(kingIndex, 7 * oppPawnDir) && board.setup[kingIndex + 7 * oppPawnDir] == (oppColor | PAWN)){
            return true;
        }
        if(isOnBoard(kingIndex, 9 * oppPawnDir) && board.setup[kingIndex + 9 * oppPawnDir] == (oppColor | PAWN)){
            return true;
        }
        // Check for knights
        // Again Hard coding this part for now
        // Hard coding this for now
        int numLeft = numToEdges[kingIndex][2]; 
        int numRight = numToEdges[kingIndex][3];
        int numBottom = numToEdges[kingIndex][0];
        int numTop = numToEdges[kingIndex][1];

        if(isOnBoard(kingIndex, -17) && (board.setup[kingIndex - 17] == (KNIGHT | oppColor)) && (numLeft > 0 && numTop > 1)){return true;}
        if(isOnBoard(kingIndex, -15) && (board.setup[kingIndex - 15] == (KNIGHT | oppColor)) && (numRight > 0 && numTop > 1)){return true;}
        if(isOnBoard(kingIndex, -10) && (board.setup[kingIndex - 10] == (KNIGHT | oppColor)) && (numLeft > 1 && numTop > 0)){return true;}
        if(isOnBoard(kingIndex, -6) && (board.setup[kingIndex - 6] == (KNIGHT | oppColor)) && (numRight > 1 && numTop > 0)){return true;}
        if(isOnBoard(kingIndex, 6) && (board.setup[kingIndex + 6] == (KNIGHT | oppColor)) && (numLeft > 1 && numBottom > 0)){return true;}
        if(isOnBoard(kingIndex, 10) && (board.setup[kingIndex + 10] == (KNIGHT | oppColor)) && (numRight > 1 && numBottom > 0)){return true;}
        if(isOnBoard(kingIndex, 15) && (board.setup[kingIndex + 15] == (KNIGHT | oppColor)) && (numLeft > 0 && numBottom > 1)){return true;}
        if(isOnBoard(kingIndex, 17) && (board.setup[kingIndex + 17] == (KNIGHT | oppColor)) && (numRight > 0 && numBottom > 1)){return true;}
   
        // Couldn't figure out checking for checks from other pieces in time

        // Check for sliding pieces
        // for(int i = 0; i < 8; i++){
        //     for(int n = 0; n < numToEdges[kingIndex][i]; n++){
        //         int targetIndex = kingIndex + directions[i] * (n + 1);
        //         if(board.setup[targetIndex] != 0){
        //             if(IsSlidingPiece(targetIndex) && isColor(board.setup[targetIndex], oppColor)){
        //                 std::cout << "Checked by: " << targetIndex << "\n";
        //                 std::cout << "King at " << kingIndex << "\n";
        //                 return true;
        //             }
        //             break;
        //         }
        //     }
        // }
        // Check for opponent King
        // for(int offset : directions){   
        //     int checkPos = kingIndex + offset;
        //     if(isOnBoard(kingIndex, offset) && board.setup[checkPos] == (oppColor | KING)){
        //         return true;
        //     } 
        // }
        // No Checks found
        return false;
    }

}
#endif