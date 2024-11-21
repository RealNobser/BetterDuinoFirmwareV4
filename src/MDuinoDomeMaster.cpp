
#include "MDuinoDomeMaster.h"

MDuinoDomeMaster::MDuinoDomeMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    MDuinoDome(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11),
    Serial_Slave(Serial_Slave),
    Serial_MP3(Serial_MP3),
    Serial_Lift(Serial_Lift)
{
    Serial_Slave.begin(SERIAL_SLAVE_BAUD);
    while(!Serial_Slave);

    Serial_MP3.begin(SERIAL_MP3_BAUD);
    while(!Serial_MP3);

    #ifdef SEPARATE_DOMELIFT
    Serial_Lift.begin(SERIAL_LIFT_BAUD);
    while(!Serial_Lift);
    #endif

    for(byte i=0; i <= MaxPanel; ++i)
    {
        Panels[i] = nullptr;
    }

    MDuinoStorage::MDuinoMP3PlayerType player = Storage.getMP3Player();

    switch (player)
    {
        case MDuinoStorage::MP3Trigger:
            Sound = new MDuinoSoundMP3Trigger(Serial_MP3);
        break;
        case MDuinoStorage::DFPlayer:
            Sound = new MDuinoSoundDFPlayer(Serial_MP3);
        break;
        case MDuinoStorage::Vocalizer:
            Sound = new MDuinoSoundVocalizer(Serial_MP3);
        break;
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::DYPlayer:
            Sound = new MDuinoSoundDYPlayer(Serial_MP3);
        break;
#endif  // INCLUDE_DY_PLAYER
        default:
            Sound = new MDuinoSoundMP3Trigger(Serial_MP3);
        break;
    }

    RandomSoundMillis   = millis();
}

void MDuinoDomeMaster::init()
{
    MDuinoDome::init();
    Sound->init();

    // 11 Panels
    Panels[1] = new Panel(Servo1, P_SERVO_01);
    Panels[2] = new Panel(Servo2, P_SERVO_02);
    Panels[3] = new Panel(Servo3, P_SERVO_03);
    Panels[4] = new Panel(Servo4, P_SERVO_04);
    Panels[5] = new Panel(Servo5, P_SERVO_05);
    Panels[6] = new Panel(Servo6, P_SERVO_06);
    Panels[7] = new Panel(Servo7, P_SERVO_07);
    Panels[8] = new Panel(Servo8, P_SERVO_08);
    Panels[9] = new Panel(Servo9, P_SERVO_09);
    Panels[10]= new Panel(Servo10, P_SERVO_10);
    Panels[11]= new Panel(Servo11, P_SERVO_11);

    adjustPanelEndPositions(Panels, MinPanel, MaxPanel);

    Sequencer.setPanels(Panels, MaxPanel+1);
    Sequencer.setPanelRange(MinPanel, MaxPanel);

    // Random Sound
    MinRandomPause = Storage.getMinRandomPause();
    MaxRandomPause = Storage.getMaxRandomPause();

    setStandardRandomSoundIntervall();

    // Startup Sound
    byte StartupSoundNr = Storage.getStartupSoundNr();
    if (StartupSoundNr != 0)
    {
        delay(3000);                // Soundboards need time to startup
        Sound->VolumeStandard();    // Store on EEPROM later
        Sound->Play(StartupSoundNr);
        if (RandomSoundIntervall != 0)
            RandomSoundIntervall = 12000;  // Extended Intervall for Startup Sound
    }

    parseCommand(":SE00");              // Init Panels
}

