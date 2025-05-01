
#include "MDuinoBase.h"
#include <Wire.h>

MDuinoBase::MDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, VarSpeedServo& Servo6,
                             VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    Servo1(Servo1), Servo2(Servo2), Servo3(Servo3), Servo4(Servo4), Servo5(Servo5), Servo6(Servo6),
    Servo7(Servo7), Servo8(Servo8), Servo9(Servo9), Servo10(Servo10), Servo11(Servo11),
    Sequencer(this)
{
    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
    memset(WireBuffer, 0x00, SERIALBUFFERSIZE);

    HeartBeatMillis     = millis();
    HeartBeatIntervall  = HEARTBEAT_MILLIS;

    ServoBuzzMillis     = millis();
    ServoBuzzIntervall  = SERVO_BUZZ_MILLIS;    // TODO Make EEPROM setting
}

void MDuinoBase::init()
{
    // Seed Random Generator
    randomSeed(analogRead(0));

    // HeartBeat-LED
    pinMode(P_LED2, OUTPUT);
    digitalWrite(P_LED2, HeartBeatStatus);

    // AUX1 Port
    #ifndef SEPARATE_DOMELIFT
    pinMode(P_AUX1, OUTPUT);
    digitalWrite(P_AUX1, LOW);
    #endif

    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
    memset(WireBuffer, 0x00, SERIALBUFFERSIZE);

    Sequencer.init();

    checkEEPROM();
}

