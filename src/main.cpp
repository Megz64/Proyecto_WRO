#include <Arduino.h>

#include <Servo.h>
Servo servo1;
Servo servo2;
int joyX = A0;
int joyY = A1;
int joyValX;
int joyValY;

void setup ()
{
  servo1.attach(5);
  servo2.attach(3);
  Serial.begin(9600);
}
void loop()
{
  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);
  servo1.write(joyValX);
  Serial.write(joyX);

  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);
  servo2.write(joyValY);
  delay(15);  
}
