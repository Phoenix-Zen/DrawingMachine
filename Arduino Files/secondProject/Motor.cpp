/*#include "Motor.h"
void Motor::setPosition(int val1, int val2, int val3, int val4) {
  digitalWrite(IN1, val1);
  digitalWrite(IN2, val2);
  digitalWrite(IN3, val3);
  digitalWrite(IN4, val4);
}
Motor::setPos(int posVal){
  switch(posVal){
    case 1:
      this->setPosition(HIGH, LOW, HIGH, LOW);
      break;
    case 2:
      this->setPosition(LOW, HIGH, HIGH, LOW);
      break;
    case 3:
      this->setPosition(LOW, HIGH, HIGH, LOW);
      break;
    case 4:
      this->setPosition(LOW, HIGH, LOW, HIGH);
      break;
    default:
      this->setPosition(HIGH, LOW, LOW, HIGH);
      break;
  }
}
Motor::Motor(int IN1, int IN2, int IN3, int IN4, int t) {
  this->IN1 = IN1;
  this->IN2 = IN2;
  this->IN3 = IN3;
  this->IN4 = IN4;
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  this->t = t;
}
Motor::getIN1() {
  return this->IN1;
}
Motor::getIN2() {
  return this->IN2;
}
Motor::getIN3() {
  return this->IN3;
}
Motor::getIN4() {
  return this->IN4;
}
Motor::marche_av(){
  this->setPos(1); delay(t);
  this->setPos(2); delay(t);
  this->setPos(3); delay(t);
  this->setPos(4); delay(t);
}
void marche_ar(){
  this->setPos(4); delay(t);
  this->setPos(3); delay(t);
  this->setPos(2); delay(t);
  this->setPos(1); delay(t);
}*/
