#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include <string>
#include <iostream>

#include "Piece.hh"

int main() {
    Fl_Window* window = new Fl_Window(480, 480, "Chess Board");

    // Create some chess pieces
    KS::PieceGUI* whitePawn = new KS::PieceGUI(new Fl_PNG_Image("Pawn_WHITE.png"), {100,100});
    KS::PieceGUI* blackPawn = new KS::PieceGUI(new Fl_PNG_Image("Pawn_BLACK.png"), {200,100});

    whitePawn -> display({100,100});
    blackPawn -> display({200,100});
    window->end();
    window->show();
    int testIn;
    std::cin >> testIn;
    whitePawn -> display({100, testIn});
    window->end();
    window->show();
    
    return Fl::run();
}