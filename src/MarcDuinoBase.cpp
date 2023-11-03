
#include "MarcDuinoBase.h"
#include "PanelSequences.h"

MarcDuinoBase::MarcDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                             VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    Servo1(Servo1), Servo2(Servo2), Servo3(Servo3), Servo4(Servo4), Servo5(Servo5), Servo6(Servo6),
    Servo7(Servo7), Servo8(Servo8), Servo9(Servo9), Servo10(Servo10), Servo11(Servo11), Servo12(Servo12), Servo13(Servo13)
{
    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);

    // Initilize Sound Bank Overview for Random Songs
    MaxSoundsPerBank[0] = 0;
    for (int i = 1; i <= MAX_SOUND_BANK; i++)
        MaxSoundsPerBank[i] = Storage.getMaxSound(i);    
}

void MarcDuinoBase::init()
{
    // Seed Random Generator
    randomSeed(analogRead(0));

    // HeartBeat-LED
    pinMode(P_LED2, OUTPUT);
    digitalWrite(P_LED2, HeartBeatStatus);

    // AUX1 Port
    pinMode(P_AUX1, OUTPUT);
    digitalWrite(P_AUX1, LOW);

    HeartBeatMillis = millis();

    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);

    checkEEPROM();

    Sequencer.init();
}

void MarcDuinoBase::run()
{
    Sequencer.run();

    // Read Serial
    if (Serial.available())
    {
        unsigned char c = Serial.read();
        SerialBuffer[BufferIndex++] = c;
        if ((c == '\r') || (BufferIndex == SERIALBUFFERSIZE))   // Command complete or buffer full
        {
            SerialBuffer[BufferIndex-1] = 0x00; // ensure proper termination
            parseCommand(SerialBuffer);
            memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
            BufferIndex = 0;
        }
    }

    // AUX1
    if ((AUX1Duration != 0) && (AUX1Duration != 99))
    {
        if ((millis() - AUX1Millis) > AUX1Duration)
        {
            digitalWrite(P_AUX1, LOW);
            AUX1Duration = 0;
            #ifdef DEBUG_MSG
            Serial.println(F("AUX1 off"));
            #endif
        }
    }

    // Heartbeat
    if ((millis() - HeartBeatMillis) > HEARTBEAT_MILLIS)
    {
        toggleHeartBeat();
        HeartBeatMillis = millis();
    }
}

void MarcDuinoBase::checkEEPROM()
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

void MarcDuinoBase::toggleHeartBeat()
{
    if (HeartBeatStatus == LOW)
      HeartBeatStatus = HIGH;
    else
      HeartBeatStatus = LOW;

    digitalWrite(P_LED2, HeartBeatStatus);
}

bool MarcDuinoBase::separateCommand(const char* command, char* cmd, unsigned int & param_num)
{
    char param[3];
    memset(param, 0x00, 3);

    if (strlen(command) != 5)
    {
        Serial.printf(F("Invalid Size: %i\r\n"), strlen(command));
        return false;
    }
    
    memcpy(cmd, command+1, 2);
    memcpy(param, command+3, 2);

    #ifdef DEBUG_MSG
    Serial.printf(F("Cmd: %s, Param: %s\r\n"), cmd, param);
    #endif

    param_num = atoi(param);    

    return true;
}

