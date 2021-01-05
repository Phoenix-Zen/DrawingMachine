/*#include "Pen.h"
Pen::Pen(int X, int Y, Motor moteurX, Motor moteurY) {
  this->X = X;
  this->Y = Y;
  this->targetX = X;
  this->targetY = Y;
  this->moteurX = moteurX;
  this->moteurY = moteurY;
}
Pen::getX() {
  return this->X;
}
Pen::getY() {
  return this->Y;
}
Pen::setX(int X) {
  this->X = X;
}
Pen::setY(int Y) {
  this->Y = Y;
}
Pen::setTarget (int x, int y) {
  this->targetX = x;
  this->targetY = y;
}
Pen::reachedTarget(){
  return this->X == this->targetX && this->Y == this->targetY;
}
Pen::reachTarget(){
  if(this->targetX > this->X){
    this->moteurX.marche_av();
    this->X++;
  }else if(this->targetX < X){
    this->moteurX.marche_ar();
    this->X--;
  }
  if(this->targetY > this->Y){
    this->moteurY.marche_av();
    this->Y++;
  }else if(this->targetY < Y){
    this->moteurY.marche_ar();
    this->Y--;
  }
}*/
