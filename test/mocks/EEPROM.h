// EEPROM mock (ATmega328P: 1024 bytes). Tracks write cycles and out-of-range accesses.
#ifndef MOCK_EEPROM_H
#define MOCK_EEPROM_H

#include <cstdint>
#include <cstring>

class EEPROMClass
{
public:
    static const int SIZE = 1024;

    uint8_t read(int idx) { return inRange(idx) ? data[idx] : 0xFF; }
    void write(int idx, uint8_t val)
    {
        if (!inRange(idx)) return;
        data[idx] = val;
        writes[idx]++;
        totalWrites++;
    }
    void update(int idx, uint8_t val) { if (read(idx) != val) write(idx, val); }

    template <typename T> T& get(int idx, T& t)
    {
        uint8_t* p = reinterpret_cast<uint8_t*>(&t);
        for (size_t i = 0; i < sizeof(T); i++) p[i] = read(idx + (int)i);
        return t;
    }
    template <typename T> const T& put(int idx, const T& t)
    {
        const uint8_t* p = reinterpret_cast<const uint8_t*>(&t);
        for (size_t i = 0; i < sizeof(T); i++) update(idx + (int)i, p[i]);
        return t;
    }
    uint16_t length() { return SIZE; }

    // --- test helpers ---
    uint8_t data[SIZE];
    uint32_t writes[SIZE];
    uint32_t totalWrites = 0;
    uint32_t outOfRange = 0;

    void erase()
    {
        memset(data, 0xFF, sizeof(data));
        memset(writes, 0, sizeof(writes));
        totalWrites = 0;
        outOfRange = 0;
    }
    void clearCounters() { memset(writes, 0, sizeof(writes)); totalWrites = 0; outOfRange = 0; }
    uint16_t word16(int idx) { return (uint16_t)(data[idx] | (data[idx + 1] << 8)); }

private:
    bool inRange(int idx)
    {
        if ((idx < 0) || (idx >= SIZE)) { outOfRange++; return false; }
        return true;
    }
};

extern EEPROMClass EEPROM;

#endif
