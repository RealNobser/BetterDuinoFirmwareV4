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
    if(!Servo.attached())
    {
        if (firstAttach) 
            Servo.write(OpenPos);
        firstAttach = false;
        Servo.attach(Pin);
    }
    Servo.write(OpenPos, speed);
}

void Panel::close(const int speed)
{
    if(!Servo.attached())
    {
        if (firstAttach) 
            Servo.write(ClosedPos);
        firstAttach = false;
        Servo.attach(Pin);
    }
    Servo.write(ClosedPos, speed);
}

void Panel::angle(const int angle, const int speed)
{
    if(!Servo.attached())
    {
        if (firstAttach) 
            Servo.write(angle);
        firstAttach = false;
        Servo.attach(Pin);
    }
    Servo.write(angle, speed);
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
