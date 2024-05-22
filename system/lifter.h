#ifndef lifter_h
#define lifter_h

#include <ESP32Servo.h>

#define DEBUG 1

class Lifter : Servo
{
public:
    Lifter(uint8_t pin) {
        attach(pin);
    }

    Lifter(uint8_t pin, int min, int max) {
        attach(pin, min, max);
    }

    void SetElevation(uint8_t elevation) {
        if (DEBUG) {
            Serial.println(elevation);
        }
        write(elevation);
    }
};

#endif