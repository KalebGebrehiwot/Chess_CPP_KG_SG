// For circular dependency issues we were having with the Gamemanger class and the BoardWindow class
#ifndef MANAGERCLASS_HH__
#define MANAGERCLASS_HH__
#include "Point.hh"
class ManagerClass{
    public:
        virtual void getInput(const AUGL::Point& point) = 0;
        virtual void startGame() = 0;
};

#endif