void MDuinoBase::run()
{
    Sequencer.run();

    // Read Serial
    if (Serial.available())
    {
        unsigned char c = Serial.read();
        if (c == '\n')
            return;        
        SerialBuffer[BufferIndex++] = c;
        if ((c == '\r') || (BufferIndex == SERIALBUFFERSIZE))   // Command complete or buffer full
        {
            SerialBuffer[BufferIndex-1] = 0x00; // ensure proper termination
            if (BufferIndex>1)
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

    // AUX1
    #ifndef SEPARATE_DOMELIFT
    if ((AUX1Duration != 0) && (AUX1Duration != 99))
    {
        if ((millis() - AUX1Millis) > AUX1Duration)
        {
            digitalWrite(P_AUX1, LOW);
            AUX1Duration = 0;
        }
    }
    #endif

    // I2C
    #ifdef INCLUDE_I2C_SLAVE
    if (Wire.available())
    {
        int i = Wire.read();
        unsigned char c;
        c = (unsigned char)i;

        WireBuffer[WireIndex++] = c;
        if ((c == '\r') || (WireIndex == SERIALBUFFERSIZE))   // Command complete or buffer full
        {
            WireBuffer[WireIndex-1] = 0x00; // ensure proper termination
            parseCommand(WireBuffer);
            memset(WireBuffer, 0x00, SERIALBUFFERSIZE);
            WireIndex = 0;
        }
    }
    #endif
}

void MDuinoBase::playSequence(const byte SeqNr)
{
    if (SequencePlayer != nullptr)
    {
        SequencePlayer->playSequence(SeqNr);
        playSequenceAddons(SeqNr);
    }
}

void MDuinoBase::checkEEPROM(const bool factoryReset /*= false*/)
{
    byte ConfigVersion = Storage.getConfigVersion();

    if ((ConfigVersion != CONFIG_VERSION) || (factoryReset == true))
    {       
        #ifdef DEBUG_MSG
        Serial.println(F("Invalid Config Version or Factory Reset. Storing defaults in EEPROM and restart."));
        #endif

        // Fast blink
        HeartBeatIntervall = HEARTBEAT_MILLIS / 8;        

        Storage.setType(MDuinoStorage::DomeMaster);
        Storage.setMP3Player(MDuinoStorage::MP3Trigger);
        Storage.setStartupSoundNr(255);
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

        for (byte i=1; i <= MAX_MARCUDINOSERVOS; i++)
        {
            Storage.setServoSpeed(i, 0);            // Full Speed
            Storage.setServoPositions(i, PANEL_OPN, PANEL_CLS); // see config.h, original MarcDuino Default Values
        }
        for (byte i=1; i <= MAX_MDUINOHOLOS; i++)
        {
            Storage.setHoloServoSpeed(i, 0, 0);     // Full speed
            Storage.setHoloPositions(i, HOLO_MIN, HOLO_MAX, HOLO_MIN, HOLO_MAX);
            Storage.setHoloLightHighActive(i, true);
            Storage.setHoloNeoPixel(i, false);  // Non NeoPixels
            Storage.setHoloLEDs(i, 7);          // 7 LEDs for NeoPixels
        }

        Storage.setConfigVersion(CONFIG_VERSION);   // Final step before restart
        delay(500);
        resetFunc();
    }
}

void MDuinoBase::toggleHeartBeat()
{
    if (HeartBeatStatus == LOW)
      HeartBeatStatus = HIGH;
    else
      HeartBeatStatus = LOW;

    digitalWrite(P_LED2, HeartBeatStatus);
}

void MDuinoBase::resetServoBuzz()
{
    ServoBuzzIntervall = SERVO_BUZZ_MILLIS;
    ServoBuzzMillis = millis();
}

void MDuinoBase::sequenceCallbackBuzz(MDuinoBase* object)
{
    object->resetServoBuzz();
}

void MDuinoBase::AUX1(const unsigned int Duration)
{
    #ifndef SEPARATE_DOMELIFT
    if (Duration == 0)
    {
        AUX1Duration = 0;
        digitalWrite(P_AUX1, LOW);
    } 
    else if (Duration == 99)
    {
        AUX1Duration = 0;
        digitalWrite(P_AUX1, HIGH);
    }
    else
    {
        AUX1Millis = millis();
        AUX1Duration = Duration*1000;
        digitalWrite(P_AUX1, HIGH);
    }
    #endif
}

bool MDuinoBase::separateCommand(const char* command, char* cmd, unsigned int & param_num, unsigned int & param_num_ext)
{
    char param[3];
    char param_ext[16];

    memset(param, 0x00, 3);
    memset(param_ext, 0x00, 16);

    // Minimum Command Size is 5
    // Prefix(1)+Command(2)+Params(>=2)

    if (strlen(command) < 5)
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Invalid Size: %i\r\n"), strlen(command));
        #endif
        return false;
    }
    
    memcpy(cmd, command+1, 2);
    memcpy(param, command+3, 2);

    param_num = atoi(param);

    if (strlen(command) > 5)
    {
        memcpy(param_ext, command+5, strlen(command)-5);
        param_num_ext = atoi(param_ext);
    }


    return true;
}

void MDuinoBase::processSetupCommand(const char* command)
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
    if (strlen(command) == 6)   // #MSxyy and #SSxxx
    {
        memcpy(cmd, command+1, 2);

        if (strcmp(cmd, "MS") == 0)
        {
            memcpy(param, command+3, 1);
            memcpy(param_ext, command+4, 2);
        }
        else if (strcmp(cmd, "SS") == 0)
        {
            memcpy(param, command+3, 3);
        }        
        else
        {
            return; // Invalid Command
        }
        param_num       = atoi(param);
        param_num_ext   = atoi(param_ext);
    }
    else // Standard #CCxxyy...
    {
        if (!separateCommand(command, cmd, param_num, param_num_ext))
            return; // Invalid Command
    }

    #ifdef DEBUG_MSG
    Serial.printf(F("cmd: %s, param_num: %d, param_num_ext: %d\r\n"), cmd, param_num, param_num_ext);
    #endif

    if (strcmp(cmd, "SO") == 0)       // Set Servo Degrees/Microseconds for Panel Open,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getServoPositions(param_num, OpenPos, ClosedPos);
        OpenPos = param_num_ext;
        Storage.setServoPositions(param_num, OpenPos, ClosedPos);
    }
    else if (strcmp(cmd, "SC") == 0)       // Set Servo Degrees/Microseconds for Panel Close,  dddd=0000-0180  deg, dddd > 0544 Microseconds
    {
        Storage.getServoPositions(param_num, OpenPos, ClosedPos);
        ClosedPos = param_num_ext;
        Storage.setServoPositions(param_num, OpenPos, ClosedPos);
    }
    else if (strcmp(cmd, "SP") == 0)       // Set Servo Speed (0-255)
    {
        Storage.setServoSpeed(param_num, param_num_ext);
    }
    else if (strcmp(cmd, "SW") == 0)       // Swap Panel xx Open<->Close value
    {
        Storage.getServoPositions(param_num, OpenPos, ClosedPos);
        Storage.setServoPositions(param_num, ClosedPos, OpenPos);
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
        Storage.setStartupSoundNr(param_num);
    }
    else if (strcmp(cmd, "SQ") == 0)       // Disable Random Sound
    {
        if (param_num <= 2)
            Storage.setDisableRandomSound(param_num);
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
    else if (strcmp(cmd, "MD") == 0)       // Set board mode and reboot in new mode
    {
        if (param_num == 0)
            Storage.setType(MDuinoStorage::DomeMaster);
        else if (param_num == 1)
            Storage.setType(MDuinoStorage::DomeSlave);
        else if (param_num == 2)
            Storage.setType(MDuinoStorage::BodyMaster);
        else if (param_num == 3)
            Storage.setType(MDuinoStorage::BodySlave);
        delay(500);
        resetFunc();
    }
    else if (strcmp(cmd, "MP") == 0)       // Set MP3Player Type
    {
        if (param_num == 0)
            Storage.setMP3Player(MDuinoStorage::MP3Trigger);
        else if (param_num == 1)
            Storage.setMP3Player(MDuinoStorage::DFPlayer);
        else if (param_num == 2)
            Storage.setMP3Player(MDuinoStorage::Vocalizer);
#ifdef INCLUDE_DY_PLAYER
        else if (param_num == 3)
            Storage.setMP3Player(MDuinoStorage::DYPlayer);
#endif
        delay(500);
        resetFunc();
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
        Storage.setHoloLightHighActive(abs(param_num/10), (param_num%10) == 1);
    }
    else if (strcmp(cmd, "HN") == 0)
    {
        Storage.setHoloNeoPixel(abs(param_num/10), (param_num%10) == 1);
    }
    else if (strcmp(cmd, "HX") == 0)
    {
        Storage.setHoloLEDs(param_num, param_num_ext);
    }
    #ifdef DEBUG_MSG
    else if (strcmp(cmd, "DM") == 0)             // Dump EEPROM
    {
        Storage.dumpToSerial(param_num);
    }
    #endif
    else if (strcmp(cmd, "RS") == 0)             // Reboot Board
    {
        if (param_num == 0x01)
            checkEEPROM(true);  // Factory Reset

        delay(500);
        resetFunc();
    }
    else
    {
        #ifdef DEBUG_MSG
        Serial.print(F("NOT "));
        #endif
    }

    #ifdef DEBUG_MSG
    Serial.printf(F("valid %s\r\n"), cmd);
    #endif
}

