#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>

HardwareSerial Serial;
EEPROMClass EEPROM;
TwoWire Wire;

namespace mock
{
    static unsigned long clockMs = 0;
    static uint32_t rngState = 1;

    uint8_t pinModes[64];
    uint8_t pinStates[64];
    unsigned long delayTotal = 0;

    void advance(unsigned long ms) { clockMs += ms; }
    void setMillis(unsigned long ms) { clockMs = ms; }

    void resetAll()
    {
        clockMs = 0;
        delayTotal = 0;
        rngState = 1;
        memset(pinModes, 0, sizeof(pinModes));
        memset(pinStates, 0, sizeof(pinStates));
        Serial.reset();
        Wire.reset();
        EEPROM.erase();
    }
}

unsigned long millis() { return mock::clockMs; }
unsigned long micros() { return mock::clockMs * 1000UL; }
void delay(unsigned long ms) { mock::clockMs += ms; mock::delayTotal += ms; }

void pinMode(uint8_t pin, uint8_t mode) { if (pin < 64) mock::pinModes[pin] = mode; }
void digitalWrite(uint8_t pin, uint8_t val) { if (pin < 64) mock::pinStates[pin] = val ? HIGH : LOW; }
int digitalRead(uint8_t pin) { return (pin < 64) ? mock::pinStates[pin] : LOW; }
int analogRead(uint8_t) { return 512; }

// Deterministic PRNG so tests are reproducible
static uint32_t nextRandom()
{
    mock::rngState = mock::rngState * 1103515245u + 12345u;
    return (mock::rngState >> 1) & 0x7FFFFFFF;
}
void randomSeed(unsigned long seed) { mock::rngState = (uint32_t)seed ? (uint32_t)seed : 1; }
long random(long howbig) { return (howbig <= 0) ? 0 : (long)(nextRandom() % (uint32_t)howbig); }
long random(long howsmall, long howbig)
{
    if (howsmall >= howbig) return howsmall;
    return random(howbig - howsmall) + howsmall;
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    if (in_max == in_min) return out_min;
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Leak detection is pointless here: the firmware allocates its objects once and never frees them.
extern "C" const char* __asan_default_options() { return "detect_leaks=0"; }
