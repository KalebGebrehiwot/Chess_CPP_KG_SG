#ifndef MOVES_HH__
#define MOVES_HH__

#include "Board.hh"

#include <array>
#include <iostream>
#include <vector>

namespace KS{
    struct Move{
        int from, to;
        int pieceType;
        //MoveType mt;

        /// @return The algebraic representation of the move.
        std::string toString(){

        }
    };
    /// @brief Make a move on the given board and add to the MoveList
    void MakeMove(int from, int to, Board& board, std::vector<Move>* moveList){
        if(board.setup[from] == 0){ return; }

        Move move;
        move.from = from; move.to = to;
        //move.mt = (board.setup[to] == 0) ? MoveType::norm : MoveType::capture; // [To-Do] Figure out how to differentiate between movetypes.
        if(moveList != nullptr) moveList->push_back(move);

        board.setup[to] = board.setup[from];
        board.setup[from] = 0;
    }

    /// @return True if piece can move to specified position
    bool CanMakeMove(int piece, int from, int offset, const Board& board){
        if(!isOnBoard(from, offset)){return false;}
        Board boardCopy = board;
        boardCopy.setup[from + offset] =  boardCopy.setup[from];
        boardCopy.setup[from] = 0;

        bool resultsInCheck = isChecked(Color(piece), boardCopy);
        bool canCapOrOccupy = (board.setup[from + offset] == 0) || !(isColor(board.setup[from + offset], Color(piece)));
    
        return (!resultsInCheck && canCapOrOccupy); 
    }
    // Available moves on the board as booleans
    struct AvailableMoves{
        std::array<bool, 64> available;

        void clear(){
            for(int i = 0; i<64; i++){
                available[i] = false;
            }
        }
        /// @return Available moves to the selected piece
        void Update(int piece, int index, const Board& board){
            clear();
            
            if(PieceType(piece) == PAWN){
                int enemyColor = (isColor(piece, WHITE)) ? BLACK : WHITE;
                int dir = (isColor(piece, WHITE)) ? -1 : 1;
                // One step forward
                if(CanMakeMove(piece, index, 8 * dir, board) && board.setup[index + 8 * dir] == 0){
                    available[index + 8 * dir] = true;
                }
                bool hasMoved = (isColor(piece, WHITE)) ? (index < 47) : (index > 16);
                // Two steps forward
                if(CanMakeMove(piece, index, 16 * dir, board) && board.setup[index + 8 * dir] == 0 && board.setup[index + 16 * dir] == 0){
                    available[index + 16 * dir] = !hasMoved;
                }
                // Left/Right capture     
                if(numToEdges[index][2] > 0 && isColor(board.setup[index + 9 * dir],enemyColor)&& CanMakeMove(piece, index, 9 * dir, board)){
                    available[index + 9 * dir] = true;
                }
                // Left/Right capture
                if(numToEdges[index][3] > 0 && isColor(board.setup[index + 7 * dir],enemyColor) && CanMakeMove(piece, index, 7 * dir, board)){
                    available[index + 7 * dir] = true;
                }     
            }else if(PieceType(piece) == KNIGHT){
                // Hard coding this for now
                int numLeft = numToEdges[index][2]; 
                int numRight = numToEdges[index][3];
                int numBottom = numToEdges[index][0];
                int numTop = numToEdges[index][1];

                if(CanMakeMove(piece, index, -17, board) && (numLeft > 0 && numTop > 1)){available[index - 17] = true;}
                if(CanMakeMove(piece, index, -15, board) && (numRight > 0 && numTop > 1) ){available[index - 15] = true;}
                if(CanMakeMove(piece, index, -10, board) && (numLeft > 1 && numTop > 0) ){available[index - 10] = true;}
                if(CanMakeMove(piece, index, -6, board) && (numRight > 1 && numTop > 0) ){available[index - 6] = true;}
                if(CanMakeMove(piece, index, 6, board) && (numLeft > 1 && numBottom > 0) ){available[index + 6] = true;}
                if(CanMakeMove(piece, index, 10, board) && (numRight > 1 && numBottom > 0) ){available[index + 10] = true;}
                if(CanMakeMove(piece, index, 15, board) && (numLeft > 0 && numBottom > 1) ){available[index + 15] = true;}
                if(CanMakeMove(piece, index, 17, board) && (numRight > 0 && numBottom > 1) ){available[index + 17] = true;}

            }else if(IsSlidingPiece(piece)){
                int startDirIndex = (PieceType(piece) == BISHOP) ? 4 : 0;
                int endDirIndex = (PieceType(piece) == ROOK) ? 4 : 8;
                
                for(int i = startDirIndex; i < endDirIndex; i++){
                    for(int n = 0; n < numToEdges[index][i]; n++){
                        int targetIndex = index + directions[i] * (n + 1);
                        // Check for friendlies
                        if(isColor(board.setup[targetIndex], Color(piece))){
                            break;
                        }
                        available[targetIndex] = true;
                        // Break on enemy piece
                        if(isColor(board.setup[targetIndex], (isColor(piece, WHITE) ? BLACK : WHITE))){
                            break;
                        }
                    }
                }

            }else if(PieceType(piece) == KING){
                for(int i = 0; i < 8; i++){
                    if(numToEdges[index][i] <= 0 || !CanMakeMove(piece, index,directions[i], board) || isColor(board.setup[index + directions[i]], Color(piece))){continue;}
                    available[index + directions[i]] = true;
                }
            }
        }
    };
    enum MoveType{
        norm,
        capture,   
        castle,
        promotion,
        check,
        checkMate
    };

}

#endif