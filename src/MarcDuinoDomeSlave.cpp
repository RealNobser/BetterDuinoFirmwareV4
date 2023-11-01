
#include"MarcDuinoDomeSlave.h"

MarcDuinoDomeSlave::MarcDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11) :
    MarcDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11),
    Serial_Magic(Serial_Magic),
    Serial_Teeces(Serial_Teeces)
{
    Serial_Magic.begin(SERIAL_MAGIC_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Magic);

    Serial_Teeces.begin(SERIAL_TEECES_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Teeces);    
}

void MarcDuinoDomeSlave::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    #ifdef DEBUG_MSG
    Serial_Magic.println(F("To Magic"));
    Serial_Teeces.println(F("To Teeces"));
    #endif    
}

void MarcDuinoDomeSlave::run()
{
    MarcDuinoBase::run();
}

void MarcDuinoDomeSlave::checkEEPROM()
{
    
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
    #ifdef DEBUG_MSG
    Serial.printf(F("Command(Salve): %s\r\n"), command);
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
    #ifdef DEBUG_MSG
    Serial.printf(F("HoloCommand(Slave): %s\r\n"), command);
    #endif
}

void MarcDuinoDomeSlave::processDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("DisplayCommand(Slave): %s\r\n"), command);
    #endif
}

void MarcDuinoDomeSlave::processAltDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltDisplayCommand(Slave): %s\r\n"), command);
    #endif
}

void MarcDuinoDomeSlave::processExpansionCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("ExpansionCommand(Slave): %s\r\n"), command);
    #endif
}
