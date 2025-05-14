
#include "MDuinoDomeSlave.h"

MDuinoDomeSlave::MDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    MDuinoDome(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11),
    Serial_Magic(Serial_Magic),
    Serial_Teeces(Serial_Teeces)
{
    Serial_Magic.begin(SERIAL_MAGIC_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Magic);

    Serial_Teeces.begin(SERIAL_TEECES_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Teeces);
    
    #ifdef SEPARATE_DOMELIFT
    Serial_Lift.begin(SERIAL_LIFT_BAUD);
    while(!Serial_Lift);
    #endif

    for(byte i=0; i <= MaxPanel; ++i)
    {
        Panels[i] = nullptr;
    }   

    for(byte i=0; i <= MaxHolo; ++i)
    {
        Holos[i] = nullptr;
    }   
}

void MDuinoDomeSlave::init()
{
    MDuinoDome::init();

    // 3 Holos
    Holos[1] = new Holo(P_FL, Storage.getHoloLightHighActive(1), Servo1, P_HPF_H, Servo2, P_HPF_V, Storage.getHoloNeoPixel(1), Storage.getHoloLEDs(1));    // Front
    Holos[2] = new Holo(P_RL, Storage.getHoloLightHighActive(2), Servo3, P_HPR_H, Servo4, P_HPR_V, Storage.getHoloNeoPixel(2), Storage.getHoloLEDs(2));    // Rear
    Holos[3] = new Holo(P_TL, Storage.getHoloLightHighActive(3), Servo5, P_HPT_H, Servo6, P_HPT_V, Storage.getHoloNeoPixel(3), Storage.getHoloLEDs(3));    // Top

    // 2 Panels
    Panels[12] = new Panel(Servo10, P_SERVO_12);
    Panels[13] = new Panel(Servo11, P_SERVO_13);

    adjustPanelEndPositions(Panels, MinPanel, MaxPanel);

    Sequencer.setPanels(Panels, MaxPanel+1);
    Sequencer.setPanelRange(MinPanel, MaxPanel);

    adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
}

void MDuinoDomeSlave::run()
{
    MDuinoDome::run();

    // Holos
    for (byte i=MinHolo; i <= MaxHolo; i++)
        Holos[i]->run();

    // Servos. TODO: Double implementation, check BaseClass Idea for Dome Board
    // check https://stackoverflow.com/questions/13340074/c-static-const-members-overriding for const static members MinPanel/MaxPanel
    if (ServoBuzzIntervall != 0)
    {
        if ((millis() - ServoBuzzMillis) > ServoBuzzIntervall)
        {
            for (byte i = MinPanel; i <= MaxPanel; i++)
            {
                if (!Panels[i]->isMoving())
                    Panels[i]->detach();
            }
            ServoBuzzMillis = millis();
        }
    } 

    // Holos Timer 
    // (moved to Holo-Run-Code)

    // Magic Panel Timer
    if (MagicPanelInterval != 0)
    {
        if ((millis() - MagicPanelMillis) > MagicPanelInterval)
        {
            MagicPanelCtrl(0); // 0 = off
        }                               
    }

    // TODO: Holo Servos Buzz?
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
 *  '#' Setup commands used to configure various settings
 */
  
void MDuinoDomeSlave::parseCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("Command(Slave): %s\r\n"), command);
    #endif

    switch (command[0])
    {
    case ':':
        // Sequences for Servo 12/13 must be played!
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
        // Ignore Sound Commands
        break;
    case '!':
        processAltDisplayCommand(command);
        break;
    case '%':
        processExpansionCommand(command);
        break;
    #ifdef INCLUDE_CLASSIC_I2C_SUPPORT
    case '&':
        processI2CCommand(command);
        break;
    #endif
    case '#':
        processSetupCommand(command);
        break;    
    default:
        break;
    }
    delay(COMMAND_DELAY);
}

