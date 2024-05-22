#include "system/system.h"

#define LED_BUILTIN 2
#define RX2 16
#define TX2 17

#define ENA 14
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33
#define ENB 32

#define DISABLE_LIFTER 5

#define LIFTER 15
#define VOLTAGE_SENSOR 4
#define TILT_SENSOR 23
#define BUZZER 19

#define MAX_SPEED 255

// #define PIN_LIGHTS 8

Motor leftMotor = Motor(ENA, IN1, IN2, MAX_SPEED);
Motor rightMotor = Motor(ENB, IN3, IN4, MAX_SPEED);
Lifter lifter = Lifter(LIFTER);
Battery battery = Battery(VOLTAGE_SENSOR);
Buzzer buzzer = Buzzer(BUZZER);

int ch1, ch2, ch3, ch4, ch5, ch6;
Control control = Control(RX2, TX2, false);

Battery::Level lastBatteryLevel;
Battery::Level batteryLevel;

bool connected;
bool lastConnected;

int elevation;
float direction;
float velocity;
int turnDirection;
bool alertTilt;
uint8_t maxSpeed;

bool isTilted();
void updateControl();
void updateMotors();
void stopMotors();
void updateLifter();
void updateLights();
void updateBattery();
void giveBatteryLevelSound();
void enableLifter();
void disableLifter();

void setup()
{
    Serial.begin(115200);
    pinMode(TILT_SENSOR, INPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(DISABLE_LIFTER, OUTPUT);

    batteryLevel = battery.GetLevel();
    lastBatteryLevel = batteryLevel;

    updateControl();
    updateLifter();
    updateMotors();
    // giveBatteryLevelSound();
    // delay(1500);
}

void loop()
{
    //
    // Check battery
    //
    updateBattery();
    //if (batteryLevel == Battery::Critical) {
    //    buzzer.SayCritical();
    //    disableLifter();
    //    stopMotors();
    //    return;
    //}

    //
    // Check control
    //
    updateControl();
    updateMotors();
    updateLifter();
    if (!connected) {
        disableLifter();
        stopMotors();
        return;
    }
    
    enableLifter();
    // Check inclination
    if (alertTilt && isTilted())
    {
        stopMotors();
        buzzer.SayAlert();
        return;
    }

    updateLifter();
    updateMotors();
}

void enableLifter() {
    digitalWrite(DISABLE_LIFTER, LOW);
}

void disableLifter() {
    digitalWrite(DISABLE_LIFTER, HIGH);
}

bool isTilted()
{
    return digitalRead(TILT_SENSOR) == HIGH;
}

void giveBatteryLevelSound()
{
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
    //Serial.print("New Battery Level: ");
    //Serial.println(batteryLevel);
}

bool isAround(int value, int ref, int tolerance = 5) {
    return abs(value - ref) < tolerance;
}

void updateControl()
{
    control.Update();
    connected = control.IsConnected();

    ch1 = control.GetData(1);
    ch2 = control.GetData(2);
    ch3 = control.GetData(3);
    ch4 = control.GetData(4);
    ch5 = control.GetData(5);
    ch6 = control.GetData(6);

    // Tilting
    if (isAround(ch6, 1800)) {
        alertTilt = false;
    } else if (isAround(ch6, 200)) {
        alertTilt = true;
    }

    // Max speed
    if (isAround(ch5, 1800)) {
        maxSpeed = 100;
    } else if (isAround(ch5, 1001)) {
        maxSpeed = 180;
    } else if (isAround(ch5, 200)) {
        maxSpeed = 255;
    }

    // Velocity
    if (isAround(ch2, 814, 10)) {
        velocity = 0;
    } else if (isAround(ch4, 1180, 20)) {
        direction = 0;
    } else {
        velocity = map(ch2, 1608, 8, -1000, 1000) / 1000.0;
        direction = map(ch4, 1992, 395, -1000, 1000) / 1000.0;
    }

    // Lifter
    elevation = map(ch3, 392, 1992, 0, 180);

}

void updateLifter()
{
    lifter.SetElevation(elevation);
}

void updateLights()
{
}

void stopMotors() {
    leftMotor.SetVelocity(0);
    rightMotor.SetVelocity(0);
}

void updateMotors()
{
    leftMotor.SetMaxSpeed(maxSpeed);
    rightMotor.SetMaxSpeed(maxSpeed);

    leftMotor.SetVelocity(velocity);
    rightMotor.SetVelocity(velocity);
}

void updateBattery()
{
    batteryLevel = battery.GetLevel();
    //if (batteryLevel != lastBatteryLevel)
    //{
    //    giveBatteryLevelSound();
    //    lastBatteryLevel = batteryLevel;
    //}
}