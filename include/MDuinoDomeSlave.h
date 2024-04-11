#ifndef __MARCDUINODOMESLAVE_H__
#define __MARCDUINODOMESLAVE_H__

#include "MDuinoDome.h"
#include "Holo.h"
#include "Panel.h"

#include <SendOnlySoftwareSerial.h>

class MDuinoDomeSlave : public MDuinoDome
{
    public:
        MDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);
            
        virtual void init() override;
        virtual void run() override;

        virtual void parseCommand(const char* command) override;

    protected:
        SendOnlySoftwareSerial& Serial_Magic;
        SendOnlySoftwareSerial& Serial_Teeces;
        SERIAL_LIFT_TYPE& Serial_Lift;

        unsigned long MagicPanelMillis  = 0;
        unsigned long MagicPanelInterval= 0;

        static const byte MinPanel = 12;   // Slave Board has 2 Panel Connectors names Panel 12 and Panel 13
        static const byte MaxPanel = 13;   // Slave Board has 2 Panel Connectors names Panel 12 and Panel 13
        static const byte MinHolo  = 1;    // Slave Board uses 3 Holos with 2 Servos and one Light GPIO each
        static const byte MaxHolo  = 3;    // Slave Board uses 3 Holos with 2 Servos and one Light GPIO each

        Panel* Panels[MaxPanel + 1];    // +1 for index 0 dummy
        Holo* Holos[MaxHolo + 1];       // +1 for index 0 dummy

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processAltDisplayCommand(const char* command);
        void processExpansionCommand(const char* command);

        void HolosOn(const byte HoloNr);
        void HolosOff(const byte HoloNr);

        #ifdef INCLUDE_HOLO_RGB
        void HolosOn(const byte HoloNr, const byte red, const byte green, const byte blue, const byte bright);
        #endif

        void HoloCenter(const byte HoloNr);

        void MagicPanelCtrl(const byte param);
        void HoloMovementCtrl(const byte param, const bool moving);
};

#endif // __MARCDUINODOMESLAVE_H__
