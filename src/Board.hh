#ifndef BOARD_HH__
#define BOARD_HH__

#include "Piece.hh"
namespace KS{
    struct Board
    {
        int setup[64];
    };

    /// @return true if the specified color is on check
    bool isChecked(Board& b, int c){
        int kingIndex;
        for(int i = 0; i < 64; i++){
            if(PieceType(b.setup[i]) == KING && isColor(b.setup[i], c)){
                kingIndex = i;
                break;
            }
        }
        
        
    }

    /// @return true if the specified color has possible moves
    bool hasMove(Board& b, int c){

    }

    
}
#endif