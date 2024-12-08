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
    // Available moves on the board as booleans
    struct AvailableMoves{
        std::array<bool, 64> available;
    };
    enum MoveType{
        norm,
        capture,   
        castle,
        promotion,
        check,
        checkMate
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
    bool CanMakeMove(int piece, int from, int to, const Board& board){
        if(!isOnBoard(to)){return false;}
        Board boardCopy = board;
        MakeMove(from, to, boardCopy, nullptr);

        bool resultsInCheck = isChecked(Color(piece), boardCopy);
        bool canCapOrOccupy = (board.setup[to] == 0) || !(isColor(board.setup[to], Color(piece)));
    
        return (!resultsInCheck && canCapOrOccupy); 
    }

    /// @return Available moves to the selected piece
    AvailableMoves getAvailableMoves(int piece, int index, const Board& board){
        AvailableMoves aMoves = { static_cast<bool>(new std::array<bool, 64>())};
        for(int i = 0; i<64; i++){
            aMoves.available[i] = false;
        }

        if(PieceType(piece) == PAWN){
            int dir = (isColor(piece, WHITE)) ? -1 : 1;
            int checkPos = index + 8 * dir; // One step forward
            aMoves.available[checkPos] = CanMakeMove(piece, index,checkPos, board);
            
            bool hasMoved = (isColor(piece, WHITE)) ? (index > 47) : (index < 16);
            checkPos = index + 16 * dir; // Two steps forward
            aMoves.available[checkPos] = !hasMoved && CanMakeMove(piece, index,checkPos, board);
          
            checkPos = index + 9 * dir; // Left/Right capture
            aMoves.available[checkPos] = CanMakeMove(piece, index,checkPos, board);
           
            checkPos = index + 7 * dir; // Left/Right capture
            aMoves.available[checkPos] = CanMakeMove(piece, index,checkPos, board);

        }else if(PieceType(piece) == KNIGHT){
            for(int offset : knightMoves){
                int checkPos = index + offset;
                if(!CanMakeMove(piece, index,checkPos, board)){continue;}
                aMoves.available[checkPos] = true;
            }
        }else if(PieceType(piece) == BISHOP){
            for(int dir : bishopDirections){
                for(int i = 1; i < 8; i++){
                    int checkPos = index + dir * i;
                    if(!CanMakeMove(piece, index,checkPos, board)){break;}
                    aMoves.available[checkPos] = true;
                }
            }
        }else if(PieceType(piece) == ROOK){
            for(int dir : rookDirections){
                for(int i = 1; i < 8; i++){
                    int checkPos = index + dir * i;
                    if(!CanMakeMove(piece, index,checkPos, board)){break;}
                    aMoves.available[checkPos] = true;
                }
            }
        }else if(PieceType(piece) == QUEEN){
            for(int dir : queenDirections){
                for(int i = 1; i < 8; i++){
                    int checkPos = index + dir * i;
                    if(!CanMakeMove(piece, index,checkPos, board)){break;}
                    aMoves.available[checkPos] = true;
                }
            }
        }else if(PieceType(piece) == KING){
            for(int offset : kingMoves){
                int checkPos = index + offset;
                if(!CanMakeMove(piece, index,checkPos, board)){continue;}
                aMoves.available[checkPos] = true;
            }
        }

        return aMoves;
    }

    

}

#endif