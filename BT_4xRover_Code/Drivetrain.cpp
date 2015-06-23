/* 
   File: Drivetrain.cpp
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
 
 
   This module creates a drivetrain instance with 4 motors (wheels)
   and sets motor speeds based on passed-in accelerometer X & Y values.
   The values are parsed to determine direction (fwd/rev), heading (rt/lt)
   and speeds. 
 
 */

#include <Arduino.h>
#include <DCMotor.h>
#include <Drivetrain.h>

bool FWD = true;
bool REV = false;

// create the new operator not supported by Arduino. Boo.
void* operator new(size_t size) { return malloc(size); }
void operator delete(void* ptr) { free(ptr); }

/* 
    Create an instance of the drive train with 4 motors
    that are precondifugrd with all the appropriate pinouts.
    Motor constructor for the SN754410 H-Bridge pins:
    Ex: DCMotor(motorNum, 1A Pin, 2A Pin, EnablePin)
*/
Drivetrain::Drivetrain(){
    
    frontLeft  = new DCMotor(1 , 4, 2,  3);
    frontRight = new DCMotor(2,  7, 8,  5);
    rearLeft   = new DCMotor(3, 10, 11, 6);
    rearRight  = new DCMotor(4, 13, 12, 9);
}


/*
   Used to slow the motor before changing the direction to avoid
   jolting.
*/
void Drivetrain::ramp_down( int spd, int dir ){
    /*
    int c; // might use this later...
    for(c = spd; c >= 0; c--){
      frontRight->set_speed(c, dir);
      rearRight->set_speed(c, dir);
      frontLeft->set_speed(c, dir);
      rearLeft->set_speed(c, dir);
     
    }
     */
    frontRight->disable();
    rearRight->disable();
    frontLeft->disable();
    rearLeft->disable();
}


/*
    Maintain the left wheels' speed and slow the right
    wheels in proportion to the "master speed" setting.
    Smaller spd values = wider turns.
*/
void Drivetrain::turn_right( int spd ){
    
    _leftWheels = _speedVal;
    _rightWheels = _speedVal - (_increment*spd); 
    
    
    frontRight->set_speed(_rightWheels, _DIR);
    rearRight->set_speed(_rightWheels, _DIR);
    frontLeft->set_speed(_leftWheels, _DIR);
    rearLeft->set_speed(_leftWheels, _DIR);
    
}


/* 
    Maintain the right wheels' speed and slow the left
    wheels in proportion to the "master speed" setting.
    Smaller spd values = wider turns.
*/
void Drivetrain::turn_left( int spd ){
    
    _rightWheels = _speedVal;
    _leftWheels = _speedVal - (_increment*spd);
    
    frontRight->set_speed(_rightWheels, _DIR);
    rearRight->set_speed(_rightWheels, _DIR);
    frontLeft->set_speed(_leftWheels, _DIR);
    rearLeft->set_speed(_leftWheels, _DIR);
    
}


/*
    Map master speed (100 - 255) to passed in abs values from 2 - 10.
    Calculation of the increment/decrement value for turning done here.
    Values of 0 or 1 set the speed to zero and are not handled here.
*/
void Drivetrain::set_speed_val( int spd ){
    switch (spd){
        case 2:
            _speedVal = 100;
            break;
        case 3:
            _speedVal = 122;
            break;
        case 4:
            _speedVal = 144;
            break;
        case 5:
            _speedVal = 166;
            break;
        case 6:
            _speedVal = 188;
            break;
        case 7:
            _speedVal = 210;
            break;
        case 8:
            _speedVal = 232;
            break;
        case 9:
            _speedVal = 250;
            break;
        case 10:
            _speedVal = 250;
            break;
        default:
            _speedVal = 0;
            
    }
    
    /* Pre-Calculate the incr value. */
    _increment = (_speedVal/10);
    Serial.print("Master Speed: ");
    Serial.println(_speedVal);
    Serial.print("Increment: ");
    Serial.println(_increment);
    
}

int Drivetrain::get_speed_val( void ){
    return _speedVal;
}


/* 
    Set the direction.
    0: reverse
    1: forward
 */
void Drivetrain::set_direction( bool dir ){
	_DIR = dir;
    //Serial.print("Direction: ");
    //Serial.println(_DIR);
}

int Drivetrain::get_direction( void ){
    return _DIR;
}

/*
    Use the passed in X and Y values to set master speed and
    and determine if we are going left (x >= 2) or right (x <= -2), 
    and forward (y <= -2) or back (y >= 2). If both X and Y are
    between -1 and 1 (phone laying flat & face up) the stop the rover.
*/
void Drivetrain::update_speed(int x, int y){
    
    // if y and x are between -1 and 1, stop
    if ( y <= 1 && y >= -1 ){
        if (x <= 1 && x>= -1){
            set_speed_val(0);
            // full stop
            frontLeft->disable();
            frontRight->disable();
            rearLeft->disable();
            rearRight->disable();
        }
        
        // x dictates speed when y is -1 to 0
        if (x >= 2){
            set_speed_val( x );
            turn_left( x );
        }
        if (x <= -2){
            set_speed_val( abs(x) );
            turn_right( abs(x) );
        }
    }
    
    // REVERSE with Turning
    if (y >= 2){
        
        // check & set direction
        int direction = get_direction();
        if(direction == FWD){
            ramp_down( get_speed_val(), direction );
            set_direction( REV );
        }
      
        set_speed_val( y );
        
        if( x >= 2 ){
            turn_left( _speedVal );
            //turn_left( get_speed_val() );
        }
        if(x <= -2 ){
            turn_right( _speedVal );
            //turn_right( get_speed_val() );
        }
        
        frontLeft->set_speed(_speedVal, _DIR);
        frontRight->set_speed(_speedVal, _DIR);
        rearLeft->set_speed(_speedVal, _DIR);
        rearRight->set_speed(_speedVal, _DIR);
        
    }
    
    // FORWARD with Turning
    if ( y <= -2){
        
        // check & set direction
        int direction = get_direction();
        if(direction == REV){
            ramp_down( get_speed_val(), direction );
            set_direction( FWD );
        }
        
        set_speed_val( abs(y) );
        
        if( x >= 2 ){
            turn_left( _speedVal );
        }
        if(x <= -2 ){
            turn_right( _speedVal );
        }
        
        frontLeft->set_speed(_speedVal, _DIR);
        frontRight->set_speed(_speedVal, _DIR);
        rearLeft->set_speed(_speedVal, _DIR);
        rearRight->set_speed(_speedVal, _DIR);

    }
    
    Serial.print("X: ");
    Serial.println(x);
    Serial.print("Y: ");
    Serial.println(y);


}