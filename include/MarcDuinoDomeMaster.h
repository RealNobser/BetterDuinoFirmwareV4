#ifndef __MARCDUINODOMEMASTER_H__
#define __MARCDUINODOMEMASTER_H__

#include "MarcDuinoBase.h"
#include "MarcDuinoStorage.h"
#include "MarcDuinoSound.h"
#include "Panel.h"
#include <SendOnlySoftwareSerial.h>

class MarcDuinoDomeMaster : public MarcDuinoBase
{
    public:
        MarcDuinoDomeMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, 
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override  { return "MarcDuino Dome Master"; }

    protected:
        SendOnlySoftwareSerial& Serial_Slave;
        SendOnlySoftwareSerial& Serial_MP3;

        Panel* Panels[MAX_PANELS+1];

        MarcDuinoSound* Sound = nullptr;

        unsigned long RandomSoundIntervall  = 0;
        unsigned long RandomSoundMillis     = 0;

        unsigned long MinRandomPause        = 6000;
        unsigned long MaxRandomPause        = 12000;

        virtual void checkEEPROM() override;        
        virtual void parseCommand(const char* command) override;

        void setStandardRandomSoundIntervall();

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processSoundCommand(const char* command);
        void processAltSoundCommand(const char* command);
        void processAltHoloCommand(const char* command);
};

#endif // __MARCDUINODOMEMASTER_H__