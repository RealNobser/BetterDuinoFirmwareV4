#include "Panel.h"

Panel::Panel(int OpenPos, int ClosedPos) :
    OpenPos(OpenPos),
    ClosedPos(ClosedPos)
{
    
}
void Panel::open()
{
    write(OpenPos, 255, true);
}

void Panel::close()
{
    write(ClosedPos, 255, true);
}

void Panel::angle(int angle)
{
    write(angle, 255, true);
}