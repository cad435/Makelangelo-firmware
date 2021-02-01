/**
 * 
 * 
 *  Section G-code parser
 * 
 * 
 **/

#define FASTER_GCODE_PARSER
#define USE_GCODE_SUBCODES //to use soemthing like G28.1
#define GCODE_CASE_INSENSITIVE //g1 equals G1
#define GCODE_QUOTED_STRINGS //allow strings with empty space, wrapped with "..."
#define SIGNED_CODENUM // Allow for a negative code like D-1 or T-1
#define BUFSIZE 4 // Number of Gcode-Lines the GcodeQueue buffers
#define MAX_CMD_SIZE 96 //Max number of characters a Gcode-Command can have