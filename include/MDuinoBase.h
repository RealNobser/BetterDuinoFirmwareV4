#ifndef __MARCDUINOS_H__
#define __MARCDUINOS_H__

#include <Arduino.h>
#include <config.h>
#include <VarSpeedServo.h>

#include "MDuinoStorage.h"
#include "MDuinoSequencer.h"

class MDuinoBase
{
    public:
        MDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                      VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11);

        virtual void init();
        virtual void run();

        virtual const char* getProductName() = 0;

        virtual void parseCommand(const char* command) = 0;

    protected:
        byte HeartBeatStatus = LOW;

        unsigned long HeartBeatMillis       = 0;
        unsigned long HeartBeatIntervall    = 0;    // Variable to enable blinking codes if necessary

        unsigned long AUX1Millis            = 0;
        unsigned long AUX1Duration          = 0;

        unsigned long ServoBuzzMillis       = 0;
        unsigned long ServoBuzzIntervall    = 0;

        char SerialBuffer[SERIALBUFFERSIZE];
        char WireBuffer[SERIALBUFFERSIZE];
        byte BufferIndex = 0;
        byte WireIndex = 0;

        MDuinoStorage    Storage;
        MDuinoSequencer  Sequencer;

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

    protected:
        virtual void playSequence(const byte SeqNr) = 0;
        virtual void playSequenceAddons(const byte SeqNr) = 0;

        void toggleHeartBeat();

        void AUX1(const unsigned int Duration);

        bool separateCommand(const char* command, char* cmd, unsigned int & param_num, unsigned int & param_num_ext);       

        void processSetupCommand(const char* command);
        virtual void processI2CCommand(const char* command);

        virtual void checkEEPROM(const bool factoryReset = false);

        void resetServoBuzz();
        static void sequenceCallbackBuzz(MDuinoBase* object);

        void(* resetFunc) (void) = 0;
};

#endif