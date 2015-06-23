#ifndef DriveTrain_h
#define DriveTrain_h

/*
   File: Drivetrain.h
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
#include <stdlib.h> 


class Drivetrain{
  private:
    bool _DIR;
    int _speedVal;
    int _increment;
    int _leftWheels;
    int _rightWheels;

    DCMotor* frontLeft; 
    DCMotor* frontRight;
    DCMotor* rearLeft; 
    DCMotor* rearRight;
    
  
  public:
    Drivetrain();
    void ramp_down( int spd, int dir ); //spd is an x or y val not "speed"
    void turn_right( int spd );
    void turn_left( int spd );
    void set_speed_val( int spd );
    int  get_speed_val( void );  // not used at this time
    void set_direction( bool dir );
    int get_direction( void );
    void update_speed( int x, int y );
  
};


#endif
