
#include "MDuinoDomeMaster.h"

MDuinoDomeMaster::MDuinoDomeMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, 
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    MDuinoDome(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13),
    Serial_Slave(Serial_Slave),
    Serial_MP3(Serial_MP3)
{
    Serial_Slave.begin(SERIAL_SLAVE_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Slave);

    Serial_MP3.begin(SERIAL_MP3_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_MP3);

    for(unsigned int i=0; i <= MaxPanel; ++i)
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

    parseCommand(":SE00");              // Close Panels
    Serial_Slave.print(F("#MD01\r"));   // Force Slave board to be in Slave Mode
}

void MDuinoDomeMaster::run()
{
    MDuinoDome::run();

    // Servos. TODO: Double implementation, check BaseClass Idea for Dome MarcDuinos
    if (ServoBuzzIntervall != 0)
    {
        if ((millis() - ServoBuzzMillis) > ServoBuzzIntervall)
        {
            for (unsigned int i = MinPanel; i <= MaxPanel; i++)
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
            unsigned int bank   = 0;
            unsigned int sound  = 0;

            getRandomSound(bank, sound);

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

            RandomSoundMillis = millis();
            setStandardRandomSoundIntervall();
        }
    }
}

void MDuinoDomeMaster::resetServoBuzz()
{
    ServoBuzzIntervall = SERVO_BUZZ_MILLIS;
}

