#ifndef __MARCDUINODOME_H__
#define __MARCDUINODOME_H__

#include "MDuinoBase.h"

class Panel;
class Holo;

class MDuinoDome : public MDuinoBase
{
    public:
        MDuinoDome(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                    VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

    protected:
        byte MaxSoundsPerBank[10];

        void adjustHoloEndPositions(Holo* Holos[], const byte MinHolo, const byte MaxHolo);
        void adjustPanelEndPositions(Panel* Panels[], const byte MinPanel, const byte MaxPanel);

        bool separateSoundCommand(const char* command, char* cmd, byte & bank, byte & sound);

        void getRandomSound(byte & bank, byte & sound);
};

#endif  //  __MARCDUINODOME_H__