bool MarcDuinoBase::separateSoundCommand(const char* command, char* cmd, unsigned int & bank, unsigned int & sound)
{
    bank = 0;
    sound = 0;

    //if ((strlen(command) != 4) && (strlen(command) != 2))
    if ((strlen(command) <2) || (strlen(command) >4))
    {
        Serial.printf(F("Invalid Size: %i\r\n"), strlen(command));
        return false;
    }
    
    if (strlen(command) == 2)
    {
        memcpy(cmd, command+1, 1);

        #ifdef DEBUG_MSG
        Serial.printf(F("Cmd: %s\r\n"), cmd);
        #endif
    }
    else if (strlen(command) == 3)
    {
        char bank_char[2];
        char sound_char[3];

        memset(cmd, 0x00, 1);

        memset(bank_char, 0x00, 2);
        memset(sound_char, 0x00, 3);

        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 1);

        bank=atoi(bank_char);
        sound=atoi(sound_char);

        #ifdef DEBUG_MSG
        Serial.printf(F("Cmd: %s, Bank: %i, Sound %i\r\n"), cmd, bank, sound);
        #endif
    }
    else if (strlen(command) == 4)
    {
        char bank_char[2];
        char sound_char[3];

        memset(cmd, 0x00, 1);

        memset(bank_char, 0x00, 2);
        memset(sound_char, 0x00, 3);

        memcpy(bank_char, command+1, 1);
        memcpy(sound_char, command+2, 2);

        bank=atoi(bank_char);
        sound=atoi(sound_char);

        #ifdef DEBUG_MSG
        Serial.printf(F("Cmd: %s, Bank: %i, Sound %i\r\n"), cmd, bank, sound);
        #endif
    }
    return true;
}

void MarcDuinoBase::getRandomSound(unsigned int & bank, unsigned int & sound)
{
    bank = random(1,6);
    sound = random(1, MaxSoundsPerBank[bank]+1);
}

/*
 *	Setup Commands
 * * 
 *	//// SERVO CONTROLS
 *	#SD00 Set Servo direction forward
 *	#SD01 Set servo direction reversed
 *
 *  // deprecated, will be removed in future
 *	#SRxxy Set individual servo to either forward or reversed xx=servo number y=direction
 *		Must be a 2 digit Servo number i.e. Servo 4 is 04
 *		Must be either 0 or 1 to set the direction (0 normal, 1 reversed)
 *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.
 *  // NEW:
 *	#SRxx Set individual servo to reversed xx=servo number
 *		Must be a 2 digit Servo number i.e. Servo 4 is 04
 *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.
 *	#SNxx Set individual servo to normal xx=servo number
 *		Must be a 2 digit Servo number i.e. Servo 4 is 04
 *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.
 *
 *  #SOxxddd Set Servo Degrees for Panel Open,  ddd=000-180 (90deg, Servo1: SO01090)
 *  #SCxxddd Set Servo Degrees for Panel Closed ddd=000-180 (180deg, Servo1: SO01180)
 *  #SPxxddd Set Servo Speed, ddd=0-255
 * 
 *  //// STARTUP SOUND CONTROLS
 *  #SSxx Set startup sound
 *	    #SS00 : Disable Startup Sound, and remove startup sound delay for fast boot of R2
 *	    #SS01 : Default Startup Sound in file 255
 *      #SS02 : Alternate Startup Sound in file 254
 *	    #SS03 : Second Alternate Startup Sound in file 253
 *
 *	// Chatty/Silent Mode
 *  #SQnn Set chatty mode
 *	    #SQ00 : Default Chatty Mode
 *  	#SQ01 : Silent on startup
 *
 *  #SMxx - Disable Random Sounds   (deprecated, will be removed in future)
 *      #SM00 : Random Sound on
 *      #SM01 : No Random Sound + Volume off
 *      #SM02 : No Random Sound
 * 
 *  #SXxx - Set Max Random Pause in seconds
 *  #SYxx - Set Min Random Pause in seconds
 *
 *	//// PANEL SEQUENCER CONTROLS
 *	#STxx Setup Delay time between Master and Slave Panel Sequences.
 *		Use this if the Slave panels are starting too soon
 *		Values up to 250 are supported.  Values are in ms.
 *
 *  //// MAIN CONFIG
 *  #MDxx Set MarcDuino Mode
 *      #MD00 : MarcDuino Dome Master
 *      #MD01 : MarcDuino Dome Slave
 *      #MD02 : MarcDuino Body Master
 *      MarcDuino will reboot immediately after setup and start in new mode.
 * 
 *  #MPxx Set MP3-Player Type
 *      #MP00 : SparkFun MP3 Trigger
 *      #MP01 : DFPlayer
 *      #MP02 : Vocalizer
 * 
 *  #MSxyy Set max Sounds per Bank. x=1-9, y=0-25
 * 
 *  //// SYSTEM FUNCTIONS
 *  #DMxx Dump EEPROM at address xx
 *  #RSET Reboot MarcDuino
 */

