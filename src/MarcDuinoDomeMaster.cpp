
#include"MarcDuinoDomeMaster.h"

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
}

void MarcDuinoDomeMaster::init()
{
    MarcDuinoBase::init();

    // Soft Serials
    #ifdef DEBUG
    Serial_Slave.println("To Slave");
    Serial_MP3.println("To MP3");
    #endif

    // TODO: Get Max/Min // Open Close from EEPROM!
    Servo1.attach(P_SERVO_01);
    Panels[1] = new Panel(Servo1, 90,180);

    Servo2.attach(P_SERVO_02);
    Panels[2] = new Panel(Servo2, 90,180);

    Servo3.attach(P_SERVO_03);
    Panels[3] = new Panel(Servo3, 90,180);

    Servo4.attach(P_SERVO_04);
    Panels[4] = new Panel(Servo4, 90,180);

    Servo5.attach(P_SERVO_05);
    Panels[5] = new Panel(Servo5, 90,180);

    Servo6.attach(P_SERVO_06);
    Panels[6] = new Panel(Servo6, 90,180);

    Servo7.attach(P_SERVO_07);
    Panels[7] = new Panel(Servo7, 90,180);

    Servo8.attach(P_SERVO_08);
    Panels[8] = new Panel(Servo8, 90,180);

    Servo9.attach(P_SERVO_09);
    Panels[9] = new Panel(Servo9, 90,180);

    Servo10.attach(P_SERVO_10);
    Panels[10] = new Panel(Servo10, 90,180);

    Servo11.attach(P_SERVO_11);
    Panels[11] = new Panel(Servo11, 90,180);

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

    if (strcmp(cmd, "SE")==0)
    {

    } 
    else if (strcmp(cmd, "OP")==0)
    {
        #ifdef DEBUG
        Serial.print("Open Panel ");
        Serial.println(param_num);
        #endif        

        if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->open();
        }
    }
    else if (strcmp(cmd, "CL")==0)
    {
        #ifdef DEBUG
        Serial.print("Open Panel ");
        Serial.println(param_num);
        #endif        

        if ((param_num > 0) && (param_num <=MAX_PANELS))
        {
            Panels[param_num]->close();
        }
    }
    else if (strcmp(cmd, "RC")==0)
    {

    }
    else if (strcmp(cmd, "ST")==0)
    {

    }
    else if (strcmp(cmd, "HD")==0)
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
    Serial_Slave.print('\r');
}

void MarcDuinoDomeMaster::processDisplayCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("DisplayCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_Slave.print(command);
    Serial_Slave.print('\r');
}

void MarcDuinoDomeMaster::processSoundCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("SoundCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_MP3.print(command);
    Serial_MP3.print('\r');
}

void MarcDuinoDomeMaster::processAltSoundCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("AltSoundCommand(Master): ");
    Serial.println((char*)command);
    #endif

    Serial_MP3.print(command+1);
    Serial_MP3.print('\r');
}

void MarcDuinoDomeMaster::processAltHoloCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("AltHoloCommand(Master): ");
    Serial.println((char*)command);
    #endif
    Serial_Slave.print(command);
    Serial_Slave.print('\r');
}
