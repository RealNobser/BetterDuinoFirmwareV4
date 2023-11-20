#include <Arduino.h>
#include "Holo.h"

Holo::Holo(const int LightPin, const bool HighActive, VarSpeedServo& HServo, const int HPin, VarSpeedServo& VServo, const int VPin) :
    LightPin(LightPin),
    HighActive(HighActive),
    HServo(HServo),
    HPin(HPin),
    VServo(VServo),
    VPin(VPin)
{
    setHighActive(HighActive);

    pinMode(LightPin, OUTPUT);
    digitalWrite(LightPin, LightStateOff);
}

void Holo::run()
{
    if (HolosIntervall != 0)
    {
        if ((millis() - HolosMillis) > HolosIntervall)
        {
            off();
        }
    }

    if (HolosFlickerIntervall != 0)
    {
        if ((millis() - HolosFlickerMillis) > HolosFlickerIntervall)
        {
            flickerToggle();
        }
    }
}

void Holo::setHighActive(const bool HighActive /*= true*/)
{
    this->HighActive = HighActive;

    if (this->HighActive)
    {
        LightStateOn = HIGH;
        LightStateOff= LOW;
    }
    else
    {
        LightStateOn = LOW;
        LightStateOff= HIGH;
    }
}

void Holo::attach()
{
    if(!HServo.attached())
        HServo.attach(HPin);
    if(!VServo.attached())
        VServo.attach(VPin);
}

void Holo::detach()
{
    if(HServo.attached())
        HServo.detach();
    if(VServo.attached())
        VServo.detach();
}

void Holo::on(const unsigned long duration/* = 0*/)
{
    digitalWrite(LightPin, LightStateOn);
    LightOn = true;

    HolosIntervall  = duration*1000;
    HolosMillis     = millis();
}

void Holo::flickerOn(const unsigned long duration/* = 0*/)
{
    HolosIntervall = duration*1000;
    HolosMillis = millis();
    flickerToggle();
}

void Holo::off()
{
    digitalWrite(LightPin, LightStateOff);

    LightOn                     = false;
    HolosIntervall              = 0;
    HolosFlickerIntervall       = 0;
}

void Holo::move(const int HPos, const int VPos, const int speed /*=0*/)
{
    if(!HServo.attached())
    {
        if (firstAttachH) 
            HServo.write(HPos);
        firstAttachH = false;
        HServo.attach(HPin);
    }
    HServo.write(HPos, speed);

    if(!VServo.attached())
    {
        if (firstAttachV) 
            VServo.write(VPos);
        firstAttachV = false;
        VServo.attach(VPin);
    }
    VServo.write(VPos, speed);
}


void Holo::setHorizontalEndPositions(const int MinPos, const int MaxPos)
{
    HMinPos = MinPos;
    HMaxPos = MaxPos;
}

void Holo::setVerticalEndPositions(const int MinPos, const int MaxPos)
{
    VMinPos = MinPos;
    VMaxPos = MaxPos;
}

void Holo::flickerToggle()
{
    // 3-10 off, 5-20 on
    if (LightOn)
    {
        HolosFlickerIntervall = random(30,100);
        digitalWrite(LightPin, LightStateOff);
        LightOn = false;
    }
    else
    {
        HolosFlickerIntervall = random(50,200);
        digitalWrite(LightPin, LightStateOn);
        LightOn = true;
    }
    HolosFlickerMillis = millis();
}