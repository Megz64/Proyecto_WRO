#include <Arduino.h>
#include <AccelStepper.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

#define Servo_num 5

AccelStepper MotorIzq (AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper MotorDer (AccelStepper::FULL4WIRE, 6, 8, 7, 9);

int joyY = A1;
int joyX = A0;

int joyValX,joyValY;
float X,Y;
float vX,vY;

int anguloX,anguloY1,anguloY2,anguloY3 = 350;

int muneca = A2;
int mano = 2;
int angulomuneca;
int estadoboton;

int full_direction,turn_direction;

int botoncontrol=3;
bool control;
bool controllast;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  MotorIzq.setMaxSpeed(1000);
  MotorDer.setMaxSpeed(1000);

  MotorIzq.setAcceleration(500);
  MotorDer.setAcceleration(500);


  pwm.begin();
  pwm.setPWMFreq(50);

  pinMode(mano, INPUT);
  pinMode(botoncontrol, INPUT);

}

void loop() {
  
  full_direction = analogRead(joyY);
  turn_direction = analogRead(joyX);

  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);

  MotorIzq.run();
  MotorDer.run();

  if (controllast==HIGH) {
    if (full_direction > 530) {
      MotorIzq.move(-100);
      MotorDer.move(-100);
    } 
  
    if (full_direction < 510) {
      MotorIzq.move(100);
      MotorDer.move(100);
    }

    if (turn_direction > 530) {
      MotorIzq.move(-100);
      MotorDer.move(100);
    }
  
    if (turn_direction < 510) {
      MotorIzq.move(100);
      MotorDer.move(-100);
    }
  } else {

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
      delay(100);
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

  control = digitalRead(botoncontrol);
  if (control = HIGH) {
    if (controllast == LOW) {
      controllast = HIGH;
    } else {
      controllast = LOW;
  
} //Loop end
