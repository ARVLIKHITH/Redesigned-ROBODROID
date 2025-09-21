#include <Servo.h>

// Script Variables
int MOTOR_SPEED = 20; // 0 = Stop Running Motors, Higher The Number Lower the speed
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
int leftFlameSensor = 10;

// Right Flame Sensor Declarations
int rightFlameSensor = 11;

void setup() 
{
  Serial.begin(115200);
    
  // Left Servo Motor Setup
  leftServo.attach(8);
  leftServo.write(0);

  // Right Servo Motor Setup
  rightServo.attach(9);
  rightServo.write(0);
  
  // Left Flame Sensor Setup
  pinMode(leftFlameSensor, INPUT);

  // Right Flame Sensor Setup
  pinMode(rightFlameSensor, INPUT);
}

void loop() 
{        
  // Left Servo Motor Moving Logic
  if
  (digitalRead(leftFlameSensor) != 0 && MOTOR_SPEED != 0)
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

  if (digitalRead(rightFlameSensor) == 0 && digitalRead(leftFlameSensor) == 0)
  {
    float distanceFromFlame;
    distanceFromFlame = (DISTANCE_BETWEEN_MOTORS * tan(leftServoAngle))/(tan(leftServoAngle) + tan(180-rightServoAngle));
    Serial.println(distanceFromFlame);
  }
}
