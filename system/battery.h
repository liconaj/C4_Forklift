#ifndef battery_h
#define battery_h

#include <Arduino.h>

class Battery
{
private:
    float fullVoltage = 11.1;
    float mediumVoltage = 10.5;
    float lowVoltage = 9.9;

    // Voltage sensor parameters
    uint8_t voltageSensor;

    int adcValue;
    float refVoltage = 5;
    float R1 = 30000.0;
    float R2 = 7500.0;
    float adcVoltage;    
    float voltage;

    void updateVoltage() {
        adcValue = analogRead(voltageSensor);
        // voltage at ADC input
        adcVoltage = (adcValue * refVoltage) / 1024.0;
        // voltage at divider input
        voltage = adcVoltage / (R2 / (R1 + R2));
    };

public:
    Battery(uint8_t pinVoltageSensor) :
        voltageSensor(pinVoltageSensor)
    {

    };

    enum Level { Full, Medium, Low, Critical };

    Level GetLevel() {
        updateVoltage();
        Level level;
        if (voltage > fullVoltage)
            level = Level::Full;
        else if (voltage > mediumVoltage)
            level = Level::Medium;
        else if (voltage > lowVoltage)
            level = Level::Low;
        else
            level = Level::Critical;
        
        return level;
    };
};

#endif