void MarcDuinoBase::processSetupCommand(const char* command)
{
    char cmd[3];
    char param[4];
    char param_ext[4];

    unsigned int param_num      = 0;
    unsigned int param_num_ext  = 0;

    memset(cmd, 0x00, 3);
    memset(param, 0x00, 4);
    memset(param_ext, 0x00, 4);

    #ifdef DEBUG_MSG
    Serial.printf(F("SetupCommand(Base): %s\r\n"), command);
    #endif

    // Command Parsing

    if (strlen(command) == 5)   // Standard #CCxx
    {
        if (!separateCommand(command, cmd, param_num))
            return; // Invalid Command
    }
    else if (strlen(command) == 6)   // #SRxxy and #MSxyy
    {
        memcpy(cmd, command+1, 2);

        if (strcmp(cmd, "SR") == 0)
        {
            memcpy(param, command+3, 2);
            memcpy(param_ext, command+5, 1);
        } 
        else if (strcmp(cmd, "MS") == 0)
        {
            memcpy(param, command+3, 1);
            memcpy(param_ext, command+4, 2);
        }
        else
        {
            Serial.println(F("Invalid Extended Command"));
            return; // Invalid Command
        }

        param_num       = atoi(param);
        param_num_ext   = atoi(param_ext);

        #ifdef DEBUG_MSG
        Serial.printf(F("Cmd: %s, Param: %i, Param Ext: %i\r\n"), cmd, param_num, param_num_ext);
        #endif        
    }
    else if (strlen(command) == 8)   // #SOxxyyy, #SCxxyyy and #SPxxyyy
    {
        memcpy(cmd, command+1, 2);

        if ((strcmp(cmd, "SO") != 0) && (strcmp(cmd, "SC") != 0) && (strcmp(cmd, "SP") != 0))
        {
            Serial.println(F("Invalid Extended Command"));
            return; // Invalid Command
        }
        else
        {
            memcpy(param, command+3, 2);
            memcpy(param_ext, command+5, 3);

            param_num       = atoi(param);
            param_num_ext   = atoi(param_ext);

            #ifdef DEBUG_MSG
            Serial.printf(F("Cmd: %s, Param: %i, Param Ext: %i\r\n"), cmd, param_num, param_num_ext);
            #endif   
        }
    }

    if (strcmp(cmd, "SD") == 0)            // Servo Direction
    {
    }
    else if (strcmp(cmd, "SR") == 0)       // Individual Servo Reverse
    {
    }
    else if (strcmp(cmd, "SN") == 0)       // Individual Servo Normal
    {
    }
    else if (strcmp(cmd, "SS") == 0)       // Sound Control
    {
        switch(param_num)
        {
            case 0:
                Storage.setStartupSoundNr(0);
            break;
            case 1:
                Storage.setStartupSoundNr(255);
            break;
            case 2:
                Storage.setStartupSoundNr(254);
            break;
            case 3:
                Storage.setStartupSoundNr(253);
            break;
            default:
                Storage.setStartupSoundNr(255);
            break;
        }
    }
    else if (strcmp(cmd, "SQ") == 0)       // Chatty Mode
    {
        if (param_num == 0)
        {
            Storage.setChattyMode();            
        }
        else if (param_num == 1)
        {
            Storage.setChattyMode(false);
        }
        else
        {
            Storage.setChattyMode();       // Default on
        }
    }
    else if (strcmp(cmd, "SM") == 0)       // Disable Random Mode
    {
        switch(param_num)
        {
            case 0:
                Storage.setDisableRandomSound(0);
            break;
            case 1:
                Storage.setDisableRandomSound(1);
            break;
            case 2:
                Storage.setDisableRandomSound(2);
            break;
            default:
                Storage.setDisableRandomSound(0);
            break;
        }
    }    
    else if (strcmp(cmd, "SX") == 0)       // Max Random Pause
    {
        Storage.setMaxRandomPause(param_num);
    }
    else if (strcmp(cmd, "SY") == 0)       // Min Random Pause
    {
        Storage.setMinRandomPause(param_num);
    }
    else if (strcmp(cmd, "ST") == 0)       // Delay Time Master/Slave
    {
    }
    else if (strcmp(cmd, "MD") == 0)       // Set MarcDuino Type and reboot in new mode
    {
        switch(param_num)
        {
            case 0:
                Storage.setType(MarcDuinoStorage::DomeMaster);
                delay(500);
                resetFunc();
            break;
            case 1:
                Storage.setType(MarcDuinoStorage::DomeSlave);
                delay(500);
                resetFunc();
            break;
            case 2:
                Storage.setType(MarcDuinoStorage::BodyMaster);
                delay(500);
                resetFunc();
            break;
            default:
            break;
        }
    }
    else if (strcmp(cmd, "MP") == 0)       // Set MarcDuinoMP3Player Type
    {
        switch(param_num)
        {
            case 0:
                Storage.setMP3Player(MarcDuinoStorage::MP3Trigger);
            break;
            case 1:
                Storage.setMP3Player(MarcDuinoStorage::DFPlayer);
            break;
            case 2:
                Storage.setMP3Player(MarcDuinoStorage::Vocalizer);
            break;
            default:
            break;
        }
    }
    else if (strcmp(cmd, "MS") == 0)
    {
        if ((param_num < 1) || (param_num) > MAX_SOUND_BANK)    // Bank must be 1-9
            return;
        if (param_num_ext > MAX_BANK_SOUND)                    // Sound must be 0-25
            return;

        Storage.setMaxSound(param_num, param_num_ext);
    }
    else if (strcmp(cmd, "DM") == 0)             // Dump EEPROM
    {
        Storage.dumpToSerial();
    }
    else if (strcmp(cmd, "RS") == 0)             // Reboot MarcDuino
    {
        delay(500);
        resetFunc();
    }
}

