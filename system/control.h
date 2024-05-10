#ifndef control_h
#define control_h

#include <Arduino.h>


class Control
{
private:
    uint8_t chDirection;
    uint8_t chElevation;
    uint8_t chVelocity;
    uint8_t chTurnDirection;

public:
    Control();

    // Valor entre -1 y 1
    float GetDirection();
    // Obtener -1 y 1
    float GetVelocity();

    int GetTurnDirection();

    // Obtener elevación como valor entre 0 y 255
    uint8_t GetElevation();
};

#endif