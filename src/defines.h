#pragma once

//------------------------------------------------------------------------------
// Robot styles supported
//------------------------------------------------------------------------------

#define MAKELANGELO   1   // polargraph like Makelangelo
#define TRADITIONALXY 3   // gantry 3 axis setup.
#define COREXY        2   // gantry CoreXY setup.
#define ZARPLOTTER    4   // 4 motor, x-shaped 2D motion
#define SKYCAM        5   // 4 motor, x-shaped 3D motion
#define DELTA         6   // 3 arm delta robot, rotary action.  untested.
#define STEWART       7   // 6 arm stewart platform, rotary action.  untested.
#define ARM3          8   // 3DOF palletizing robot arm.
#define SIXI_MEGA     9   // 6DOF robot arm. With Mega board 
#define TRADITIONAL6  10  // 6 axis machine, no restrictions.
#define SCARA         11  // 2 axis SCARA.


//------------------------------------------------------------------------------
// Microcontrollers supported
//------------------------------------------------------------------------------

#define BOARD_RUMBA        1  // Reprap discount Rumba board
#define BOARD_RAMPS        2  // Mega2560 + Ramps 1.4
#define BOARD_SANGUINOLULU 3  // Sanguinolulu
#define BOARD_TEENSYLU     4  // Teensylu
#define BOARD_WEMOS        5  // Wemos D1 R2 + CNC Shield v3 (see board_wemos.h)
#define BOARD_SIXI_MEGA    6  // Arduino Mega + custom shield for Sixi 2 robot
#define BOARD_CNCV3        7  // Mega2560 + CNC Shield v3
#define BOARD_ESP32        8  // ESP32 + Marginally Clever Polargraph PCB.
#define BOARD_SKRPRO1_2    9  // SKR Pro 1.2

//------------------------------------------------------------------------------
// LCD panels supported
//------------------------------------------------------------------------------

#define LCD_NONE      0
#define LCD_IS_128X64 1  // reprapdiscount Full Graphic Smart LCD Controller
#define LCD_IS_SMART  2  // reprapdiscount Smart LCD Controller (including XXL model)


#define MOTOR_LETTERS {'L', 'R', 'U', 'V', 'W', 'T'}