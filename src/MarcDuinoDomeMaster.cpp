
#include"MarcDuinoDomeMaster.h"
#include "PanelSequences.h"

MarcDuinoDomeMaster::MarcDuinoDomeMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, 
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11) :
    MarcDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11),
    Serial_Slave(Serial_Slave),
    Serial_MP3(Serial_MP3)
{
    Serial_Slave.begin(SERIAL_SLAVE_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Slave);

    Serial_MP3.begin(SERIAL_MP3_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_MP3);

    for(int i=0; i <= MAX_PANELS; ++i)
    {
        Panels[i] = nullptr;
    }

    MarcDuinoStorage::MarcDuinoMP3PlayerType player = Storage.getMP3Player();
    switch (player)
    {
        case MarcDuinoStorage::MP3Trigger:
            Sound = new MarcDuinoSoundMP3Trigger(Serial_MP3);
        break;
        case MarcDuinoStorage::DFPlayer:
            Sound = new MarcDuinoSoundDFPlayer(Serial_MP3);
        break;
        case MarcDuinoStorage::Vocalizer:
            Sound = new MarcDuinoSoundVocalizer(Serial_MP3);
        break;
        default:
            Sound = new MarcDuinoSoundMP3Trigger(Serial_MP3);
        break;
    }

    // Medium Sound at startup
    Sound->VolumeMid();

    RandomSoundMillis = millis();
}

void MarcDuinoDomeMaster::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    #ifdef DEBUG_MSG
    Serial_Slave.println(F("To Slave"));
    Serial_MP3.println(F("To MP3"));
    #endif

    // TODO: Get Max/Min // Open Close from EEPROM!
    Panels[1] = new Panel(Servo1, P_SERVO_01, 90,180);
    Panels[2] = new Panel(Servo2, P_SERVO_02, 90,180);
    Panels[3] = new Panel(Servo3, P_SERVO_03, 90,180);
    Panels[4] = new Panel(Servo4, P_SERVO_04, 90,180);
    Panels[5] = new Panel(Servo5, P_SERVO_05, 90,180);
    Panels[6] = new Panel(Servo6, P_SERVO_06, 90,180);
    Panels[7] = new Panel(Servo7, P_SERVO_07, 90,180);
    Panels[8] = new Panel(Servo8, P_SERVO_08, 90,180);
    Panels[9] = new Panel(Servo9, P_SERVO_09, 90,180);
    Panels[10] = new Panel(Servo10, P_SERVO_10, 0,180);
    Panels[11] = new Panel(Servo11, P_SERVO_11, 0,180);

    // Random Sound
    MinRandomPause = Storage.getMinRandomPause();
    MaxRandomPause = Storage.getMaxRandomPause();

    setStandardRandomSoundIntervall();

    // Startup Sound
    byte StartupSoundNr = Storage.getStartupSoundNr();
    if (StartupSoundNr != 0)
    {
        Sound->Play(StartupSoundNr);
        if (RandomSoundIntervall != 0)
            RandomSoundIntervall = 12000;  // Extended Intervall for Startup Sound
    }

    Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
    Sequencer.startSequence();
}

void MarcDuinoDomeMaster::run()
{
    MarcDuinoBase::run();

    if (RandomSoundIntervall != 0)
    {
        if ((millis()-RandomSoundMillis) > RandomSoundIntervall)
        {
            unsigned int bank   = 0;
            unsigned int sound  = 0;

            getRandomSound(bank, sound);

            if ((bank != 0) && (sound != 0))
                Sound->Play(bank, sound);

            RandomSoundMillis = millis();
            setStandardRandomSoundIntervall();

            #ifdef DEBUG_MSG
            Serial.printf(F("Random Sound, Bank %i, Sound %i\r\n"), bank, sound);
            #endif
        }
    }
}

void MarcDuinoDomeMaster::checkEEPROM()
{
    byte ConfigVersion = Storage.getConfigVersion();
    if (ConfigVersion != CONFIG_VERSION)
    {
        #ifdef DEBUG_MSG
        Serial.println(F("Invalid Config Version. Storing defaults in EEPROM and restart."));
        #endif
        Storage.setType(MarcDuinoStorage::DomeMaster);
        Storage.setMP3Player(MarcDuinoStorage::MP3Trigger);
        Storage.setStartupSound(1);
        Storage.setStartupSoundNr(255);
        Storage.setChattyMode();
        Storage.setDisableRandomSound(0);

        // check SD-Card and edit sound banks!
        Storage.setMaxSound(1, 19);
        Storage.setMaxSound(2, 18);
        Storage.setMaxSound(3,  7);
        Storage.setMaxSound(4,  4);
        Storage.setMaxSound(5,  3);
        Storage.setMaxSound(6,  3);
        Storage.setMaxSound(7,  3);
        Storage.setMaxSound(8,  6);
        Storage.setMaxSound(9,  8);
        // check SD-Card and edit sound banks!

        Storage.setMinRandomPause(MINRANDOMPAUSE);
        Storage.setMaxRandomPause(MAXRANDOMPAUSE);

        for (int i=0; i <= MAX_MARCUDINOSERVOS; i++)
        {
            Storage.setServoDirection(i, 0);        // Direction normal, Global Setting plus each individual
            Storage.setServoSpeed(i, 255);          // Full Speed, Global Setting plus each individual
            Storage.setServoOpenPosDeg(i, 0);       // 0 deg open
            Storage.setServoClosedPosDeg(i, 180);   // 180 deg open
            Storage.setServoMidPosDeg(i, 90);       // 180 deg open
        }
        Storage.setConfigVersion(CONFIG_VERSION);   // Final step before restart
        delay(500);
        resetFunc();
    }
}

