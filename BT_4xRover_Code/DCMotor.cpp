/*
   File: DCMotor.cpp
   Author: JKniss
   Date: April 2015
 
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
 
*/

#include <Arduino.h>
#include <DCMotor.h>

/*
   Constructor sets up pinouts per motor and Pin Modes for
   the Ardunio Pro Mini
*/
DCMotor::DCMotor( int motor_num, int motora1pin, int motora2pin, int enPin ){
  // SN754410 Pinout connections
  Motor_Num  = motor_num;
  MotorA1Pin = motora1pin;
  MotorA2Pin = motora2pin;
  PWM_Speed_Pin = enPin;
    
  pinMode(MotorA1Pin, OUTPUT);
  pinMode(MotorA2Pin, OUTPUT);
  pinMode(PWM_Speed_Pin, OUTPUT); 
}

/*
   Motors only need direction and speed settings.
*/
void DCMotor::set_speed( int spd, boolean dir ){
  if(dir){ // Forward
    digitalWrite(MotorA1Pin, LOW);
    digitalWrite(MotorA2Pin, HIGH);
    analogWrite(PWM_Speed_Pin, spd);
    delay(10);
  } else {  // Reverse
    digitalWrite(MotorA1Pin, HIGH);
    digitalWrite(MotorA2Pin, LOW);
    analogWrite(PWM_Speed_Pin, spd);
    delay(10);
  }
    
}

/* 
   Full stop. Decided not to disable them, but you could.
*/
void DCMotor::disable(void){
  // may need to use digitalWrite(<pin>, LOW)
  // but would need to reenable with HIGH?
  analogWrite(PWM_Speed_Pin, 0);
}
