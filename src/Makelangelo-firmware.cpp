//------------------------------------------------------------------------------
// Makelangelo - firmware for various robot kinematic models
// dan@marginallycelver.com 2013-12-26
// Please see http://www.github.com/MarginallyClever/makelangeloFirmware for more information.
//------------------------------------------------------------------------------


// (unofficial) Version 2 started by cad435 on 27.01.2021

//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------


// runs once on machine start
void setup() {
  parser.start();

  eepromManager.loadAll();

  // unitTestWrapDegrees();
  // unitTestBitMacros();

#ifdef HAS_SD
  SD_setup();
#endif
#ifdef HAS_LCD
  LCD_setup();
#endif

  // clockISRProfile();

  motor_setup();
  findStepDelay();

  // easyPWM_init();

  // initialize the plotter position.
  float pos[NUM_AXIES];
  for (ALL_AXIES(i)) pos[i] = 0;

#ifdef MACHINE_HAS_LIFTABLE_PEN
  if (NUM_AXIES >= 3) pos[2] = PEN_UP_ANGLE;
#endif

#if MACHINE_STYLE == SIXI && defined(HAS_GRIPPER)
  gripper.setup();
#endif

  teleport(pos);

  setFeedRate(DEFAULT_FEEDRATE);

  robot_setup();

  // reportAllMotors();

  parser.M100();
  parser.ready();
}

// after setup runs over and over.
void loop() {
  parser.update();

#ifdef HAS_SD
  SD_check();
#endif
#ifdef HAS_LCD
  LCD_update();
#endif

  // The PC will wait forever for the ready signal.
  // if Arduino hasn't received a new instruction in a while, send ready() again
  // just in case USB garbled ready and each half is waiting on the other.
  if (!segment_buffer_full() && (millis() - parser.lastCmdTimeMs) > TIMEOUT_OK) {
#ifdef HAS_TMC2130
    {
      uint32_t drv_status = driver_0.DRV_STATUS();
      uint32_t stallValue = (drv_status & SG_RESULT_bm) >> SG_RESULT_bp;
      Serial.print(stallValue, DEC);
      Serial.print('\t');
    }
    {
      uint32_t drv_status = driver_1.DRV_STATUS();
      uint32_t stallValue = (drv_status & SG_RESULT_bm) >> SG_RESULT_bp;
      Serial.println(stallValue, DEC);
    }
#endif
    parser.ready();
  }

  meanwhile();
}

