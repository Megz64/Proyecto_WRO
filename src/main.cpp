#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

#define Servo_num 5


int buttoncurrent;
int buttonlast;

int joyX = A1;
int joyY = A0;
float joyValX,joyValY;
float X,Y;
float vX,vY;

int anguloX,anguloY1,anguloY2,anguloY3 = 350;

int muneca = A2;
int mano = 2;
int angulomuneca;
int estadoboton;

int brazo_adelante = 3;
int brazo_atras = 4;

void setup ()
{
  pwm.begin();
  pwm.setPWMFreq(50);

  /*pinMode(button, INPUT_PULLUP);
  buttoncurrent = HIGH;
  buttonlast = LOW;*/

  Serial.begin(9600);
  pinMode(mano, INPUT);

  pinMode(brazo_adelante, INPUT);
  pinMode(brazo_atras, INPUT);

}
void loop()
{



  //Horizontal rotation
  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);
  
  anguloX = constrain(anguloX, 125, 575);

    if (joyValX > 95) {
    vX = map(joyValX,90,180,1,100);
  } else if (joyValX < 85) {
    vX = map(joyValX,90,0,1,100);
  }
  vX = vX * 0.1;

    
  if (joyValX > 95) {
    anguloX = anguloX + vX;
    pwm.setPWM(0, 0, anguloX);
  }
  if (joyValX < 85) {
    anguloX = anguloX - vX;
    pwm.setPWM(0, 0, anguloX);
  }


  //Vertical rotation
  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);
  
  anguloY1 = constrain(anguloY1, 125, 575);
  anguloY2 = constrain(anguloY2, 125, 575);
  anguloY3 = constrain(anguloY3, 200, 575);


    if (joyValY > 95) {
    vY = map(joyValY,90,180,1,50);
  } else if (joyValY < 85) {
    vY = map(joyValY,90,0,1,50);
  }
  vY = vY * 0.1;

    
  if (joyValY > 95) {
    anguloY1 = anguloY1 + vY;
    anguloY2 = 600 - anguloY1;
    anguloY3 = 600 - anguloY1;
    anguloY3 = constrain(anguloY3, 200, 575);

    pwm.setPWM(1, 0, anguloY1);
    pwm.setPWM(2, 0, anguloY2);
    pwm.setPWM(3, 0, anguloY3);
  }
  if (joyValY < 85) {
    anguloY1 = anguloY1 - vY;
    anguloY2 = 600 - anguloY1;
    anguloY3 = 600 - anguloY1;
    anguloY3 = constrain(anguloY3, 200, 575);

    pwm.setPWM(1, 0, anguloY1);
    pwm.setPWM(2, 0, anguloY2);
    pwm.setPWM(3, 0, anguloY3);
  }

      //Para avanzar el brazo con el boton
  if (anguloY1 > 288) {
    while (digitalRead(brazo_adelante) == HIGH) {
      anguloY1++;
      anguloY2++;
      anguloY3=anguloY1-160;

      pwm.setPWM(1, 0, anguloY1);
      pwm.setPWM(2, 0, anguloY2);
      pwm.setPWM(3, 0, anguloY3);
      delay(100);
    }

    while (digitalRead(brazo_atras) == HIGH) {
      anguloY1--;
      anguloY2=anguloY1-250;
      anguloY3=anguloY1+5;

      pwm.setPWM(1, 0, anguloY1);
      pwm.setPWM(2, 0, anguloY2);
      pwm.setPWM(3, 0, anguloY3);
      delay(100);
    }
  } else {
    while (digitalRead(brazo_adelante) == HIGH) {
      anguloY1--;
      anguloY2--;
      anguloY3=anguloY1+50;

      pwm.setPWM(1, 0, anguloY1);
      pwm.setPWM(2, 0, anguloY2);
      pwm.setPWM(3, 0, anguloY3);
      delay(100);
    }

    while (digitalRead(brazo_atras) == HIGH) {
      anguloY1++;
      anguloY2=anguloY1+200;
      anguloY3=anguloY1+20;

      pwm.setPWM(1, 0, anguloY1);
      pwm.setPWM(2, 0, anguloY2);
      pwm.setPWM(3, 0, anguloY3);
      delay(100);
    }
  }
  

  //Wrist rotation/closing

  angulomuneca = analogRead(muneca);
  angulomuneca = map(angulomuneca, 0, 1023, 125, 575);
  pwm.setPWM(4, 0, angulomuneca);

  estadoboton = digitalRead(mano);
  if (estadoboton == HIGH) {
    delay(100);
    if (buttonlast == LOW) {
      pwm.setPWM(5,0,400);
      buttonlast = HIGH;
    } else {
      pwm.setPWM(5,0,250);
      buttonlast = LOW;
    }
  }
  


    /*
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
  */
  delay(30);
  }