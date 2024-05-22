#ifndef buzzer_h
#define buzzer_h

class Buzzer 
{
private:
    uint8_t pin;
    uint8_t volume = 255;

    void beep(int duration, uint8_t pwm = 100) {
        analogWrite(pin, pwm);
        delay(duration * 1.5);
        analogWrite(pin, 0);
        delay(duration);
    }

public:
    Buzzer(uint8_t pin) : pin(pin)
    {
        pinMode(pin, OUTPUT);
    };

    void SayAlert() {
        beep(100, 80);
    }

    void SayOK() {
        beep(50);
        beep(50);
    }

    void SayWarning() {
        beep(500);
        delay(300);
        beep(500);
    }

    void SayCritical() {
        beep(1000);
    }

    void SayWasted() {
        beep(50);
        beep(50);
        volume = 1;
        beep(1000);
        volume = 255;
    }

    void SayNoWay() {
        // :V
    }

    void SayBye() {
        beep(500, 150);
        beep(500, 80);
        beep(1000, 30);
    }

    void SayReady() {
        beep(500, 30);
        beep(500, 80);
        beep(1000, 150);
    }

    void Write(uint8_t pwm) {
        analogWrite(pin, pwm);
    }
};

#endif