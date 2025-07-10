#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

int motor11 = 2;
int motor12 = 3;
int motor21 = 4;
int motor22 = 5;

int joyY = A1;
int joyX = A0;

int joyValX,joyValY;
float X,Y;
float vX,vY;

int anguloX,anguloY1,anguloY2,anguloY3 = 350;

int muneca = A2;
int mano = 10;
int angulomuneca;
int estadoboton;

int full_direction,turn_direction;

int botoncontrol=11;
bool control;
bool controllast;
bool buttonlast;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(50);

  pinMode(mano, INPUT);
  pinMode(botoncontrol, INPUT);

  controllast = LOW;
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(12, OUTPUT);
}

void loop() {
  
  full_direction = analogRead(joyY);
  turn_direction = analogRead(joyX);

  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);

  Serial.println(joyX);
  Serial.println(joyY);

  control = digitalRead(botoncontrol);
    if (control == HIGH) {
      delay(500);
      if (controllast == LOW) {
        controllast = HIGH;
      } else {
        controllast = LOW;
      }
    }
  

  if (controllast==HIGH) {
    digitalWrite(12,HIGH);
    if (full_direction > 540) {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    } else if (full_direction < 500) {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (turn_direction > 540) {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
    } else if (turn_direction < 500) {
      digitalWrite(2, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    } else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    }


  } else if (controllast==LOW) {
    digitalWrite(12,LOW);
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

    //Wrist rotation/closing

    angulomuneca = analogRead(muneca);
    angulomuneca = map(angulomuneca, 0, 1023, 125, 575);
    pwm.setPWM(4, 0, angulomuneca);
  
    estadoboton = digitalRead(mano);
    if (estadoboton == HIGH) {
      delay(500);
      if (buttonlast == LOW) {
        pwm.setPWM(5,0,400);
        buttonlast = HIGH;
      } else {
        pwm.setPWM(5,0,250);
        buttonlast = LOW;
      }
    }
    delay(30);
  }//Control condition end

  
} //Loop end
