#include <FL/Fl.H> 
#include <FL/FL_draw.H> 
#include <FL/FL_Widget.H> 
#include <FL/FL_Window.H> 
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <iostream>

class MainMenu : public Fl_Window {
private:
    Fl_Box *titleBox;        // Box to display the text "CHESS"
    Fl_Button *playButton;    // Button to start local multiplayer
    Fl_Button *quitButton;    // Button to quit

public:
    // Constructor for the Main Menu window
    MainMenu(int width, int height, const char* title) : Fl_Window(width, height, title) {
        // Set window size and title
        this->color(FL_WHITE);  // Set background color

        // Display "CHESS" text in the center of the window
        titleBox = new Fl_Box(FL_FLAT_BOX, 150, 50, width - 300, 100, "CHESS");
        titleBox->labelsize(48);  // Set font size for the text
        //titleBox->labeltype(FL_BOLD);  // Set text to bold
        titleBox->align(FL_ALIGN_CENTER);  // Center the text within the box

        // Play Local Multiplayer Button
        playButton = new Fl_Button(150, 200, 200, 40, "Play Local Multiplayer");
        playButton->callback(playButtonCallback, this);

        // Quit Button
        quitButton = new Fl_Button(150, 270, 200, 40, "Quit");
        quitButton->callback(quitButtonCallback, this);

        // Show the window
        end();
        show();
    }

    // Callback for Play Local Multiplayer button
    static void playButtonCallback(Fl_Widget* widget, void* data) {
        MainMenu* menu = (MainMenu*)data;
        std::cout << "Play Local Multiplayer clicked\n";
        // Here, we can navigate to the game start screen or new window.
  
    }

    // Callback for Quit button
    static void quitButtonCallback(Fl_Widget* widget, void* data) {
        std::cout << "Quit button clicked\n";
        exit(0);  // Quit the application 
    }
};

// Main function to create and run the MainMenu window
int main() {
    MainMenu mainMenu(500, 400, "Chess Game - Main Menu");
    return Fl::run();
}