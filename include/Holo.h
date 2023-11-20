#ifndef __HOLO_H__
#define __HOLO_H__

#include <VarSpeedServo.h>

class Holo
{
    public:
        Holo(const int LightPin, const bool HighActive, VarSpeedServo& HServo, const int HPin, VarSpeedServo& VServo, const int VPin);

        void setHighActive(const bool HighActive = true);

        void attach();
        void detach();

        void on(const unsigned long duration = 0);
        void flickerOn(const unsigned long duration = 0);
        void off();
        void move(const int HPos, const int VPos, const int speed = 0);

        bool isOn() { return LightOn; }

        void setHorizontalEndPositions(const int MinPos, const int MaxPos);
        void setVerticalEndPositions(const int MinPos, const int MaxPos);

        void run();

    protected:
        int LightPin    = 0;
        bool HighActive = true;
        bool LightOn    = false;
        uint8_t LightStateOn = HIGH;
        uint8_t LightStateOff= LOW;

        VarSpeedServo HServo;
        int HPin = 0;
        
        VarSpeedServo VServo;
        int VPin = 0;

        int HMinPos     = 0;
        int HMaxPos     = 0;
        int VMinPos     = 0;
        int VMaxPos     = 0;

        bool firstAttachH   = true;    // Bug in VarSpeedServo
        bool firstAttachV   = true;    // Bug in VarSpeedServo

        unsigned long HolosMillis   = 0;
        unsigned long HolosIntervall= 0;

        unsigned long HolosFlickerMillis      = 0;
        unsigned long HolosFlickerIntervall   = 0;

        void flickerToggle();
};
#endif