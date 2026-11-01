// SendOnlySoftwareSerial mock: everything written is captured in `out`.
#ifndef MOCK_SENDONLYSOFTWARESERIAL_H
#define MOCK_SENDONLYSOFTWARESERIAL_H

#include <Arduino.h>

class SendOnlySoftwareSerial : public Stream
{
public:
    explicit SendOnlySoftwareSerial(uint8_t transmitPin) : pin(transmitPin) {}
    void begin(long speed) { baud = speed; }
    operator bool() { return true; }

    // --- test helpers ---
    uint8_t pin;
    long baud = 0;
    void reset() { clearOutput(); baud = 0; }
};

#endif
