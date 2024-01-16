#include <Arduino.h>
#include "Panel.h"

Panel::Panel(VarSpeedServo& Servo, const uint8_t Pin) :
    Servo(Servo),
    Pin(Pin)
{
    //attach();
}

Panel::Panel(VarSpeedServo& Servo, const uint8_t Pin, const word OpenPos, const word ClosedPos) :
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

void Panel::open(const byte speed)
{
    move(OpenPos, speed);
}

void Panel::close(const byte speed)
{
    move(ClosedPos, speed);
}

void Panel::move(const word position, const byte speed)
{
    if (locked)
        return;
        
    if(!Servo.attached())
    {
        if (firstAttach) 
            Servo.write(position);
        firstAttach = false;
        Servo.attach(Pin);
    }
    Servo.write(position, speed);
}

void Panel::move(const byte percent, const byte speed)
{
    word position = map(percent, 0, 100, ClosedPos, OpenPos);
    move(position, speed);
}

void Panel::setEndPositions(const word OpenPos, const word ClosedPos)
{
    this->OpenPos     = OpenPos;
    this->ClosedPos   = ClosedPos;
}

void Panel::setOpenPos(const word Pos)
{
    this->OpenPos = Pos;
}

void Panel::setClosedPos(const word Pos)
{
    this->ClosedPos = Pos;
}
