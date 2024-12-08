//#ifndef BOARDWINDOW_HH__
//#define BOARDWINDOW_HH__

#include "Window.hh"
//#include "GUI.hh"
#include "Shapes.hh"

#include "Board.hh"
#include "Moves.hh"

#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <FL/Fl_PNG_Image.H>
/**
 * @author Kaleb Gebrehiwot and Sofonias Gebre
 * @brief This class inherits from the AUGL::Window class and represents the chess board.
 * @date 11/14/2024
 */
class BoardWindow : public AUGL::Window{
    public:

        /*
            To ADD: Object pool for image objects to be pieces and pool of squares to be highlights
                    Look into events to handle click inputs and board updates.
                    
        */

        static const int SQUARE_WIDTH = 100;
        static const int PADDING = 50;

        BoardWindow(AUGL::Point p,const std::string& title):
        Window(p,SQUARE_WIDTH * 8 + 300, PADDING + SQUARE_WIDTH * 8,title){
            // Construct the squares
            std::vector<AUGL::Square> squares;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    AUGL::Square* sq = new AUGL::Square({PADDING + SQUARE_WIDTH * i, SQUARE_WIDTH * j}, SQUARE_WIDTH);
                    sq->setFillColor(((i+j)%2 == 0) ? AUGL::Color::WHITE : AUGL::Color::BLACK);
                    attach(*sq);
                }               
            }
            // Read in the Imgs
            pieceImages.insert(std::make_pair("Pawn_WHITE", new Fl_PNG_Image("Pawn_WHITE.png")));
            pieceImages.insert(std::make_pair("Pawn_BLACK", new Fl_PNG_Image("Pawn_BLACK.png")));
            // Create an Fl_Box to display the image
            Fl_Box image_box(200, 200, 64, 64, nullptr);
            image_box.image(pieceImages["Pawn_WHITE"]);  // Set the image for the box
            image_box.redraw();      // Redraw the box to show the image


        }
        
        int handle(int event) override{
            if(event == FL_PUSH){
                int clickX = Fl::event_x();
                int clickY = Fl::event_y();
                std::cout << clickX << "," << clickY << "\n";
            }
        }

        void UpdateBoard(const KS::Board& board, const KS::AvailableMoves& aMoves){
            
        }
        // need to add destructor
    private:
        std::map<std::string, Fl_PNG_Image*> pieceImages;

};
int main(){
    BoardWindow window({100,100}, "Chess");
    window.show();
    return AUGL::run();
}

//#endif