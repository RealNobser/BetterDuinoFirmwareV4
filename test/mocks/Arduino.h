// Minimal Arduino API mock for native (host) unit tests.
// Only what the firmware actually uses is provided. All hardware state is observable via mock::.
#ifndef MOCK_ARDUINO_H
#define MOCK_ARDUINO_H

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <string>
#include <deque>

#include "avr/pgmspace.h"

typedef uint8_t byte;
typedef uint16_t word;
typedef bool boolean;

#define HIGH 0x1
#define LOW  0x0
#define INPUT  0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

class __FlashStringHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(string_literal))

using std::abs;
// Arduino's abs() is a macro and therefore also accepts unsigned arguments
inline unsigned int abs(unsigned int x) { return x; }
inline unsigned long abs(unsigned long x) { return x; }

unsigned long millis();
unsigned long micros();
void delay(unsigned long ms);

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t val);
int digitalRead(uint8_t pin);
int analogRead(uint8_t pin);

long random(long howbig);
long random(long howsmall, long howbig);
void randomSeed(unsigned long seed);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#define lowByte(w)  ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))

// ---------------------------------------------------------------------------
// Print / Stream: every byte written ends up in `out` (inspectable by tests)
// ---------------------------------------------------------------------------
class Print
{
public:
    virtual ~Print() = default;

    virtual size_t write(uint8_t c) { out.push_back((char)c); return 1; }
    size_t write(const uint8_t* buf, size_t len) { for (size_t i = 0; i < len; i++) write(buf[i]); return len; }
    size_t write(const char* str) { return write((const uint8_t*)str, strlen(str)); }

    size_t print(const char* s) { return write(s); }
    size_t print(const __FlashStringHelper* s) { return write(reinterpret_cast<const char*>(s)); }
    size_t print(char c) { return write((uint8_t)c); }
    size_t print(int n) { return printf("%d", n); }
    size_t print(unsigned int n) { return printf("%u", n); }
    size_t print(long n) { return printf("%ld", n); }
    size_t print(unsigned long n) { return printf("%lu", n); }

    size_t println() { return write("\r\n"); }
    template <typename T> size_t println(T v) { size_t n = print(v); return n + println(); }

    int16_t printf(const char* format, ...) __attribute__((format(printf, 2, 3)))
    {
        va_list ap; va_start(ap, format);
        int16_t n = vprint(format, ap);
        va_end(ap);
        return n;
    }
    int16_t printf(const __FlashStringHelper* format, ...)
    {
        va_list ap; va_start(ap, format);
        int16_t n = vprint(reinterpret_cast<const char*>(format), ap);
        va_end(ap);
        return n;
    }

    void flush() {}

    // --- test helpers ---
    std::string out;
    void clearOutput() { out.clear(); }

private:
    int16_t vprint(const char* format, va_list ap)
    {
        char buf[512];
        int n = vsnprintf(buf, sizeof(buf), format, ap);
        if (n > 0) write((const uint8_t*)buf, (size_t)n < sizeof(buf) ? (size_t)n : sizeof(buf) - 1);
        return (int16_t)n;
    }
};

class Stream : public Print
{
public:
    virtual int available() { return 0; }
    virtual int read() { return -1; }
};

class HardwareSerial : public Stream
{
public:
    void begin(unsigned long baud) { this->baud = baud; }
    void end() {}
    int available() override { return (int)rx.size(); }
    int read() override
    {
        if (rx.empty()) return -1;
        int c = (unsigned char)rx.front();
        rx.pop_front();
        return c;
    }
    operator bool() { return true; }

    // --- test helpers ---
    unsigned long baud = 0;
    std::deque<char> rx;
    void inject(const std::string& s) { for (char c : s) rx.push_back(c); }
    void reset() { rx.clear(); clearOutput(); baud = 0; }
};

extern HardwareSerial Serial;

// ---------------------------------------------------------------------------
// Mock control interface
// ---------------------------------------------------------------------------
namespace mock
{
    // Thrown by the reset hook (replacement for jumping to address 0).
    struct Reset {};

    void resetAll();                      // clock, pins, Serial, Wire, EEPROM (0xFF), random seed
    void advance(unsigned long ms);       // advance virtual clock
    void setMillis(unsigned long ms);

    extern uint8_t pinModes[64];
    extern uint8_t pinStates[64];
    extern unsigned long delayTotal;      // accumulated blocking delay() time
}

#endif // MOCK_ARDUINO_H
