#ifndef __PANEL_H__
#define __PANEL_H__

#include <VarSpeedServo.h>

class Panel
{
    public:
        Panel(VarSpeedServo& Servo, const uint8_t Pin);
        Panel(VarSpeedServo& Servo, const uint8_t Pin, const word OpenPos, const word ClosedPos, const byte Speed = 0);

        void attach();
        void detach();

        void open(const int speed = -1);
        void close(const int speed = -1);
        void move(const word angle, const int speed = -1);
        void move(const byte percent, const int speed = -1);
        void lock(const bool lock) { locked = lock; }
        
        void setEndPositions(const word OpenPos, const word ClosedPos);
        void setOpenPos(const word Pos);
        void setClosedPos(const word Pos);
        void setSpeed(const byte Speed);

    protected:
        VarSpeedServo& Servo;
        uint8_t Pin         = 0;
        word OpenPos        = 0;
        word ClosedPos      = 0;
        byte Speed          = 0;
        bool firstAttach    = true;     // Bug in VarSpeedServo
        bool locked         = false;    // Don't react on movement commands
};

#endif // __PANEL_H__