/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * parser.cpp - Parser for a GCode line, providing a parameter interface.
 */

#include "parser.h"



char *GCodeParser::command_ptr,
     *GCodeParser::string_arg,
     *GCodeParser::value_ptr;
char GCodeParser::command_letter;
uint16_t GCodeParser::codenum;

#ifdef USE_GCODE_SUBCODES
  uint8_t GCodeParser::subcode;
#endif

#ifdef GCODE_MOTION_MODES
  int16_t GCodeParser::motion_mode_codenum = -1;
  #if ENABLED(USE_GCODE_SUBCODES)
    uint8_t GCodeParser::motion_mode_subcode;
  #endif
#endif

#ifdef FASTER_GCODE_PARSER
  // Optimized Parameters
  uint32_t GCodeParser::codebits;  // found bits
  uint8_t GCodeParser::param[26];  // parameter offsets from command_ptr
#else
  char *GCodeParser::command_args; // start of parameters
#endif

// Create a global instance of the GCode parser singleton
GCodeParser parser;

/**
 * Clear all code-seen (and value pointers)
 *
 * Since each param is set/cleared on seen codes,
 * this may be optimized by commenting out ZERO(param)
 */
void GCodeParser::reset() {
  string_arg = nullptr;                 // No whole line argument
  command_letter = '?';                 // No command letter
  codenum = 0;                          // No command code
  TERN_(USE_GCODE_SUBCODES, subcode = 0); // No command sub-code
  #ifdef FASTER_GCODE_PARSER
    codebits = 0;                       // No codes yet
    //ZERO(param);                      // No parameters (should be safe to comment out this line)
  #endif
}

uint8_t GCodeParser::fetchAndParse()
{
  uint8_t numCharRead = 0;
  char buffer[58] = {0};
  if (Serial.available())
  {
    numCharRead = Serial.readBytesUntil('\n', buffer, 58);
    parser.parse(buffer);
  }

  return numCharRead;
}


#ifdef GCODE_QUOTED_STRINGS

  // Pass the address after the first quote (if any)
  char* GCodeParser::unescape_string(char* &src) {
    if (*src == '"') ++src;     // Skip the leading quote
    char * const out = src;     // Start of the string
    char *dst = src;            // Prepare to unescape and terminate
    for (;;) {
      char c = *src++;          // Get the next char
      switch (c) {
        case '\\': c = *src++; break; // Get the escaped char
        case '"' : c = '\0'; break;   // Convert bare quote to nul
      }
      if (!(*dst++ = c)) break; // Copy and break on nul
    }
    return out;
  }

#endif

