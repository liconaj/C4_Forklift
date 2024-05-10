#include "system/system.h"

#define ENA 1
#define IN1 2
#define IN2 3
#define IN3 4
#define IN4 5
#define ENB 6

#define LIFTER 7
#define VOLTAGE_SENSOR 9
#define INCLINATION_SENSOR 10
#define BUZZER 11

#define CH1 13
#define CH2 14
#define CH3 15
#define CH4 16

#define MAX_SPEED 255

#define PIN_LIGHTS 8

Motor leftMotor = Motor(ENA, IN1, IN2, MAX_SPEED);
Motor rightMotor = Motor(ENB, IN3, IN4, MAX_SPEED);
Lifter lifter = Lifter(LIFTER);
Battery battery = Battery(VOLTAGE_SENSOR);
Buzzer buzzer = Buzzer(BUZZER);

Control control = Control();

Battery::Level lastBatteryLevel;
Battery::Level batteryLevel;

uint8_t elevation;
float direction;
float velocity;
int turnDirection;

bool isInclined();
void updateControl();
void updateMotors();
void updateLifter();
void updateLights();
void updateBattery();
void giveBatteryLevelSound();

void setup() {
    Serial.begin(9600);
    pinMode(INCLINATION_SENSOR, INPUT);

    Lights::Init();
    Lights::SetAlwaysOn();

    batteryLevel = battery.GetLevel();
    lastBatteryLevel = batteryLevel;

    giveBatteryLevelSound();
}

void loop() {
    updateBattery();
    updateLights();

    if (batteryLevel == Battery::Critical) {
        buzzer.SayCritical();
    }

    updateControl();
    updateLifter();

    if (isInclined()) {
        buzzer.SayAlert();
        return;
    }
    updateMotors();
}

bool isInclined() {
    return digitalRead(INCLINATION_SENSOR);
}

void giveBatteryLevelSound() {
    switch (battery.GetLevel())
    {
    case Battery::Full:
        buzzer.SayOK();
        break;
    case Battery::Medium:
        buzzer.SayOK();
        break;
    case Battery::Low:
        buzzer.SayWarning();
        break;
    case Battery::Critical:
        buzzer.SayWasted();
        break;
    }
}

void updateControl() {
    uint8_t elevation = control.GetElevation();
    float direction = control.GetDirection();
    float velocity = control.GetVelocity();
    int turnDirection = control.GetTurnDirection();
}

void updateLifter() {
    lifter.SetElevation(elevation);
}

void updateLights() {

}

void updateBattery() {
    batteryLevel = battery.GetLevel();
    if (batteryLevel != lastBatteryLevel) {
        giveBatteryLevelSound();
        lastBatteryLevel = batteryLevel;
    }
}