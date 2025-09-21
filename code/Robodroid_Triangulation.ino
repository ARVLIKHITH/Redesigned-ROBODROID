// Robodroid - Fire-Fighting Robot (Triangulation)
// V2: 3 analog flame sensors -> bearing control + MQ2 + SIM800L
// Authors: Likhith Anand (electronics/integration), Arnav Bajaj (triangulation logic)

#include <Servo.h>
#include <SoftwareSerial.h>
#include <math.h>

// ---------- Pin map (adjust to your wiring) ----------
#define FL_LEFT    A0
#define FL_FRONT   A1
#define FL_RIGHT   A2
#define GAS_DPIN   7        // MQ2 digital output (use analog if you prefer)

#define LM1 8               // left motor IN1
#define LM2 9               // left motor IN2
#define RM1 10              // right motor IN1
#define RM2 11              // right motor IN2
#define PUMP 12             // relay for water pump
#define SERVO_PIN 13

#define GSM_RX 2            // Arduino D2 <- SIM800L TX
#define GSM_TX 3            // Arduino D3 -> SIM800L RX

// ---------- GSM ----------
SoftwareSerial sim800L(GSM_RX, GSM_TX);
const char* PHONE = "+91XXXXXXXXXX";   // <-- your number

// ---------- Servo ----------
Servo nozzle;
const int SERVO_LEFT   = 50;           // sweep endpoints
const int SERVO_CENTER = 90;
const int SERVO_RIGHT  = 110;

// ---------- Triangulation config ----------
const float ANG_L = -30.0f;            // sensor angles relative to forward
const float ANG_F =   0.0f;
const float ANG_R = +30.0f;

int   FLAME_THRESH = 120;              // ignore weak ambient (0..1023)
int   TOTAL_MIN    = 80;               // minimal combined signal to accept
float FACING_WIN   = 8.0f;             // |bearing| <= deg considered centered

// Motion tuning
int TURN_MS   = 150;                   // pivot pulse
int STEP_MS   = 220;                   // forward pulse
int STEP_COUNT_BEFORE_SPRAY = 4;       // forward steps after centered

// ---------- Helpers ----------
void motorsStop() {
  digitalWrite(LM1, LOW); digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW); digitalWrite(RM2, LOW);
}
void motorsForward() {
  digitalWrite(LM1, HIGH); digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
}
void turnLeft() {
  digitalWrite(LM1, LOW);  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH); digitalWrite(RM2, LOW);
}
void turnRight() {
  digitalWrite(LM1, HIGH); digitalWrite(RM2, HIGH); // hold right wheel back
  digitalWrite(LM2, LOW);  digitalWrite(RM1, LOW);  // small pivot to right
}

// ---------- GSM ----------
void gsmInit() {
  sim800L.begin(9600);
  delay(700);
  sim800L.println("AT");        delay(600);
  sim800L.println("AT+CMGF=1"); delay(600);
  while (sim800L.available()) Serial.write(sim800L.read());
}
void gsmCall() {
  sim800L.print("ATD"); sim800L.print(PHONE); sim800L.println(";");
  delay(20000);
  sim800L.println("ATH");
}
void gsmSMS(const char* msg) {
  sim800L.println("AT+CMGF=1");      delay(300);
  sim800L.print("AT+CMGS=\""); sim800L.print(PHONE); sim800L.println("\"");
  delay(300);
  sim800L.print(msg);
  sim800L.write(0x1A);               // Ctrl+Z
  delay(2500);
}

// ---------- Fire action ----------
void spraySequence() {
  digitalWrite(PUMP, HIGH);
  delay(400);
  for (int p = SERVO_LEFT; p <= SERVO_RIGHT; p++) { nozzle.write(p); delay(10); }
  for (int p = SERVO_RIGHT; p >= SERVO_LEFT;  p--) { nozzle.write(p); delay(10); }
  digitalWrite(PUMP, LOW);
  nozzle.write(SERVO_CENTER);
}

// Weighted-angle bearing from three analog flame sensors
// returns bearing in degrees (neg=left,pos=right), or 9999 if invalid
float computeBearingDeg(int rL, int rF, int rR) {
  int sL = rL > FLAME_THRESH ? (rL - FLAME_THRESH) : 0;
  int sF = rF > FLAME_THRESH ? (rF - FLAME_THRESH) : 0;
  int sR = rR > FLAME_THRESH ? (rR - FLAME_THRESH) : 0;
  int total = sL + sF + sR;
  if (total < TOTAL_MIN) return 9999.0f;
  float wL = (float)sL, wF = (float)sF, wR = (float)sR;
  return (wL*ANG_L + wF*ANG_F + wR*ANG_R) / (wL + wF + wR);
}

void setup() {
  Serial.begin(115200);

  pinMode(GAS_DPIN, INPUT);
  pinMode(LM1, OUTPUT); pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT); pinMode(RM2, OUTPUT);
  pinMode(PUMP, OUTPUT);
  motorsStop(); digitalWrite(PUMP, LOW);

  nozzle.attach(SERVO_PIN);
  nozzle.write(SERVO_CENTER);

  gsmInit();
  gsmSMS("Robodroid triangulation ready.");
}

void loop() {
  // GAS alert path (active-low on many MQ2 boards; flip if needed)
  if (digitalRead(GAS_DPIN) == LOW) {
    Serial.println("Gas detected");
    gsmSMS("Gas detected");
    gsmCall();
  }

  // Read flame sensors
  int rL = analogRead(FL_LEFT);
  int rF = analogRead(FL_FRONT);
  int rR = analogRead(FL_RIGHT);

  float bearing = computeBearingDeg(rL, rF, rR);
  Serial.print("rL="); Serial.print(rL);
  Serial.print(" rF="); Serial.print(rF);
  Serial.print(" rR="); Serial.print(rR);
  Serial.print(" | bearing="); Serial.println(bearing);

  if (bearing == 9999.0f) {
    motorsStop();
    // idle: small center hold
    nozzle.write(SERVO_CENTER);
    delay(120);
    return;
  }

  if (bearing < -FACING_WIN) {
    turnLeft();  delay(TURN_MS); motorsStop();
  } else if (bearing >  FACING_WIN) {
    turnRight(); delay(TURN_MS); motorsStop();
  } else {
    // Facing flame: step forward a few pulses, re-check, then spray
    for (int i = 0; i < STEP_COUNT_BEFORE_SPRAY; i++) {
      motorsForward(); delay(STEP_MS); motorsStop(); delay(90);
      // optional quick re-aim
      int rl = analogRead(FL_LEFT), rf = analogRead(FL_FRONT), rr = analogRead(FL_RIGHT);
      float b2 = computeBearingDeg(rl, rf, rr);
      if (b2 == 9999.0f) break;
      if (fabs(b2) > FACING_WIN)  break;
    }
    spraySequence();
  }

  delay(70);
}
