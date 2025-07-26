#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;

int joyY = A1;
int joyX = A0;

int joyValX,joyValY=512;
float X,Y;
float vX,vY;

int anguloX,anguloY1,anguloY2,anguloY = 90;

int muneca = A2;
int mano = 2;
int angulomuneca;
int estadoboton;

int full_direction,turn_direction;

int botoncontrol=3;
bool control;
bool controllast;
bool buttonlast;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);

  pinMode(mano, INPUT);
  pinMode(botoncontrol, INPUT);

  controllast = LOW;
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  pinMode(4, OUTPUT);

}

void loop() {
  
  full_direction = analogRead(joyY);
  turn_direction = analogRead(joyX);
  static int desiredvalue = 512;

  joyValX = analogRead(joyX);
  joyValX = map (joyValX, 0, 1023, 0, 180);

  joyValY = analogRead(joyY);
  joyValY = map (joyValY, 0, 1023, 0, 180);

  //Serial.println(full_direction);
  //Serial.println(turn_direction);

  control = digitalRead(botoncontrol);
    if (control == HIGH) {
      delay(500);
      if (controllast == LOW) {
        controllast = HIGH;
        Serial.println("Motor control");
      } else {
        controllast = LOW;
        Serial.println("Servo control");
      }
      
    }
  

  if (controllast==HIGH) {
    digitalWrite(4,HIGH);

    full_direction = (desiredvalue * 0.8) + (full_direction * 0.2);
    turn_direction = (desiredvalue * 0.8) + (turn_direction * 0.2);

    if (full_direction > 530) {
      analogWrite(5, 200);
      analogWrite(6, 0);
      analogWrite(9, 200);
      analogWrite(10, 0);
    } else if (full_direction < 490) {
      analogWrite(5, 0);
      analogWrite(6, 200);
      analogWrite(9, 0);
      analogWrite(10, 200);
    } else if (turn_direction > 530) {
      analogWrite(5, 200);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 200);
    } else if (turn_direction < 490) {
      analogWrite(5, 0);
      analogWrite(6, 200);
      analogWrite(9, 200);
      analogWrite(10, 0);
    } else {
      analogWrite(5, 0);
      analogWrite(6, 0);
      analogWrite(9, 0);
      analogWrite(10, 0);
    }


  } else if (controllast==LOW) {
    digitalWrite(4,LOW);
    if (joyValY > 95) {
      anguloY++;

    } else if (joyValY < 85) {
      anguloY--;
    }

    anguloY = constrain(anguloY,0,180);
    
    anguloY1 = map(anguloY,0,180,150,600);
    anguloY2 = map(90-anguloY,0,180,150,600);

    pwm.setPWM(1,0,anguloY1);
    pwm.setPWM(2,0,anguloY2);

    //Wrist rotation/closing

    angulomuneca = analogRead(muneca);
    angulomuneca = map(angulomuneca, 0, 1023, 125, 575);
    pwm.setPWM(3, 0, angulomuneca);
    
    
    estadoboton = digitalRead(mano);
    if (estadoboton == HIGH) {
      delay(500);
      if (buttonlast == LOW) {
        pwm.setPWM(4,0,400);
        buttonlast = HIGH;
      } else {
        pwm.setPWM(4,0,250);
        buttonlast = LOW;
      
    }//Control condition end
    }
    delay(50);
  } //Loop end
}
