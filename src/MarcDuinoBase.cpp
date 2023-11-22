
#include "MarcDuinoBase.h"

MarcDuinoBase::MarcDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                             VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    Servo1(Servo1), Servo2(Servo2), Servo3(Servo3), Servo4(Servo4), Servo5(Servo5), Servo6(Servo6),
    Servo7(Servo7), Servo8(Servo8), Servo9(Servo9), Servo10(Servo10), Servo11(Servo11), Servo12(Servo12), Servo13(Servo13)
{
    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);

    HeartBeatMillis     = millis();
    HeartBeatIntervall  = HEARTBEAT_MILLIS;
}

void MarcDuinoBase::init()
{
    // Seed Random Generator
    randomSeed(analogRead(0));

    // HeartBeat-LED
    pinMode(P_LED2, OUTPUT);
    digitalWrite(P_LED2, HeartBeatStatus);

    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);

    checkEEPROM();
}

void MarcDuinoBase::run()
{
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

    // Heartbeat
    if ((millis() - HeartBeatMillis) > HeartBeatIntervall)
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

        Storage.setIndividualSettings(0);

        for (int i=0; i <= MAX_MARCUDINOSERVOS; i++)
        {
            Storage.setServoDirection(i, 0);                    // Direction normal, Global Setting plus each individual
            Storage.setServoSpeed(i, 255);                      // Full Speed, Global Setting plus each individual
            Storage.setServoPositions(i, PANEL_OPN, PANEL_CLS); // see config.h, original MarcDuino Default Values
        }
        for (int i=0; i <= MAX_MARCDUINOHOLOS; i++)
        {
            Storage.setHoloDirection(i, 0, 0);
            Storage.setHoloPositions(i, HOLO_MIN, HOLO_MAX, HOLO_MIN, HOLO_MAX);
            Storage.setHoloLightHighActive(i, true);
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

    param_num = atoi(param);    

    return true;
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
 *  #IOxx - Use individual open settings (0 = no, 1 = yes)
 *  #ICxx - Use individual close settings (0 = no, 1 = yes)
 *  #IMxx - Use individual mid settings (0 = no, 1 = yes)
 *
 *  #SOxxdddd Set Servo Degrees/Microseconds for Panel Open,  dddd=0000-0180  deg, dddd > 0544 Microseconds
 *  #SCxxdddd Set Servo Degrees/Microseconds for Panel Close,  dddd=0000-0180  deg, dddd > 0544 Microseconds
 *  #SPxxdddd Set Servo Degrees/Microseconds for Panel Mid,  dddd=0000-0180  deg, dddd > 0544 Microseconds
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
    char param_ext[5];

    unsigned int param_num      = 0;
    unsigned int param_num_ext  = 0;

    word OpenPos    = 0;
    word ClosedPos  = 0;

    word HMinPos    = 0;
    word HMaxPos    = 0;
    word VMinPos    = 0;
    word VMaxPos    = 0;

    memset(cmd, 0x00, 3);
    memset(param, 0x00, 4);
    memset(param_ext, 0x00, 5);

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
            return; // Invalid Command
        }

        param_num       = atoi(param);
        param_num_ext   = atoi(param_ext);
    }
    else if (strlen(command) == 9)   // #SOxxyyyy, #SCxxyyyy / #HOxxyyyy, #HCxxyyyy / #VOxxyyyy, #VCxxyyyy
    {
        memcpy(cmd, command+1, 2);

        if ((strcmp(cmd, "SO") != 0) && (strcmp(cmd, "SC") != 0) && (strcmp(cmd, "SI") != 0) &&
            (strcmp(cmd, "HO") != 0) && (strcmp(cmd, "HC") != 0) &&
            (strcmp(cmd, "VO") != 0) && (strcmp(cmd, "VC") != 0) )
        {
            Serial.println(F("Invalid Extended Command"));
            return; // Invalid Command
        }
        else
        {
            memcpy(param, command+3, 2);
            memcpy(param_ext, command+5, 4);

            param_num       = atoi(param);
            param_num_ext   = atoi(param_ext);

            // Serial.printf("cmd: %s, param_num: %d, param_num_ext: %d\r\n", cmd, param_num, param_num_ext);
        }
    }

    if (strcmp(cmd, "SD") == 0)            // Servo Direction
    {
        Storage.setServoDirection(0, param_num);
    }
    else if (strcmp(cmd, "SR") == 0)       // Individual Servo Reverse
    {
        Storage.setServoDirection(param_num, 1);
    }
    else if (strcmp(cmd, "SN") == 0)       // Individual Servo Normal
    {
        Storage.setServoDirection(param_num, 0);
    }
    else if (strcmp(cmd, "SV") == 0)       // Use individual servo settings (0 = no, 1 = yes)
    {
        Storage.setIndividualSettings(param_num);
    }
    else if (strcmp(cmd, "SO") == 0)       // Set Servo Degrees/Microseconds for Panel Open,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getServoPositions(param_num, OpenPos, ClosedPos);

        if (Storage.getServoDirection(param_num) == 0x01)
            ClosedPos = param_num_ext;
        else
            OpenPos = param_num_ext;

        Storage.setServoPositions(param_num, OpenPos, ClosedPos);

        if (Storage.getAdjustmentMode())
        {
            char ServoCommand[6];
            memset(ServoCommand, 0x00, 6);
            sprintf(ServoCommand, ":OP%02d", param_num);
            delay(250);
            parseCommand(ServoCommand);
        }
    }
    else if (strcmp(cmd, "SC") == 0)       // Set Servo Degrees/Microseconds for Panel Close,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getServoPositions(param_num, OpenPos, ClosedPos);

        if (Storage.getServoDirection(param_num) == 0x01)
            OpenPos = param_num_ext;
        else
            ClosedPos = param_num_ext;

        Storage.setServoPositions(param_num, OpenPos, ClosedPos);

        if (Storage.getAdjustmentMode())
        {
            char ServoCommand[6];
            memset(ServoCommand, 0x00, 6);
            sprintf(ServoCommand, ":CL%02d", param_num);
            delay(250);
            parseCommand(ServoCommand);            
        }
    }
    else if (strcmp(cmd, "SP") == 0)       // Set Servo Degrees/Microseconds for Panel Mid,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.setServoSpeed(param_num, param_num_ext);
    }
    else if (strcmp(cmd, "HO") == 0)       // Set Holo HServo Degrees/Microseconds Max Pos,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
        HMaxPos = param_num_ext;
        Storage.setHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
    }    
    else if (strcmp(cmd, "HC") == 0)       // Set Holo HServo Degrees/Microseconds Min Pos,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
        HMinPos = param_num_ext;
        Storage.setHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
    }    
    else if (strcmp(cmd, "HP") == 0)       // Set Holo HServo Speed (0-255)
    {
    }    
    else if (strcmp(cmd, "VO") == 0)       // Set Holo VServo Degrees/Microseconds Max Pos,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
        VMaxPos = param_num_ext;
        Storage.setHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
    }    
    else if (strcmp(cmd, "VC") == 0)       // Set Holo VServo Degrees/Microseconds Min Pos,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
        VMinPos = param_num_ext;
        Storage.setHoloPositions(param_num, HMinPos, HMaxPos, VMinPos, VMaxPos);
    }    
    else if (strcmp(cmd, "VP") == 0)       // Set Holo VServo Speed (0-255)
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
            case 1:
            case 2:
                Storage.setDisableRandomSound(param_num);
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
                delay(500);
                resetFunc();
            break;
            case 1:
                Storage.setMP3Player(MarcDuinoStorage::DFPlayer);
                delay(500);
                resetFunc();
            break;
            case 2:
                Storage.setMP3Player(MarcDuinoStorage::Vocalizer);
                delay(500);
                resetFunc();
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
    else if (strcmp(cmd, "HL") == 0)
    {
        switch(param_num)
        {
            case 00:    // All Holos LOW Active
                Storage.setHoloLightHighActive(0, false);
            break;
            case 01:    // All Holos HIGH Active
                Storage.setHoloLightHighActive(0, true);
            break;
            default:
                // TODO
            break;
        }
    }
    else if (strcmp(cmd, "DM") == 0)             // Dump EEPROM
    {
        Storage.dumpToSerial(param_num);
    }
    else if (strcmp(cmd, "RS") == 0)             // Reboot MarcDuino
    {
        delay(500);
        resetFunc();
    }
    else if (strcmp(cmd, "AD") == 0)             // Reboot MarcDuino
    {
        Storage.setAdjustmentMode(param_num == 0x01);
    }
    else
        Serial.print(F("NOT "));

    Serial.printf(F("valid %s\r\n"), cmd);
}