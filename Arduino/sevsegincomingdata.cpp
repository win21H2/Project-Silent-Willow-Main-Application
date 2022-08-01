#include <SoftwareSerial.h>
#include <AccelStepper.h>

SoftwareSerial Bluetooth(A5, 0);
AccelStepper LB(1, 3, 2);
AccelStepper LF(1, 5, 4);
AccelStepper RB(1, 7, 6);
AccelStepper RF(1, 9, 8);

int wheelSpeed = 1500;
int dataIn;

const int latchPin = 12;
const int clockPin = 8;
const int dataPin = 11;

/*
0 - 252
1 - 96
2 - 218
3 - 242
4 - 102
5 - 182
6 - 190
7 - 224
8 - 254
9 - 246
*/

void setup (){
  LB.setMaxSpeed(3000);
  LF.setMaxSpeed(3000);
  RB.setMaxSpeed(3000);
  RF.setMaxSpeed(3000);

  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  Bluetooth.begin(9600);
  Serial.begin(38400);
}

void loop(){
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read();
    if (dataIn == 0) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (252));
      digitalWrite(latchPin,HIGH);
      stopmoving();
    }
    if (dataIn == 2) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (218));
      digitalWrite(latchPin,HIGH);
      forward();
    }
    if (dataIn == 1) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (96));
      digitalWrite(latchPin,HIGH);
      backward();
    }
    if (dataIn == 3) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (242));
      digitalWrite(latchPin,HIGH);
      sidewaysleft();
    }
    if (dataIn == 4) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (102));
      digitalWrite(latchPin,HIGH);
      sidewaysright();
    }
    if (dataIn == 5) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (182));
      digitalWrite(latchPin,HIGH);
      rotateleft();
    }
    if (dataIn == 6) {
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST, (190));
      digitalWrite(latchPin,HIGH);
      rotateright();
    }
  }

  LB.runSpeed();
  LF.runSpeed();
  RB.runSpeed();
  RF.runSpeed();
}

void forward() {
  LF.setSpeed(-wheelSpeed);
  LB.setSpeed(wheelSpeed);
  RF.setSpeed(wheelSpeed);
  RB.setSpeed(-wheelSpeed);
  Serial.println("forward");
}
void backward() {
  LF.setSpeed(wheelSpeed);
  LB.setSpeed(-wheelSpeed);
  RF.setSpeed(-wheelSpeed);
  RB.setSpeed(wheelSpeed);
  Serial.println("backward");
}
void sidewaysright() {
  LF.setSpeed(wheelSpeed);
  LB.setSpeed(-wheelSpeed);
  RF.setSpeed(wheelSpeed);
  RB.setSpeed(-wheelSpeed);
  Serial.println("sidewaysright");
}
void sidewaysleft() {
  LF.setSpeed(-wheelSpeed);
  LB.setSpeed(wheelSpeed);
  RF.setSpeed(-wheelSpeed);
  RB.setSpeed(wheelSpeed);
  Serial.println("sidewaysleft");
}
void rotateleft() {
  LF.setSpeed(wheelSpeed);
  LB.setSpeed(wheelSpeed);
  RF.setSpeed(wheelSpeed);
  RB.setSpeed(wheelSpeed);
  Serial.println("rotateleft");
}
void rotateright() {
  LF.setSpeed(-wheelSpeed);
  LB.setSpeed(-wheelSpeed);
  RF.setSpeed(-wheelSpeed);
  RB.setSpeed(-wheelSpeed);
  Serial.println("rotateright");
}
void stopmoving() {
  LF.setSpeed(0);
  LB.setSpeed(0);
  RF.setSpeed(0);
  RB.setSpeed(0);
  Serial.println("stopmoving");
}