void MarcDuinoDomeMaster::setStandardRandomSoundIntervall()
{
    byte DisableRandomSound = Storage.getDisableRandomSound();

    if (!Storage.getChattyMode())
    {
        RandomSoundIntervall = 0;
        return;
    }

    if ((MinRandomPause > MaxRandomPause) || (MaxRandomPause < MinRandomPause))
    {
        MinRandomPause = MINRANDOMPAUSE;
        MaxRandomPause = MAXRANDOMPAUSE;
        Storage.setMinRandomPause(MinRandomPause);
        Storage.setMaxRandomPause(MaxRandomPause);
    }

    switch (DisableRandomSound)
    {
        case 0:
            RandomSoundIntervall = random(MinRandomPause * 1000, MaxRandomPause * 1000 + 1);
        break;
        case 1:
            RandomSoundIntervall = 0;
            Sound->VolumeOff();
        break;
        case 2:
            RandomSoundIntervall = 0;
        break;
        default:
            RandomSoundIntervall = random(MinRandomPause * 1000, MaxRandomPause * 1000 + 1);
            Storage.setDisableRandomSound(0);
        break;
    }
}

/*
 * ':' Pie panel command, parsed and treated by this controller in the "process_command" routine
 * '*' HP commands, passed on to the HoloController board daisy chained to suart1, see "parse_hp_command"
 * '@' Display commands, also passed to the HoloController board, see "parse_display_command"
 * '$' Sound commands, passed to the CFIII sound controller on suart2 "parse_sound_command"
 * '!' Alt1 alternate sound command, passed to suart2 after stripping
 * '%' Alt2 alternate HP board command, passed to suart without stripping
 *		The slave HP board will output it on suart2 after stripping
 * '#' MarcDuino Setup commands used to configure various settings on the MarcDuino
*/
void MarcDuinoDomeMaster::parseCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("Command(Master): %s\r\n"), command);
    #endif

    switch (command[0])
    {
    case ':':
        processPanelCommand(command);
        break;
    case '*':
        processHoloCommand(command);
        break;
    case '@':
        processDisplayCommand(command);
        break;
    case '$':
        processSoundCommand(command);
        break;
    case '!':
        processAltSoundCommand(command);
        break;
    case '%':
        processAltHoloCommand(command);
        break;
    case '#':
        processSetupCommand(command);
        break;    
    default:
        break;
    }    
}
/*
 * Panel commands
 * They must follow the syntax ":CCxx\r" where CC=command , xx= two digit decimal number, \r is carriage return
 * The following commands are recognized in v1.4 (in process_command)
 * :SExx launches sequences, see below
 * :OPxx open panel number xx=01-13. If xx=00, opens all panels
 * 		OP14= open top panels
 * 		OP15= open bottom panels
 * :CLxx close panel number xx=01-13, removes from RC if it was, stops servo. If xx=00, all panels, slow close.
 * :RCxx places panel xx=01-11 under RC input control. If xx=00, all panels placed on RC.
 * :STxx buzz kill/soft hold: removes panel from RC control AND shuts servo off to eliminate buzz.
 * 		xx=00 all panels off RC servos off.
 * :HDxx RC hold: removes from RC, but does not turn servo off, keeps at last position. xx=00 all panels hold.
 */
void MarcDuinoDomeMaster::processPanelCommand(const char* command)
{
    char cmd[3];
    unsigned int param_num = 0;

    memset(cmd, 0x00, 3);

    #ifdef DEBUG_MSG
    Serial.printf(F("PanelCommand(Master): %s\r\n"), command);
    #endif

    if (!separateCommand(command, cmd, param_num))
        return;

    if (strcmp(cmd, "SE")==0)       // Start Sequence
    {

    } 
    else if (strcmp(cmd, "OP")==0)  // Open Panel
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Open Panel %i\r\n"), param_num);
        #endif        

        if (param_num == 0)         // open all
        {
            for(int i=1; i<=MAX_PANELS; i++)
                Panels[i]->open();
            
            // Open Slave, too
            Serial_Slave.print(F(":OP00\r"));
        }
        else if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->open();
        }
        else if (param_num == 12)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":OP07\r"));
        }
        else if (param_num == 13)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":OP08\r"));
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (int i=7; i<=MAX_PANELS; i++)
            {
                Panels[i]->open();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (int i=1; i<=6; i++)
            {
                Panels[i]->open();
            }
        }

    }
    else if (strcmp(cmd, "CL")==0)  // Close Panel
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Close Panel %i\r\n"), param_num);
        #endif        

        if (param_num == 0)         // close all
        {
            for(int i=1; i<=MAX_PANELS; i++)
                Panels[i]->close();
            
            // Open Slave, too
            Serial_Slave.print(F(":CL00\r"));
        }
        else if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->close();
        }
        else if (param_num == 12)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":CL07\r"));
        }
        else if (param_num == 13)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":CL08\r"));
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (int i=7; i<=MAX_PANELS; i++)
            {
                Panels[i]->close();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (int i=1; i<=6; i++)
            {
                Panels[i]->close();
            }
        }        
    }
    else if (strcmp(cmd, "RC")==0)
    {

    }
    else if (strcmp(cmd, "ST")==0)
    {
        if (param_num == 0)    // Alle panels
        {
            for(int i=1; i <= MAX_PANELS; i++)
                Panels[i]->detach();

            Serial_Slave.print(F(":ST00\r"));
        }
        else if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->detach();
        }
    }
    else if (strcmp(cmd, "HD")==0)
    {

    }
    // NEW
    else if (strcmp(cmd, "DT")==0)  // Detach servo from pin / Check if identical to ST
    {
        if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->detach();
        }       
    }

}

