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
 * 
 * Modified for Makelangelo Firmware
 * 
 * 
 * 
 */
#pragma once

/**
 * gcode.h - Temporary container for all gcode handlers
 */

/**
 * -----------------
 * G-Codes in Makelangelo
 * -----------------
 *
 * Helpful G-code references:
 *  - https://marlinfw.org/meta/gcode
 *  - https://reprap.org/wiki/G-code
 *  - https://linuxcnc.org/docs/html/gcode.html
 *
 * Help to document Marlin's G-codes online:
 *  - https://github.com/MarlinFirmware/MarlinDocumentation
 *
 * -----------------
 *
 * "D" Codes
 * 
 *  D0 [Lnn] [Rnn] [Unn] [Vnn] [Wnn] [Tnn] - Jog each motor nn steps.
 *  D5 - report current firmware version
 *  D6 [Lnn] [Rnn] [Unn] [Vnn] [Wnn] [Tnn] - Set home position for each axis.
 *  D7 [Lnn] [Rnn] - Polargraph only.  Set calibration length of each belt (mm)
 *  D8 - Polargraph only.  Report calibration values for left and right belts (mm)
 *  D13 Znn - !! UNUSED !! Polargraph only.  Set pen angle 
 *  D14 - get machine style
 *  D15 - !! UNUSED !! Sixi only.  Sixi demo
 *  D17 - Sixi only.  report sensor values for each axis.
 *  D18 - Sixi only.  copy sensor values to motor step positions (set current position)
 *  D19 [Pxx]- Sixi only.  sets continuous D17 reporting accepts either P0 or P1
 *  D20 - Sixi only.  clear error flags
 *  D21 - Sixi only.  toggle software ESTOP
 *  D23 - Sixi only.  Set home position defined in config.h.
 *  D50 Snn - Set and report strict mode.  where nn=0 for off and 1 for on.
 * 
 * "G" Codes
 *
 * G0   -> G1
 * G1   - G0/G1 [Ln] [Rn] [Un] [Vn] [Wn] [Tn] - linear travel. Either mm or in case of Sixi degrees
 * G2   - CW ARC
 * G3   - CCW ARC
 * G4   - Dwell S<seconds> or P<milliseconds>
 * G28  - Go home
 * G90  - Use Absolute Coordinates
 * G91  - Use Relative Coordinates
 * G92  - Set current position to coordinates given ("teleport")
 *
 * "M" Codes
 *
 * M6 Tnn - Toolchange to tool number nn
 * M100 - Print a helpful message to serial.
 * M101 Annn Tnnn Bnnn - Change axis A limits to max T and min B.
 * M110 Nnn - sets next expected line number to n.
 * M112 - Full Shutdown./Emergency stop
 * M114 - Report current position.
 * M117 - Display a message on the controller screen. (Requires an LCD)
 * M203 [Lnn] [Rnn] [Unn] [Vnn] [Wnn] [Tnn] - set max feedrate per axis
 * M204 - Set default acceleration in units/sec^2: P<printing> R<extruder_only> T<travel>
 * M205 [Xnn] [Ynn] [Znn] [Unn] [Vnn] [Wnn] [Bnn] - set jerk for all axies. B is minimum segment time (us)
 * M206 - Set additional homing offset. (Disabled by NO_WORKSPACE_OFFSETS or DELTA)
 * M226 - Wait until a pin is in a given state: "M226 P<pin> S<state>" (Requires DIRECT_PIN_CONTROL)
 * M300 - Play beep sound S<frequency Hz> P<duration ms> (requires speaker)
 * M428 - M428 - Sixi only.  set home position to the current raw angle values (don't use home position to adjust home position!) !! HÄ?? !!
 * M500 - Store parameters in EEPROM. (Requires EEPROM_SETTINGS)
 * M501 - Restore parameters from EEPROM. (Requires EEPROM_SETTINGS)
 * M502 - Revert to the default "factory settings". ** Does not write them to EEPROM! **
 * M503 - Print the current settings (in memory): "M503 S<verbose>". S0 specifies compact output.
 */

#include "config.h"
#include "parser.h"


class GcodeSuite {
public:


private:


  static void M81();
  static void M82();
  static void M83();
  static void M85();
  static void M92();

};

extern GcodeSuite gcode;
