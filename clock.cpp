#include "configure.h"

#if defined( ESP32 )
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

extern void IRAM_ATTR onTimer();  // defined in motor.cpp.

void CLOCK_ADJUST(long x) {
  timerAlarmWrite(timer, (80000L*(x)), true );  // microseconds
}

void CRITICAL_SECTION_START() {
  portENTER_CRITICAL_ISR(&timerMux);
}

void CRITICAL_SECTION_END() {
  portEXIT_CRITICAL_ISR(&timerMux);
}
#endif
#if !defined(ESP32) && !defined(ESP8266)

unsigned char _sreg = 0;
#endif

void clockStart() {
#ifndef DEBUG_STEPPING
  // disable global interrupts
  CRITICAL_SECTION_START();

#if defined( ESP8266 )
  timer0_isr_init();
  timer0_attachInterrupt(itr);
  CLOCK_ADJUST(2000);
#endif
#if defined( ESP32 )
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);

  CLOCK_ADJUST(2000);
#endif
#if !defined( ESP8266 ) && !defined( ESP32 )
  // set entire TCCR1A register to 0
  TCCR1A = 0;
  // set the overflow clock to 0
  TCNT1  = 0;
  // set compare match register to desired timer count
  OCR1A = 2000;  // 1ms
  // turn on CTC mode
  TCCR1B = (1 << WGM12);
  // Set 8x prescaler
  TCCR1B = (TCCR1B & ~(0x07 << CS10)) | (2 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
#endif  // ESP8266

  CRITICAL_SECTION_END();
#endif // DEBUG_STEPPING
}

void clockStop() {
  
}
