#ifndef GAMEMANAGER_HH__
#define GAMEMANAGER_HH__

#include "Board.hh"
#include "Moves.hh"
#include "Point.hh"
#include "MainMenu.hh"
#include "BoardWindow.hh"
#include "ManagerClass.hh"

#include <FL/Fl.H>
#include <vector>
namespace KS{
    
    int screenPoint_toIndex(const AUGL::Point& point){
        int x = std::floor((point.x - 50) / 100);
        int y = 8 * std::floor(point.y / 100);
        return x + y;
    }
    class GameManager : ManagerClass{
        public:

            GameManager():
            menuWin({100,100}, {500, 600}, "Chess Menu", this),
            boardWin({100,100}, {1200, 850}, "Chess", this),
            currentBoard(Board()),
            aMoves(),
            capturedPieces(){
                menuWin.show();
                populateNumToEdges();
                
            }

            void startGame(){
                menuWin.hide();
                boardWin.show();
                UpdateWindow();
            }

            void UpdateWindow(){     
                boardWin.UpdateBoard(currentBoard,aMoves, capturedPieces);
            }
            void getInput(const AUGL::Point& point){
                if(50 < point.x && point.x < 850 && 0 < point.y && point.y < 800){

                    int index = screenPoint_toIndex(point);
                    if(aMoves.available[index]){
                        // Handle making a move
                        if(currentBoard.setup[index] != 0){capturedPieces.push_back(currentBoard.setup[index]);}
                        currentBoard.setup[index] = currentBoard.setup[selectedIndex];
                        currentBoard.setup[selectedIndex] = 0;
                        aMoves.clear();
                        selectedIndex = -1;
                        whiteTurn = !whiteTurn;     
                    }else if(isColor(currentBoard.setup[index], (whiteTurn) ? WHITE : BLACK)){
                        // Handle displaying available moves
                        aMoves.Update(currentBoard.setup[index], index, currentBoard);
                        selectedIndex = index;
                    }else{
                        // Empty square clicked
                        aMoves.clear();
                    }
                    UpdateWindow();
                    boardWin.redraw();
                }

            }
        private:
            MainMenu menuWin;
            BoardWindow boardWin;
            Board currentBoard;
            AvailableMoves aMoves;
            std::vector<int> capturedPieces;
            bool whiteTurn = true;
            
            int selectedIndex = -1;
    };

    


}

#endif