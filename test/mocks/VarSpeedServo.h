// VarSpeedServo mock (API of github.com/RealNobser/VarSpeedServo). Movement is instantaneous
// unless `moving` is set by a test.
#ifndef MOCK_VARSPEEDSERVO_H
#define MOCK_VARSPEEDSERVO_H

#include <cstdint>

class VarSpeedServo
{
public:
    uint8_t attach(const uint8_t pin) { return attach(pin, 544, 2400, value); }
    uint8_t attach(const uint8_t pin, const uint16_t defaultPulseWidth) { return attach(pin, 544, 2400, defaultPulseWidth); }
    uint8_t attach(const uint8_t pin, const uint16_t min, const uint16_t max) { return attach(pin, min, max, value); }
    uint8_t attach(const uint8_t pin, const uint16_t min, const uint16_t max, const uint16_t defaultPulseWidth)
    {
        isAttached = true;
        this->pin = pin;
        this->min = min;
        this->max = max;
        value = defaultPulseWidth;
        attachCount++;
        return 0;
    }
    void detach() { isAttached = false; detachCount++; }
    void write(uint16_t value, const uint8_t speed = 0) { this->value = value; this->speed = speed; writeCount++; }
    void write(uint16_t value, const uint8_t speed, const bool) { write(value, speed); }
    void writeMicroseconds(uint16_t value, const uint8_t speed) { write(value, speed); }
    void stop() { moving = false; }
    uint16_t read() { return value; }
    uint16_t readMicroseconds() { return value; }
    bool attached() { return isAttached; }
    void wait() {}
    bool isMoving() { return moving; }

    // --- test helpers ---
    bool isAttached = false;
    bool moving = false;
    uint8_t pin = 0;
    uint16_t min = 0, max = 0;
    uint16_t value = 1500;
    uint8_t speed = 0;
    unsigned writeCount = 0, attachCount = 0, detachCount = 0;

    void reset() { *this = VarSpeedServo(); }
};

#endif
