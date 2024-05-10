#ifndef lights_h
#define lights_h

#ifndef PIN_LIGHTS
#define PIN_LIGHTS 0
#endif


hw_timer_t * timer = NULL;

void IRAM_ATTR timerISR()
{
    digitalWrite(PIN_LIGHTS, !digitalRead(PIN_LIGHTS));
}

namespace Lights
{
    enum State {AlwaysOn, AlwaysOff, Blinking};
    
    void Init() {
        pinMode(PIN_LIGHTS, OUTPUT);
        timer = timerBegin(0, 80, true);
        timerAttachInterrupt(timer, &timerISR, true);
    }

    void SetAlwaysOn() {
        if (timerAlarmEnabled(timer))
            timerAlarmDisable(timer);
        digitalWrite(PIN_LIGHTS, HIGH);
    }

    void SetAlwaysOff() {
        if (timerAlarmEnabled(timer))
            timerAlarmDisable(timer);
        digitalWrite(PIN_LIGHTS, LOW);
    }

    void Blink(unsigned int blink_ms = 0) {
        timerAlarmWrite(timer, blink_ms, true);
        timerAlarmEnable(timer);
    }
};

#endif