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
        return true;
        Board boardCopy = board;
        MakeMove(from, from + offset, boardCopy, nullptr);

        bool resultsInCheck = isChecked(Color(piece), boardCopy);
        bool canCapOrOccupy = (board.setup[from + offset] == 0) || !(isColor(board.setup[from + offset], Color(piece)));
    
        return (!resultsInCheck && canCapOrOccupy); 
    }
    // Available moves on the board as booleans
    struct AvailableMoves{
        std::array<bool, 64> available;
        /// @return Available moves to the selected piece
        void Update(int piece, int index, const Board& board){
            for(int i = 0; i<64; i++){
                available[i] = false;
            }

            if(PieceType(piece) == PAWN){
                // int dir = (isColor(piece, WHITE)) ? -1 : 1;
                // // One step forward
                // available[index + 8 * dir] = CanMakeMove(piece, index,8 * dir, board);
                
                // bool hasMoved = (isColor(piece, WHITE)) ? (index > 47) : (index < 16);
                // // Two steps forward
                // available[index + 16 * dir] = !hasMoved && CanMakeMove(piece, index,16 * dir, board);
            
                // checkPos = index + 9 * dir; // Left/Right capture
                // available[checkPos] = CanMakeMove(piece, index,checkPos, board);
            
                // checkPos = index + 7 * dir; // Left/Right capture
                // available[checkPos] = CanMakeMove(piece, index,checkPos, board);

            }else if(PieceType(piece) == KNIGHT){
                for(int offset : knightMoves){
                    if(!CanMakeMove(piece, index,offset, board)){continue;}
                    available[index + offset] = true;
                }
            }else if(PieceType(piece) == BISHOP){
                for(int dir : bishopDirections){
                    for(int i = 1; i < 8; i++){
                        int checkPos = index + dir * i;
                        if(!CanMakeMove(piece, index,checkPos, board)){break;}
                        available[checkPos] = true;
                    }
                }
            }else if(PieceType(piece) == ROOK){
                for(int dir : rookDirections){
                    for(int i = 1; i < 8; i++){
                        int checkPos = index + dir * i;
                        if(!CanMakeMove(piece, index,checkPos, board)){break;}
                        available[checkPos] = true;
                    }
                }
            }else if(PieceType(piece) == QUEEN){
                for(int dir : queenDirections){
                    for(int i = 1; i < 8; i++){
                        int checkPos = index + dir * i;
                        if(!CanMakeMove(piece, index,checkPos, board)){break;}
                        available[checkPos] = true;
                    }
                }
            }else if(PieceType(piece) == KING){
                for(int offset : kingMoves){
                    int checkPos = index + offset;
                    if(!CanMakeMove(piece, index,checkPos, board)){continue;}
                    available[checkPos] = true;
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