#include "MDuinoDome.h"
#include "PanelSequences.h"

MDuinoDome::MDuinoDome(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
    VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
    VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    MDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13),
    Sequencer(this)
{
     // Initilize Sound Bank Overview for Random Songs
    MaxSoundsPerBank[0] = 0;
    for (int i = 1; i <= MAX_SOUND_BANK; i++)
        MaxSoundsPerBank[i] = Storage.getMaxSound(i);    

    ServoBuzzMillis     = millis();
    ServoBuzzIntervall  = SERVO_BUZZ_MILLIS;    // TODO Make EEPROM setting    
  
}

void MDuinoDome::init()
{
    MDuinoBase::init();
    Sequencer.init();

    // AUX1 Port
    pinMode(P_AUX1, OUTPUT);
    digitalWrite(P_AUX1, LOW);    
}

void MDuinoDome::run()
{
    MDuinoBase::run();
    Sequencer.run();

    // AUX1
    if ((AUX1Duration != 0) && (AUX1Duration != 99))
    {
        if ((millis() - AUX1Millis) > AUX1Duration)
        {
            digitalWrite(P_AUX1, LOW);
            AUX1Duration = 0;
        }
    }    
}

void MDuinoDome::adjustHoloEndPositions(Holo* Holos[], const unsigned int MinHolo, const unsigned int MaxHolo)
{
    word HMin          = 0;
    word HMax          = 0;
    word VMin          = 0;
    word VMax          = 0;

    for (unsigned int i=MinHolo; i<= MaxHolo; i++)
    {
        Storage.getHoloPositions(i, HMin, HMax, VMin, VMax);
        Holos[i]->setEndPositions(HMin, HMax, VMin, VMax);
    }
}

void MDuinoDome::adjustPanelEndPositions(Panel* Panels[], const unsigned int MinPanel, const unsigned int MaxPanel)
{
    word OpenPos        = 0;
    word ClosedPos      = 0;

    for (unsigned int i=MinPanel; i<= MaxPanel; i++)
    {
        Storage.getServoPositions(i, OpenPos, ClosedPos);
        Panels[i]->setEndPositions(OpenPos, ClosedPos);
    }
}

bool MDuinoDome::separateSoundCommand(const char* command, char* cmd, unsigned int & bank, unsigned int & sound)
{
    char bank_char[2];
    char sound_char[3];

    bank = 0;
    sound = 0;

    memset(cmd, 0x00, 1);

    memset(bank_char, 0x00, 2);
    memset(sound_char, 0x00, 3);

    //if ((strlen(command) != 4) && (strlen(command) != 2))
    if ((strlen(command) <2) || (strlen(command) >4))
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Invalid Size: %i\r\n"), strlen(command));
        #endif
        return false;
    }
    
    if (strlen(command) == 2)
    {
        memcpy(cmd, command+1, 1);
    }
    else if (strlen(command) == 3)
    {
        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 1);

        bank=atoi(bank_char);
        sound=atoi(sound_char);
    }
    else if (strlen(command) == 4)
    {
        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 2);

        bank=atoi(bank_char);
        sound=atoi(sound_char);
    }
    return true;
}

void MDuinoDome::getRandomSound(unsigned int & bank, unsigned int & sound)
{
    bank = random(1,6);
    sound = random(1, MaxSoundsPerBank[bank]+1);
}

void MDuinoDome::AUX1(const unsigned int Duration)
{
    switch (Duration)
    {
    case 0:
        digitalWrite(P_AUX1, LOW);
        AUX1Duration = 0;
        break;
    case 99:
        digitalWrite(P_AUX1, HIGH);
        AUX1Duration = 0;
        break;
    default:
        AUX1Millis = millis();
        AUX1Duration = Duration*1000;
        digitalWrite(P_AUX1, HIGH);
        break;
    }
}

void MDuinoDome::playSequence(const unsigned int SeqNr)
{
    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 1:  // SCREAM
    case 51: // Panel only Version
        Sequencer.loadSequence(panel_all_open, SEQ_SIZE(panel_all_open));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 2: // WAVE
    case 52:// Panel only Version
        Sequencer.loadSequence(panel_wave, SEQ_SIZE(panel_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 3: // MOODY FAST WAVE
    case 53:// Panel only Version
        Sequencer.loadSequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 4: // OPEN WAVE
    case 54:// Panel only Version
        Sequencer.loadSequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 5: // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
    case 55:// Panel only Version
        Sequencer.loadSequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 6: // SHORT CIRCUIT / FAINT
    case 56:// Panel only Version
        Sequencer.loadSequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
        Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
        break;
    case 7: // Cantina (Orchestral Cantina, Rhythmic Panels)
    case 57:// Panel only Version
        Sequencer.loadSequence(panel_dance, SEQ_SIZE(panel_dance));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 8: // LEIA
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));	// Close panels
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 9:	// DISCO
        Sequencer.loadSequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 10: // QUIET   sounds off, holo stop, panel closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        // stop_command(0);					// all panels off RC        
        break;
    case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        //stop_command(0);					// all panels off RC and closed
        break;
    case 12: // TOP PIE PANELS RC
        /*
        rc_command(7);
        rc_command(8);
        rc_command(9);
        rc_command(10);
        */
        break;
    case 13: // AWAKE	random sounds, holos off, panels closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        // stop_command(0);					// all panels off RC and closed
        break;
    case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        //stop_command(0);					// all panels off RC and closed
        break;

    case 15: // SCREAM no panels: sound + lights but no panels
        break;
    case 16: // Panel Wiggle
        Sequencer.loadSequence(panel_wiggle, SEQ_SIZE(panel_wiggle));
        Sequencer.setServoSpeed(MDuinoSequencer::medium);
        break;

    case 58: // Panel Wave Bye Bye
        Sequencer.loadSequence(panel_bye_bye_wave, SEQ_SIZE(panel_bye_bye_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;

    default:
        break;         
    }
    playSequenceAddons(SeqNr);
}
