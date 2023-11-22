
#include"MarcDuinoDomeSlave.h"
#include"PanelSequences.h"

MarcDuinoDomeSlave::MarcDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13) :
    MarcDuinoDome(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13),
    Serial_Magic(Serial_Magic),
    Serial_Teeces(Serial_Teeces)
{
    Serial_Magic.begin(SERIAL_MAGIC_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Magic);

    Serial_Teeces.begin(SERIAL_TEECES_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
    while(!Serial_Teeces);

    for(unsigned int i=0; i <= MaxHolo; ++i)
    {
        Holos[i] = nullptr;
    }   

    for(unsigned int i=0; i <= MaxPanel; ++i)
    {
        Panels[i] = nullptr;
    }   
}

void MarcDuinoDomeSlave::init()
{
    MarcDuinoDome::init();

    // 3 Holos
    Holos[1] = new Holo(P_FL, Storage.getHoloLightHighActive(1), Servo1, P_HPF_H, Servo2, P_HPF_V);    // Front
    Holos[2] = new Holo(P_RL, Storage.getHoloLightHighActive(2), Servo3, P_HPR_H, Servo4, P_HPR_V);    // Rear
    Holos[3] = new Holo(P_TL, Storage.getHoloLightHighActive(3), Servo5, P_HPT_H, Servo6, P_HPT_V);    // Top

    // 2 Panels
    Panels[12] = new Panel(Servo11, P_SERVO_12);
    Panels[13] = new Panel(Servo11, P_SERVO_13);

    adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
    adjustPanelEndPositions(Panels, MinPanel, MaxPanel);

    Sequencer.setPanels(Panels, MaxPanel+1);
    Sequencer.setPanelRange(MinPanel, MaxPanel);

    parseCommand(":SE00");    // Close Panels
}

void MarcDuinoDomeSlave::run()
{
    MarcDuinoDome::run();

    // Holos
    for (unsigned int i=MinHolo; i <= MaxHolo; i++)
        Holos[i]->run();

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
        // Ignore Sound Commands
        break;
    case '!':
        processAltDisplayCommand(command);
        break;
    case '%':
        processExpansionCommand(command);
        break;
    case '&':
        processI2CCommand(command);
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
    char cmd[3];
    unsigned int param_num = 0;

    memset(cmd, 0x00, 3);
    
    #ifdef DEBUG_MSG
    Serial.printf(F("HoloCommand(Slave): %s\r\n"), command);
    #endif

    if (!separateCommand(command, cmd, param_num))
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
    else if (strcmp(cmd, "RC")==0)  // Holo vertical movement under RC
    {
    }    
    else if (strcmp(cmd, "TE")==0)  // Holo Movement Test
    {
        adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
        Holos[param_num]->testTrigger();
    }    
    else if (strcmp(cmd, "CH")==0)  // Center Holo
    {
        adjustHoloEndPositions(Holos, MinHolo, MaxHolo);
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
        for (unsigned int i=MinHolo; i <= MaxHolo; i++)
        {
            Holos[i]->on(param_num);
        }
    }    
    else if (strcmp(cmd, "H1")==0)  // Holo1 On for xx seconds
    {
        Holos[1]->on(param_num);
    }    
    else if (strcmp(cmd, "H2")==0)  // Holo2 On for xx seconds
    {
        Holos[2]->on(param_num);
    }    
    else if (strcmp(cmd, "H3")==0)  // Holo3 On for xx seconds
    {
        Holos[3]->on(param_num);
    }    
    else if (strcmp(cmd, "F0")==0)  // Holos Flicker for xx seconds
    {        
        for (unsigned int i=MinHolo; i <= MaxHolo; i++)
        {
            Holos[i]->flickerOn(param_num);
        }
    }    
    else if (strcmp(cmd, "F1")==0)  // Holo1 Flicker for xx seconds
    {
        Holos[1]->flickerOn(param_num);
    }    
    else if (strcmp(cmd, "F2")==0)  // Holo2 Flicker for xx seconds
    {
        Holos[2]->flickerOn(param_num);
    }    
    else if (strcmp(cmd, "F3")==0)  // Holo3 Flicker for xx seconds
    {
        Holos[3]->flickerOn(param_num);
    }    
    else if (strcmp(cmd, "EO")==0)  // AUX1 on
    {
        AUX1(param_num);
    }    
}

void MarcDuinoDomeSlave::processDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("DisplayCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Teeces.printf(F("%s\r"), command+1);    // stripped
}

void MarcDuinoDomeSlave::processAltDisplayCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("AltDisplayCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Teeces.printf(F("%s\r"), command+1);    // stripped
}

void MarcDuinoDomeSlave::processExpansionCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("ExpansionCommand(Slave): %s\r\n"), command);
    #endif
    Serial_Magic.printf(F("%s\r"), command+1);    // stripped
}

void MarcDuinoDomeSlave::processI2CCommand(const char* command)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("I2CCommand(Master): %s\r\n"), command);
    #endif
}

void MarcDuinoDomeSlave::playSequenceAddons(const unsigned int SeqNr)
{
    #ifdef DEBUG_MSG
    Serial.printf(F("PlaySequenceAddons(Slave): %i\r\n"), SeqNr);
    #endif
}


void MarcDuinoDomeSlave::HolosOn(const byte HoloNr)
{
    if (HoloNr > (MAX_MARCDUINOHOLOS + 1)) // Parameter = 4
        return;

    if((HoloNr == 0) || (HoloNr == 4))  // All Holos
    {
        for(unsigned int i=1; i<= MAX_MARCDUINOHOLOS; i++)
            Holos[i]->on();
    }
    else
        Holos[HoloNr]->on();
}

void MarcDuinoDomeSlave::HolosOff(const byte HoloNr)
{
    if (HoloNr > (MAX_MARCDUINOHOLOS + 1))    // Parameter = 4
        return;

    if((HoloNr == 0) || (HoloNr == 4))  // All Holos
    {
        for(unsigned int i=1; i<= MAX_MARCDUINOHOLOS; i++)
            Holos[i]->off();
    }
    else
        Holos[HoloNr]->off();
}

void MarcDuinoDomeSlave::HoloCenter(const byte HoloNr)
{
    word HMin, HMax, VMin, VMax, HCenter, VCenter = 0;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;
    
    Storage.getHoloPositions(HoloNr, HMin, HMax, VMin, VMax);

    HCenter = abs(HMax-HMin)/2+HMin;
    VCenter = abs(VMax-VMin)/2+VMin;

    Holos[HoloNr]->move(HCenter, VCenter);
}

void MarcDuinoDomeSlave::MagicPanelCtrl(const unsigned int param_num)
{
    MagicPanelInterval = 0;

    if(param_num == 0)
        Serial_Magic.print(F("T0\r"));   // OFF
    else if (param_num == 99)
        Serial_Magic.print(F("T1\r"));   // ON
    else
    {
        MagicPanelInterval = param_num * 1000;
        MagicPanelMillis = millis();
        Serial_Magic.print(F("T1\r"));   // Timer
    }
}

void MarcDuinoDomeSlave::HoloMovementCtrl(const unsigned int param_num, const bool moving)
{
    if ((param_num == 0) || (param_num >3))
    {
        for (unsigned int i=MinHolo; i <= MaxHolo; i++)
            Holos[i]->randomMove(moving);
    }
    else
        Holos[param_num]->randomMove(moving);
}