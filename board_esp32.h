#pragma once
//------------------------------------------------------------------------------
// Makelangelo - firmware for various robot kinematic models
// dan@marginallycelver.com 2013-12-26
// Please see http://www.github.com/MarginallyClever/makelangeloFirmware for more information.
//------------------------------------------------------------------------------

// https://www.instructables.com/id/Programming-the-ESP32-Using-Arduino-SoftwareIDE/

// Requires File > Preferences > Additional Boards Manager URL must include https://dl.espressif.com/dl/package_esp32_index.json
// board type should be set to "DOIT ESP32 DEVKIT V1"
// Also see https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/

#if MOTHERBOARD == BOARD_ESP32

#pragma message "Compiling BOARD_ESP32"

// wrong board type set
#ifndef ESP32
  #error "Oops!  Make sure you have 'DOIT ESP32 DEVKIT V1' selected from the 'Tools -> Boards' menu."
#endif

#define MAX_MOTORS                (2)

#define MOTOR_0_LETTER            'X'
#define MOTOR_0_DIR_PIN           (15)
#define MOTOR_0_STEP_PIN          (13)
#define MOTOR_0_ENABLE_PIN        (12)
#define MOTOR_0_LIMIT_SWITCH_PIN  (14)   /* X min */

#define MOTOR_1_LETTER            'Y'
#define MOTOR_1_DIR_PIN           (0)
#define MOTOR_1_STEP_PIN          (4)
#define MOTOR_1_ENABLE_PIN        (5)
#define MOTOR_1_LIMIT_SWITCH_PIN  (16)  /* Y min */

#define MAX_BOARD_SERVOS          (1)
#define SERVO0_PIN                (23)   /* Servo 1 */

#define LIMIT_SWITCH_PIN_LEFT     (MOTOR_0_LIMIT_SWITCH_PIN)
#define LIMIT_SWITCH_PIN_RIGHT    (MOTOR_1_LIMIT_SWITCH_PIN)

//#define HAS_WIFI
#define WIFI_SSID_NAME ""  // WiFi AP SSID Name - define this in local_config.h
#define WIFI_SSID_PASS ""  // WiFi AP SSID Password - define this in local_config.h

#define CLOCK_FREQ            (80000000L)

#undef HAS_SD  
#undef HAS_LCD

#ifdef HAS_TMC2130

#define CS_PIN_0 9
#define CS_PIN_1 10

#endif

#define MAX_SEGMENTS         (64)  // number of line segments to buffer ahead. 

#endif // MOTHERBOARD == BOARD_ESP32 
