#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
private:
    uint8_t pinSpeed;
    uint8_t pinForward;
    uint8_t pinBackwards;

    uint8_t minSpeed = 0;
    uint8_t maxSpeed;

public:
    Motor(uint8_t pinSpeed, uint8_t pinForward, uint8_t pinBackwards, uint8_t maxSpeed = 255) :
        pinSpeed(pinSpeed),
        pinForward(pinForward),
        pinBackwards(pinBackwards),
        maxSpeed(maxSpeed)
    {
        pinMode(pinForward, OUTPUT);
        pinMode(pinBackwards, OUTPUT);
    };

    void SetVelocity(float velocity) {
        uint8_t Dv = maxSpeed - minSpeed;
        float speed = minSpeed + abs(velocity) * Dv;

        analogWrite(pinSpeed, speed);
        if (velocity > 0) {
            digitalWrite(pinForward, HIGH);
            digitalWrite(pinBackwards, LOW);
        }            
        else if (velocity < 0) {
            digitalWrite(pinForward, LOW);
            digitalWrite(pinBackwards, HIGH);
        } else {
            digitalWrite(pinForward, LOW);
            digitalWrite(pinBackwards, LOW);
        }
    };
};

#endif