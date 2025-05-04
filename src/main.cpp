#include <Arduino.h>

#include <Servo.h>
Servo servo1;
Servo servo2;
int joyX = A1;
int joyY = A0;
float joyValX,joyValY;
float X,Y;
float vX,vY;

void setup ()
{
  servo1.attach(3);
  servo2.attach(5);

  servo1.write(90);

  Serial.begin(9600);

}
void loop()
{


  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  X = constrain(X,0,180);

  Serial.println(vX);

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
}