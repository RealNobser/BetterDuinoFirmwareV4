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
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override  { return "MarcDuino Dome Master"; }

    protected:
        SendOnlySoftwareSerial& Serial_Slave;
        SendOnlySoftwareSerial& Serial_MP3;

        static const unsigned int MinPanel =  1;   // Master Board has 11 Panel Connectors
        static const unsigned int MaxPanel = 11;   // Master Board has 11 Panel Connectors

        Panel* Panels[MaxPanel + 1];               // +1 for index 0 dummy

        MarcDuinoSound* Sound = nullptr;

        unsigned long RandomSoundIntervall  = 0;
        unsigned long RandomSoundMillis     = 0;

        unsigned long MinRandomPause        = 6000;
        unsigned long MaxRandomPause        = 12000;

        virtual void parseCommand(const char* command) override;

        void setStandardRandomSoundIntervall();

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processSoundCommand(const char* command);
        void processAltSoundCommand(const char* command);
        void processAltHoloCommand(const char* command);

        void playSequenceAddons(const unsigned int SeqNr) override;
};

#endif // __MARCDUINODOMEMASTER_H__