void MDuinoDomeMaster::run()
{
    MDuinoDome::run();

    // Servos. TODO: Double implementation, check BaseClass Idea for Dome Board
    // check https://stackoverflow.com/questions/13340074/c-static-const-members-overriding for const static members MinPanel/MaxPanel
    if (ServoBuzzIntervall != 0)
    {
        if ((millis() - ServoBuzzMillis) > ServoBuzzIntervall)
        {
            for (byte i = MinPanel; i <= MaxPanel; i++)
            {
                Panels[i]->detach();
            }
            ServoBuzzMillis = millis();
        }
    }

    // Random Sounds
    if (RandomSoundIntervall != 0)
    {
        if ((millis()-RandomSoundMillis) > RandomSoundIntervall)
        {
            byte bank   = 0;
            byte sound  = 0;

            getRandomSound(bank, sound);
            setStandardRandomSoundIntervall();
            
            // Additional check / override
            byte DisableRandomSound = Storage.getDisableRandomSound();
            if (DisableRandomSound != 0)
            {
                RandomSoundIntervall = 0;
                return;
            }

            if (Sound->hasVocalizer())
            {
                // Using Muse function of vocalizer
                Sound->Muse();
            }
            else
            {
                if ((bank != 0) && (sound != 0))
                    Sound->Play(bank, sound);
            }
        }
    }
}

void MDuinoDomeMaster::setStandardRandomSoundIntervall()
{
    RandomSoundMillis       = millis();

    if ((MinRandomPause > MaxRandomPause) || (MaxRandomPause < MinRandomPause))
    {
        MinRandomPause = MINRANDOMPAUSE;
        MaxRandomPause = MAXRANDOMPAUSE;
        Storage.setMinRandomPause(MinRandomPause);
        Storage.setMaxRandomPause(MaxRandomPause);
    }

    byte DisableRandomSound = Storage.getDisableRandomSound();
    if (DisableRandomSound == 0)
    {
        RandomSoundIntervall = random(MinRandomPause * 1000, MaxRandomPause * 1000 + 1);
    }
    else if (DisableRandomSound == 1)
    {
        RandomSoundIntervall = 0;
        Sound->VolumeOff();
    }
    else if (DisableRandomSound == 2)
    {
        RandomSoundIntervall = 0;
    }
    else
    {
        RandomSoundIntervall = random(MinRandomPause * 1000, MaxRandomPause * 1000 + 1);
        Storage.setDisableRandomSound(0);        
    }
}

void MDuinoDomeMaster::setSoundIntervall(const unsigned long Intervall)
{
    RandomSoundMillis       = millis();
    RandomSoundIntervall    = Intervall;
}

/*
 * ':' Pie panel command, parsed and treated by this controller in the "process_command" routine
 * '*' HP commands, passed on to the HoloController board daisy chained to suart1, see "parse_hp_command"
 * '@' Display commands, also passed to the HoloController board, see "parse_display_command"
 * '$' Sound commands, passed to the CFIII sound controller on suart2 "parse_sound_command"
 * '!' Alt1 alternate sound command, passed to suart2 after stripping
 * '%' Alt2 alternate HP board command, passed to suart without stripping
 *		The slave HP board will output it on suart2 after stripping
 * '#' Setup commands used to configure various settings
*/
void MDuinoDomeMaster::parseCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("Command(Master): %s\r\n"), command);
    #endif
    switch (command[0])
    {
    case ':':
        adjustPanelEndPositions(Panels, MinPanel, MaxPanel);
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
    case '&':
        processI2CCommand(command);
        // Forward to slave
        Serial_Slave.printf(F("%s\r"), command);
        break;
    case '#':
        processSetupCommand(command);
        // Forwarding all but #MD to Slave to be in sync
        if (strncmp(command, "#MD", 3) != 0)
        {
            Serial_Slave.printf(F("%s\r"), command);
        }
        break;
    case '>':
        // Forward to slave without prefix
        Serial_Slave.printf(F("%s\r"), command+1);
        break;    
    default:
        break;
    }
    Serial_Slave.flush();
}

