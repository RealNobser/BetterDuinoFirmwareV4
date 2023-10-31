#ifndef __MARCDUINOS_H__
#define __MARCDUINOS_H__

#include <Arduino.h>
#include <config.h>
#include <SendOnlySoftwareSerial.h>
#include <VarSpeedServo.h>

#include "MarcDuinoStorage.h"

class MarcDuinoBase
{
    public:
        MarcDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
                      VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11);

        virtual void init();
        virtual void run();

        virtual void parseCommand(const char* command) = 0;

        virtual const char* getProductName() = 0;

        void toggleHeartBeat();

    protected:
        unsigned long HeartBeatMillis = 0;
        byte HeartBeatStatus = LOW;

        char SerialBuffer[SERIALBUFFERSIZE];
        int BufferIndex = 0;

        MarcDuinoStorage Storage;

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

        bool separateCommand(const char* command, char* cmd, unsigned int & param_num);
        bool separateSoundCommand(const char* command, char* cmd, unsigned int & bank, unsigned int & sound);

        void processSetupCommand(const char* command);

        void(* resetFunc) (void) = 0;
};

#endif