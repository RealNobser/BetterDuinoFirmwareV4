#include "MarcDuinos.h"
#include <Wire.h>

/////////////////////////

MarcDuinoBase::MarcDuinoBase()
{

}

void MarcDuinoBase::init()
{
    // I2C
    Wire.begin();

    // HeartBeat-LED
    pinMode(P_LED2, OUTPUT);
    digitalWrite(P_LED2, HeartBeatStatus);

    HeartBeatMillis = millis();

    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
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
    if ((millis() - HeartBeatMillis) > HEARTBEAT_MILLIS)
    {
        toggleHeartBeat();
        HeartBeatMillis = millis();
    }
}

void MarcDuinoBase::toggleHeartBeat()
{
    #ifdef DEBUG
    // Serial.print(".");
    #endif

    if (HeartBeatStatus == LOW)
      HeartBeatStatus = HIGH;
    else
      HeartBeatStatus = LOW;

    digitalWrite(P_LED2, HeartBeatStatus);
}

void MarcDuinoBase::processSetupCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("SetupCommand(Base): ");
    Serial.println((char*)command);
    #endif
}

/////////////////////////

MarcDuinoDomeMaster::MarcDuinoDomeMaster()
{

}

void MarcDuinoDomeMaster::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    Serial_Slave.begin(SERIAL_SLAVE_BAUD);
    Serial_MP3.begin(SERIAL_MP3_BAUD);
    
    #ifdef DEBUG
    Serial_Slave.println("To Slave");
    Serial_MP3.println("To MP3");
    #endif
}

void MarcDuinoDomeMaster::run()
{
    MarcDuinoBase::run();
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
    #ifdef DEBUG
    Serial.print("Command(Master): ");
    Serial.println((char*)command);
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
    char param[3];

    #ifdef DEBUG
    Serial.print("PanelCommand(Master): ");
    Serial.println((char*)command);
    #endif

    memset(cmd, 0x00, 3);
    memset(param, 0x00, 3);

    if (strlen(command) != 5)
    {
        Serial.print("Invalid Size: ");
        Serial.println(strlen(command));
        return;
    }
    
    memcpy(cmd, command+1, 2);
    memcpy(param, command+3, 2);

    #ifdef DEBUG
    Serial.print("Cmd:   ");
    Serial.println(cmd);
    Serial.print("Param: ");
    Serial.println(param);
    #endif

    int param_num = atoi(param);

    if (strcmp(cmd, "SE"))
    {

    } 
    else if (strcmp(cmd, "OP"))
    {
        
    }
    else if (strcmp(cmd, "CL"))
    {

    }
    else if (strcmp(cmd, "RC"))
    {

    }
    else if (strcmp(cmd, "ST"))
    {

    }
    else if (strcmp(cmd, "HD"))
    {

    }

}

void MarcDuinoDomeMaster::processHoloCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("HoloCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_Slave.print(command);
}

void MarcDuinoDomeMaster::processDisplayCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("DisplayCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_Slave.print(command);
}

void MarcDuinoDomeMaster::processSoundCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("SoundCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_MP3.print(command);
}

void MarcDuinoDomeMaster::processAltSoundCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("AltSoundCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_MP3.print(command+1);
}

void MarcDuinoDomeMaster::processAltHoloCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("AltHoloCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_Slave.print(command);
}

/////////////////////////

MarcDuinoDomeSlave::MarcDuinoDomeSlave()
{

}

void MarcDuinoDomeSlave::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    Serial_Teeces.begin(SERIAL_TEECES_BAUD);
    Serial_Magic.begin(SERIAL_MAGIC_BAUD);

    #ifdef DEBUG
    Serial_Teeces.println("To Teeces");
    Serial_Magic.println("To Magic");
    #endif
}

void MarcDuinoDomeSlave::run()
{
    MarcDuinoBase::run();
}

/*
 *  Valid start characters recognized in main()
 *  ':' panel command, ignored (see parse_panel_command). This should not be received by this slaved module anyhow
 *  '$' sound command, ignored (see parse_sound_command). This should not be received by this slaved module anyhow
 *  '@' display command, forwarded to JEDI controller on suart1 after stripping the '@' control character
 *  '*' hp command, acted upon here, see below
 *  '!' Alt1 alternate display command, passed to suart after stripping
 *  '%' Alt2 expansion command, passed to suart2 after stripping
 *		The master HP board will forward these to us
 *  '#' MarcDuino Setup commands used to configure various settings on the MarcDuino
 */
  
void MarcDuinoDomeSlave::parseCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("Command(Salve): ");
    Serial.println((char*)command);
    #endif

    switch (command[0])
    {
    case ':':  
        // Ignore
        break;
    case '*':
        processHoloCommand(command);
        break;
    case '@':
        processDisplayCommand(command);
        break;
    case '$':
        // Ignore
        break;
    case '!':
        processAltDisplayCommand(command);
        break;
    case '%':
        processExpansionCommand(command);
        break;
    case '#':
        processSetupCommand(command);
        break;    
    default:
        break;
    }    
}

void MarcDuinoDomeSlave::processHoloCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("HoloCommand(Slave): ");
    Serial.println((char*)command);
    #endif
}

void MarcDuinoDomeSlave::processDisplayCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("DisplayCommand(Slave): ");
    Serial.println((char*)command);
    #endif
}

void MarcDuinoDomeSlave::processAltDisplayCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("AltDisplayCommand(Slave): ");
    Serial.println((char*)command);
    #endif
}

void MarcDuinoDomeSlave::processExpansionCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("ExpansionCommand(Slave): ");
    Serial.println((char*)command);
    #endif
}

/////////////////////////

MarcDuinoBody::MarcDuinoBody()
{

}

void MarcDuinoBody::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    Serial_Slave.begin(SERIAL_SLAVE_BAUD);
    Serial_MP3.begin(SERIAL_MP3_BAUD);

    #ifdef DEBUG
    Serial_Slave.println("To Slave");
    Serial_MP3.println("To MP3");
    #endif
}

void MarcDuinoBody::run()
{
    MarcDuinoBase::run();
}

void MarcDuinoBody::parseCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("Command(Body): ");
    Serial.println((char*)command);
    #endif

    switch (command[0])
    {
    case ':':
        break;
    case '*':
        break;
    case '@':
        break;
    case '$':
        break;
    case '!':
        break;
    case '%':
        break;
    case '#':
        break;    
    default:
        break;
    }        
}