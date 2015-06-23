/* 
   File:   4WheelerDCMotorTest.ino
   Author: JKniss
   Date:   April 2015

    ******************************************************************** 
    Copyright 2015 Jenny Kniss

    This file is part of BT_4xRover.

    BT_4xRover is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    BT_4xRover is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with BT_4xRover.  If not, see <http://www.gnu.org/licenses/>.
    ********************************************************************  



   4-Wheeled Rover with 2 SN754410 H-Bridge ICs and Arduino Pro Mini
   Power: 9-Volt battery *per* H-Bridge 
             (motor sets draw enough power to each need their own)
          9-Volt Battery -> LM7805 -> 5V -> Arduino VCC Pin 
             (also powers bluetooth & H-Bridges)
   Wiring: 
   SN754410 Pinouts
   ----------V----------
   1 (1/2 EN)  (VCC1) 16
   2 (1A)        (4A) 15
   3 (1Y)        (4Y) 14
   4 (GND)      (GND) 13
   5 (GND)      (GND) 12
   6 (2Y)        (5Y) 11
   7 (2A)        (5A) 10
   8 (M VCC2) (3/4 EN) 9
   ---------------------
   
  Using a rainbow ribbon cable with 8 wires *per* HBridge
  H-Bridge 1 (front wheels):                H-Bridge 2 (rear-wheels)
  H-PIN: Arduino Pin                        H-PIN: Arduino Pin 
      1: PWM Pin 3      (white)                 1: PWM Pin 6      (white)
      2: Pin 4          (grey)                  2: Pin 10         (grey)
      3: Motor 1 lead 1 (white)                 3: Motor 3 lead 1 (yellow)
  4 & 5: GND                                4 & 5: GND
      6: Motor 1 lead 2 (yellow)                6: Motor 3 lead 2 (white)
      7: Pin 2          (purple)                7: Pin 11         (purple)
      8: To 9Volt motor 1&2 supply #1 (Pos)     8: To 9Volt #2 motor 3&4 supply (pos) 
      9: PWM Pin 5      (green)                 9: PWM Pin 9      (green)
     10: Pin 7          (yellow)               10: Pin 13         (yellow)
     11: Motor 2 lead 1 (yellow)               11: Motor 4 lead 1 (white)
12 & 13: GND                              12 & 13: GND
     14: Motor 2 lead 2 (white)                14: Motor 4 lead 2 (yellow)
     15: Pin 8          (orange)               15: Pin 12         (orange)
     16: To 5V VCC line powering the Mini      16: To 5V VCC Line powering the Mini

  Rotary Encoders: (using 2 4-wire ribbons [blk/wht/gry/prpl] & [grn/blu/prpl/gry] )
         ENC A: SIGA Pin A0 - white - front - 
         ENC A: SIGB Pin A6 - black - front - 
         ENC B: SIGA Pin A1 - purple- front - 
         ENC B: SIGB Pin A7 - grey  - front -
         ENC C: SIGA Pin A2 - green - rear  -
         ENC C: SIGB Pin A4 - blue  - rear  -
         ENC D: SIGA Pin A3 - purple- rear  -
         ENC D: SIGB Pin A5 - grey  - rear  -
*/

#define ENCA_A A0
#define ENCA_B A6 // not useable :(
#define ENCB_A A1
#define ENCB_B A7 // not usable :(
#define ENC1_A A2
#define ENC1_B A4
#define ENC4_A A3
#define ENC4_B A5


int allSpeed = 100;

// Front Left
int speedPin1 = 3; //pwm
int motorA1Pin = 4;
int motorA2Pin = 2;
int speedVal1;
// Front Right
int speedPin2 = 5; //pwm
int motorA3Pin = 8;
int motorA4Pin = 7;
int speedVal2;
// Rear Left
int speedPin3 = 6; //pwm
int motorA5Pin = 11;
int motorA6Pin = 10;
int speedVal3;
// Rear Right
int speedPin4 = 9; //pwm
int motorA7Pin = 13;
int motorA8Pin = 12;
int speedVal4;

