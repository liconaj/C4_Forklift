#ifndef system_h
#define system_h

#include <Arduino.h>
#include <ESP32Servo.h>
#include "motor.h"
#include "lifter.h"
#include "control.h"

class System
{
private:
    Motor leftMotor;
    Motor rightMotor;
    Lifter lifter;
    Control control;

public:
    System(Control control, Lifter lifter, Motor rightMotor, Motor leftMotor) :
        control(control),
        lifter(lifter),
        rightMotor(rightMotor),
        leftMotor(leftMotor)
    {

    }
};


#endif