void MarcDuinoBase::playSequence(const unsigned int SeqNr)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("PlaySequence(Base): %i\r\n"), SeqNr);
    #endif

    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.startSequence();
        break;
    case 1:  // SCREAM
        Sequencer.loadSequence(panel_all_open, SEQ_SIZE(panel_all_open));
        //seq_loadspeed(panel_slow_speed);	// slow open
        Sequencer.startSequence();
        break;
    case 2: // WAVE
        Sequencer.loadSequence(panel_wave, SEQ_SIZE(panel_wave));
        //seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 3: // MOODY FAST WAVE
        Sequencer.loadSequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
        //seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 4: // OPEN WAVE
        Sequencer.loadSequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
        //seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 5: // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
        Sequencer.loadSequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
        //seq_loadspeed(panel_slow_speed);					// slow speed marching ants
        Sequencer.startSequence();
        break;
    case 6: // SHORT CIRCUIT / FAINT
        Sequencer.loadSequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
        //seq_loadspeed(panel_super_slow_speed);	// very slow speed open
        //EXT1On(4); // Turn on Smoke for 4 seconds  Do first so there's smoke when the panels open.
        Sequencer.startSequence();
        break;
    case 7: // Cantina (Orchestral Cantina, Rhythmic Panels)
        Sequencer.loadSequence(panel_dance, SEQ_SIZE(panel_dance));
        // seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 8: // LEIA
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));	// Close panels
        // seq_loadspeed(panel_slow_speed);	// Go slow
        Sequencer.startSequence();       
        break;
    case 9:	// DISCO
        Sequencer.loadSequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
        // seq_resetspeed();
        Sequencer.startSequence();       
        break;
    case 10: // QUIET   sounds off, holo stop, panel closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        //seq_loadspeed(panel_slow_speed);	// go slow
        // seq_resetspeed();				// sequence speed to fast
        // stop_command(0);					// all panels off RC        
        Sequencer.startSequence();       
        break;
    case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        //seq_loadspeed(panel_slow_speed);	// go slow
        //seq_resetspeed();					// sequence speed to fast
        //stop_command(0);					// all panels off RC and closed
        Sequencer.startSequence();
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
        //seq_loadspeed(panel_slow_speed);	// go slow
        // seq_resetspeed();				// sequence speed to fast
        // stop_command(0);					// all panels off RC and closed
        Sequencer.startSequence();
        break;
    case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        // seq_loadspeed(panel_slow_speed);	// go slow
        //seq_resetspeed();					// sequence speed to fast
        //stop_command(0);					// all panels off RC and closed
        Sequencer.startSequence();
        break;

    case 15: // SCREAM no panels: sound + lights but no panels
        break;
    case 16: // Panel Wiggle
        Sequencer.loadSequence(panel_wiggle, SEQ_SIZE(panel_wiggle));
        //seq_loadspeed(panel_medium_speed);
        Sequencer.startSequence();
        break;

    ///////////////////////////////////////////
    //	sequences of panels only, no sounds or light effects
    //
    //	:SE51 Scream, with all panels open
    //	:SE52 Wave, one panel at a time
    //	:SE53 Fast (Smirk) back and forth wave
    //	:SE54 Wave 2 (open progressively all panels, then close one by one)
    //	:SE55 Marching ants
    //	:SE56 Faint/Short Circuit
    //	:SE57 Rythmic panel dance
    //  :SE58 Bye Bye Wave
    //	:SE59 Open Panels half way
    //////////////////////////////////////////

    case 51: // SCREAM
        Sequencer.loadSequence(panel_all_open, SEQ_SIZE(panel_all_open));
        // seq_loadspeed(panel_slow_speed);	// softer close
        Sequencer.startSequence();
        break;
    case 52: // WAVE1
        Sequencer.loadSequence(panel_wave, SEQ_SIZE(panel_wave));
        // seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 53: // MOODY FAST WAVE
        Sequencer.loadSequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
        // seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 54: // WAVE2
        Sequencer.loadSequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
        // seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 55: // Marching ant
        Sequencer.loadSequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
        // seq_loadspeed(panel_slow_speed);	// softer close
        Sequencer.startSequence();
        break;
    case 56: // SHORT CIRCUIT / FAINT
        Sequencer.loadSequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
        // seq_loadspeed(panel_super_slow_speed);	// very slow close
        // EXT1On(4); // Turn on Smoke for 4 seconds
        Sequencer.startSequence();
        break;
    case 57: // Rhythmic Panels
        Sequencer.loadSequence(panel_dance, SEQ_SIZE(panel_dance));
        // seq_resetspeed();
        Sequencer.startSequence();
        break;
    case 58: // Panel Wave Bye Bye
        Sequencer.loadSequence(panel_bye_bye_wave, SEQ_SIZE(panel_bye_bye_wave));
        // seq_loadspeed(panel_slow_speed);
        Sequencer.startSequence();
        break;
    case 59: // Panel all open Middle - Neil's test sequence to check partial panel opening.
        Sequencer.loadSequence(panel_all_open_mid, SEQ_SIZE(panel_all_open_mid));
        // seq_loadspeed(panel_slow_speed);
        Sequencer.startSequence();
        break;
    default:
        break;         
    }

    playSequenceAddons(SeqNr);
}

void MarcDuinoBase::AUX1(const unsigned int Duration)
{
    switch (Duration)
    {
    case 0:
        digitalWrite(P_AUX1, LOW);
        AUX1Duration = 0;
        #ifdef DEBUG_MSG
        Serial.println(F("AUX1 off"));
        #endif
        break;
    case 99:
        digitalWrite(P_AUX1, HIGH);
        AUX1Duration = 0;
        #ifdef DEBUG_MSG
        Serial.println(F("AUX1 on"));
        #endif
        break;
    default:
        AUX1Millis = millis();
        AUX1Duration = Duration*1000;
        digitalWrite(P_AUX1, HIGH);
        #ifdef DEBUG_MSG
        Serial.printf(F("AUX1 on for %i seconds.\r\n"), Duration);
        #endif
        break;
    }
}
