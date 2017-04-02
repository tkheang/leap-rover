// Leap Rover (Arduino)
// Timothy Kheang and Saarthak Ahlawat
// Created for LA Hacks 2017
#include <SoftwareSerial.h>
#include <AFMotor.h>
SoftwareSerial XBee(2, 3); // set up XBee TX and RX

AF_DCMotor motorL(1); // digital pin 11
AF_DCMotor motorR(2); // digital pin 3

int serialInput;

void setup() {
  XBee.begin(9600);
  Serial.begin(9600);
  pinMode(5, OUTPUT); // electromagnet 1
  pinMode(6, OUTPUT); // electromagnet 2
  motorL.setSpeed(63); // set up motor speeds
  motorR.setSpeed(63);
}

void loop() {
  if (XBee.available())
  {
    serialInput = XBee.read();
    Serial.println(serialInput);
    // forward movement
    if (serialInput == 'F')
    {
      motorL.run(FORWARD);
      motorR.run(FORWARD);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
    // backwards movement
    else if (serialInput == 'B')
    {
      motorL.run(BACKWARD);
      motorR.run(BACKWARD);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
    // rotate right
    else if (serialInput == 'R')
    {
      motorL.run(FORWARD);
      motorR.run(RELEASE);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
    // rotate left
    else if (serialInput == 'L')
    {
      motorL.run(RELEASE);
      motorR.run(FORWARD);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
    // stop all movement
    else if (serialInput == 'S')
    {
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
    }
    // forward movement w/ electromagnets on
    else if (serialInput == 'V')
    {
      motorL.run(FORWARD);
      motorR.run(FORWARD);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    // backwards movement w/ electromagnets on
    else if (serialInput == 'W')
    {
      motorL.run(BACKWARD);
      motorR.run(BACKWARD);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    // rotate right w/ electromagnets on
    else if (serialInput == 'X')
    {
      motorL.run(FORWARD);
      motorR.run(RELEASE);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    // rotate left w/ electromagnets on
    else if (serialInput == 'Y')
    {
      motorL.run(RELEASE);
      motorR.run(FORWARD);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
    // stop all movement w/ electromagnets on
    else if (serialInput == 'Z')
    {
      motorL.run(RELEASE);
      motorR.run(RELEASE);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
    }
  } 
}
