#pragma once
//------------------------------------------------------------------------------
// Makelangelo - firmware for various robot kinematic models
// dan@marginallycelver.com 2013-12-26
// Please see http://www.github.com/MarginallyClever/makelangeloFirmware for more information.
//------------------------------------------------------------------------------

#include "defines.h"


//------------------------------------------------------------------------------
// DEBUG
//------------------------------------------------------------------------------

//#define VERBOSE           (1)  // uncomment to get a lot more serial output.
//#define DEBUG_STEPPING         // uncomment to debug stepper internal timer

//------------------------------------------------------------------------------
// Robot styles supported
//------------------------------------------------------------------------------

/*
 * MAKELANGELO      Makelangelo
 * TRADITIONALXY    !! UNUSED !! gantry 3 axis setup.
 * COREXY           !! UNUSED !! gantry CoreXY setup.
 * ZARPLOTTER       !! UNUSED !! 4 motor, x-shaped 2D motion
 * SKYCAM           !! UNUSED !! 4 motor, x-shaped 3D motion
 * DELTA            !! UNUSED !! 3 arm delta robot, rotary action.  untested.
 * STEWART          !! UNUSED !! 6 arm stewart platform, rotary action.  untested.
 * ARM3             !! UNUSED !! 3DOF palletizing robot arm.
 * SIXI             6DOF robot arm.
 * TRADITIONAL6     !! UNUSED !! 6 axis machine, no restrictions.
 * SCARA            !! UNUSED !! 2 axis SCARA.
 */

 #define MACHINE_STYLE SIXI

//------------------------------------------------------------------------------
// LCD panels supported
//------------------------------------------------------------------------------
/**
 * LCD_NONE         No LCD
 * LCD_IS_128X64    reprapdiscount Full Graphic Smart LCD Controller
 * LCD_IS_SMART     reprapdiscount Smart LCD Controller (including XXL model)
 */

#define LCD_TYPE LCD_NONE


//how many stepper motor
#define NUM_MOTORS  6
