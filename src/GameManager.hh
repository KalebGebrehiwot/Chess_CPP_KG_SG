#ifndef GAMEMANAGER_HH__
#define GAMEMANAGER_HH__

#include "Board.hh"
#include "Moves.hh"
#include "Point.hh"
#include "BoardWindow.hh"
#include "ManagerClass.hh"

#include <FL/Fl.H>
#include <vector>
namespace KS{
    class GameManager : ManagerClass{
        public:

            GameManager():
            boardWin({100,100}, {1200, 850}, "Chess", this),
            currentBoard(Board()),
            aMoves(),
            capturedPieces(){
                boardWin.show();
                
            }
            void UpdateWindow(){     
                boardWin.UpdateBoard(currentBoard,aMoves, capturedPieces);
            }
            void getInput(const AUGL::Point& point){
                if(50 < point.x && point.x < 800 && 0 < point.y && point.y < 800){
                    int index = screenPoint_toIndex(point);
                    std::cout << index;
                    currentBoard.setup[index] = 0;
                    UpdateWindow();
                }
                
            }
        private:
            BoardWindow boardWin;
            Board currentBoard;
            AvailableMoves aMoves;
            std::vector<int> capturedPieces;
    }; 
    //
    int screenPoint_toIndex(const AUGL::Point& point){
        int x = std::floor(point.x / 100);
        int y = std::floor(point.y / 100);
        return x + y;
    }


}

#endif