#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>

// A simple window to display the image
class ImageWindow : public Fl_Window {
public:
    Fl_Box* imageBox;  // Box to display the image
    Fl_PNG_Image* pngImage;  // Image object

    ImageWindow(int w, int h, const char* title = "FLTK Image Viewer")
        : Fl_Window(w, h, title) {
        imageBox = new Fl_Box(20, 20, w - 40, h - 40);
        pngImage = nullptr;
        end();
    }

    // Function to load and display a PNG image
    void loadImage(const char* filename) {
        if (pngImage) {
            delete pngImage;
        }

        pngImage = new Fl_PNG_Image(filename);  // Load PNG image
        if (pngImage->fail()) {
            std::cerr << "Failed to load image: " << filename << std::endl;
            return;
        }

        imageBox->image(pngImage);  // Set the image in the box
        imageBox->redraw();  // Redraw the box to display the image
    }
};

int main() {
    const char* default_image = "image.png"; // Change to your PNG file path

    // Create a window with specified size (e.g., 600x400)
    ImageWindow window(600, 400);

    // Load the image from file
    window.loadImage(default_image);

    // Show the window
    window.show();

    // Run the FLTK event loop
    return Fl::run();
}