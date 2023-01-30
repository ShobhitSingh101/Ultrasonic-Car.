#include <AFMotor.h>
#include <Servo.h>


AF_DCMotor rightBack(1);
AF_DCMotor rightFront(2);
AF_DCMotor leftFront(3);
AF_DCMotor leftBack(4);
Servo servolook;

byte trig = 2;
byte echo = 13;
byte maxDist = 150;
byte stopDist = 50;
float timeOut = 2*(maxDist+10)/100/340*1000000;

byte motorSpeed = 55;
int motorOffset = 10;
int turnSpeed = 50;

void setup()
{
  rightBack.setSpeed(motorSpeed);
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed+motorOffset);
  leftBack.setSpeed(motorSpeed+motorOffset);
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
  servolook.attach(10);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
}

void loop()
{
  servolook.write(90);
  delay(750);
  int distance=getDistance();
  if(distance >= stopDist)
  {
    moveForward(); 
  }
  while(distance >= stopDist)
  {
    distance = getDistance();
    delay(250);
  }
  stopMove();
  int turnDir = checkDirection();
  Serial.print(turnDir);
  switch(turnDir)
  {
    case 0:
      turnLeft(400);
      break;
    case 1:
      turnLeft(700);
      break;
    case 2:
      turnRight(400);
      break;
  }
}
void accelerate()
{
  for (int i=0; i<motorSpeed; i++)
  {
    rightBack.setSpeed(i);
    rightFront.setSpeed(i);
    leftFront.setSpeed(i+motorOffset);
    leftBack.setSpeed(i+motorOffset);
    delay(10);  
  }
}
void decelerate()
{
  for (int i=motorSpeed; i!=0; i++)
  {
    rightBack.setSpeed(i);
    rightFront.setSpeed(i);
    leftFront.setSpeed(i+motorOffset);
    leftBack.setSpeed(i+motorOffset);
    delay(10);
  }
}
void moveForward()
{
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD); 
}
void stopMove()
{
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
}
void turnLeft(int duration)
{
  rightBack.setSpeed(motorSpeed+turnSpeed);
  rightFront.setSpeed(motorSpeed+turnSpeed);
  leftFront.setSpeed(motorSpeed+motorOffset+turnSpeed);
  leftBack.setSpeed(motorSpeed+motorOffset+turnSpeed);
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);
  delay(duration);
  rightBack.setSpeed(motorSpeed);
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed+motorOffset);
  leftBack.setSpeed(motorSpeed+motorOffset);
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE); 
}
void turnRight(int duration)
{
  rightBack.setSpeed(motorSpeed+turnSpeed);
  rightFront.setSpeed(motorSpeed+turnSpeed);
  leftFront.setSpeed(motorSpeed+motorOffset+turnSpeed);
  leftBack.setSpeed(motorSpeed+motorOffset+turnSpeed);
  rightBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
  delay(duration);
  rightBack.setSpeed(motorSpeed);
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed+motorOffset);
  leftBack.setSpeed(motorSpeed+motorOffset);
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE); 
}
int getDistance()
{
  unsigned long pulseTime;
  int distance;
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pulseTime = pulseIn(echo,HIGH,timeOut);
  distance = (float)pulseTime*340/2/10000;
  return distance; 
}
int checkDirection()
{
  int distance [2] = {0,0};
  int turnDir = 1;
  servolook.write(180);
  delay(500);
  distance[0] = getDistance();
  servolook.write(0);
  delay(1000);
  distance[1] = getDistance();
  if (distance[0]>=200 && distance[1]>=200)
  turnDir = 0;
  else if (distance[0]<=stopDist && distance[1]<=stopDist)
  turnDir = 1;
  else if (distance[0]>= distance[1])
  turnDir = 0;
  else if (distance[0]<distance[1])
  turnDir = 2;
  return turnDir;
}
