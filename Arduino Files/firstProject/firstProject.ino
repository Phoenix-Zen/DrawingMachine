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
int t = 2;
int posA[2] = {0, 0};

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
    int IN1, IN2, IN3, IN4;
  public:
    Moteur(int IN1, int IN2, int IN3, int IN4) {
      this->IN1 = IN1;
      this->IN2 = IN2;
      this->IN3 = IN3;
      this->IN4 = IN4;
      pinMode(IN1, OUTPUT);
      pinMode(IN2, OUTPUT);
      pinMode(IN3, OUTPUT);
      pinMode(IN4, OUTPUT);
    }
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
};

class Droite {
  private:
    float m, p; // coeff directeur et ordinnée à l'origine
  public:
    Droite(int a[2], int b[2]) {
      this->m = (b[1] - a[1]) / (b[0] - a[0]);  // m = (yb - yb)/(xb - xa)
      this->p = a[1] - this->m * a[0];  // ya = m*xa + p <=> p = ya - m*xa
    }
    float calc_y(int x) {
      return this->m * x + this->p; // y = mx+p
    }
    float calc_x(int y) {
      return (y - this->p) / this->m; // x = (y - p)/m
    }
};

Moteur moteur_y(IN1_Y, IN2_Y, IN3_Y, IN4_Y);
Moteur moteur_x(IN1_X, IN2_X, IN3_X, IN4_X);

void setup() {
  
}

bool a = true;
int _posB[2] = {100, 150};

void loop() {
  if (a) {
    goTo(_posB);
    a = false;
  }
}


//void marche_av(Moteur m){
//  pos1(m); delay(t);
//  pos2(m); delay(t);
//  pos3(m); delay(t);
//  pos4(m); delay(t);
//}
//void marche_ar(Moteur m){
//  pos4(m); delay(t);
//  pos3(m); delay(t);
//  pos2(m); delay(t);
//  pos1(m); delay(t);
//}

void goTo (int posB[2]) {
  int delta_x = posB[0] - posA[0]; // différence d'abscisse
  int delta_y = posB[1] - posA[1]; // différence d'ordonnée
  Droite d(posA, posB);
  if (delta_x < delta_y) {
    for (int i = 1; i < delta_x; i++) {
      int next_x = posA[0] + i;
      int previous_y = round(d.calc_y(next_x - 1));
      int next_y = round(d.calc_y(next_x));
      rotation(moteur_x, delta_x);
      for (int j = 0; j < next_y - previous_y; j++) { 
        rotation(moteur_y, delta_y);
      }
    }
  } else {
    for (int i = 1; i < delta_y; i++) {
      int next_y = posA[1] + i;
      int previous_x = round(d.calc_x(next_y - 1));
      int next_x = round(d.calc_x(next_y));
      rotation(moteur_y, delta_y);
      for (int j = 0; j < next_x - previous_x; j++) {
        rotation(moteur_x, delta_x);
      }
    }
  }
  posA[2] = posB;
}

void pos1(Moteur moteur) {
  digitalWrite(moteur.getIN1(), HIGH);
  digitalWrite(moteur.getIN2(), LOW);
  digitalWrite(moteur.getIN3(), HIGH);
  digitalWrite(moteur.getIN4(), LOW);
}
void pos2(Moteur moteur) {
  digitalWrite(moteur.getIN1(), LOW);
  digitalWrite(moteur.getIN2(), HIGH);
  digitalWrite(moteur.getIN3(), HIGH);
  digitalWrite(moteur.getIN4(), LOW);
}
void pos3(Moteur moteur) {
  digitalWrite(moteur.getIN1(), LOW);
  digitalWrite(moteur.getIN2(), HIGH);
  digitalWrite(moteur.getIN3(), LOW);
  digitalWrite(moteur.getIN4(), HIGH);
}
void pos4(Moteur moteur) {
  digitalWrite(moteur.getIN1(), HIGH);
  digitalWrite(moteur.getIN2(), LOW);
  digitalWrite(moteur.getIN3(), LOW);
  digitalWrite(moteur.getIN4(), HIGH);
}

void rotation(Moteur moteur, int sens) {
  if (sens >= 0) {  // sens positif = vers la droite / vers le bas
    pos1(moteur); delay(t);
    pos2(moteur); delay(t);
    pos3(moteur); delay(t);
    pos4(moteur); delay(t);
  } else {  // sens négatif = vers la gauche / vers le haut
    pos4(moteur); delay(t);
    pos3(moteur); delay(t);
    pos2(moteur); delay(t);
    pos1(moteur); delay(t);
  }
}
