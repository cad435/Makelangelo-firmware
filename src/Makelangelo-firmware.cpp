//------------------------------------------------------------------------------
// Makelangelo - firmware for various robot kinematic models
// dan@marginallycelver.com 2013-12-26
// Please see http://www.github.com/MarginallyClever/makelangeloFirmware for more information.
//------------------------------------------------------------------------------


// (unofficial) Version 2 started by cad435 on 27.01.2021

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
#include "config.h"
#include "gcode/parser.h"

//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------

extern GCodeParser parser;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


// runs once on machine start
void setup() {
  Serial.begin(115200);

}

// after setup runs over and over.
void loop() {

  uint8_t cProcessed = parser.fetchAndParse();

  if (cProcessed>0)
  {
        Serial.print("NumChars: "); Serial.print(cProcessed);
      Serial.print(" CodeLetter: "); Serial.print(parser.command_letter);
      Serial.print(" CodeNum: "); Serial.print(parser.codenum);
      Serial.print(" SubCodeNum: "); Serial.print(parser.subcode);

      if (parser.seen('L')) {Serial.print(" L:"); Serial.print(parser.value_long());}
      if (parser.seen('R')) {Serial.print(" R:"); Serial.print(parser.value_long());}
      if (parser.seen('U')) {Serial.print(" U:"); Serial.print(parser.value_long());}
      if (parser.seen('V')) {Serial.print(" V:"); Serial.print(parser.value_long());}
      if (parser.seen('W')) {Serial.print(" W:"); Serial.print(parser.value_long());}
      if (parser.seen('T')) {Serial.print(" T:"); Serial.print(parser.value_long());}
      if (parser.seen('J')) {Serial.print(" J:"); Serial.print(parser.value_long());}

      Serial.println();
  }


}


