// Motoare stanga
int enableA = 6;
int pinA1 = 7;
int pinA2 = 5;

int servoPin = 11;

//Motoare dreapta
int enableB = 3;
int pinB1 = 2;
int pinB2 = 4;

//senzor ultrasunete
#define trigPin 1
#define echoPin 12


void setup() {
  //Configuratia pinilor (intrare/iesire)
  pinMode (enableA, OUTPUT);
  pinMode (pinA1, OUTPUT);
  pinMode (pinA2, OUTPUT);
  pinMode (enableB, OUTPUT);
  pinMode (pinB1, OUTPUT);
  pinMode (pinB2, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  car(); /*functia car deplaseaza masina in fata pana
          cand senzorul detecteaza un obiect la mai putin de 15 cm
          in fata*/
          
  avoid(); /*functia avoid deplaseaza masina in spate, vireaza putin
            la dreapta si deplaseaza masina in fata dupa noua directie */
}


//functiile motorului
void motorAforward() {
  digitalWrite (pinA1, HIGH);
  digitalWrite (pinA2, LOW);
}

void motorBforward() {
  digitalWrite (pinB1, LOW);
  digitalWrite (pinB2, HIGH);
}

void motorAbackward () {
  digitalWrite (pinA1, LOW);
  digitalWrite (pinA2, HIGH);
}

void motorBbackward() {
  digitalWrite (pinB1, HIGH);
  digitalWrite (pinB2, LOW);
}

void motorAstop () {
  digitalWrite (pinA1, HIGH);
  digitalWrite (pinA2, HIGH);
}

void motorBstop() {
  digitalWrite (pinB1, HIGH);
  digitalWrite (pinB2, HIGH);
}

void motorAon() {
  digitalWrite (enableA, HIGH);
}

void motorBon() {
  digitalWrite (enableB, HIGH);
}

//functiile de deplasare
void forward (int duration) {
  motorAforward();
  motorBforward();
  delay (duration);
}

void backward (int duration) {
  motorAbackward();
  motorBbackward();
  delay (duration);
}

void right (int duration) {
  motorAbackward();
  motorBforward();
  delay (duration);
}

void left (int duration) {
  motorAforward();
  motorBbackward();
  delay (duration);
}

void breakRobot (int duration) {
  motorAstop();
  motorBstop();
  delay (duration);
}

void enableMotors() {
  motorAon();
  motorBon();
}

//functia de masurare a distantei cu ajutorul senzorului ultrasonic
int distance() {
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

//functia car
void car() {
  int distance_0;
  distance_0 = distance();
    while(distance_0 > 15)
    {
      motorAon();
      motorBon();
      forward(1);
      distance_0 = distance();
    }
    breakRobot(0);
}

// Functia avoid
void avoid() {
  backward(1000);
  right(500);
}
