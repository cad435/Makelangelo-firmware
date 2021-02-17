#pragma once
#include <Arduino.h>
#include "macros.h"

class Sensor
{

public:
    sensor();

    //everything to setup the sensor goes here!
    uint8_t setup();

    //sets the absolute position and has to make the internal Offset Handling
    void setAbsolutePosition(long Position);

    //will retriev the position from the sensor, apply offset and other calculations and return the value
    long getSensorPositionRadian();

    long getSensorPositionDeg() { RAD2DEG(getSensorPositionRadian());}


private:

    long offset;
    
};

