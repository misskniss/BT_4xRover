/*

  File: BT_4xRover.ino
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


 Sensoduino Android Phone App -> HC-05 Bluetooth Module -> Arduino Pro Mini

 This module parses the data sent from the SensoDuino Android App, 
 (reading Accelerometer Sensor data from the phone) into 
 standard X, Y, Z whole number values from -10 to 10 for each axis. 
 These values are then mapped to the 0 - 255 PWM speed range for 
 PWM control of some device. (Minimum speed is 0 or 100)
 
 X values: 
            -1 to 1     stop
            -2 to -10   (increasingly) right
             2 to 10    (incrasingly) left
 Y values: 
            -1 to 1     stop
            -2 to -10    slowest to fastest
             2 to 10     reverse, slowest to fastest
 Z values:
            parsed but not used at this time 
            
 The SensoDuino app is v0.160 by Hazim Bitar (2013) from the 
 Android Play Store. My phone is the Galaxy S5, Android v4.4.2
*/

#include <Arduino.h>
#include <Drivetrain.h>

unsigned int startNum, readingCount;
int X, Y, Z;
unsigned int x_dec, y_dec, z_dec;
Drivetrain drive;

void setup() {
  Serial.begin(9600);
}

/* 
   Collect and parse the sensor data via the serial 
   connection/Bluetooth HC-05 module connected to the 
   phone app and transmitting to the Arduino Pro Mini
   Example reading: 
     startNum,readingCount,X,Y,Z
     >1,2086,-0.9588778,3.430891,9.527127
*/

void loop() {
  
  if(Serial.available() && Serial.read() == '>'){
    
    startNum = Serial.parseInt();
    readingCount = Serial.parseInt();
    X = Serial.parseInt();
    x_dec = Serial.parseInt(); // truncate the decimal
    Y = Serial.parseInt();
    y_dec = Serial.parseInt(); // truncate the decimal
    Z = Serial.parseInt();
    z_dec = Serial.parseInt();
    drive.update_speed(X, Y);
    
  } 
  
}