void setup(){
  // serial settings
  Serial.begin(115200);
  Serial.println("Start");
  
  
  // Encoders
  // ENCA
  pinMode(ENCA_A,INPUT); // set to input
  digitalWrite(ENCA_A,HIGH); // enable pullup
  pinMode(ENCA_B,INPUT); // set to input
  //digitalWrite(ENCA_B,HIGH); // enable pullup
  // ENCB
  pinMode(ENCB_A,INPUT); // set to input
  digitalWrite(ENCB_A,HIGH); // enable pullup
  pinMode(ENCB_B,INPUT); // set to input
  //digitalWrite(ENCB_B,HIGH); // enable pullup
  // ENCC
  pinMode(ENC1_A,INPUT); // set to input
  digitalWrite(ENC1_A,HIGH); // enable pullup
  pinMode(ENC1_B,INPUT); // set to input
  digitalWrite(ENC1_B,HIGH); // enable pullup
  // ENCD
  pinMode(ENC4_A,INPUT); // set to input
  digitalWrite(ENC4_A,HIGH); // enable pullup
  pinMode(ENC4_B,INPUT); // set to input
  digitalWrite(ENC4_B,HIGH); // enable pullup
  
  // Wheels
  // FRONT LEFT
  pinMode(motorA1Pin, OUTPUT);
  pinMode(motorA2Pin, OUTPUT);
  pinMode(speedPin1, OUTPUT);
  analogWrite(speedPin1, 0);
  
   // FRONT RIGHT
  pinMode(motorA3Pin, OUTPUT);
  pinMode(motorA4Pin, OUTPUT);
  pinMode(speedPin2, OUTPUT);
  analogWrite(speedPin2, 0);
  
  // REAR LEFT
  pinMode(motorA5Pin, OUTPUT);
  pinMode(motorA6Pin, OUTPUT);
  pinMode(speedPin3, OUTPUT);
  analogWrite(speedPin3, 0);
  
  // REAR RIGHT
  pinMode(motorA7Pin, OUTPUT);
  pinMode(motorA8Pin, OUTPUT);
  pinMode(speedPin4, OUTPUT);
  analogWrite(speedPin4, 0);
  
  
}

void loop() {
  
  // FRONT LEFT FORWARD
  digitalWrite(motorA1Pin, LOW);
  digitalWrite(motorA2Pin, HIGH);
  analogWrite(speedPin1, allSpeed);
  delay(500);
  analogWrite(speedPin1, 0);
  
  // FRONT RIGHT FORWARD
  digitalWrite(motorA3Pin, HIGH);
  digitalWrite(motorA4Pin, LOW);
  analogWrite(speedPin2, allSpeed);
  delay(500);
  analogWrite(speedPin2, 0);
  
  // REAR LEFT FORWARD
  digitalWrite(motorA5Pin, HIGH);
  digitalWrite(motorA6Pin, LOW);
  analogWrite(speedPin3, allSpeed);
  delay(100);
  analogWrite(speedPin3, 0);
  
  // REAR RIGHT FORWARD
  digitalWrite(motorA7Pin, LOW);
  digitalWrite(motorA8Pin, HIGH);
  analogWrite(speedPin4, allSpeed);
  delay(100);
  analogWrite(speedPin4, 0);
  
  
  // FRONT LEFT REVERSE
  digitalWrite(motorA1Pin, HIGH);
  digitalWrite(motorA2Pin, LOW);
  analogWrite(speedPin1, allSpeed);
  delay(500);
  analogWrite(speedPin1, 0);
  
  // FRONT RIGHT REVERSE
  digitalWrite(motorA3Pin, LOW);
  digitalWrite(motorA4Pin, HIGH);
  analogWrite(speedPin2, allSpeed);
  delay(500);
  analogWrite(speedPin2, 0);
  
  // REAR LEFT REVERSE
  digitalWrite(motorA5Pin, LOW);
  digitalWrite(motorA6Pin, HIGH);
  analogWrite(speedPin3, allSpeed);
  delay(100);
  analogWrite(speedPin3, 0);
  
  // REAR RIGHT REVERSE
  digitalWrite(motorA7Pin, HIGH);
  digitalWrite(motorA8Pin, LOW);
  analogWrite(speedPin4, allSpeed);
  delay(100);
  analogWrite(speedPin4, 0);
  

  // Note: Encoder A and B are only possible if you have 8 analog
  //       inputs that you can do a digital read on. Pro Mini has
  //       8 but only 6 are actually usable. You can't use encoders if
  //       you are using 4 wheels.
    Serial.print("Encoder A: ");
  Serial.println(digitalRead(ENCA_A));
  Serial.println(analogRead(ENCA_B));
  delay(100);
    Serial.print("Encoder B: ");
  Serial.println(digitalRead(ENCB_A));
  Serial.println(analogRead(ENCB_B));
  delay(100);
    Serial.print("Encoder 1: ");
  Serial.println(digitalRead(ENC1_A));
  Serial.println(digitalRead(ENC1_B));
  delay(100);
    Serial.print("Encoder 4: ");
  Serial.println(digitalRead(ENC4_A));
  Serial.println(digitalRead(ENC4_B));
  delay(100);
  
  
} //loop()
