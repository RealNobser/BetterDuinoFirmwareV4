#include <Arduino.h>
#include "Holo.h"

Holo::Holo(const uint8_t LightPin, const bool HighActive, VarSpeedServo& HServo, const uint8_t HPin, VarSpeedServo& VServo, const uint8_t VPin, const bool NeoPixelHolo /*= false*/, const uint8_t NrPixels /*= 7*/) :
    LightPin(LightPin),
    HighActive(HighActive),
    HServo(HServo),
    HPin(HPin),
    VServo(VServo),
    VPin(VPin),
    NeoPixelHolo(NeoPixelHolo),
    NrPixels(NrPixels)
{
    #ifdef INCLUDE_HOLO_RGB
    if (NeoPixelHolo)
    {
        pixels = new Adafruit_NeoPixel(NrPixels, LightPin, HP_NEO_TYPE);
        pixels->begin();
        pixels->clear();
    }
    else
    #endif
    {
        setHighActive(HighActive);
        pinMode(LightPin, OUTPUT);
        digitalWrite(LightPin, LightStateOff);
    }
}

void Holo::run()
{
    checkTimer(HoloIntervall, HoloMillis, static_Off);
    checkTimer(HoloFlickerIntervall, HoloFlickerMillis, static_flickerTrigger);
    checkTimer(HoloMoveIntervall, HoloMoveMillis, static_moveTrigger);
    checkTimer(HoloTestIntervall, HoloTestMillis, static_testTrigger);
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
    #ifdef INCLUDE_HOLO_RGB
    if(NeoPixelHolo)
    {
        this->on(red, green, blue, bright, duration);
        return;
    }
    else
    #endif
        digitalWrite(LightPin, LightStateOn);
    
    LightOn = true;

    HoloIntervall  = duration*1000;
    HoloMillis     = millis();
}

void Holo::flickerOn(const unsigned long duration/* = 0*/)
{
    HoloIntervall = duration*1000;
    HoloMillis = millis();
    flickerTrigger();
}

#ifdef INCLUDE_HOLO_RGB
void Holo::setColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright)
{
    this->red   = red;
    this->green = green;
    this->blue  = blue;
    this->bright= bright;

    uint32_t color = 0x00000000;

    pixels->clear();

    color |= static_cast<uint32_t>(0x00)    << 24;
    color |= static_cast<uint32_t>(red)     << 16;
    color |= static_cast<uint32_t>(green)   << 8;
    color |= static_cast<uint32_t>(blue);

    pixels->fill(color, 0, NrPixels);

    /*
    for(int i=0; i<NEO_JEWEL_LEDS; i++) 
    {
        pixels->setPixelColor(i, pixels->Color(red, green, blue));
    }
    */

    pixels->setBrightness(bright);

}

void Holo::on(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright, const unsigned long duration)
{
    setColor(red, green, blue, bright);

    pixels->show();

    LightOn = true;

    HoloIntervall  = duration*1000;
    HoloMillis     = millis();
}

void Holo::flickerOn(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright, const unsigned long duration)
{
    setColor(red, green, blue, bright);

    HoloIntervall = duration*1000;
    HoloMillis = millis();
    flickerTrigger();
}
#endif


void Holo::off()
{
    #ifdef INCLUDE_HOLO_RGB
    if(NeoPixelHolo)
    {
        pixels->clear();
        pixels->show();
    }
    else
    #endif
        digitalWrite(LightPin, LightStateOff);

    LightOn                    = false;
    HoloIntervall              = 0;
    HoloFlickerIntervall       = 0;
}


void Holo::setBrightness(const uint8_t bright)
{
    #ifdef INCLUDE_HOLO_RGB
    if(NeoPixelHolo)
    {
        pixels->setBrightness(bright);
        pixels->show();
    }
    else
    #endif
        ;    // PWM ?
}

void Holo::move(const word HPos, const word VPos, const byte speed /*=0*/)
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

void Holo::setEndPositions(const word HMin, const word HMax, const word VMin, const word VMax)
{
    HMinPos = HMin;
    HMaxPos = HMax;
    VMinPos = VMin;
    VMaxPos = VMax;
}

void Holo::flickerTrigger()
{
    // 3-10 off, 5-20 on
    if (LightOn)
    {
        HoloFlickerIntervall = random(30,100);

        #ifdef INCLUDE_HOLO_RGB
        if (NeoPixelHolo)
        {
            pixels->clear();
            pixels->show();
        }
        else
        #endif
            digitalWrite(LightPin, LightStateOff);

        LightOn = false;
    }
    else
    {
        HoloFlickerIntervall = random(50,200);

        #ifdef INCLUDE_HOLO_RGB
        if (NeoPixelHolo)
        {
            setColor(red, green, blue, bright);
            pixels->show();
        }
        else
        #endif
            digitalWrite(LightPin, LightStateOn);

        LightOn = true;
    }
    HoloFlickerMillis = millis();
}

void Holo::moveTrigger()
{
    word HPos = 0;
    word VPos = 0;
    word Speed = 0;

    HPos = random(HMinPos, HMaxPos);
    VPos = random(VMinPos, VMaxPos);
    Speed= random(0,255);
    
    move(HPos, VPos, Speed);

    HoloMoveIntervall   = random(200, 2000);
    HoloMoveMillis      = millis();
}

void Holo::testTrigger()
{
    word HPos    = 0;
    word VPos    = 0;
    word Speed   = 0;

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
    move(HPos, VPos, Speed);
    testStep++;

    if (testStep > 10)
        testStep = 0;
}

void Holo::checkTimer(const unsigned long intervall, const unsigned long milli, void (*func)(Holo*))
{
    if (intervall != 0)
    {
        if ((millis() - milli) > intervall)
        {
            func(this);
        }
    }
}

void Holo::static_Off(Holo* object)
{
    object->off();
}

void Holo::static_flickerTrigger(Holo* object)
{
    object->flickerTrigger();
}

void Holo::static_moveTrigger(Holo* object)
{
    object->moveTrigger();
}

void Holo::static_testTrigger(Holo* object)
{
    object->testTrigger();
}