// Populate all fields by parsing a single line of GCode
// 58 bytes of SRAM are used to speed up seen/value
void GCodeParser::parse(char *p) {

  reset(); // No codes to report

  //if GCODE_CASE_INSENSITIVE is enabled, make all letters uppercase
  auto uppercase = [](char c) {
    if (TERN0(GCODE_CASE_INSENSITIVE, WITHIN(c, 'a', 'z')))
      c += 'A' - 'a';
    return c;
  };

  // Skip spaces
  while (*p == ' ') ++p;

  // Skip N[-0-9] if included in the command line
  if (uppercase(*p) == 'N' && NUMERIC_SIGNED(p[1])) {
    //TERN_(FASTER_GCODE_PARSER, set('N', p + 1)); // (optional) Set the 'N' parameter value
    p += 2;                  // skip N[-0-9]
    while (NUMERIC(*p)) ++p; // skip [0-9]*
    while (*p == ' ')   ++p; // skip [ ]*
  }

  // *p now points to the current command, which should be G, M, or T
  command_ptr = p;

  // Get the command letter, which must be G, M, or T
  const char letter = uppercase(*p++);

  // Nullify asterisk and trailing whitespace
  char *starpos = strchr(p, '*');
  if (starpos) {
    --starpos;                          // *
    while (*starpos == ' ') --starpos;  // spaces...
    starpos[1] = '\0';
  }

  // Bail if the letter is not G, M, or T
  // (or a valid parameter for the current motion mode)
  switch (letter) {

    case 'G': case 'M': case 'T': case 'D':
      // Skip spaces to get the numeric part
      while (*p == ' ') p++;

      // Bail if there's no command code number
      if (!TERN(SIGNED_CODENUM, NUMERIC_SIGNED(*p), NUMERIC(*p))) return;

      // Save the command letter at this point
      // A '?' signifies an unknown command
      command_letter = letter;

      {
        #ifdef SIGNED_CODENUM
          int sign = 1; // Allow for a negative code like D-1 or T-1
          if (*p == '-') { sign = -1; ++p; }
        #endif

        // Get the code number - integer digits only
        codenum = 0;

        do { codenum = codenum * 10 + *p++ - '0'; } while (NUMERIC(*p));

        // Apply the sign, if any
        TERN_(SIGNED_CODENUM, codenum *= sign);
      }

      // Allow for decimal point in command
      #ifdef USE_GCODE_SUBCODES
        if (*p == '.') {
          p++;
          while (NUMERIC(*p))
            subcode = subcode * 10 + *p++ - '0';
        }
      #endif

      // Skip all spaces to get to the first argument, or nul
      while (*p == ' ') p++;
      break;

    default: return;
  }

  // The command parameters (if any) start here, for sure!

  #ifndef FASTER_GCODE_PARSER
    command_args = p; // Scan for parameters in seen()
  #endif

  // Only use string_arg for these M codes
  if (letter == 'M') switch (codenum) {
    case 23: case 28: case 30: case 117 ... 118: case 928:
      string_arg = unescape_string(p);
      return;
    default: break;
  }


  /**
   * Find all parameters, set flags and pointers for fast parsing
   *
   * Most codes ignore 'string_arg', but those that want a string will get the right pointer.
   * The following loop assigns the first "parameter" having no numeric value to 'string_arg'.
   * This allows M0/M1 with expire time to work: "M0 S5 You Win!"
   * For 'M118' you must use 'E1' and 'A1' rather than just 'E' or 'A'
   */
  #ifdef GCODE_QUOTED_STRINGS
    bool quoted_string_arg = false;
  #endif
  string_arg = nullptr;
  while (const char param = uppercase(*p++)) {  // Get the next parameter. A NUL ends the loop

    // Special handling for M32 [P] !/path/to/file.g#
    // The path must be the last parameter
    if (param == '!' && is_command('M', 32)) {
      string_arg = p;                           // Name starts after '!'
      char * const lb = strchr(p, '#');         // Already seen '#' as SD char (to pause buffering)
      if (lb) *lb = '\0';                       // Safe to mark the end of the filename
      return;
    }

    #ifdef GCODE_QUOTED_STRINGS
      if (!quoted_string_arg && param == '"') {
        quoted_string_arg = true;
        string_arg = unescape_string(p);
      }
    #endif

    #ifdef FASTER_GCODE_PARSER
      // Arguments MUST be uppercase for fast GCode parsing
      #define PARAM_OK(P) WITHIN((P), 'A', 'Z')
    #else
      #define PARAM_OK(P) true
    #endif

    if (PARAM_OK(param)) {

      while (*p == ' ') p++;                    // Skip spaces between parameters & values

      #ifdef GCODE_QUOTED_STRINGS
        const bool is_str = (*p == '"'), has_val = is_str || valid_float(p);
        char * const valptr = has_val ? is_str ? unescape_string(p) : p : nullptr;
      #else
        const bool has_val = valid_float(p);
        #ifdef FASTER_GCODE_PARSER
          char * const valptr = has_val ? p : nullptr;
        #endif
      #endif


      if (!has_val && !string_arg) {            // No value? First time, keep as string_arg
        string_arg = p - 1;
      }

      TERN_(FASTER_GCODE_PARSER, set(param, valptr)); // Set parameter exists and pointer (nullptr for no value)
    }
    else if (!string_arg) {                     // Not A-Z? First time, keep as the string_arg
      string_arg = p - 1;
    }

    if (!WITHIN(*p, 'A', 'Z')) {                // Another parameter right away?
      while (*p && DECIMAL_SIGNED(*p)) p++;     // Skip over the value section of a parameter
      while (*p == ' ') p++;                    // Skip over all spaces
    }
  }
}

void GCodeParser::unknown_command_warning() {
  Serial_Echo_msg(STR_UNKNOWN_COMMAND, command_ptr, "\"");
}