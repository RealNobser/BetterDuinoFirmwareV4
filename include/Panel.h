#ifndef __PANEL_H__
#define __PANEL_H__

#include <VarSpeedServo.h>

class Panel
{
    public:
        Panel(VarSpeedServo& Servo, const int & Pin);
        Panel(VarSpeedServo& Servo, const int & Pin, const int & OpenPos, const int & ClosedPos);
        void attach();
        void detach();

        void open(const int & speed=0);
        void close(const int & speed=0);
        void move(const int & angle, const int & speed=0);
        void lock(const bool & lock) { locked = lock; }
        
        void setEndPositions(const int & OpenPos, const int & ClosedPos);
        void setOpenPos(const int & Pos);
        void setClosedPos(const int & Pos);

    protected:
        VarSpeedServo& Servo;
        int Pin             = 0;
        int OpenPos         = 0;
        int ClosedPos       = 0;
        bool firstAttach    = true;     // Bug in VarSpeedServo
        bool locked         = false;    // Don't react on movement commands
};

#endif // __PANEL_H__