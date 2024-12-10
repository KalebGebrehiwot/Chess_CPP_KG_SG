echo "Compiling the chess program ..."
g++ `fltk-config --cxxflags` -std=c++11 -o ../Chess Chess.cpp `fltk-config --ldflags` -lfltk_images
echo "Done: launcher placed in parent directory."
cd ..
./Chess