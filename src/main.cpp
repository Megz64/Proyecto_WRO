#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

static int desiredvalue = 512;

int joyY = A1;
int joyX = A0;
int secondaryjoyY = A3;

int joyValX,joyValY,secondaryjoyValY=512;

int  anguloY1,anguloY2,anguloY = 180;
int anguloX1,anguloX = 180;

int muneca = A2;
int mano = 2;
int angulomuneca;
int estadoboton;

int full_direction,turn_direction,motor_velocity;

int botoncontrol=3;
bool control;
bool buttonlast;



void setup() {
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);
  Wire.setClock(50000);
  delay(1000);

  pinMode(mano, INPUT_PULLUP);
  pinMode(botoncontrol, INPUT_PULLUP);

  control = LOW;
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(4, OUTPUT);

}

void loop() {
  
  full_direction = analogRead(joyY);
  turn_direction = analogRead(joyX);

  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);

  secondaryjoyValY = analogRead(secondaryjoyY);
  secondaryjoyValY = map (secondaryjoyValY,300,1023,0,180);
  

  motor_velocity = analogRead(secondaryjoyY);
  motor_velocity = map (motor_velocity,300,1023,0,200);

  control = digitalRead(botoncontrol);

  if (control==HIGH) {
    Serial.println(motor_velocity);
    digitalWrite(4,HIGH);

    full_direction = (desiredvalue * 0.8) + (full_direction * 0.2);
    turn_direction = (desiredvalue * 0.8) + (turn_direction * 0.2);
    

    if (full_direction > 530) {
      analogWrite(5, 0);
      analogWrite(6, motor_velocity);
      analogWrite(9, 0);
      analogWrite(10, motor_velocity);
    } else if (full_direction < 490) {
      analogWrite(5, motor_velocity);
      analogWrite(6, 0);
      analogWrite(9, motor_velocity);
      analogWrite(10, 0);
    } else if (turn_direction > 530) {
      analogWrite(5, 20+motor_velocity);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 20+motor_velocity);
    } else if (turn_direction < 490) {
      analogWrite(5, 0);
      analogWrite(6, 20+motor_velocity);
      analogWrite(9, 20+motor_velocity);
      analogWrite(10, 0);
    } else {
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 0);
    }


  } else if (control==LOW) {
    Serial.println(secondaryjoyValY);
    digitalWrite(4,LOW);
    if (joyValY > 95) {
      anguloY+=2;

    } else if (joyValY < 85) {
      anguloY-=2;
    }

    anguloY = constrain(anguloY,0,180);

    anguloY1 = map(anguloY,0,180,150,600);
    
    if (secondaryjoyValY > 100) {
      anguloY2 = map(secondaryjoyValY,0,180,150,600);
    } else if (secondaryjoyValY < 80) {
      anguloY2 = map(secondaryjoyValY,0,180,200,325);
    } else {
      anguloY2 = map(90-anguloY,0,180,200,600);
      Serial.println(anguloY2);
    }

    delay(20);
    pwm.setPWM(1,0,anguloY1);
    delay(20);
    pwm.setPWM(2,0,anguloY2);

    if (joyValX > 95) {
      anguloX+=2;

    } else if (joyValX < 85) {
      anguloX-=2;
    }

    anguloX = constrain(anguloX,0,180);
    
    anguloX1 = map(anguloX,0,180,150,600);

    delay(20);
    pwm.setPWM(0,0,anguloX1);

    //Wrist rotation/closing

    angulomuneca = analogRead(muneca);
    angulomuneca = map(angulomuneca, 0, 1023, 125, 575);
    delay(20);
    pwm.setPWM(3, 0, angulomuneca);
    
    
    estadoboton = digitalRead(mano);
    if (estadoboton == LOW) {
      delay(500);
      if (buttonlast == LOW) {
        pwm.setPWM(15,0,400);
        buttonlast = HIGH;
      } else {
        pwm.setPWM(15,0,250);
        buttonlast = LOW;
      
    }//Control condition end
    }
  } //Loop end
}
