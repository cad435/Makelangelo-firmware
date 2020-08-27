#pragma once


//------------------------------------------------------------------------------
// TIMERS
//------------------------------------------------------------------------------

#ifndef CLOCK_FREQ
#define CLOCK_FREQ                (16000000L)
#endif

#if defined( ESP8266 ) || defined( ESP32 )
  #define MAX_COUNTER             (4294967295L)  // 32 bits
  
  #define STEPPER_TIMER_PRESCALE     40
  #define STEPPER_TIMER_TICKS_PER_US ((STEPPER_TIMER_RATE) / 1000000)              // stepper timer ticks per µs

#else
  #define MAX_COUNTER             (65536L)  // 16 bits
  
  #define STEPPER_TIMER_PRESCALE     8
  #define STEPPER_TIMER_TICKS_PER_US ((STEPPER_TIMER_RATE) / 1000000)              // stepper timer ticks per µs
#endif

extern void CRITICAL_SECTION_START();
extern void CRITICAL_SECTION_END();

#define TIMER_RATE            ((CLOCK_FREQ)/STEPPER_TIMER_PRESCALE)

// TODO a guess.  use real math here!
// https://reprap.org/wiki/Step_rates
// 0.9deg stepper @ 1/16 microstepping = 6400 steps/turn.  w/ 20-tooth GT2 pulley, 6400 steps = 40mm. 
// 1M us / 6400 = 156us/step.  100mm/s would be 2.5x faster, or 62.4us/step.  not much!
//#define CLOCK_MAX_STEP_FREQUENCY (240000L)
#define CLOCK_MIN_STEP_FREQUENCY (CLOCK_FREQ/500000U)

#define TIMEOUT_OK (1000)

// uncomment this to slow the machine and smooth movement if the segment buffer is running low.
#define BUFFER_EMPTY_SLOWDOWN
#ifndef MIN_SEGMENT_TIME_US
#define MIN_SEGMENT_TIME_US  (25000)
#endif

// if a segment added to the buffer is less tahn this many motor steps, roll it into the next move.
#define MIN_STEPS_PER_SEGMENT 6

#define MINIMUM_PLANNER_SPEED 0.05 // (mm/s)

#ifndef MAX_OCR1A_VALUE
//#define MAX_OCR1A_VALUE (0xFFFF)
#define MAX_OCR1A_VALUE (MAX_COUNTER-1)
#endif


//------------------------------------------------------------------------------
// MACROS
//------------------------------------------------------------------------------

#if defined( ESP8266 )
// ESP8266 board
#define CLOCK_ADJUST(x) {  timer0_write(ESP.getCycleCount() + (long) (80000L*(x)) );  }  // microseconds

inline void CRITICAL_SECTION_START() {}
inline void CRITICAL_SECTION_END() {}

#endif

#if defined( ESP32 )
// ESP32 board
// See https://techtutorialsx.com/2017/10/07/esp32-arduino-timer-interrupts/

extern void CLOCK_ADJUST(long x);
extern void CRITICAL_SECTION_START();
extern void CRITICAL_SECTION_END();

#endif

#if !defined( ESP8266 ) && !defined( ESP32 )
// AVR boards
#define CLOCK_ADJUST(x) {  OCR1A = (x);  }  // microseconds

extern unsigned char _sreg;
inline void CRITICAL_SECTION_START() {
  _sreg = SREG;  cli();
}
inline void CRITICAL_SECTION_END() {
  SREG = _sreg;
}
#endif

//------------------------------------------------------------------------------
// EXTERN
//------------------------------------------------------------------------------

extern void clockStart();
extern void clockStop();
