#ifndef __PANEL_H__
#define __PANEL_H__

#include <VarSpeedServo.h>

class Panel : public VarSpeedServo
{
    public:
        Panel(int OpenPos, int ClosedPos);
        void open();
        void close();
        void angle(int angle);

    protected:
        int OpenPos = 0;
        int ClosedPos = 0;
};

#endif // __PANEL_H__