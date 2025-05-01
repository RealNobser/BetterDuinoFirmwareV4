#include <Arduino.h>
#include "Panel.h"

Panel::Panel(VarSpeedServo& Servo, const uint8_t Pin) :
    Servo(Servo),
    Pin(Pin)
{
    //attach();
}

Panel::Panel(VarSpeedServo& Servo, const uint8_t Pin, const uint16_t OpenPos, const uint16_t ClosedPos, const uint8_t Speed ) :
    Servo(Servo),
    Pin(Pin),
    OpenPos(OpenPos),
    ClosedPos(ClosedPos),
    Speed(Speed)
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

void Panel::open(const uint8_t speed)
{
    moveMS(OpenPos, speed, false);
}

void Panel::close(const uint8_t speed)
{
    moveMS(ClosedPos, speed, false);
}

void Panel::moveMS(const uint16_t position, const uint8_t speed,  const bool storedSpeed)
{
    if (locked)
        return;

    if(!Servo.attached())
        Servo.attach(Pin);

    if (storedSpeed)    // Use stored speed value
        Servo.write(position, this->Speed);
    else
        Servo.write(position, speed);
}

void Panel::moveDeg(const uint8_t percent, const uint8_t speed, const bool storedSpeed)
{
    uint16_t position = map(percent, 0, 100, ClosedPos, OpenPos);
    moveMS(position, speed, storedSpeed);
}

bool Panel::isMoving()
{
    if (!Servo.attached())
        return false;

    return Servo.isMoving();
}

void Panel::setEndPositions(const uint16_t OpenPos, const uint16_t ClosedPos)
{
    this->OpenPos     = OpenPos;
    this->ClosedPos   = ClosedPos;
}

void Panel::setOpenPos(const uint16_t Pos)
{
    this->OpenPos = Pos;
}

void Panel::setClosedPos(const uint16_t Pos)
{
    this->ClosedPos = Pos;
}

void Panel::setSpeed(const uint8_t Speed)
{
    this->Speed = Speed;
}
