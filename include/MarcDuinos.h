#ifndef __MARCDUINOS_H__
#define __MARCDUINOS_H__

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

#include <Arduino.h>
#include <SendOnlySoftwareSerial.h>
#include <config.h>
#include "Panel.h"

#define SERIALBUFFERSIZE 256

class MarcDuinoBase
{
    public:
        MarcDuinoBase();
        void init();
        void run();

        virtual void parseCommand(const char* command) = 0;

        void toggleHeartBeat();

    protected:
        unsigned long HeartBeatMillis = 0;
        byte HeartBeatStatus = LOW;

        char SerialBuffer[SERIALBUFFERSIZE];
        int BufferIndex = 0;

        void processSetupCommand(const char* command);
};

class MarcDuinoDomeMaster : public MarcDuinoBase
{
    public:
        MarcDuinoDomeMaster();
        void init();
        void run();

        virtual void parseCommand(const char* command) override;

    protected:
        SendOnlySoftwareSerial Serial_MP3   = SendOnlySoftwareSerial(P_MP3);
        SendOnlySoftwareSerial Serial_Slave = SendOnlySoftwareSerial(P_SLAVE);

        Panel Panel1 = Panel(90, 180);
        Panel Panel2 = Panel(90, 180);
        Panel Panel3 = Panel(90, 180);
        Panel Panel4 = Panel(90, 180);
        Panel Panel5 = Panel(90, 180);
        Panel Panel6 = Panel(90, 180);
        Panel Panel7 = Panel(90, 180);
        Panel Panel8 = Panel(90, 180);
        Panel Panel9 = Panel(90, 180);
        Panel Panel10= Panel(90, 180);
        Panel Panel11= Panel(90, 180);

        Panel* Panel0 = nullptr;    // Placeholder for index
        Panel* Panels[MAX_PANELS+1];

        void processPanelCommand(const char* command);
        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processSoundCommand(const char* command);
        void processAltSoundCommand(const char* command);
        void processAltHoloCommand(const char* command);
};

class MarcDuinoDomeSlave : public MarcDuinoBase
{
    public:
        MarcDuinoDomeSlave();
        void init();
        void run();

        virtual void parseCommand(const char* command);

    protected:
        SendOnlySoftwareSerial Serial_Teeces  = SendOnlySoftwareSerial(P_TEECES);
        SendOnlySoftwareSerial Serial_Magic   = SendOnlySoftwareSerial(P_MAGIC);

        void processHoloCommand(const char* command);
        void processDisplayCommand(const char* command);
        void processAltDisplayCommand(const char* command);
        void processExpansionCommand(const char* command);

};

class MarcDuinoBody : public MarcDuinoBase
{
    public:
        MarcDuinoBody();
        void init();
        void run();

        virtual void parseCommand(const char* command);

    protected:
        SendOnlySoftwareSerial Serial_MP3     = SendOnlySoftwareSerial(P_MP3);
        SendOnlySoftwareSerial Serial_Slave   = SendOnlySoftwareSerial(P_SLAVE);

};

#endif