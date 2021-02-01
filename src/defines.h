#pragma once
#include <Arduino.h>

enum AxisEnum : uint8_t {
  L_AXIS   = 0,
  R_AXIS   = 1,
  U_AXIS   = 2,
  V_AXIS   = 3,
  W_AXIS   = 4,
  T_AXIS   = 5,
  ALL_AXES = 0xFE, NO_AXIS = 0xFF
};


#define SERIAL_EOL()                SERIAL_CHAR('\n')

#define STR_UNKNOWN_COMMAND                 "Unknown command: \""
#define STR_ENQUEUEING                      "enqueueing \""
#define STR_ERROR                           "Error: "
#define STR_RESEND                          "Resend: "

#define ERRORPREFIX "Error:"
#define ECHOPREFIX "echo:"