void MDuinoDomeMaster::setStandardRandomSoundIntervall()
{
    byte DisableRandomSound = Storage.getDisableRandomSound();

    RandomSoundMillis       = millis();

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
 * '#' MarcDuino Setup commands used to configure various settings on the MarcDuino
*/
void MDuinoDomeMaster::parseCommand(const char* command)
{
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
        break;
    case '#':
        processSetupCommand(command);
        // Forwarding all but #MD to Slave to be in sync
        if (strncmp(command, "#MD", 3) != 0)
            Serial_Slave.printf(F("%s\r"), command);
        break;    
    default:
        break;
    }
    delay(COMMAND_DELAY);
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
void MDuinoDomeMaster::processPanelCommand(const char* command)
{
    char cmd[3];
    char param[4];
    char param_ext[5];

    unsigned int param_num = 0;
    unsigned int param_num_ext = 0;

    memset(cmd, 0x00, 3);
    memset(param, 0x00, 4);
    memset(param_ext, 0x00, 5);

    #ifdef DEBUG_MSG
    Serial.printf(F("PanelCommand(Master): %s\r\n"), command);
    #endif

    if (strlen(command) == 9)   // :MVxxyyyy
    {
        memcpy(cmd, command+1, 2);

        if ((strcmp(cmd, "MV") != 0))
            return; // Invalid Command
        else
        {
            memcpy(param, command+3, 2);
            memcpy(param_ext, command+5, 4);
        }
        param_num       = atoi(param);
        param_num_ext   = atoi(param_ext);
    }
    else if (!separateCommand(command, cmd, param_num))
        return;

    if (strcmp(cmd, "MV")==0)
    {
        if (param_num > MaxPanel)
            return;

        Panels[param_num]->move(param_num_ext);
    }
    else if (strcmp(cmd, "SE")==0)       // Start Sequence
    {
        playSequence(param_num);
    } 
    else if (strcmp(cmd, "OP")==0)  // Open Panel
    {
        if (param_num == 0)         // open all
        {
            for(unsigned int i=MinPanel; i<=MaxPanel; i++)
                Panels[i]->open();
            
            // Open Slave, too
            Serial_Slave.print(F(":OP00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->open();
        }
        else if (param_num == 12)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":OP12\r"));
        }
        else if (param_num == 13)   // Send commands to slave to open slave panels
        {
            Serial_Slave.print(F(":OP13\r"));
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (unsigned int i=7; i<=MaxPanel; i++)
            {
                Panels[i]->open();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (int i=MinPanel; i<=6; i++)
            {
                Panels[i]->open();
            }
        }

    }
    else if (strcmp(cmd, "CL")==0)  // Close Panel
    {
        if (param_num == 0)         // close all
        {
            for(unsigned int i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->close();
            
            // Open Slave, too
            Serial_Slave.print(F(":CL00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->close();
        }
        else if (param_num == 12)   // Send commands to slave to open slave panels
        {
            // Serial_Slave.print(F(":CL07\r")); // OLD
            Serial_Slave.print(F(":CL12\r"));
        }
        else if (param_num == 13)   // Send commands to slave to open slave panels
        {
            // Serial_Slave.print(F(":CL08\r"));  // OLD
            Serial_Slave.print(F(":CL13\r"));
        }
        else if (param_num == 14)    // Open Top Panels
        {
            for (unsigned int i=7; i<=MaxPanel; i++)
            {
                Panels[i]->close();
            }
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
            for (int i=MinPanel; i<=6; i++)
            {
                Panels[i]->close();
            }
        }        
    }
    else if (strcmp(cmd, "ST")==0)
    {
        if (param_num == 0)    // Alle panels
        {
            for(unsigned int i=MinPanel; i <= MaxPanel; i++)
                Panels[i]->detach();

            Serial_Slave.print(F(":ST00\r"));
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->detach();
        }
        else if (param_num == 12)
        {
            Serial_Slave.print(F(":ST12\r"));
        }
        else if (param_num == 13)
        {
            Serial_Slave.print(F(":ST13\r"));
        }
    }
    else if (strcmp(cmd, "RC")==0)
    {

    } 
    else if (strcmp(cmd, "HD")==0)
    {

    }
    else if (strcmp(cmd, "EO")==0)
    {
        AUX1(param_num);
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
    unsigned int bank = 0;
    unsigned int sound= 0;

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

void MDuinoDomeMaster::processI2CCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("I2CCommand(Master): %s\r\n"), command);
    #endif
}

void MDuinoDomeMaster::playSequenceAddons(const unsigned int SeqNr)
{
    // Also forward to Slave
    Serial_Slave.printf(F(":SE%2d\r"), SeqNr);

    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        break;
    case 1:  // SCREAM
        parseCommand("$S");         // Scream Sound
        parseCommand("@0T5");       // Scream Display
        parseCommand("*MF04");      // Magic Flicker for 4 seconds
        parseCommand("*F004");      // HP Flicker for 4 seconds
        break;
    case 2: // WAVE
        parseCommand("*H004");      // flash holos for 4 seconds
        parseCommand("$213");		// happy sound
        break;
    case 3: // MOODY FAST WAVE
        parseCommand("@0T2");       // flash display ...
        parseCommand("@0W4");       // ... for 4 seconds
        parseCommand("*F004");      // HP Flicker for 4 seconds
        parseCommand("$34");		// moody sound
        break;
    case 4: // OPEN WAVE
        parseCommand("*H005");      // flash holos for 5 seconds
        parseCommand("$36");		// long happy sound
        break;
    case 5: // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("@0T92");      // spectrum display
        parseCommand("*HP17");      // HPs flash for 17 seconds
        parseCommand("$c");         // beeping cantina sound
        parseCommand("%T52");	    // Magic Panel in VU Mode
        break;
    case 6: // SHORT CIRCUIT / FAINT
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        //EXT1On(4); // Turn on Smoke for 4 seconds  Do first so there's smoke when the panels open.
        parseCommand("$F");         // Faint sound
        parseCommand("@0T4");       // short circuit display ...
        parseCommand("@0W10");      // ... for 10 seconds 
        parseCommand("*MF10");      // Magic Panel Flicker for 10 seconds
        parseCommand("*F010");      // HPs flicker 10 seconds
        break;
    case 7: // Cantina (Orchestral Cantina, Rhythmic Panels)
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("$C");         // Cantina sound        
        parseCommand("@0T92");      // spectrum display
        parseCommand("*F046");      // HPs flicker 46 seconds        
        parseCommand("%T52");	    // Magic Panel in VU Mode        
        break;
    case 8: // LEIA
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("*RC01"); 	    // HP 01 in RC mode
        parseCommand("$L");         // Leia message sound  
        parseCommand("*F134");      // front holos flicker for 34 sec 
        parseCommand("@0T6");       // Leia display
        parseCommand("%T22");	    // HP in Cylon Row Scan mode       
        break;
    case 9:	// DISCO
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("@0T92");      // spectrum display
        parseCommand("*F099");      // HPs flicker as long as possible   
        parseCommand("%T52");	    // Magic Panel in VU Mode
        parseCommand("$D");         // disco music
        break;
    case 10: // QUIET   sounds off, holo stop, panel closed
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("*H000");  // quick way to turn off holos if connected to MarcDuino  
        parseCommand("@0T1");   // abort test routine, reset all to normal
        parseCommand("*ST00");  // all holos to stop
        parseCommand("$s");		// stop sounds
        // stop_command(0);					// all panels off RC        
        break;
    case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
        // init_jedi();						// JEDI back to default
        parseCommand("*RD00\r");			// all HPs to random
        parseCommand("$R");					// random sounds mode
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
        //init_jedi();						// JEDI back to default
        parseCommand("*ST00\r");			// all HPs to stop
        parseCommand("$R");					// random sounds mode
        // stop_command(0);					// all panels off RC and closed
        break;
    case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
        // init_jedi();						// JEDI back to default
        parseCommand("*RD00\r");			// all HPs to random
        parseCommand("*ON00\r");			// all HPs lights on
        parseCommand("$R");					// random sounds mode
        //stop_command(0);					// all panels off RC and closed
        break;

    case 15: // SCREAM no panels: sound + lights but no panels
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("$S");	 				// code for scream sound
        parseCommand("@0T5\r");				// scream display
        parseCommand("*F003\r");			// holos flicker for 4 seconds
        parseCommand("*MF04\r");			// magic panel on for 4 seconds
        break;
    case 16: // Panel Wiggle
        parseCommand("@0T5\r");				// scream display
        break;
    default:
        break;
    }
    // Finally GOOOOO
    Sequencer.startSequence();
}

void MDuinoDomeMaster::sequenceCallbackBuzz(MDuinoBase* object)
{
    ((MDuinoDomeMaster*)object)->resetServoBuzz();
}

// callback to reset JEDI to normal after a sequence, works only once
void MDuinoDomeMaster::sequenceCallbackJedi(MDuinoBase* object)
{
    object->parseCommand("*H000\r"); // quick way to turn off holos if connected to MarcDuino
	object->parseCommand("@0T1\r");  // abort test routine, reset all to normal
	object->parseCommand("%T00\r");  // MP Off
}

// callback to reset JEDI to normal after a sequence, works only once
void MDuinoDomeMaster::sequenceCallbackResetMP(MDuinoBase* object)
{
	object->parseCommand("%T00\r");  	// Off
}