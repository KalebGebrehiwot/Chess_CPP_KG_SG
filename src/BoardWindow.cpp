#ifndef BOARDWINDOW_HH__
#define BOARDWINDOW_HH__

#include "Board.hh"
#include "Moves.hh"
#include "Piece.hh"
#include "Graphics.hh"
#include "GameManager.hh"

#include <cmath>
#include <map>
#include <vector>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_PNG_Image.H>

/**
 * @author Kaleb Gebrehiwot and Sofonias Gebre
 * @brief
 * @date 11/14/2024
 */
namespace KS{
    class BoardWindow : public Fl_Window{
        public:
            static const int SQUARE_WIDTH = 100;
            static const int PADDING = 50;
            BoardWindow( AUGL::Point pos, AUGL::Point dimension, const std::string& title, GameManager* gameMan)
                : Fl_Window(pos.x, pos.y, dimension.x, dimension.y, title.c_str())
                , gameManager(gameMan)
            {
                // Construct the squares
                std::vector<Square> squares;
                for(int i = 0; i < 8; i++){
                    for(int j = 0; j < 8; j++){
                        Square* sq = new Square({PADDING + SQUARE_WIDTH * i, SQUARE_WIDTH * j}, SQUARE_WIDTH, ((i+j)%2 == 0) ? 0 : 1);
                    }               
                }
                // Read in the Imgs
                piecePNGs.insert(std::make_pair("Pawn_WHITE", new Fl_PNG_Image("assets/Pawn_WHITE.png")));
                piecePNGs.insert(std::make_pair("Pawn_BLACK", new Fl_PNG_Image("assets/Pawn_BLACK.png")));
                piecePNGs.insert(std::make_pair("Knight_WHITE", new Fl_PNG_Image("assets/Knight_WHITE.png")));
                piecePNGs.insert(std::make_pair("Knight_BLACK", new Fl_PNG_Image("assets/Knight_BLACK.png")));
                piecePNGs.insert(std::make_pair("Bishop_WHITE", new Fl_PNG_Image("assets/Bishop_WHITE.png")));
                piecePNGs.insert(std::make_pair("Bishop_BLACK", new Fl_PNG_Image("assets/Bishop_BLACK.png")));
                piecePNGs.insert(std::make_pair("Rook_WHITE", new Fl_PNG_Image("assets/Rook_WHITE.png")));
                piecePNGs.insert(std::make_pair("Rook_BLACK", new Fl_PNG_Image("assets/Rook_BLACK.png")));
                piecePNGs.insert(std::make_pair("Queen_WHITE", new Fl_PNG_Image("assets/Queen_WHITE.png")));
                piecePNGs.insert(std::make_pair("Queen_BLACK", new Fl_PNG_Image("assets/Queen_BLACK.png")));
                piecePNGs.insert(std::make_pair("King_WHITE", new Fl_PNG_Image("assets/King_WHITE.png")));
                piecePNGs.insert(std::make_pair("King_BLACK", new Fl_PNG_Image("assets/King_BLACK.png")));
                // Create PieceImage:Fl_Box to display the Piece Images
                for(int i = 0; i < 32; i++){
                    pieceImages[i] = new PieceImage(piecePNGs["Pawn_WHITE"], {-100, -100});
                }
            }
            /// @brief Handle fltk events like a click 
            int handle(int event) override{
                if(event == FL_PUSH){
                    int clickX = Fl::event_x();
                    int clickY = Fl::event_y();
                    gameManager -> getInput({clickX, clickY});
                }
            }
            /// @brief Update the board visuals to the passed in board setup
            void UpdateBoard(const Board& board, const AvailableMoves& aMoves, const std::vector<int>& capturedPieces){
                int imgCounter = 0;
                for(int i = 0; i < 64; i++){
                    if(board.setup[i] != 0){
                        AUGL::Point coordinates(index_toCoordinates(i));
                        pieceImages[imgCounter]->display({PADDING + SQUARE_WIDTH * coordinates.x, SQUARE_WIDTH * coordinates.y});
                        imgCounter++;
                    }
                }
            }
            // need to add destructor
        private:
            std::map<std::string, Fl_PNG_Image*> piecePNGs;
            std::array<PieceImage*, 32> pieceImages;
            GameManager* gameManager;

    };  
}


#endif