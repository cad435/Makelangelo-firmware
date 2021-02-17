#pragma once

#include <Arduino.h>
#include "MultiStepper.h"
#include "sensors/sensor.h"


class robot
{
    public:
    //constructor, take the number of motors and setup 
    robot(const uint8_t NumAxis_) : NumAxis(NumAxis_) {



    }



private:
    const uint8_t NumAxis;
    
    //the Sixi has a unique gearbox at the wrist, which requires to calculate the motor positions from 
    void calculateMotorPositionsFromJointPositions(long &JointValues, long &Motorvalues);

    MultiStepper Motors;

    Sensor Sensor[6] = null;

};
