
#include"MarcDuinoDomeSlave.h"
#include"PanelSequences.h"

MarcDuinoDomeSlave::MarcDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    MarcDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13),
    Serial_Magic(Serial_Magic),
    Serial_Teeces(Serial_Teeces)
{
    Serial_Magic.begin(SERIAL_MAGIC_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Magic);

    Serial_Teeces.begin(SERIAL_TEECES_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Teeces);

    for(unsigned int i=0; i <= MaxPanel; ++i)
    {
        Panels[i] = nullptr;
    }    
}

void MarcDuinoDomeSlave::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    #ifdef DEBUG_MSG
    Serial_Magic.println(F("To Magic"));
    Serial_Teeces.println(F("To Teeces"));
    #endif

    // TODO: Get Max/Min // Open Close from EEPROM!
    Panels[12] = new Panel(Servo10, P_SERVO_12, 0,180);
    Panels[13] = new Panel(Servo11, P_SERVO_13, 0,180);

    Sequencer.setPanels(Panels, MaxPanel+1);
    Sequencer.setPanelRange(MinPanel, MaxPanel);

    Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
    Sequencer.startSequence();    
}

void MarcDuinoDomeSlave::run()
{
    MarcDuinoBase::run();
}

/*
 *  Valid start characters recognized in main()
 *  ':' panel command, ignored (see parse_panel_command). This should not be received by this slaved module anyhow, NEW: Sequences and Panel Commands for Servo 12/13 must be played!
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
        // NEW: Sequences for Servo 12/13 must be played!    
        processPanelCommand(command);
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

void MarcDuinoDomeSlave::processPanelCommand(const char* command)
{
    // Sequence and Panel Commands will be processed
    char cmd[3];
    unsigned int param_num = 0;

    memset(cmd, 0x00, 3);

    #ifdef DEBUG_MSG
    Serial.printf(F("PanelCommand(Slave): %s\r\n"), command);
    #endif

    if (!separateCommand(command, cmd, param_num))
        return;

    if (strcmp(cmd, "SE")==0)       // Start Sequence
    {
        playSequence(param_num);
    } 
    else if (strcmp(cmd, "OP")==0)  // Open Panel
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Open Panel %i\r\n"), param_num);
        #endif        

        if (param_num == 0)         // open all
        {
            for(unsigned int i=MinPanel; i<=MaxPanel; i++)
                Panels[i]->open();
            
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->open();
        }
        else if (param_num == 14)    // Open Top Panels
        {
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
        }

    }
    else if (strcmp(cmd, "CL")==0)  // Close Panel
    {
        #ifdef DEBUG_MSG
        Serial.printf(F("Close Panel %i\r\n"), param_num);
        #endif        

        if (param_num == 0)         // close all
        {
            for(unsigned int i=MinPanel; i<=MaxPanel; i++)
                Panels[i]->close();            
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->close();
        }
        else if (param_num == 14)    // Close Top Panels
        {
        }
        else if (param_num == 15)    // Close Bottom Panels
        {
        }
    }
    else if (strcmp(cmd, "ST")==0)
    {
        if (param_num == 0)    // Alle panels
        {
            for(unsigned int i=MinPanel; i <= MaxPanel; i++)
                Panels[i]->detach();
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->detach();
        }
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

void MarcDuinoDomeSlave::playSequence(const unsigned int SeqNr)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("PlaySequence(Slave): %i\r\n"), SeqNr);
    #endif

    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
    switch (SeqNr)
    {
        case 0: // CLOSE ALL PANELS    
        break;
        default:
        break;
    }
}