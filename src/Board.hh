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

        // Copy constructors
        Board(const Board& other){
            setup = other.setup;
        }
        Board(std::array<int, 64>& other){
            setup = other;
        }
    };

    // Starting setup of a chess board
    std::array<int, 64> initBoard() {
        std::array<int, 64> board;
        // White pieces
        board[0] = ROOK | WHITE;      // A1
        board[1] = KNIGHT | WHITE;    // B1
        board[2] = BISHOP | WHITE;    // C1
        board[3] = QUEEN | WHITE;     // D1
        board[4] = KING | WHITE;      // E1
        board[5] = BISHOP | WHITE;    // F1
        board[6] = KNIGHT | WHITE;    // G1
        board[7] = ROOK | WHITE;      // H1
        for (int i = 8; i < 16; ++i) board[i] = PAWN | WHITE;  // White pawns

        // Black pieces
        board[56] = ROOK | BLACK;     // A8
        board[57] = KNIGHT | BLACK;   // B8
        board[58] = BISHOP | BLACK;   // C8
        board[59] = QUEEN | BLACK;    // D8
        board[60] = KING | BLACK;     // E8
        board[61] = BISHOP | BLACK;   // F8
        board[62] = KNIGHT | BLACK;   // G8
        board[63] = ROOK | BLACK;     // H8
        for (int i = 48; i < 56; ++i) board[i] = PAWN | BLACK;  // Black pawns
    }
    
    
    int coordinates_toIndex(const AUGL::Point& point){
        int index = point.x + point.y;
        return index;
    }

    AUGL::Point index_toCoordinates(int index){
        AUGL::Point coordinates = {index % 8, index / 8};
        return coordinates;
    }

    bool isOnBoard(int index){
        return 0 < index && index > 64;
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
        if(isOnBoard(kingIndex + 7 * oppPawnDir) && board.setup[kingIndex + 7 * oppPawnDir] == (oppColor | PAWN)){
            return true;
        }
        if(isOnBoard(kingIndex + 9 * oppPawnDir) && board.setup[kingIndex + 9 * oppPawnDir] == (oppColor | PAWN)){
            return true;
        }
        // Check for knights
        for(int offset : knightMoves){
            int checkPos = kingIndex + offset;
            if(isOnBoard(checkPos) && board.setup[checkPos] == (oppColor | KNIGHT)){
                return true;
            }
        }
        // Check for Bishops, or Queens
        for(int dir : bishopDirections){
            for(int i = 1; i < 8; i++){
               int checkPos = kingIndex + dir * i;
               if(!isOnBoard(checkPos) || !IsBishopOrQueen(board.setup[checkPos])) {break;} 
               if(isColor(board.setup[checkPos], oppColor)){
                    return false;
               } 
            }
        }
        // Check for Rooks, or Queens
        for(int dir : rookDirections){
            for(int i = 1; i < 8; i++){
               int checkPos = kingIndex + dir * i;
               if(!isOnBoard(checkPos) || !IsRookOrQueen(board.setup[checkPos])) {break;} 
               if(isColor(board.setup[checkPos], oppColor)){
                    return true;
               } 
            }
        }
        // Check for opponent King
        for(int offset : kingMoves){   
            int checkPos = kingIndex + offset;
            if(isOnBoard(checkPos) && board.setup[checkPos] == (oppColor | KING)){
                return true;
            } 
        }
        // No Checks found
        return false;
    }

}
#endif