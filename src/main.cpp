#include <Arduino.h>
#include <AccelStepper.h>



AccelStepper MotorIzq (AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper MotorDer (AccelStepper::FULL4WIRE, 6, 8, 7, 9);

int joyY = A1;
int joyX = A0;


int full_direction,turn_direction;



<<<<<<< HEAD

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  MotorIzq.setMaxSpeed(1000);
  MotorDer.setMaxSpeed(1000);

  MotorIzq.setAcceleration(500);
  MotorDer.setAcceleration(500);

}

void loop() {
  
  full_direction = analogRead(joyY);
  turn_direction = analogRead(joyX);

  Serial.println(full_direction);

    MotorIzq.run();
    MotorDer.run();

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

}
=======
int motor11=2;
int motor12=3;

int motor21=4;
int motor22=5;

int joyY = A0;
int joyX = A1;

int motor_v1 = 9;
int motor_v2 = 10;

int full_direction,turn_direction;

//Velocidad 1 y 2 para avanzar con los 2, 3 y 4 para giro a cierta direccion
int velocidad1,velocidad2,velocidad3,velocidad4 = 255;


void forward() {
  analogWrite(motor_v1, velocidad1);
  analogWrite(motor_v2, velocidad1);
  digitalWrite(motor11, LOW);
  digitalWrite(motor12, HIGH);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, LOW);
}

void backward() {
  analogWrite(motor_v1, velocidad2);
  analogWrite(motor_v2, velocidad2);
  digitalWrite(motor11, HIGH);
  digitalWrite(motor12, LOW);
  digitalWrite(motor21, LOW);
  digitalWrite(motor22, LOW);
}

/*void right() {
  analogWrite(motor_v1, velocidad3);
  analogWrite(motor_v2, velocidad3);
  digitalWrite(motor12,LOW);
  digitalWrite(motor21,LOW);
  digitalWrite(motor11,HIGH);
  digitalWrite(motor22,HIGH);
}

void left() {
  analogWrite(motor_v1, velocidad4);
  analogWrite(motor_v2, velocidad4);
  digitalWrite(motor11,LOW);
  digitalWrite(motor22,LOW);
  digitalWrite(motor12,HIGH);
  digitalWrite(motor21,HIGH);
}*/

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  pinMode(motor11,OUTPUT);
  pinMode(motor12,OUTPUT);
  pinMode(motor21,OUTPUT);
  pinMode(motor12,OUTPUT);
  Serial.begin(4800);

  pinMode(motor_v1,OUTPUT);
  pinMode(motor_v2,OUTPUT);
}

void loop() {
  full_direction = analogRead(joyY);
  //turn_direction = analogRead(joyX);

  velocidad1 = map(full_direction, 524, 0, 0, 225);
  velocidad2 = map(full_direction, 524, 1023, 0, 225);
  //velocidad3 = map(turn_direction, 524, 0, 0, 225);
  //velocidad4 = map(turn_direction, 524, 1023, 0, 225);
  Serial.println(velocidad2);

  if (full_direction < 530) {
    forward();
    delay(15);
    
  } 
  
  if (full_direction > 510) {
    backward();
    delay(15);
    
  }

    /*digitalWrite(motor11,LOW);
    digitalWrite(motor21,LOW);
    digitalWrite(motor12,LOW);
    digitalWrite(motor22,LOW);*/

/*  if (turn_direction > 510 < 530) {
    right();
    delay(15);
  } else if (turn_direction < 510) {
    left();
    delay(15);
  } else {
    digitalWrite(motor11,LOW);
    digitalWrite(motor21,LOW);
    digitalWrite(motor12,LOW);
    digitalWrite(motor22,LOW);
  }
*/
}
>>>>>>> 5519b8ae883936318eb9f99b024c43b17dba45e9
