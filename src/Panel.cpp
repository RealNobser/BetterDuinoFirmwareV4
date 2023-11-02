#include <Arduino.h>
#include "Panel.h"

Panel::Panel(VarSpeedServo& Servo, const int Pin) :
    Servo(Servo),
    Pin(Pin)
{
    //attach();
}

Panel::Panel(VarSpeedServo& Servo, const int Pin, const int OpenPos, const int ClosedPos) :
    Servo(Servo),
    Pin(Pin),
    OpenPos(OpenPos),
    ClosedPos(ClosedPos)
{
    // attach();    
}

void Panel::attach()
{
    Servo.attach(Pin);
}

void Panel::detach()
{
    Servo.detach();
}

void Panel::open()
{
    if(!Servo.attached())
    {
        Servo.write(OpenPos);
        Servo.attach(Pin);
    }
    Servo.write(OpenPos, 255);
}

void Panel::close()
{
    if(!Servo.attached())
    {
        Servo.write(ClosedPos);
        Servo.attach(Pin);
    }
    Servo.write(ClosedPos, 255);
}

void Panel::angle(const int angle)
{
    if(!Servo.attached())
    {
        Servo.write(angle);
        Servo.attach(Pin);
    }
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
