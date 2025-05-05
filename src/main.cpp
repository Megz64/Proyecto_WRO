#include <Arduino.h>

#include <Servo.h>
Servo servo1; //X rotation
Servo servo2; //Arm Base
Servo servo3; //Arm Middle

int button = 2;
int buttoncurrent;
int buttonlast;
bool Lockangle;

int joyX = A1;
int joyY = A0;
float joyValX,joyValY;
float X,Y;
float vX,vY;

void setup ()
{
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);

  pinMode(button, INPUT_PULLUP);
  buttoncurrent = HIGH;
  buttonlast = LOW;

  Serial.begin(9600);

}
void loop()
{

  //Horizontal rotation
  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  X = constrain(X,0,180);

  if (joyValX > 95) {
    vX = map(joyValX,90,180,1,20);
    vX = vX*0.1;
  } else if (joyValX < 85) {
    vX = map(joyValX,90,0,1,20);
    vX = vX*0.1;
  }


  if (joyValX < 180 && joyValX > 100) {
    X = X + vX;
    servo1.write(X);
  }
  if (joyValX < 80 && joyValX >= 0) {
    X = X - vX;
    servo1.write(X);
  }


  //Arm rotation
  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);

  Y = constrain(Y,0,180);

  if (joyValY > 95) {
    vY = map(joyValY,90,180,1,20);
    vY = vY*0.1;
  } else if (joyValY < 85) {
    vY = map(joyValY,90,0,1,20);
    vY = vY*0.1;
  }


  if (joyValY < 180 && joyValY > 100) {
    Y = Y + vY;
    servo2.write(Y);
    if (Lockangle == false){
      servo3.write(180-Y);
    }

  }
  if (joyValY < 80 && joyValY >= 0) {
    Y = Y - vY;
    servo2.write(Y);
    if (Lockangle == false){
      servo3.write(180-Y);
    }
  }


  //Button presses
  buttoncurrent = digitalRead(button);
 
  if (buttoncurrent == LOW){
    delay(50);
    if (buttonlast == HIGH){
      Lockangle = true;
      
      buttonlast = false;
    } else {
      Lockangle = false;
      
      buttonlast = true;
    }
  
  }
  delay(10);
}