#ifndef __MARCDUINODOMESLAVE_H__
#define __MARCDUINODOMESLAVE_H__

#include "MarcDuinoDome.h"
#include "Panel.h"
#include <SendOnlySoftwareSerial.h>

/** Commands implemented in v1.2
 *
 * 	Hardware Setup:
 * 	- 8 servo outputs
 * 		Holo 1 V on pins 1 (front, holo 1)
 * 		Holo 1 H on pins 2
 * 		Holo 2 V on pins 3 (rear, holo 2)
 * 		Holo 2 H on pins 4
 * 		Holo 3 V on pins 5 (top, holo 3)
 * 		Holo 3 H on pins 6
 * 		Panel 12 on pin 10 (Smallest front Panel)
 * 		Panel 13 on AUX2 (Top centre panel)
 * 	- 4 digital outputs
 * 		HP1 (front, holo 1) on PORT B Pin 2 (pins labeled SRV7)
 * 		HP2 (rear, holo 2)  on PORT B Pin 3 (pins labeled SRV8)
 * 		HP3 (top, holo 3)   on PORT B Pin 4 (pins labeled SRV9)
 * 	- two suarts (software uart) output
 * 		- suart connected to the JEDI Display light control system at 2400 bauds
 * 		- suart2 initialized at 9600 bauds, for future use (daisy-chain expansion?)
 * 	- one RC input
 * 	- one main hardware UART input
 *		- connected to the master panel controller suart output at 9600 bauds, to receive commands
 *		- output sends commands acknowledgments, (not physically connected to anything at present)
 *
 *  Valid start characters recognized in main()
 *  ':' panel command, ignored (see parse_panel_command). This should not be received by this slaved module anyhow
 *  '$' sound command, ignored (see parse_sound_command). This should not be received by this slaved module anyhow
 *  '@' display command, forwarded to JEDI controller on suart1 after stripping the '@' control character
 *  '*' hp command, acted upon here, see below
 *  '!' Alt1 alternate display command, passed to suart after stripping
 *  '%' Alt2 expansion command, passed to suart2 after stripping
 *		The master HP board will forward these to us
 * "#" MarcDuino Setup commands used to configure various settings on the MarcDuino
 *
 *  Commands recognized (see parse_hp_command)
 *  *RDxx Random Holo movement (xx=01 to 03). xx=00 and >3 all random.
 *  *ONxx Turns Holo Light on (xx=01 to 03). xx=00 or >3 all lights on
 *  *OFxx Turns Holo Lights off (xx=01 to 03). xx=00 turns all lights off
 *  *RCxx Holo vertical movement under RC control, horizontal centered (xx=01-03).
 *  	00 or >3 all RC
 *  *TExx Holo movement test (xx=01-03). Goes through a loop of holo movements
 *  	to assist in adjusting holo servos mechanical setup
 *  	00 or >3 all HPs to test
 *  *STxx stop/reset Holos random movement, turns lights off, and RC off. 00=all off
 *  *HDxx hold: stop holo, do not change light level. 00=all stopped
 *  *MOxx magic panel on. xx=01 to 98, on from 1 to 98 seconds. 00=off, 99=on permanent
 *  *MFxx magic panel flicker xx=1 to 99 flicker for 1 to 99 seconds. 00= off.
 *  *H1xx, *H2xx, *H3xx, and *H0xx
 * 		Will turn on-board HP1, 2, 3, and all (HP0xx) for xx seconds
 * 		99 is on permanently.
 * 		0 is off.
 * 	*F1xx, *F2xx, *F3xx, and *F0xx
 * 		Will flicker on-board HP1, 2, 3, and all (F0xx) for xx seconds
 * 		0 is off.
 * 		(99 is not permanently, but 99 seconds)
 *
 *	Setup Commands
 *	//// SERVO CONTROLS
 *	#SD00 Set Servo direction forward
 *	#SD01 Set servo direction reversed
 *	#SRxxy Set individual servo to either forward or reversed xx=servo number y=direction
 *		Must be a 2 digit Servo number i.e. Servo 4 is 04
 *		Must be either 0 or 1 to set the direction (0 normal, 1 reversed)
 *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.*
 */

class MarcDuinoDomeSlave : public MarcDuinoDome
{
    public:
        MarcDuinoDomeSlave(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);
            
        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "MarcDuino Dome Slave"; }
        virtual void parseCommand(const char* command);

    protected:
        SendOnlySoftwareSerial& Serial_Magic;
        SendOnlySoftwareSerial& Serial_Teeces;

        static const unsigned int MinPanel = 12;   // Master Board has 11 Panel Connectors
        static const unsigned int MaxPanel = 13;   // Master Board has 11 Panel Connectors
        
        Panel* Panels[MaxPanel + 1];               // +1 for index 0 dummy

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processAltDisplayCommand(const char* command);
        void processExpansionCommand(const char* command);
        void processI2CCommand(const char* command);

        void playSequenceAddons(const unsigned int SeqNr) override;
};

#endif // __MARCDUINODOMESLAVE_H__
