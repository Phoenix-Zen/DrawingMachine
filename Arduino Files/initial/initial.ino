
/*
 * https://www.motedis.fr/shop/Dynamic-unites-lineaire/Courroies-dentees-et-roues-a-dents/Type-GT2-6mm/GT2-poulie-20-dents-al%E9sage-635-mm-pour-courroie-6-mm::999994247.html
 * https://www.motedis.fr/shop/Dynamic-unites-lineaire/Roue-interm%E9diaire-pour-courroie-6mm-large::999994523.html
 * https://www.motedis.fr/shop/products_filter.php?filter%5B147%5D=461&filter%5B148%5D=468&filter%5B149%5D=-1&master_id=9205
*/

/*
int IN1 = 3;
int IN2 = 4;
int IN3 = 6;
int IN4 = 7;
*/
int t=2;

int IN1_Y = 9;
int IN2_Y = 10;

int IN3_Y = 12;
int IN4_Y = 13;

int IN1_X = 3;
int IN2_X = 4;

int IN3_X = 6;
int IN4_X = 7;

class Moteur{
  private:
    int IN1, IN2, IN3, IN4;
  public:
    Moteur(int IN1, int IN2, int IN3, int IN4){
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->IN3 = IN3;
      this->IN4 = IN4;
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT); 
    }
    int getIN1(){
      return this->IN1;
    }
    int getIN2(){
      return this->IN2;
    }
    int getIN3(){
      return this->IN3;
    }
    int getIN4(){
      return this->IN4;
    }
};


Moteur moteur_y(IN1_Y, IN2_Y, IN3_Y, IN4_Y);
Moteur moteur_x(IN1_X, IN2_X, IN3_X, IN4_X);

void setup() {
}

void loop() {
  for (int i = 0; i <= 100; i++) {
    marche_av(moteur_x);
  }
  for (int i = 0; i <= 100; i++) {
    marche_ar(moteur_x);
  }
  for (int i = 0; i <= 100; i++) {
    marche_av(moteur_y);
  }
  for (int i = 0; i <= 100; i++) {
    marche_ar(moteur_y);
  }
}


void marche_av(Moteur m){
  pos1(m);
  pos2(m);
  pos3(m);
  pos4(m);
}
void marche_ar(Moteur m){
  pos4(m);
  pos3(m);
  pos2(m);
  pos1(m);
}

void pos1(Moteur moteur){
digitalWrite(moteur.getIN1(),HIGH);
digitalWrite(moteur.getIN2(),LOW);
digitalWrite(moteur.getIN3(),HIGH);
digitalWrite(moteur.getIN4(),LOW);
 delay(t);
}
void pos2(Moteur moteur){
digitalWrite(moteur.getIN1(),LOW);
digitalWrite(moteur.getIN2(),HIGH);
digitalWrite(moteur.getIN3(),HIGH);
digitalWrite(moteur.getIN4(),LOW);
 delay(t);
}
void pos3(Moteur moteur){
digitalWrite(moteur.getIN1(),LOW);
digitalWrite(moteur.getIN2(),HIGH);
digitalWrite(moteur.getIN3(),LOW);
digitalWrite(moteur.getIN4(),HIGH);
 delay(t);
}
void pos4(Moteur moteur){
  digitalWrite(moteur.getIN1(),HIGH);
  digitalWrite(moteur.getIN2(),LOW);
  digitalWrite(moteur.getIN3(),LOW);
  digitalWrite(moteur.getIN4(),HIGH);
  delay(t);
}
