#ifndef __MARCDUINOS_H__
#define __MARCDUINOS_H__

#include <Arduino.h>
#include <config.h>
#include <VarSpeedServo.h>

#include "MDuinoStorage.h"

class MDuinoBase
{
    public:
        MDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                      VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);

        virtual void init();
        virtual void run();

        virtual const char* getProductName() = 0;
        virtual void parseCommand(const char* command) = 0;

    protected:
        unsigned long HeartBeatMillis       = 0;
        unsigned long HeartBeatIntervall    = 0;    // Variable to enable blinking codes if necessary
        byte HeartBeatStatus = LOW;

        char SerialBuffer[SERIALBUFFERSIZE];
        int BufferIndex = 0;

        MDuinoStorage    Storage;

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
        void processSetupCommand(const char* command);

        void adjustServo(const unsigned int & servo, const unsigned int & value);

        void(* resetFunc) (void) = 0;
};

#endif