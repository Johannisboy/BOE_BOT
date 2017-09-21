#include <Servo.h>

Servo servoLeft;
Servo servoRight;

byte wLeftOld;
byte wRightOld;
byte counter;

void setup()
{
  pinMode(8, INPUT);
  pinMode(6, INPUT);
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  tone(4, 3000, 1000);
  
  delay(1000);
  
  servoLeft.attach(11);
  servoRight.attach(10);
  
  wLeftOld = 0;
  wRightOld = 1;
  counter = 0;
}

void loop()
{

  // Corner Escape
  byte wLeft = digitalRead(6);
  byte wRight = digitalRead(8);
  
  if(wLeft != wRight)
  {
    if ((wLeft != wLeftOld) && (wRight != wRightOld))
    {
      counter++;
      wLeftOld = wLeft;
      wRightOld = wRight;
      if(counter == 4)
      {
        wLeft = 0;
        wRight = 0;
        counter = 0;
      }
    }
    else
    {
      counter = 0;
    }
  }
  
  // Whisker Navigation
  if((wLeft == 0) && (wRight == 0))
  {
    backward(1000, wLeft, wRight);
    turnLeft(800);
  }
  else if(wLeft == 0)
  {
    digitalWrite(9,HIGH);
    digitalWrite(2,LOW);
    backward(1000, wLeft, wRight);
    turnRight(400);
  }
  else if(wRight == 0)
  {
    digitalWrite(9,LOW);
    digitalWrite(2,HIGH);
    backward(1000, wLeft, wRight);
    turnLeft(400);
  }
  else
  {
    digitalWrite(9,LOW);
    digitalWrite(2,LOW);
    forward(20);
  }
}

void forward(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void turnLeft(int time)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void turnRight(int time)
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

void backward(int time, int left, int right)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);

  if (left == 0 && right == 0)
  {
    for (int i = 0; i < 3; i++)
    {
      tone(4, 3000, 250);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
    
      delay(time/6);
    
      digitalWrite(9, LOW);
      digitalWrite(2, LOW);
    
      delay(time/6);
    }
  }
  else
  {
    delay(time);
  }
}
