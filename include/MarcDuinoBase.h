#ifndef __MARCDUINOS_H__
#define __MARCDUINOS_H__

#include <Arduino.h>
#include <config.h>
#include <SendOnlySoftwareSerial.h>
#include <VarSpeedServo.h>

#include "MarcDuinoStorage.h"
#include "MarcDuinoSequencer.h"

class MarcDuinoBase
{
    public:
        MarcDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                      VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);

        virtual void init();
        virtual void run();

        virtual const char* getProductName() = 0;
        virtual void parseCommand(const char* command) = 0;

    protected:
        unsigned long HeartBeatMillis = 0;
        byte HeartBeatStatus = LOW;

        unsigned long AUX1Millis        = 0;
        unsigned long AUX1Duration      = 0;

        char SerialBuffer[SERIALBUFFERSIZE];
        int BufferIndex = 0;

        unsigned int MaxSoundsPerBank[10];

        MarcDuinoStorage    Storage;
        MarcDuinoSequencer  Sequencer;

        VarSpeedServo& Servo1;
        VarSpeedServo& Servo2;
        VarSpeedServo& Servo3;
        VarSpeedServo& Servo4;
        VarSpeedServo& Servo5;
        VarSpeedServo& Servo6;
        VarSpeedServo& Servo7;
        VarSpeedServo& Servo8;
        VarSpeedServo& Servo9;
        VarSpeedServo& Servo10;
        VarSpeedServo& Servo11;
        VarSpeedServo& Servo12;
        VarSpeedServo& Servo13;

        virtual void checkEEPROM();

        void toggleHeartBeat();

        bool separateCommand(const char* command, char* cmd, unsigned int & param_num);
        bool separateSoundCommand(const char* command, char* cmd, unsigned int & bank, unsigned int & sound);
        void getRandomSound(unsigned int & bank, unsigned int & sound);

        void processSetupCommand(const char* command);

        void playSequence(const unsigned int SeqNr);
        virtual void playSequenceAddons(const unsigned int SeqNr) = 0;

        void AUX1(const unsigned int Duration);

        void(* resetFunc) (void) = 0;
};

#endif