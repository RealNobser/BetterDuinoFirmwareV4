#include "MDuinoDome.h"
#include "PanelSequences.h"
#include "Panel.h"
#include "Holo.h"

MDuinoDome::MDuinoDome(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
    VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    MDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{
     // Initilize Sound Bank Overview for Random Songs
    MaxSoundsPerBank[0] = 0;
    for (byte i = 1; i <= MAX_SOUND_BANK; i++)
        MaxSoundsPerBank[i] = Storage.getMaxSound(i);  
}

void MDuinoDome::init()
{
    MDuinoBase::init();
}

void MDuinoDome::run()
{
    MDuinoBase::run();
}

void MDuinoDome::adjustHoloEndPositions(Holo* Holos[], const byte MinHolo, const byte MaxHolo)
{
    word HMin          = 0;
    word HMax          = 0;
    word VMin          = 0;
    word VMax          = 0;

    for (byte i=MinHolo; i<= MaxHolo; i++)
    {
        Storage.getHoloPositions(i, HMin, HMax, VMin, VMax);
        Holos[i]->setEndPositions(HMin, HMax, VMin, VMax);
    }
}

void MDuinoDome::adjustPanelEndPositions(Panel* Panels[], const byte MinPanel, const byte MaxPanel)
{
    word OpenPos        = 0;
    word ClosedPos      = 0;
    byte Speed          = 0;

    for (byte i=MinPanel; i<= MaxPanel; i++)
    {
        Storage.getServoPositions(i, OpenPos, ClosedPos);
        Speed = Storage.getServoSpeed(i);
        Panels[i]->setEndPositions(OpenPos, ClosedPos);
        Panels[i]->setSpeed(Speed);
    }
}

bool MDuinoDome::separateSoundCommand(const char* command, char* cmd, byte & bank, byte & sound)
{
    char bank_char[2];
    char sound_char[3];

    bank = 0;
    sound = 0;

    memset(cmd, 0x00, 1);

    memset(bank_char, 0x00, 2);
    memset(sound_char, 0x00, 3);

    if (strlen(command) == 3)
    {
        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 1);
    }
    else if (strlen(command) == 4)
    {
        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 2);
    }
    else
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Invalid Size: %i\r\n"), strlen(command));
        #endif
        return false;        
    }

    bank=atoi(bank_char);
    sound=atoi(sound_char);

    return true;
}

void MDuinoDome::getRandomSound(byte & bank, byte & sound)
{
    bank = random(1,6);
    sound = random(1, MaxSoundsPerBank[bank]+1);
}
