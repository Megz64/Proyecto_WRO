#include <Arduino.h>

<<<<<<< HEAD
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
  Serial.begin(9600);
  servo1.write(90);


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
int velocidad1,velocidad2,velocidad3,velocidad4;


void forward() {
  analogWrite(motor_v1, velocidad1);
  analogWrite(motor_v2, velocidad1);
  digitalWrite(motor12,LOW);
  digitalWrite(motor22,LOW);
  digitalWrite(motor11,HIGH);
  digitalWrite(motor21,HIGH);
}

void backward() {
  analogWrite(motor_v1, velocidad2);
  analogWrite(motor_v2, velocidad2);
  digitalWrite(motor11,LOW);
  digitalWrite(motor21,LOW);
  digitalWrite(motor12,HIGH);
  digitalWrite(motor22,HIGH);
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
>>>>>>> 5fdf71cd521ba6ce1ba412149d170cd1b0fd5c45
}
void loop()
{

<<<<<<< HEAD
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
=======
void loop() {
  full_direction = analogRead(joyY);
  //turn_direction = analogRead(joyX);

  Serial.println(full_direction);

  velocidad1 = map(full_direction, 524, 1023, 0, 225);
  velocidad2 = map(full_direction, 524, 0, 0, 225);
  //velocidad3 = map(turn_direction, 524, 0, 0, 225);
  //velocidad4 = map(turn_direction, 524, 1023, 0, 225);


  if (full_direction > 520) {
    forward();
    delay(15);
  } else if (full_direction < 520) {
    backward();
    delay(15);
  } else {
    digitalWrite(motor11,LOW);
    digitalWrite(motor21,LOW);
    digitalWrite(motor12,LOW);
    digitalWrite(motor22,LOW);
  }

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
>>>>>>> 5fdf71cd521ba6ce1ba412149d170cd1b0fd5c45
