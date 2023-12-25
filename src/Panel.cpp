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
    if(!Servo.attached())
        Servo.attach(Pin);
}

void Panel::detach()
{
    if(Servo.attached())
        Servo.detach();
}

void Panel::open(const int speed)
{
    move(OpenPos, speed);
}

void Panel::close(const int speed)
{
    move(ClosedPos, speed);
}

void Panel::move(const int position, const int speed)
{
    if(!Servo.attached())
    {
        if (firstAttach) 
            Servo.write(position);
        firstAttach = false;
        Servo.attach(Pin);
    }
    Servo.write(position, speed);
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
