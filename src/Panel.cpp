#include "Panel.h"

Panel::Panel(int OpenPos, int ClosedPos) :
    OpenPos(OpenPos),
    ClosedPos(ClosedPos)
{
    
}
void Panel::open()
{
    write(OpenPos);
}

void Panel::close()
{
    write(ClosedPos);
}

void Panel::angle(int angle)
{
    write(angle);
}