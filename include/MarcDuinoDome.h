#ifndef __MARCDUINODOME_H__
#define __MARCDUINODOME_H__

#include "MarcDuinoBase.h"
#include "MarcDuinoSequencer.h"

#include "Holo.h"

class MarcDuinoDome : public MarcDuinoBase
{
    public:
        MarcDuinoDome(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                    VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);

        virtual void init();
        virtual void run();

        virtual const char* getProductName() = 0;
        virtual void parseCommand(const char* command) = 0;

    protected:
        unsigned long AUX1Millis            = 0;
        unsigned long AUX1Duration          = 0;

        unsigned long ServoBuzzMillis       = 0;
        unsigned long ServoBuzzIntervall    = 0;

        MarcDuinoSequencer  Sequencer;

        unsigned int MaxSoundsPerBank[10];

        void adjustHoloEndPositions(Holo* Holos[], const unsigned int MinHolo, const unsigned int MaxHolo);
        void adjustPanelEndPositions(Panel* Panels[], const unsigned int MinPanel, const unsigned int MaxPanel);

        bool separateSoundCommand(const char* command, char* cmd, unsigned int & bank, unsigned int & sound);
        void getRandomSound(unsigned int & bank, unsigned int & sound);

        virtual void playSequence(const unsigned int SeqNr);
        virtual void playSequenceAddons(const unsigned int SeqNr) = 0;

        void AUX1(const unsigned int Duration);

};

#endif  //  __MARCDUINODOME_H__