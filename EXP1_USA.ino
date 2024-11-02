#define E 13
#define D 12
#define C 11
#define DP 10
#define B 9
#define A 8
#define F 7
#define G 6

#define TRIG 5
#define ECHO 3

void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(DP, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(TRIG, OUTPUT);  // Use TRIG here
  pinMode(ECHO, INPUT);    // Use ECHO here
  Serial.begin(9600);
}

void one(void) {
  digitalWrite(A, HIGH); 
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D, HIGH);
  digitalWrite(E, HIGH);  
  digitalWrite(F, HIGH);
  digitalWrite(G, HIGH);
}

void two(void) {
  digitalWrite(E, LOW);
  digitalWrite(D, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(DP, LOW);
  digitalWrite(B, LOW);
  digitalWrite(A, LOW);
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void three(void) {
  digitalWrite(A, LOW);  
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, HIGH);    
  digitalWrite(F, HIGH);
  digitalWrite(G, LOW);
}

void zero(void) {
  digitalWrite(A, LOW);
  digitalWrite(B, LOW);
  digitalWrite(C, LOW);
  digitalWrite(DP, LOW);
  digitalWrite(D, LOW);
  digitalWrite(E, LOW);
  digitalWrite(F, LOW);
  digitalWrite(G, HIGH);
}

void loop() {
  digitalWrite(TRIG, LOW);  // Use TRIG here
  delayMicroseconds(5);
  
  digitalWrite(TRIG, HIGH);  // Use TRIG here
  delayMicroseconds(10);
  
  digitalWrite(TRIG, LOW);   // Use TRIG here
  
  int a = pulseIn(ECHO, HIGH); // Use ECHO here
  
  float d = a * 0.034 / 2;
  
  Serial.println(d);
  
  if (d < 100) {
    one();
    delay(100);
  } else if (d < 200) {
    two();
    delay(100);
  } else if (d < 300) {
    three();
    delay(100);
  } else {
    zero();
  }
  
  delay(1000);
}
