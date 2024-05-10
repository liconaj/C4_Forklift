#ifndef lifter_h
#define lifter_h

#include <ESP32Servo.h>

class Lifter : Servo
{
public:
    Lifter(uint8_t pin) {
        attach(pin);
    }

    void SetElevation(uint8_t elevation) {
        write(elevation);
    }
};

#endif