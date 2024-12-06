#ifndef MOVES_HH__
#define MOVES_HH__

#include "Board.hh"

#include <iostream>
#include <vector>

namespace KS{
    struct Move{
        int from, to;
        int pieceType;
        MoveType mt;

        /// @return The algebraic representation of the move.
        std::string toString(){

        }
    };
    enum MoveType{
        norm,
        capture,
        check,
        castle,
        promotion,
        check,
        checkMate
    };

    /// @brief Make a move on the given board and add to the MoveList
    void MakeMove(int from, int to, Board& b, std::vector<Move> moveList){
        if(b.setup[from] = 0){ return; }

        Move move;
        move.from = from; move.to = to;
        move.mt = (b.setup[to] == 0) ? MoveType::norm : MoveType::capture; // [To-Do] Figure out how to differentiate between movetypes.
        moveList.push_back(move);

        b.setup[to] = b.setup[from];
        b.setup[from] = 0;
    }

}

#endif