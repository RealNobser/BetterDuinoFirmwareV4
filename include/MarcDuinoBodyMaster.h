#ifndef __MARCDUINOBODYMASTER_H__
#define __MARCDUINOBODYMASTER_H__

#include <SendOnlySoftwareSerial.h>

#include "MarcDuinoBase.h"
#include "Panel.h"

/** Command implementation
 *
 * Hardware setup: the board has
 * 	- 12 servo outputs for the dome panel doors (Master uses 11 only)
 * 	- one suart (suart) at 9600 bauds connected the slave HP Controller board
 * 	- a second suart (suart2) at 2400 bauds with RS232 level translation
 * 	- the main UART input at 9600 bauds connected to the XBee radio
 * 	- one RC input connected to a RC channel
 *
 * Every command must start with one of these special characters (defined in the header file)
 * The start character is recognized in the main loop:
 *
 * ":" Pie panel command, parsed and treated by this controller in the "process_command" routine
 * "*" HP commands, passed on to the HoloController board daisy chained to suart1, see "parse_hp_command"
 * "@" Display commands, also passed to the HoloController board, see "parse_display_command"
 * "$" Sound commands, passed to the CFIII sound controller on suart2 "parse_sound_command"
 * "!" Alt1 alternate sound command, passed to suart2 after stripping
 * "%" Alt2 alternate HP board command, passed to suart without stripping
 *		The slave HP board will output it on suart2 after stripping
 * "#" MarcDuino Setup commands used to configure various settings on the MarcDuino
 *
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
 *
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *	:SE00 Close all panels (full speed), servo off - use as init only. Use CL00 for all soft close.
 *	:SE01 Scream, with all panels open
 *	:SE02 Wave, one panel at a time
 *	:SE03 Fast (Smirk) back and forth wave
 *	:SE04 Wave 2 (open progressively all panels, then close one by one)
 *	:SE05 Beep Cantina (with marching ants panel action)
 *	:SE06 Faint/Short Circuit
 *	:SE07 Cantina dance (orchestral, rythmic panel dance)
 *	:SE08 Leia
 *	:SE09 Disco
 *	:SE10 Quite Mode reset (panel close, stop holos, stop sounds)
 *	:SE11 Full Awake Mode reset (panel close, random sound, holo movement, no holo lights)
 *	:SE12 Top Panels to RC
 *	:SE13 Mid Awake Mode reset (panel close, random sound, stop holos)
 *	:SE14 Awake+ Mode reset ((panel close, random sound, holo movement, lights on)
 *	:SE15 Screams no panels
 *	:SE16 Panel Wiggle
 *
 *	Panel Moves Only
 *	:SE51 Scream, with all panels open
 *	:SE52 Wave, one panel at a time
 *	:SE53 Fast (Smirk) back and forth wave
 *	:SE54 Wave 2 (open progressively all panels, then close one by one)
 *	:SE55 Marching ants
 *	:SE56 Faint/Short Circuit
 *	:SE57 Rythmic panel dance)
 *	:SE58 Panel Wave Bye Bye
 *	:SE59 Open panels half way
 *
 *	Setup Commands
 *	//// SERVO CONTROLS
 *	#SD00 Set Servo direction forward
 *	#SD01 Set servo direction reversed
 *	#SRxxy Set individual servo to either forward or reversed xx=servo number y=direction
 *		Must be a 2 digit Servo number i.e. Servo 4 is 04
 *		Must be either 0 or 1 to set the direction (0 normal, 1 reversed)
 *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.
 *	//// STARTUP SOUND CONTROLS
 *	#SS00 Disable Startup Sound, and remove startup sound delay for fast boot of R2
 *	#SS01 Default Startup Sound in file 255
 *	#SS02 Alternate Startup Sound in file 254
 *	#SS03 Second Alternate Startup Sound in file 253
 *	// Chatty/Silent Mode
 *	#SQ00 Default Chatty Mode
 *	#SQ01 Silent on startup
 *	//// PANEL SEQUENCER CONTROLS
 *	#STxx Setup Delay time between Master and Slave Panel Sequences.
 *		Use this if the Slave panels are starting too soon
 *		Values up to 250 are supported.  Values are in ms.
 *
 *  Client Features
 *  *EOxx Pull pin high/low (config in Client code) on EXT1.
 *        Can be used to trigger a smoke machine as an example.
 *        xx is the time in seconds.
 *        00 - off
 *        01-98 is the time in seconds (don't use values >10 for smoke machines!)
 *        99 on permanently (again don't use for smoke machines)
 *
 */

class MarcDuinoBodyMaster : public MarcDuinoBase
{
    public:
        MarcDuinoBodyMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        void init() override;
        void run() override;

        virtual void parseCommand(const char* command) override;
        virtual const char* getProductName() override { return "MarcDuino Body Master"; }

    protected:
        SendOnlySoftwareSerial& Serial_Slave;
        SendOnlySoftwareSerial& Serial_MP3;

        
};

#endif // __MARCDUINOBODYMASTER_H__
