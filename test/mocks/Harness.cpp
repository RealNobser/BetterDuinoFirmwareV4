#include "Harness.h"

namespace harness
{
    SendOnlySoftwareSerial Serial1(P_SERIAL1);
    SendOnlySoftwareSerial Serial2(P_SERIAL2);
    VarSpeedServo Servo[12];

    void onReset() { throw mock::Reset(); }

    void resetHardware()
    {
        mock::resetAll();
        Serial1.reset();
        Serial2.reset();
        for (auto& s : Servo)
            s.reset();
    }

    void clearOutputs()
    {
        Serial.clearOutput();
        Serial1.clearOutput();
        Serial2.clearOutput();
    }
}
