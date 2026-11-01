// Wire (TWI) mock: inject slave RX bytes, capture master TX transmissions.
#ifndef MOCK_WIRE_H
#define MOCK_WIRE_H

#include <cstdint>
#include <deque>
#include <string>
#include <vector>

class TwoWire
{
public:
    void begin() { master = true; }
    void begin(uint8_t addr) { address = addr; master = false; }
    void begin(int addr) { begin((uint8_t)addr); }
    void onReceive(void (*cb)(int)) { onReceiveCb = cb; }

    void beginTransmission(uint8_t addr) { txAddress = addr; txOpen = true; tx.clear(); }
    uint8_t endTransmission() { txOpen = false; transmissions.push_back({txAddress, tx}); return 0; }
    size_t write(uint8_t b) { tx.push_back(b); return 1; }

    int available() { return (int)rx.size(); }
    int read()
    {
        if (rx.empty()) return -1;
        int c = rx.front();
        rx.pop_front();
        return c;
    }

    // --- test helpers ---
    struct Transmission { uint8_t address; std::vector<uint8_t> data; };

    bool master = false;
    int address = -1;
    void (*onReceiveCb)(int) = nullptr;
    std::deque<uint8_t> rx;
    std::vector<uint8_t> tx;
    uint8_t txAddress = 0;
    bool txOpen = false;
    std::vector<Transmission> transmissions;

    // Mimics the AVR core: received slave data only becomes readable if a receive callback is registered.
    void receiveAsSlave(const std::string& s)
    {
        if (onReceiveCb == nullptr) return;
        for (char c : s) rx.push_back((uint8_t)c);
        onReceiveCb((int)s.size());
    }
    void reset()
    {
        master = false; address = -1; onReceiveCb = nullptr;
        rx.clear(); tx.clear(); transmissions.clear(); txOpen = false;
    }
};

extern TwoWire Wire;

#endif