void MarcDuinoDomeMaster::processHoloCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("HoloCommand(Master): %s\r\n"), command);
    #endif

    // Forward to slave
    Serial_Slave.printf(F("%s\r"), command);
}

void MarcDuinoDomeMaster::processDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("DisplayCommand(Master): %s\r\n"), command);
    #endif

    // Forward to slave
    Serial_Slave.printf(F("%s\r"), command);
}

	////////////////////////////////////////////////
	// Play sound command by bank/sound numbers
	// $xyy
	// x=bank number
	// yy=sound number. If none, next sound is played in the bank
	//
	// Other commands
	// $c
	// where c is a command character
	// R - random from 4 first banks
	// O - sound off
	// L - Leia message (bank 7 sound 1)
	// C - Cantina music (bank 9 sound 5)
	// c - Beep cantina (bank 9 sound 1)
	// S - Scream (bank 6 sound 1)
	// F - Faint/Short Circuit (bank 6 sound 3)
	// D - Disco (bank 9 sound 6)
	// s - stop sounds
	// + - volume up
	// - - volume down
	// m - volume mid
	// f - volume max
	// p - volume min
	// W - Star Wars music (bank 9 sound 2)
	// w - Beep Star Wars music (bank 9 sound 7)
	// M - Imperial March (bank 9 sound 3)
	// i - Beep Imperial March (bank 9 sound 8)    
	//
	///////////////////////////////////////////////

void MarcDuinoDomeMaster::processSoundCommand(const char* command)
{
    char cmd[3];
    unsigned int bank = 0;
    unsigned int sound= 0;

    memset(cmd, 0x00, 3);
    
    #ifdef DEBUG_MSG
    Serial.printf(F("SoundCommand(Master): %s\r\n"), command);
    #endif

    if (!separateSoundCommand(command, cmd, bank, sound))
        return;

    if ((bank != 0) && (sound != 0))
    {
        RandomSoundIntervall = 0;   // Stop Random sounds
        Sound->Play(bank, sound);
        return;
    }

    switch(cmd[0])
    {
        case 'R':   // random from 4 first banks
            RandomSoundIntervall = 0;   // Stop Random sounds
        break;
        case 'O':   // sound off
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->VolumeOff();
        break;
        case 'L':   // Leia message (bank 7 sound 1)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(7,1);
        break;
        case 'C':   // Cantina music (bank 9 sound 5)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,5);
        break;
        case 'c':   // Beep cantina (bank 9 sound 1)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,1);
        break;
        case 'S':   // Scream (bank 6 sound 1)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(6,1);
        break;
        case 'F':   // Faint/Short Circuit (bank 6 sound 3)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(6,3);
        break;
        case 'D':   // Disco (bank 9 sound 6)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,6);
        break;
        case 's':   // stop sounds
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Stop();
        break;
        case '+':   // volume up
            Sound->VolumeUp();
        break;
        case '-':   // volume down
            Sound->VolumeDown();
        break;
        case 'm':   // volume mid
            Sound->VolumeMid();
        break;
        case 'f':   // volume max
            Sound->VolumeMax();
        break;
        case 'p':   // volume min
            Sound->VolumeMin();
        break;
        case 'W':   // Star Wars music (bank 9 sound 2)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,2);
        break;
        case 'w':   // Beep Star Wars music (bank 9 sound 2)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,7);
        break;
        case 'M':   // Imperial March (bank 9 sound 3)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,3);
        break;
        case 'i':   // Beep Imperial March (bank 9 sound 3)
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->Play(9,8);
        break;
        default:    // Ignore
        break;
    }
}

void MarcDuinoDomeMaster::processAltSoundCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltSoundCommand(Master): %s\r\n"), command);
    #endif

    Serial_MP3.printf(F("%s\r"), command+1);
}

void MarcDuinoDomeMaster::processAltHoloCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltHoloCommand(Master): %s\r\n"), command);
    #endif
    Serial_Slave.printf(F("%s\r"), command);
}
