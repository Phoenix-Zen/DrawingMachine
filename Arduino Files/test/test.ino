x/*
int IN1 = 9;
int IN2 = 10;
int IN3 = 12;
int IN4 = 13;
*/
int IN1 = 3;
int IN2 = 4;
int IN3 = 6;
int IN4 = 7;
int t = 2;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  for(int i = 0; i < 100; i++){
    marche_av();
  }
  for(int i = 0; i < 100; i++){
    marche_ar();
  }
}
void pos1() {
  digitalWrite(IN1, 1);
  digitalWrite(IN2, 0);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void pos2() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 1);
  digitalWrite(IN4, 0);
}
void pos3() {
  digitalWrite(IN1, 0);
  digitalWrite(IN2, 1);
  digitalWrite(IN3, 0);
  digitalWrite(IN4, 1);
}
void pos4() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void marche_av(){
  pos1(); delay(t);
  pos2(); delay(t);
  pos3(); delay(t);
  pos4(); delay(t);
}
void marche_ar(){
  pos4(); delay(t);
  pos3(); delay(t);
  pos2(); delay(t);
  pos1(); delay(t);
}