void MDuinoDomeMaster::processPanelCommand(const char* command)
{
    // Sequence and Panel Commands will be processed
    char cmd[3];

    unsigned int param_num = 0;
    unsigned int param_num_ext = 0;

    memset(cmd, 0x00, 3);

    #ifdef DEBUG_MSG
    Serial.printf(F("PanelCommand(Master): %s\r\n"), command);
    #endif

    if (!separateCommand(command, cmd, param_num, param_num_ext))
        return;

    // Address Slave Panels (12+13) + Addon Body Slave Servos (16-24)
    if ((param_num == 12) || (param_num == 13) || ((param_num >= 16) && (param_num <= 24)))   
    {
        if (strcmp(cmd, "SE") != 0)
        { 
            Serial_Slave.printf(F("%s\r"), command);
            return;
        }
    }

    // Address Master Panels
    if (strcmp(cmd, "MV")==0)
    {
        if (param_num > MaxPanel)
            return;

        Panels[param_num]->move((word)param_num_ext);
    }
    else if (strcmp(cmd, "SE")==0)       // Start Sequence
    {
        playSequence(param_num);
    } 
    else if (strcmp(cmd, "OP")==0)  // Open Panel
    {
        if (param_num == 0)         // open all
        {
            for(byte i=MinPanel; i<=MaxPanel; i++)
                Panels[i]->open();
            
            // Open Slave, too
            Serial_Slave.print(F(":OP00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->open();
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (byte i=7; i<=MaxPanel; i++)
            {
                Panels[i]->open();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (byte i=MinPanel; i<=6; i++)
            {
                Panels[i]->open();
            }
            // Open Tiny, too (Dome MK4)
            Serial_Slave.print(F(":OP12\r"));
            Serial_Slave.print(F(":OP13\r"));
        }

    }
    else if (strcmp(cmd, "CL")==0)  // Close Panel
    {
        if (param_num == 0)         // close all
        {
            for(byte i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->close();
            
            // Open Slave, too
            Serial_Slave.print(F(":CL00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->close();
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (byte i=7; i<=MaxPanel; i++)
            {
                Panels[i]->close();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (byte i=MinPanel; i<=6; i++)
            {
                Panels[i]->close();
            }
            // Close Tiny, too (Dome MK4)
            Serial_Slave.print(F(":CL12\r"));
            Serial_Slave.print(F(":CL13\r"));
        }        
    }
    else if (strcmp(cmd, "LK")==0)  // Lock Panel
    {
        if (param_num == 0)         // lock all
        {
            for(byte i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->lock(true);
            
            // Open Slave, too
            Serial_Slave.print(F(":LK00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->lock(true);
        }
        else if (param_num == 14)    // Lock Top Panels
        {
            for (byte i=7; i<=MaxPanel; i++)
            {
                Panels[i]->lock(true);
            }
        }
        else if (param_num == 15)    // Lock Bottom Panels
        {
            for (byte i=MinPanel; i<=6; i++)
            {
                Panels[i]->lock(true);
            }
            // Lock Tiny, too (Dome MK4)
            Serial_Slave.print(F(":LK12\r"));
            Serial_Slave.print(F(":LK13\r"));
        }        
    }
    else if (strcmp(cmd, "UL")==0)  // Unlock Panel
    {
        if (param_num == 0)         // Unlock all
        {
            for(byte i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->lock(false);
            
            // Open Slave, too
            Serial_Slave.print(F(":UL00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->lock(false);
        }
        else if (param_num == 14)    // Unlock Top Panels
        {
            for (byte i=7; i<=MaxPanel; i++)
            {
                Panels[i]->lock(false);
            }
        }
        else if (param_num == 15)    // Unlock Bottom Panels
        {
            for (byte i=MinPanel; i<=6; i++)
            {
                Panels[i]->lock(false);
            }
            // Unlock Tiny, too (Dome MK4)
            Serial_Slave.print(F(":UL12\r"));
            Serial_Slave.print(F(":UL13\r"));
        }        
    }
    else if (strcmp(cmd, "ST")==0)
    {
        if (param_num == 0)    // Alle panels
        {
            for(byte i=MinPanel; i <= MaxPanel; i++)
                Panels[i]->detach();

            Serial_Slave.print(F(":ST00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->detach();
        }
    }
    else if (strcmp(cmd, "EO")==0)
    {
        AUX1(param_num);
    }
    else if (strcmp(cmd, "LI")==0)
    {
        Serial_Lift.printf(F("%s\r"), command);
    }
}

void MDuinoDomeMaster::processHoloCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("HoloCommand(Master): %s\r\n"), command);
    #endif

    // Forward to slave
    Serial_Slave.printf(F("%s\r"), command);
}

void MDuinoDomeMaster::processDisplayCommand(const char* command)
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

void MDuinoDomeMaster::processSoundCommand(const char* command)
{
    char cmd[3];
    byte bank = 0;
    byte sound= 0;

    memset(cmd, 0x00, 3);
    
    #ifdef DEBUG_MSG
    Serial.printf(F("SoundCommand(Master): %s\r\n"), command);
    #endif

    if (!separateSoundCommand(command, cmd, bank, sound))
        return;

    Sound->VolumeStandard();

    if ((bank != 0) && (sound != 0))
    {
        RandomSoundIntervall = 0;   // Stop Random sounds
        RandomSoundMillis = millis();
        Sound->Play(bank, sound);
        return;
    }

    switch(cmd[0])
    {
        case 'R':   // random from 4 first banks
            setStandardRandomSoundIntervall();
            RandomSoundIntervall = 1;   // Immediately play new random sound
        break;
        case 'O':   // sound off
            RandomSoundIntervall = 0;   // Stop Random sounds
            Sound->VolumeOff();
        break;
        case 'L':   // Leia message (bank 7 sound 1)
            setSoundIntervall(44000);
            Sound->Play(7,1);
        break;
        case 'C':   // Cantina music (bank 9 sound 5)
            setSoundIntervall(56000);
            Sound->Play(9,5);
        break;
        case 'c':   // Beep cantina (bank 9 sound 1)
            setSoundIntervall(27000);        
            Sound->Play(9,1);
        break;
        case 'S':   // Scream (bank 6 sound 1)
            RandomSoundMillis    = millis();
            Sound->Play(6,1);
        break;
        case 'F':   // Faint/Short Circuit (bank 6 sound 3)
            RandomSoundMillis    = millis();
            if (Sound->hasVocalizer())
            {
                Sound->Overload();
            }
            else
                Sound->Play(6,3);
        break;
        case 'D':   // Disco (bank 9 sound 6)
            setSoundIntervall(396000);
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
            setSoundIntervall(335000);
            Sound->Play(9,2);
        break;
        case 'w':   // Beep Star Wars music (bank 9 sound 7)
            setSoundIntervall(15000);
            Sound->Play(9,7);
        break;
        case 'M':   // Imperial March (bank 9 sound 3)
            setSoundIntervall(195000);
            Sound->Play(9,3);
        break;
        case 'i':   // Beep Imperial March (bank 9 sound 8)
            setSoundIntervall(25000);
            Sound->Play(9,8);
        break;
        case 'B':   // Startup Sound
            setSoundIntervall(10000);
            Sound->Play(Storage.getStartupSoundNr());            
        break;
        default:    // Ignore
        break;
    }
}

void MDuinoDomeMaster::processAltSoundCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltSoundCommand(Master): %s\r\n"), command);
    #endif
    RandomSoundMillis = millis();
    Serial_MP3.printf(F("%s\r"), command+1);
}

void MDuinoDomeMaster::processAltHoloCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltHoloCommand(Master): %s\r\n"), command);
    #endif
    Serial_Slave.printf(F("%s\r"), command);
}

// callback to reset JEDI to normal after a sequence, works only once
void MDuinoDomeMaster::sequenceCallbackJedi(MDuinoBase* object)
{
    object->parseCommand("*H000\r"); // quick way to turn off holos if connected to board
	object->parseCommand("@0T1\r");  // abort test routine, reset all to normal
	object->parseCommand("%T00\r");  // MP Off
	object->parseCommand("$R\r");  	 // Back to random mode if configured
}

// callback to reset JEDI to normal after a sequence, works only once
void MDuinoDomeMaster::sequenceCallbackResetMP(MDuinoBase* object)
{
	object->parseCommand("%T00\r");  	// Off
}

void MDuinoDomeMaster::sequenceCallbackResetSound(MDuinoBase* object)
{
	object->parseCommand("$R\r");  	    // Back to random mode if configured
}