void MDuinoDomeSlave::processPanelCommand(const char* command)
{
    // Sequence and Panel Commands will be processed
    char cmd[3];

    unsigned int param_num = 0;
    unsigned int param_num_ext = 0;

    memset(cmd, 0x00, 3);

    #ifdef DEBUG_MSG
    Serial.printf(F("PanelCommand(Slave): %s\r\n"), command);
    #endif

    if (!separateCommand(command, cmd, param_num, param_num_ext))
        return;

    if (strcmp(cmd, "MV")==0)
    {
        if (param_num > MaxPanel)
            return;

        Panels[param_num]->moveMS((uint16_t)param_num_ext, 0, true);
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
            
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->open();
        }
        /*
        else if (param_num == 14)    // Open Top Panels
        {
        }
        else if (param_num == 15)    // Open Bottom Panels
        {
        }
        */

    }
    else if (strcmp(cmd, "CL")==0)  // Close Panel
    {
        if (param_num == 0)         // close all
        {
            for(byte i=MinPanel; i<=MaxPanel; i++)
                Panels[i]->close();            
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->close();
        }
        /*
        else if (param_num == 14)    // Close Top Panels
        {
        }
        else if (param_num == 15)    // Close Bottom Panels
        {
        }
        */
    }
    else if (strcmp(cmd, "LK")==0)  // Lock Panel
    {
        if (param_num == 0)         // lock all
        {
            for(byte i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->lock(true);            
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->lock(true);
        }
        /*
        else if (param_num == 14)    // Lock Top Panels
        {
        }
        else if (param_num == 15)    // Lock Bottom Panels
        {
        }
        */       
    }
    else if (strcmp(cmd, "UL")==0)  // Unlock Panel
    {
        if (param_num == 0)         // Unlock all
        {
            for(byte i=MinPanel; i<= MaxPanel; i++)
                Panels[i]->lock(false);
        }
        else if ((param_num >= MinPanel) && (param_num <= MaxPanel))
        {
            Panels[param_num]->lock(false);
        }
        /*
        else if (param_num == 14)    // Unlock Top Panels
        {
        }
        else if (param_num == 15)    // Unlock Bottom Panels
        {
        }
        */
    }    
    else if (strcmp(cmd, "ST")==0)
    {
        if (param_num == 0)    // Alle panels
        {
            for(byte i=MinPanel; i <= MaxPanel; i++)
                Panels[i]->detach();
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
}

void MDuinoDomeSlave::processHoloCommand(const char* command)
{
    char cmd[3];
    unsigned int param_num = 0;
    unsigned int param_num_ext = 0;

    memset(cmd, 0x00, 3);
    
    #ifdef DEBUG_MSG
    Serial.printf(F("HoloCommand(Slave): %s\r\n"), command);
    #endif

    #ifdef INCLUDE_HOLO_RGB
    if (strlen(command) == 17)  // RGB LED *ON command
    {
        char param[3];
        char red[4];
        char green[4];
        char blue[4];
        char bright[4];

        unsigned int red_num = 0;
        unsigned int green_num = 0;
        unsigned int blue_num = 0;
        unsigned int bright_num = 0;

        memset(param,   0x00, 3);
        memset(red,     0x00, 4);
        memset(green,   0x00, 4);
        memset(blue,    0x00, 4);
        memset(bright,  0x00, 4);

        memcpy(cmd,     command+1, 2);
        memcpy(param,   command+3, 2);
        memcpy(red,     command+5, 3);
        memcpy(green,   command+8, 3);
        memcpy(blue,    command+11, 3);
        memcpy(bright,  command+14, 3);

        param_num   = atoi(param);
        red_num     = atoi(red);
        green_num   = atoi(green);
        blue_num    = atoi(blue);
        bright_num  = atoi(bright);

        if (strcmp(cmd, "CO")==0)  // Holo Lights Color
        {
            Holos[param_num]->setColor(red_num, green_num, blue_num, bright_num);
        }
        else if (strcmp(cmd, "ON")==0)  // Holo Lights on
        {
            HolosOn(param_num, red_num, green_num, blue_num, bright_num);
        }
        else if (strcmp(cmd, "H0")==0)  // Holos On for xx seconds
        {
            for (byte i=MinHolo; i <= MaxHolo; i++)
            {
                if (param_num > 0)
                    Holos[i]->on(red_num, green_num, blue_num, bright_num, param_num);
                else
                    Holos[i]->off();
            }
        }    
        else if (strcmp(cmd, "H1")==0)  // Holo1 On for xx seconds
        {
            if (param_num > 0)
                Holos[1]->on(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[1]->off();
        }    
        else if (strcmp(cmd, "H2")==0)  // Holo2 On for xx seconds
        {
            if (param_num > 0)
                Holos[2]->on(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[2]->off();
        }    
        else if (strcmp(cmd, "H3")==0)  // Holo3 On for xx seconds
        {
            if (param_num > 0)
                Holos[3]->on(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[3]->off();
        }    
        else if (strcmp(cmd, "F0")==0)  // Holos Flicker for xx seconds
        {        
            for (byte i=MinHolo; i <= MaxHolo; i++)
            {
                if (param_num > 0)
                    Holos[i]->flickerOn(red_num, green_num, blue_num, bright_num, param_num);
                else
                    Holos[i]->off();
            }
        }    
        else if (strcmp(cmd, "F1")==0)  // Holo1 Flicker for xx seconds
        {
            if (param_num > 0)
                Holos[1]->flickerOn(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[1]->off();
        }    
        else if (strcmp(cmd, "F2")==0)  // Holo2 Flicker for xx seconds
        {
            if (param_num > 0)
                Holos[2]->flickerOn(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[2]->off();
        }    
        else if (strcmp(cmd, "F3")==0)  // Holo3 Flicker for xx seconds
        {
            if (param_num > 0)
                Holos[3]->flickerOn(red_num, green_num, blue_num, bright_num, param_num);
            else
                Holos[3]->off();
        }
        return;         
    }
    #endif

    if (!separateCommand(command, cmd, param_num, param_num_ext))
        return;

    if (strcmp(cmd, "RD")==0)       // Random Holo Movement
    {
        HoloMovementCtrl(param_num, true);
    }
    else if (strcmp(cmd, "ON")==0)  // Holo Lights on
    {
        HolosOn(param_num);
    }    
    else if (strcmp(cmd, "OF")==0)  // Holo Lights off
    {
        HolosOff(param_num);
    }
    #ifdef INCLUDE_HOLO_TEST    
    else if (strcmp(cmd, "TE")==0)  // Holo Movement Test
    {
        adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
        Holos[param_num]->testTrigger();
    }
    #endif
    else if (strcmp(cmd, "CH")==0)  // Center Holo
    {
        adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
        if(param_num == 0)
        {
            for (byte i=MinHolo; i <= MaxHolo; i++)
                HoloCenter(i);
        }
        else
            HoloCenter(param_num);
    }    
   else if (strcmp(cmd, "ST")==0)  // Stop movement, lights off
    {
        HoloMovementCtrl(param_num, false);
        HolosOff(param_num);
    }    
    else if (strcmp(cmd, "HD")==0)  // Stop movement, no light change
    {
        HoloMovementCtrl(param_num, false);
    }    
    else if (strcmp(cmd, "MO")==0)  // Magic Panel On
    {
        MagicPanelCtrl(param_num);
    }    
    else if (strcmp(cmd, "MF")==0)  // Magic Panel Flicker
    {
        MagicPanelInterval = 0;

        if(param_num == 0)
            Serial_Magic.print(F("T0\r"));
        else
        {
            MagicPanelInterval = param_num * 1000;
            MagicPanelMillis = millis();
            Serial_Magic.print(F("T42\r"));
        }
    }    
    else if (strcmp(cmd, "H0")==0)  // Holos On for xx seconds
    {
        for (byte i=MinHolo; i <= MaxHolo; i++)
            HoloOnOffCtrl(i, param_num);
    }    
    else if (strcmp(cmd, "H1")==0)  // Holo1 On for xx seconds
    {
        HoloOnOffCtrl(1, param_num);
    }    
    else if (strcmp(cmd, "H2")==0)  // Holo2 On for xx seconds
    {
        HoloOnOffCtrl(2, param_num);
    }    
    else if (strcmp(cmd, "H3")==0)  // Holo3 On for xx seconds
    {
        HoloOnOffCtrl(3, param_num);
    }    
    else if (strcmp(cmd, "F0")==0)  // Holos Flicker for xx seconds
    {        
        for (byte i=MinHolo; i <= MaxHolo; i++)
            HoloFlickerCtrl(i, param_num);
    }    
    else if (strcmp(cmd, "F1")==0)  // Holo1 Flicker for xx seconds
    {
        HoloFlickerCtrl(1, param_num);
    }    
    else if (strcmp(cmd, "F2")==0)  // Holo2 Flicker for xx seconds
    {
        HoloFlickerCtrl(2, param_num);
    }    
    else if (strcmp(cmd, "F3")==0)  // Holo3 Flicker for xx seconds
    {
        HoloFlickerCtrl(3, param_num);
    }    
    else if (strcmp(cmd, "EO")==0)  // AUX1 on
    {
        AUX1(param_num);
    }    
}

void MDuinoDomeSlave::processDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("DisplayCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Teeces.printf(F("%s\r"), command+1);    // stripped
}

void MDuinoDomeSlave::processAltDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltDisplayCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Teeces.printf(F("%s\r"), command+1);    // stripped
}

void MDuinoDomeSlave::processExpansionCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("ExpansionCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Magic.printf(F("%s\r"), command+1);    // stripped
}


void MDuinoDomeSlave::HolosOn(const byte HoloNr)
{
    if (HoloNr > (MAX_MDUINOHOLOS + 1)) // Parameter = 4
        return;

    if((HoloNr == 0) || (HoloNr == 4))  // All Holos
    {
        for(byte i=1; i<= MAX_MDUINOHOLOS; i++)
            Holos[i]->on();
    }
    else
        Holos[HoloNr]->on();
}

#ifdef INCLUDE_HOLO_RGB
void MDuinoDomeSlave::HolosOn(const byte HoloNr, const byte red, const byte green, const byte blue, const byte bright)
{
    if (HoloNr > (MAX_MDUINOHOLOS + 1)) // Parameter = 4
        return;

    if((HoloNr == 0) || (HoloNr == 4))  // All Holos
    {
        for(byte i=1; i<= MAX_MDUINOHOLOS; i++)
            Holos[i]->on(red, green, blue, bright);
    }
    else
        Holos[HoloNr]->on(red, green, blue, bright);
}
#endif

void MDuinoDomeSlave::HolosOff(const byte HoloNr)
{
    if (HoloNr > (MAX_MDUINOHOLOS + 1))    // Parameter = 4
        return;

    if((HoloNr == 0) || (HoloNr == 4))  // All Holos
    {
        for(byte i=1; i<= MAX_MDUINOHOLOS; i++)
            Holos[i]->off();
    }
    else
        Holos[HoloNr]->off();
}

void MDuinoDomeSlave::HoloCenter(const byte HoloNr)
{
    word HMin, HMax, VMin, VMax, HCenter, VCenter = 0;

    if (HoloNr > MAX_MDUINOHOLOS)
        return;
    
    Storage.getHoloPositions(HoloNr, HMin, HMax, VMin, VMax);

    HCenter = abs(HMax-HMin)/2+HMin;
    VCenter = abs(VMax-VMin)/2+VMin;

    Holos[HoloNr]->move(HCenter, VCenter);
}

void MDuinoDomeSlave::MagicPanelCtrl(const byte param)
{
    MagicPanelInterval = 0;

    if(param == 0)
        Serial_Magic.print(F("T0\r"));   // OFF
    else if (param == 99)
        Serial_Magic.print(F("T1\r"));   // ON
    else
    {
        MagicPanelInterval = param * 1000;
        MagicPanelMillis = millis();
        Serial_Magic.print(F("T1\r"));   // Timer
    }
}

void MDuinoDomeSlave::HoloMovementCtrl(const byte param, const bool moving)
{
    if ((param == 0) || (param >3))
    {
        for (byte i=MinHolo; i <= MaxHolo; i++)
            Holos[i]->randomMove(moving);
    }
    else
        Holos[param]->randomMove(moving);
}

void MDuinoDomeSlave::HoloOnOffCtrl(const byte holo, const unsigned int param)
{
    if (param > 0)
        Holos[holo]->on(param);
    else
        Holos[holo]->off();
}

void MDuinoDomeSlave::HoloFlickerCtrl(const byte holo, const unsigned int param)
{
    if (param > 0)
        Holos[holo]->flickerOn(param);
    else
        Holos[holo]->off();
}
