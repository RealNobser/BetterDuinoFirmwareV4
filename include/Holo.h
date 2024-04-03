#ifndef __HOLO_H__
#define __HOLO_H__

#include <Arduino.h>
#include <VarSpeedServo.h>
#include <Adafruit_NeoPixel.h>

#include "config.h"

class Holo
{
    public:
        Holo(const uint8_t LightPin, const bool HighActive, VarSpeedServo& HServo, const uint8_t HPin, VarSpeedServo& VServo, const uint8_t VPin, const bool NeoPixelHolo = true, const uint8_t NrPixels = 7);

        void setHighActive(const bool HighActive = true);

        void attach();
        void detach();

        void on(const unsigned long duration = 0);
        void flickerOn(const unsigned long duration = 0);
        void off();

        void setBrightness(const uint8_t bright);

        #ifdef INCLUDE_HOLO_RGB
        void setColor(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright);
        void on(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright, const unsigned long duration = 0);
        void flickerOn(const uint8_t red, const uint8_t green, const uint8_t blue, const uint8_t bright, const unsigned long duration = 0);
        #endif

        void move(const word HPos, const word VPos, const byte speed = 0);
               
        void randomMove(const bool moving=true);

        bool isOn() { return LightOn; }
        bool isNeoPixelHolo() { return NeoPixelHolo; }

        void setEndPositions(const word HMin, const word HMax, const word VMin, const word VMax);

        void run();

        void flickerTrigger();
        void moveTrigger();
        void testTrigger();

    protected:
        uint8_t LightPin        = 0;
        bool HighActive         = true;
        bool LightOn            = false;
        uint8_t LightStateOn    = HIGH;
        uint8_t LightStateOff   = LOW;

        VarSpeedServo HServo;
        uint8_t HPin = 0;
        
        VarSpeedServo VServo;
        uint8_t VPin = 0;

        bool NeoPixelHolo       = false;
        uint8_t NrPixels        = 7;

        #ifdef INCLUDE_HOLO_RGB
        Adafruit_NeoPixel* pixels = nullptr;
        uint8_t red             = 255;
        uint8_t green           = 255;
        uint8_t blue            = 255;
        uint8_t bright          = 200;
        #endif

        word HMinPos     = 0;
        word HMaxPos     = 0;
        word VMinPos     = 0;
        word VMaxPos     = 0;

        byte testStep   = 0;

        bool firstAttachH   = true;    // Bug in VarSpeedServo
        bool firstAttachV   = true;    // Bug in VarSpeedServo

        unsigned long HoloMillis   = 0;
        unsigned long HoloIntervall= 0;

        unsigned long HoloFlickerMillis      = 0;
        unsigned long HoloFlickerIntervall   = 0;

        unsigned long HoloMoveMillis      = 0;
        unsigned long HoloMoveIntervall   = 0;

        unsigned long HoloTestMillis      = 0;
        unsigned long HoloTestIntervall   = 0;

        void checkTimer(const unsigned long intervall, const unsigned long milli, void (*func)(Holo*));

        static void static_Off(Holo* object);
        static void static_flickerTrigger(Holo* object);
        static void static_moveTrigger(Holo* object);
        static void static_testTrigger(Holo* object);
};
#endif