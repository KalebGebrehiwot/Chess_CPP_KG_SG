#ifndef MANAGERCLASS_HH__
#define MANAGERCLASS_HH__
#include "Point.hh"
class ManagerClass{
    public:
        virtual void getInput(const AUGL::Point& point) = 0;
};

#endif