#ifndef __MDUINODOMEMASTER_H__
#define __MDUINODOMEMASTER_H__

#include "MDuinoDome.h"
#include "MDuinoStorage.h"
#include "MDuinoSound.h"
#include "Panel.h"
#include <SendOnlySoftwareSerial.h>

class MDuinoDomeMaster : public MDuinoDome
{
    public:
        MDuinoDomeMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

    protected:
        SendOnlySoftwareSerial& Serial_Slave;
        SendOnlySoftwareSerial& Serial_MP3;
        SERIAL_LIFT_TYPE& Serial_Lift;
        bool LiftModuleConnected = false;

        static const byte MinPanel =  1;   // Master Board has 11 Panel Connectors
        static const byte MaxPanel = 11;   // Master Board has 11 Panel Connectors

        Panel* Panels[MaxPanel + 1];      // +1 for index 0 dummy

        MDuinoSound* Sound = nullptr;

        unsigned long RandomSoundIntervall  = 0;
        unsigned long RandomSoundMillis     = 0;

        unsigned long MinRandomPause        = 6000;
        unsigned long MaxRandomPause        = 12000;

        void setStandardRandomSoundIntervall();
        void setSoundIntervall(const unsigned long Intervall);

        virtual void parseCommand(const char* command) override;

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processSoundCommand(const char* command);
        void processAltSoundCommand(const char* command);
        void processAltHoloCommand(const char* command);

        static void sequenceCallbackJedi(MDuinoBase* object);
        static void sequenceCallbackResetMP(MDuinoBase* object);
        static void sequenceCallbackResetSound(MDuinoBase* object);
};

#endif // __MDUINODOMEMASTER_H__