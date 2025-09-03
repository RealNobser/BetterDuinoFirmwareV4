#ifndef __HOLO_H__
#define __HOLO_H__

#include <Arduino.h>
#include <VarSpeedServo.h>
#include "config.h"

#ifdef INCLUDE_HOLO_RGB
#if defined(ARDUINO_NEOPIXEL)
#include <Adafruit_NeoPixel.h>
#elif defined(FASTLED_NEOPIXEL)
#include <FastLED.h>
#endif
#endif  // INCLUDE_HOLO_RGB

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

        void move(const int16_t HPos, const int16_t VPos, const uint8_t speed = 0);
               
        void randomMove(const bool moving=true);

        bool isOn() { return LightOn; }
        bool isNeoPixelHolo() { return NeoPixelHolo; }

        void setEndPositions(const uint16_t HMin, const uint16_t HMax, const uint16_t VMin, const uint16_t VMax);

        void run();

        void flickerTrigger();
        void moveTrigger();
        #ifdef INCLUDE_HOLO_TEST
        void testTrigger();
        #endif

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
        #if defined(ARDUINO_NEOPIXEL)
        Adafruit_NeoPixel* pixels = nullptr;
        #elif defined(FASTLED_NEOPIXEL)
        CLEDController& ledController;
        CRGB* led_array			= nullptr;
        #endif        
        uint8_t red             = 255;
        uint8_t green           = 255;
        uint8_t blue            = 255;
        uint8_t bright          = 200;
        #endif

        uint16_t HMinPos     = 0;
        uint16_t HMaxPos     = 0;
        uint16_t VMinPos     = 0;
        uint16_t VMaxPos     = 0;

        #ifdef INCLUDE_HOLO_TEST
        uint8_t testStep   = 0;
        #endif

        unsigned long HoloMillis   = 0;
        unsigned long HoloIntervall= 0;

        unsigned long HoloFlickerMillis      = 0;
        unsigned long HoloFlickerIntervall   = 0;

        unsigned long HoloMoveMillis      = 0;
        unsigned long HoloMoveIntervall   = 0;

        #ifdef INCLUDE_HOLO_TEST
        unsigned long HoloTestMillis      = 0;
        unsigned long HoloTestIntervall   = 0;
        #endif

        void checkTimer(const unsigned long intervall, const unsigned long milli, void (*func)(Holo*));

        static void static_Off(Holo* object);
        static void static_flickerTrigger(Holo* object);
        static void static_moveTrigger(Holo* object);

        #ifdef INCLUDE_HOLO_TEST
        static void static_testTrigger(Holo* object);
        #endif
};
#endif