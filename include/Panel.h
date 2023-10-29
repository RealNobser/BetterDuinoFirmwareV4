#ifndef __PANEL_H__
#define __PANEL_H__

#include <VarSpeedServo.h>

class Panel
{
    public:
        Panel(VarSpeedServo& Servo, const int Pin);
        Panel(VarSpeedServo& Servo, const int Pin, const int OpenPos, const int ClosedPos);
        void attach();
        void detach();
        void open();
        void close();
        void angle(const int angle);
        void setEndPositions(const int OpenPos, const int ClosedPos);
        void setOpenPos(const int Pos);
        void setClosedPos(const int Pos);

    protected:
        VarSpeedServo& Servo;
        int Pin         = 0;
        int OpenPos     = 0;
        int ClosedPos   = 0;
};

#endif // __PANEL_H__