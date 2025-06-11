#include <Arduino.h>
#include <AccelStepper.h>



AccelStepper MotorIzq (AccelStepper::FULL4WIRE, 2, 4, 3, 5);
AccelStepper MotorDer (AccelStepper::FULL4WIRE, 6, 8, 7, 9);

int joyY = A1;
int joyX = A0;


int full_direction,turn_direction;

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
