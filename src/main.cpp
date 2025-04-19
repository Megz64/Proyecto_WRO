#include <Arduino.h>

#include <Servo.h>
Servo servo1;
Servo servo2;
int joyX = A1;
int joyY = A0;
int joyValX;
int lastX;
int lastY;
int joyValY;

void setup ()
{
  servo1.attach(3);
  servo2.attach(5);


}
void loop()
{

  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  if (joyValX > 92) {
    if (lastX < joyValX) {
      delay(15);
      servo1.write(lastX);
      
    } else if (lastX > joyValX) {}
    
    lastX = joyValX-1;
    delay(20);

  } else if (joyValX < 88) {
    if (lastX < joyValX) {
    } else if (lastX > joyValX) {
      delay(15);
      servo1.write(lastX);
    }
    lastX = joyValX+1;
    delay(20);
    }
  
 
  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);
  

  if (joyValY > 92) {
    if (lastY < joyValY) {
      delay(15);
      servo2.write(lastY);
    } else if (lastY > joyValY) {}
    
    lastY = joyValY-1;
    delay(20);

  } else if (joyValY < 88) {
    if (lastY < joyValY) {
    } else if (lastY > joyValY) {
      delay(15);
      servo2.write(lastY);
    }
    lastY = joyValY+1;
    delay(20);
    }
}
