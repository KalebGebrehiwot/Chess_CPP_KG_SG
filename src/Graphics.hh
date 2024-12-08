#ifndef GRAPHICS_HH__
#define GRAPHICS_HH__

#include <FL/Fl.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Box.H>

#include "Point.hh"
namespace KS{

        // Piece
    class PieceImage{
        public:
            PieceImage(Fl_PNG_Image *img, const AUGL::Point& initPos) : piece_IMG(img), position(initPos){
                image_Box = new Fl_Box(initPos.x, initPos.y, 100,100);
                image_Box->resize(initPos.x, initPos.y, 100,100);
            }
            void setImage(Fl_PNG_Image *img){
                piece_IMG = img;
            }
            void display(const AUGL::Point& pos){
                image_Box -> position(pos.x, pos.y);
                image_Box -> image(piece_IMG);
                image_Box->resize(pos.x, pos.y, 100,100);
                image_Box -> redraw();
            }
            Fl_Box *getImgBox(){
                return image_Box;
            }
            ~PieceImage(){
                delete image_Box;
            };
        private:
            Fl_PNG_Image *piece_IMG;
            Fl_Box *image_Box;
            AUGL::Point position;
    };

    class ImageBox : public Fl_Box {
        public:
            // Constructor: takes image, position, and size
            ImageBox(int x, int y, int w, int h, const char* label = nullptr) 
                : Fl_Box(x, y, w, h, label), image(nullptr) {}

            // Destructor: clean up the image if necessary
            ~ImageBox() {
                if (image) {
                    delete image;
                }
            }

            // Set the image for the box (e.g., an Fl_PNG_Image)
            void set_image(Fl_PNG_Image* img) {
                if (image) {
                    delete image;  // Delete old image if it exists
                }
                image = img;  // Set new image
                this->redraw();  // Request a redraw
            }

            // Override the draw function to display the image
            void draw() override {
                Fl_Box::draw();  // Call base class's draw function for any default behavior (like border)
                
                if (image) {
                    // Draw the image centered in the box (or adjust positioning as needed)
                    image->draw(x(), y(), w(), h());
                }
            }

        private:
            Fl_PNG_Image* image;  // Pointer to the image (this can be any FLTK image type)
    };

    // Custom widget to draw a square
    class Square : public Fl_Widget {
        public:
            Square(const AUGL::Point& pos, int side, int cIndex) : Fl_Widget(pos.x, pos.y, side, side), colorIndex(cIndex) {}

            void draw() override {
                // Set the color for the square
                fl_color(palette[colorIndex]);
                
                // Draw a square inside the widget area
                fl_rectf(x(), y(), w(), h());  
                // fl_color(palette[colorIndex]);
                // fl_rect(x(), y(), w(), h());  
            }
        private:
            int colorIndex = 0;
            const Fl_Color palette[3] = {FL_BLACK, FL_WHITE, FL_GRAY};
    };
}
    
#endif