#ifdef INCLUDE_CLASSIC_I2C_SUPPORT
void MDuinoBase::processI2CCommand(const char* command)
{

    #ifdef DEBUG_MSG
    Serial.printf(F("I2CCommand(Base): %s\r\n"), command);
    #endif

    // Supported I2C Address Range: 0-127 (7 Bit)
	unsigned int I2C_Address = 0;
    char* token = NULL;
    char* cmd   = NULL;
  	const char delim[] = ",";

    if (strlen(command) < 2)
        return;

    cmd = new char[strlen(command)];
    memset(cmd, 0x00, strlen(command));
    memcpy(cmd, command+1, strlen(command)-1);  // truncate leading "&"

    // get the address field. Need to tokenize on the next "," or "\0"
	token = strtok(cmd, delim);
    if (token == NULL) {
        return;
    }

	if (sscanf(token, "%u", &I2C_Address) != 1) {
        return;
    }

    if (I2C_Address > 127) {
        return;
    }     

    Wire.beginTransmission((uint8_t)I2C_Address);
    token=strtok(NULL, delim); 	// get next token
    while(token != NULL)
    {
        uint8_t data;
        bool isValid = false;
        switch(token[0])
        {
            case 'x':   // Hex Character
                unsigned int hex;
	            if (sscanf(token, "%x", &hex) == 1)
                {
                    isValid = true;
                    data = (uint8_t)hex;
                }
            break;
            case '"':   // String
                for (unsigned int ui = 1; ui < strlen(token); ui++)
                {
                    data = (uint8_t)token[ui];
                    Wire.write(data);
                }
            break;
            case '\'':  // Single Character
                char ch;
	            if (sscanf(token, "%c", &ch) == 1)
                {
                    isValid = true;
                    data = (uint8_t)ch;
                }                
            break;
            default:
                int num;
	            if (sscanf(token, "%d", &num) == 1)
                {
                    isValid = true;
                    data = (uint8_t)num;
                }                   
            break;
        }
        if (isValid) 
        {
            Wire.write(data);
        }
        token=strtok(NULL, delim); 	// get next token
    }
    Wire.endTransmission();
}
#endif