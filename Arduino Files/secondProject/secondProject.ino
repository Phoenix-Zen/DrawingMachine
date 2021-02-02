#include <SD.h>
/*
   https://www.motedis.fr/shop/Dynamic-unites-lineaire/Courroies-dentees-et-roues-a-dents/Type-GT2-6mm/GT2-poulie-20-dents-al%E9sage-635-mm-pour-courroie-6-mm::999994247.html
   https://www.motedis.fr/shop/Dynamic-unites-lineaire/Roue-interm%E9diaire-pour-courroie-6mm-large::999994523.html
   https://www.motedis.fr/shop/products_filter.php?filter%5B147%5D=461&filter%5B148%5D=468&filter%5B149%5D=-1&master_id=9205
*/

/*
  int IN1 = 3;
  int IN2 = 4;

  int IN3 = 6;
  int IN4 = 7;
*/
int IN1_X = 3;
int IN2_X = 4;
int IN3_X = 6;
int IN4_X = 7;

int IN1_Y = 9;
int IN2_Y = 10;
int IN3_Y = 12;
int IN4_Y = 13;


class Moteur {
  private:
    int IN1, IN2, IN3, IN4, pos;
  public:
    int t, factRed;
    void pos1() {
      digitalWrite(this->IN1, 1);
      digitalWrite(this->IN2, 0);
      digitalWrite(this->IN3, 1);
      digitalWrite(this->IN4, 0);
    }
    void pos2() {
      digitalWrite(this->IN1, 0);
      digitalWrite(this->IN2, 1);
      digitalWrite(this->IN3, 1);
      digitalWrite(this->IN4, 0);
    }
    void pos3() {
      digitalWrite(this->IN1, 0);
      digitalWrite(this->IN2, 1);
      digitalWrite(this->IN3, 0);
      digitalWrite(this->IN4, 1);
    }
    void pos4() {
      digitalWrite(this->IN1, 1);
      digitalWrite(this->IN2, 0);
      digitalWrite(this->IN3, 0);
      digitalWrite(this->IN4, 1);
    }
  public:
    Moteur(int IN1, int IN2, int IN3, int IN4, int t, int factRed) {
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->IN3 = IN3;
      this->IN4 = IN4;
      pinMode(IN1, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN4, OUTPUT);
      this->t = t;
      this->pos = 1;
      this->pos1();
      this->factRed = factRed;
    }
    Moteur() {}
    int getIN1() {
      return this->IN1;
    }
    int getIN2() {
      return this->IN2;
    }
    int getIN3() {
      return this->IN3;
    }
    int getIN4() {
      return this->IN4;
    }
    void definePos() {
      switch (this->pos) {
        case 1:
          this->pos1();
          break;
        case 2:
          this->pos2();
          break;
        case 3:
          this->pos3();
          break;
        case 4:
          this->pos4();
          break;
      }

    }
    void nextPos() {
      this->pos += 1;
      if (this->pos >= 5) {
        this->pos = 1;
      }
    }
    void prevPos() {
      this->pos -= 1;
      if (this->pos <= 0) {
        this->pos = 4;
      }
    }
};
class Pen {
  private:
    int X, Y, targetX, targetY, actual;
    Moteur moteurX, moteurY;
  public:
    Pen(int X, int Y, Moteur moteurX, Moteur moteurY) {
      this->X = X;
      this->Y = Y;
      this->targetX = X;
      this->targetY = Y;
      this->moteurX = moteurX;
      this->moteurY = moteurY;
    }
    int getX() {
      return this->X;
    }
    int getY() {
      return this->Y;
    }
    void setX(int X) {
      this->X = X;
    }
    void setY(int Y) {
      this->Y = Y;
    }
    void setTarget (int x, int y) {
      this->targetX = x;
      this->targetY = y;
    }
    bool reachedTarget() {
      return this->X == this->targetX && this->Y == this->targetY;
    }
    void reachTargetX() {
      if (this->targetX > this->X) {
        this->moteurX.nextPos();
        this->X++;
      } else if (this->targetX < this->X) {
        this->moteurX.prevPos();
        this->X--;
      }
      this->moteurX.definePos();
    }
    void reachTargetY() {
      if (this->targetY > this->Y) {
        this->moteurY.nextPos();
        this->Y++;
      } else if (this->targetY < Y) {
        this->moteurY.prevPos();
        this->Y--;
      }
      this->moteurY.definePos();
    }
    void reach(int x, int y) {
      this->setTarget(int(x * this->moteurX.factRed / 10), int(y * this->moteurY.factRed / 10));
      this->actual = 0;
      while (!this->reachedTarget()) {
        if (this->actual % moteurX.t == 0)
          this->reachTargetX();
        if (this->actual % moteurY.t == 0)
          this->reachTargetY();
        delay(1);
        this->actual += 1;
      }
    }
};
Moteur moteur_y(IN1_Y, IN2_Y, IN3_Y, IN4_Y, 3, 16);
Moteur moteur_x(IN1_X, IN2_X, IN3_X, IN4_X, 3, 25);
Pen pen = Pen(0, 0, moteur_x, moteur_y);

File myFile;

String split(String s, char ctest){
  String r = ""; 
  for(char& c : s){
    if(c != ctest){
      r+=c;
    }else{
      return r;
    }
  }
}
void setup() {
  Serial.begin(9600);
  
  //Xmax = 1300
  //Ymax = 850
  //pen.reach(0, 0);
  delay(1000);
  if (!SD.begin(10)) { //make sure sd card was found
    while(true){
      Serial.println("NO SD DETECTED");
    }
  }
  int fileNumber = 0;
  myFile = SD.open("points"+fileNumber);
  while(myFile){
    myFile.close();
    myFile = SD.open("points"+fileNumber);
    int i1 = -1;
    int i2 = -1;
    int actualNumber = i1;
    char c;
    while(myFile.available() > 1){
      Serial.println(myFile.available());
      c = myFile.read();
      if(c == ' '){
        if(i1 != -1){
          i2 = actualNumber;
          actualNumber = -1;
          //pen.reach(i1, i2);
          /*
          Serial.print("atteind ");
          Serial.print(i1);
          Serial.print(" ");
          Serial.println(i2);*/
          pen.reach(i1, i2);
          i1 = -1;
          i2 = -1;
          actualNumber = -1;
        }
      }
      else if(c == 'n'){
        //soulever le stylo
        //Serial.println("souleve");
      }
      else if(c == ','){
        i1 = actualNumber;
        actualNumber = -1;
      }else{
        if(actualNumber == -1)
          actualNumber=0;
        actualNumber*=10;
        actualNumber+=c - '0';
        if(actualNumber < 1300){
          /*Serial.println(actualNumber);
          Serial.println(c);*/
        }else{
          actualNumber = 0;
        }
      }
    }
  }  

  Serial.println("END");
}

void loop() {
}
