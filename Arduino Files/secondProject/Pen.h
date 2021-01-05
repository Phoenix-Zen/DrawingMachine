/*#ifndef Pen_h
#define Pen_h

#include "Motor.h"

class Pen{
  private:
    int X, Y;
    Motor moteurX, moteurY;
  public:
    Pen(int X, int Y, Motor moteurX, Motor moteurY);
    int getX();
    int getY();
    int setX();
    int setY();
    void setTarget (int x, int y);
    bool reachedTarget();
    void reachTarget();
};
#endif*/
