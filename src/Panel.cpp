
#include "Panel.h"

Panel::Panel(VarSpeedServo& Servo) :
    Servo(Servo)
{

}

Panel::Panel(VarSpeedServo& Servo, const int OpenPos, const int ClosedPos) :
    Servo(Servo),
    OpenPos(OpenPos),
    ClosedPos(ClosedPos)
{
    
}
void Panel::open()
{
    Servo.write(OpenPos, 255);
}

void Panel::close()
{
    Servo.write(ClosedPos, 255);
}

void Panel::angle(const int angle)
{
    Servo.write(angle, 255);
}

void Panel::setEndPositions(const int OpenPos, const int ClosedPos)
{
    this->OpenPos     = OpenPos;
    this->ClosedPos   = ClosedPos;
}

void Panel::setOpenPos(const int Pos)
{
    this->OpenPos = Pos;
}

void Panel::setClosedPos(const int Pos)
{
    this->ClosedPos = Pos;
}
