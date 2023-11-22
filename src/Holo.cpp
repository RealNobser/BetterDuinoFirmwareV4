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
    if (HoloIntervall != 0)
    {
        if ((millis() - HoloMillis) > HoloIntervall)
        {
            off();
        }
    }

    if (HoloFlickerIntervall != 0)
    {
        if ((millis() - HoloFlickerMillis) > HoloFlickerIntervall)
        {
            flickerToggle();
        }
    }

    if (HoloMoveIntervall != 0)
    {
        if ((millis() - HoloMoveMillis) > HoloMoveIntervall)
        {
            moveTrigger();
        }
    }

    if (HoloTestIntervall != 0)
    {
        if ((millis() - HoloTestMillis) > HoloTestIntervall)
        {
            testTrigger();
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

    HoloIntervall  = duration*1000;
    HoloMillis     = millis();
}

void Holo::flickerOn(const unsigned long duration/* = 0*/)
{
    HoloIntervall = duration*1000;
    HoloMillis = millis();
    flickerToggle();
}

void Holo::off()
{
    digitalWrite(LightPin, LightStateOff);

    LightOn                     = false;
    HoloIntervall              = 0;
    HoloFlickerIntervall       = 0;
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

void Holo::randomMove(const bool moving /*=true*/)
{
    HoloMoveIntervall = 0;
    HoloTestIntervall = 0;
    
    if (!moving)
    {
        HServo.detach();
        VServo.detach();
        return;
    }
    moveTrigger();
}

void Holo::setEndPositions(const int HMin, const int HMax, const int VMin, const int VMax)
{
    HMinPos = HMin;
    HMaxPos = HMax;
    VMinPos = VMin;
    VMaxPos = VMax;
}

void Holo::flickerToggle()
{
    // 3-10 off, 5-20 on
    if (LightOn)
    {
        HoloFlickerIntervall = random(30,100);
        digitalWrite(LightPin, LightStateOff);
        LightOn = false;
    }
    else
    {
        HoloFlickerIntervall = random(50,200);
        digitalWrite(LightPin, LightStateOn);
        LightOn = true;
    }
    HoloFlickerMillis = millis();
}

void Holo::moveTrigger()
{
    int HPos = 0;
    int VPos = 0;
    int Speed = 0;

    HPos = random(HMinPos, HMaxPos);
    VPos = random(VMinPos, VMaxPos);
    Speed= random(0,255);
    
    move(HPos, VPos, Speed);

    HoloMoveIntervall   = random(200, 2000);
    HoloMoveMillis      = millis();
}

void Holo::testTrigger()
{
    int HPos    = 0;
    int VPos    = 0;
    int Speed   = 0;

    // Center
    HPos = (HMaxPos-HMinPos)/2 + HMinPos;
    VPos = (VMaxPos-VMinPos)/2 + VMinPos;

    HoloTestMillis      = millis();
    HoloTestIntervall   = 1000;

    switch (testStep)
    {
    case 0: // Center
        break;
    case 1: // HMin
        HPos = HMinPos;
        break;
    case 2: // HMax
        HPos = HMaxPos;
        break;
    case 3: // VMin
        VPos = VMinPos;
        break;
    case 4: // VMax
        VPos = VMaxPos;
        break;
    case 5: // VMax
        HPos = HMinPos;
        VPos = VMinPos;
        break;
    case 6: // VMax
        HPos = HMaxPos;
        VPos = VMinPos;
        break;
    case 7: // VMax
        HPos = HMinPos;
        VPos = VMaxPos;
        break;
    case 8: // VMax
        HPos = HMaxPos;
        VPos = VMaxPos;
        break;
    default:
        break;
    }
    Serial.printf("%d %d %d\r\n", HPos, VPos, Speed);
    move(HPos, VPos, Speed);
    testStep++;

    if (testStep > 10)
        testStep = 0;
}
