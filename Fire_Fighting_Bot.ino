#include <Servo.h>            //include servo.h library
#include <SoftwareSerial.h>  //include SoftwareSerial.h library

Servo myservo;

// Script Variables
int MOTOR_SPEED = 8; // 0 = Stop Running Motors, Higher The Number Lower the speed
float DISTANCE_BETWEEN_MOTORS = 10;

// Left Servo Motor Declarations
Servo leftServo;
int leftServoAngle = 0;
bool isLeftIncreasing;

// Right Servo Motor Declarations
Servo rightServo;
int rightServoAngle = 0;
bool isRightIncreasing;

// Left Flame Sensor Declarations
int leftFlameSensor = 5;

// Right Flame Sensor Declarations
int rightFlameSensor = 4;
 
int pos = 0;    
boolean fire = false;


const String PHONE = "+918800703592"; //use your number with country code

#define rxPin 2
#define txPin 3 
SoftwareSerial sim800L(rxPin,txPin);
#define LM1 8           // left motor
#define LM2 9           // left motor
#define RM1 10          // right motor
#define RM2 11          // right motor
#define pump 12         //water pumb


void setup()
{

  digitalWrite(pump , HIGH);
   
  Serial.begin(115200);
 
  sim800L.begin(9600);

  sim800L.println("AT");
  delay(1000);
  sim800L.println("AT+CMGF=1");
  delay(1000);
  
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
 
  myservo.attach(13);
  myservo.write(90); 
  
   // Left Servo Motor Setup
  leftServo.attach(7);
  leftServo.write(0);

  // Right Servo Motor Setup
  rightServo.attach(6);
  rightServo.write(0);
  
  // Left Flame Sensor Setup
  pinMode(leftFlameSensor, INPUT);

  // Right Flame Sensor Setup
  pinMode(rightFlameSensor, INPUT);
  
}
 
void put_off_fire()
{
  
 
 
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(pump,LOW);
    delay(3000);
 
 
    for (pos = 50; pos <= 110; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 110; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  digitalWrite(pump,HIGH);
  myservo.write(90); 
  fire=false;
}



void loop()
{
  /*if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    delay(500);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    Serial.print("Forward Detect");
    
    }
    
    else if (digitalRead(Left) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    Serial.print("Left Detect");
    }
    
    else if (digitalRead(Right) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    Serial.print("Right Detect..");
    }
    delay(400);//change this value to change the distance*/
    

   // Right Servo Motor Moving Logic
  if (digitalRead(rightFlameSensor) != 0 && MOTOR_SPEED != 0)
  {
    if (isRightIncreasing == true)
    {
      rightServoAngle++;
      if (rightServoAngle >= 180)
      {
        isRightIncreasing = false;
      }
    }
    else
    {
      rightServoAngle --;
      if (rightServoAngle <= 0)
      {
        isRightIncreasing = true;
      }
    }
    delay(MOTOR_SPEED);
    rightServo.write(rightServoAngle);
  }

    if (digitalRead(leftFlameSensor) != 0 && MOTOR_SPEED != 0)
  {
    if (isLeftIncreasing == true)
    {
      leftServoAngle++;
      if (leftServoAngle >= 180)
      {
        isLeftIncreasing = false;
      }
    }
    else
    {
      leftServoAngle --;
      if (leftServoAngle <= 0)
      {
        isLeftIncreasing = true;
      }
    }
    delay(MOTOR_SPEED);
    leftServo.write(leftServoAngle);
  }

  /*if (digitalRead(rightFlameSensor) == 0)
  {

    leftServo.write(60);

    while (digitalRead(leftFlameSensor) == 1 && rightServoAngle <= 180 && rightServoAngle >= 120)
    {
              digitalWrite(LM1, HIGH);
              digitalWrite(LM2, HIGH);
              digitalWrite(RM1, HIGH);
              digitalWrite(RM2, LOW);
    }

        while (digitalRead(leftFlameSensor) == 1 && rightServoAngle <= 60 && rightServoAngle >= 0)
    {
          digitalWrite(LM1, HIGH);
          digitalWrite(LM2, LOW);
          digitalWrite(RM1, HIGH);
          digitalWrite(RM2, HIGH);
    }



  }*/

  if (digitalRead(rightFlameSensor) == 0 && digitalRead(leftFlameSensor) == 0)
  {
        float distanceFromFlame;
        distanceFromFlame = (DISTANCE_BETWEEN_MOTORS * tan(leftServoAngle))/(tan(leftServoAngle) + tan(180-rightServoAngle));
        Serial.println(distanceFromFlame);
  }
  
   
     while (fire == true)
     {
      put_off_fire();
      Serial.println("Fire Detected.");
      make_call();
     }
   }

void make_call()
{
    Serial.println("calling....");
    sim800L.println("ATD"+PHONE+";");
    delay(5000); //20 sec delay
    sim800L.println("ATH");
    delay(1000); //1 sec delay
}

void send_sms()
{
    Serial.println("sending sms....");
    delay(50);
    sim800L.print("AT+CMGF=1\r");
    delay(1000);
    sim800L.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    sim800L.print("Gas Detected");
    delay(100);
    sim800L.write(0x1A);
    delay(5000);
}
