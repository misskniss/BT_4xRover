#ifndef DCMotor_h
#define DCMotor_h

/* 
   File: DCMotor.h
   Author: Jkniss
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

class DCMotor {
  private:
    
    int Motor_Num;        // motor num
    int MotorA1Pin;  	   // 1A on HBridge, assumes: Forward = set LOW
    int MotorA2Pin;       // 2A on Hbridge, assumes: Forward = set HIGH
    int PWM_Speed_Pin;    // Enable Pin, use PWM
    
  public:
  
    DCMotor( int motor_num, int motora1pin, int motora2pin, int enPin );
    void set_speed( int spd, boolean dir );
    void disable(void);
};

#endif
