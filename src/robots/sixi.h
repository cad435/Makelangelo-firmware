#pragma once
#include <Arduino.h>
#include "robot.h"

class sixi : public virtual robot
{
public:

    //define a robot with 5 Axis
    sixi() : robot(6) {}



private:
    /* data */
};
