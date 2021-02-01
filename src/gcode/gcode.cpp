#include "gcode.h"


uint8_t GcodeSuite::ReadSerial()
{
    uint8_t cProcessed = parser.fetchAndParse();


    return cProcessed;
}


void GcodeSuite::process_parsed_command(const bool no_ok = false) {


    // Handle a known G, M, or D
    switch (parser.command_letter) {
        case 'G': switch (parser.codenum) {

            case 0: case 1: //G01();
            break;                                            // G0: Fast Move, G1: Linear Move
            
            default: parser.unknown_command_warning(); break;
        }
        case 'M': switch (parser.codenum) {

            case 17: //M17(); 
            break;                                      // M17: Enable all stepper motors


            default: parser.unknown_command_warning(); break;
        }
        
        case 'D': switch (parser.codenum) {

            case 0: //D0();

            default: parser.unknown_command_warning(); break;
        }
    break;
    }

  if (!no_ok) queue.ok_to_send();
}