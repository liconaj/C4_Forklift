#ifndef control_h
#define control_h

// CH6 - Sensor inclinación
// CH5 - Velocidad (3 cambios)
// CH4 - L / R
// CH3 - E
// CH2 - U / D
// CH1 - Turn


#include <Arduino.h>
#include <sbus.h>

#define DEBUG 0

class Control
{
private:
    bfs::SbusRx sbusRx;
    bfs::SbusData sbusData;

    uint8_t chDirection;
    uint8_t chElevation;
    uint8_t chVelocity;
    uint8_t chTurnDirection;

public:
    Control(uint8_t rxPin, uint8_t txPin, bool inv) : sbusRx(&Serial2, rxPin, txPin, inv)
    {
        sbusRx.Begin();
    }


    void Update() {
        if (sbusRx.Read()) {
            sbusData = sbusRx.data();
            if (DEBUG) {
                for (int8_t i = 0; i < sbusData.NUM_CH; i++)
                {
                    Serial.print(sbusData.ch[i]);
                    Serial.print("\t");
                }
                Serial.print(sbusData.lost_frame);
                Serial.print("\t");
                Serial.println(sbusData.failsafe);
            }
        }
    }

    int GetData(int channel) {
        return sbusData.ch[channel-1];
    }

    // Valor entre -1 y 1
    float GetDirection() {
        return 0;
    }

    // Obtener -1 y 1
    float GetVelocity() {
        return 0;
    }

    int GetTurnDirection(){
        return 0;
    }

    // Obtener elevación como valor entre 0 y 255
    uint8_t GetElevation() {
        return 0;
    }

    bool IsConnected() {
        int ch1 = GetData(1);
        int ch2 = GetData(2);
        int ch3 = GetData(3);
        int ch4 = GetData(4);

        if (ch1 != 1000) return true;
        if (ch2 != 1000) return true;
        if (ch3 != 40) return true;
        if (ch4 != 1000) return true;

        return false;
    }
};

#endif