#ifndef __PANELSEQUENCES_H__
#define __PANELSEQUENCES_H__

#include "config.h"
#include "MDuinoSequencer.h"

#include <avr/pgmspace.h>

/************ example of how to use the sequencer
* define a sequence matrix like this
* make sure to follow exactly this declaration to put the array in program memory
* (it needs the const and the PROGMEM):

	sequence_t const servo_dance PROGMEM=
	{
			//  ---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 			
			// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13
			{50, 	1000, 	1000, 	1000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	2000, 	1000, 	1000, 	1000,   11000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	2000, 	1000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	1000, 	2000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	1000, 	1000, 	2000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	1000, 	1000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	2000, 	2000, 	1000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	1000, 	1000, 	1000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1000, 	1000, 	2000, 	2000,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{50, 	1500, 	1500, 	1500, 	1500,   1000, 	1000, 	1000, 	1000,	1000, 	1000, 	1000, 	1000,	1000 },
			{0, 	_NP, 	_NP, 	_NP, 	_NP,    _NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP,	_NP  } 
	};

	// time units are 1/100 seconds. Max is 65535.
	// 10 is 1/10 of a second
	// 100 is 1 second
	// 1000 is 10 second
	// 6000 is a minute
	// 36000 is 6 minutes
	*/

sequence_t const panel_all_open PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(300), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,   _OPN,  _OPN,	_OPN},
		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const panel_all_open_long PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(1000), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,    _NP,	_NP}
};

sequence_t const panel_wave PROGMEM =  //SE02 WAVE
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS},		
		{SPLIT_WORD(60), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS}, // 90 accounts for the slave panels
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,    _NP,	_NP}
};

sequence_t const panel_fast_wave PROGMEM = //SE03 SMIRK
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(7), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN}, // = 11*15=165
		{SPLIT_WORD(45), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN, 	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(7), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS}, //30 accounts for Slave sequences.
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(15), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};



sequence_t const panel_open_close_wave PROGMEM= //SE04 OPEN WAVE
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_OPN, 	_OPN,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS},
		{SPLIT_WORD(80), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN}, //= 9x20 + 80 + 3x20 = 180+80+60 = 320
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_OPN, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN}, // Stay open for 180
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN,	_CLS, 	_CLS,	_OPN},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

sequence_t const panel_marching_ants PROGMEM = //Used in SE05
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //1
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //2
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //3
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //4
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //5
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //6
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //7
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //8
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //9
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //10
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //11
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //12
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //13
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(0), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //14
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN}, //15
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // Close all
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

sequence_t const panel_dance PROGMEM =  //Used in SE07
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // 4 pie, 1 by one
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // 4 side, 1 by one
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // 4 pies. 2 by 2
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // 2 large sides
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // interleaved
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // 2nd interleaved
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // transition
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, // Good
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS, 	_OPN, 	_CLS,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_NP,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

sequence_t const panel_init PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP}
};

/*
sequence_t const panel_init PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_CLS, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_CLS, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_CLS,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_CLS, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_CLS, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_CLS, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_CLS, 	_NP,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_CLS,	_NP,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_CLS,	_NP,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_CLS,	_NP,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_CLS,	_NP},
		{SPLIT_WORD(10), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP}
};
*/

// 6min26sec disco sequence to trigger callback at the right time
sequence_t const panel_long_disco PROGMEM =  //SE09
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(7), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN}, // = 11*15=165
		{SPLIT_WORD(40), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN, 	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(7), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS}, //30 accounts for Slave sequences.
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(36000), _NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP},  // 6 minutes
		{SPLIT_WORD(2100), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP},  // 21 seconds
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

// Maxstang's sequences
sequence_t const panel_bye_bye_wave PROGMEM = //SE58
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(70), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(70), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

// Maxstang's sequences
sequence_t const panel_wiggle PROGMEM = //SE16
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(14), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(14), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(14), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(14), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(14), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(14), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN, 	_OPN,	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};


//
// Body Sequences
//

sequence_t const body_utility_arms_open PROGMEM = //SE30
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     				DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(150), 	_CLS, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_CLS, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(190), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP }
};


 sequence_t const body_panel_all_test PROGMEM =	//SE31
 {
 		// Open all doors and use all tools
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open Doors
 		{SPLIT_WORD(150), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Raise Arms open tools
 		{SPLIT_WORD(300), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open DPL (it hits tool if opened first
 		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open tools
 		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open tools
 		{SPLIT_WORD(70), 	_CLS, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Lower Arms
 		{SPLIT_WORD(200), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close Doors
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };

 sequence_t const body_panel_spook PROGMEM = //SE32
 {
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };

 sequence_t const body_panel_use_gripper PROGMEM = //SE33
 {
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(170), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };

 sequence_t const body_panel_use_interface_tool PROGMEM = //SE34
 {
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(170), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };

 sequence_t const body_panel_pingpong_Doors PROGMEM = //SE35
 {
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(110), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(110), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(80), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(80), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(130), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(130), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(200), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };
//Eebel END

sequence_t const body_panel_all_open PROGMEM = //SE51
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(150), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open Doors
		{SPLIT_WORD(150), 	_OPN, 	_NP, 	_NP, 	_NP,	_OPN, 	_OPN, 	_NP, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Raise Arms open tools
		{SPLIT_WORD(50), 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CLS, 	_NP, 	_NP,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
		{SPLIT_WORD(50), 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_OPN, 	_NP, 	_NP,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open tools
		{SPLIT_WORD(50), 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CLS, 	_NP, 	_NP,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
		{SPLIT_WORD(150), 	_OPN, 	_CLS, 	_CLS, 	_NP,	_CLS, 	_CLS, 	_NP, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Lower Arms
		{SPLIT_WORD(200), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close Doors
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const body_panel_all_open_long PROGMEM = //SE56
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_NP, 	_OPN, 	_OPN,	_NP, 	_NP,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};


sequence_t const body_panel_wave PROGMEM = //SE52
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     				DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_OPN,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const body_panel_init PROGMEM = //SE00
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(130), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

/*
 *****
 ***** Chopper Sequences *****
 *****
 *
 * See README.md for Servo Connections
 */

/*
// Template

sequence_t cp_name PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,	_NP,	_NP},
};
*/

sequence_t cp_dome_panel_init PROGMEM = //SE00
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_MID,	_NP,	_CLS,	_CLS},
		{SPLIT_WORD(100), 	_NP, 	_NP, 	_NP, 	_CLS,	_NP,	_NP, 	_NP, 	_CLS, 	_CLS,	_MID, 	_NP,	_CLS,	_CLS},
		{SPLIT_WORD(100), 	_NP, 	_NP, 	_CLS, 	_CLS, 	_NP,	_NP, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_NP,	_CLS,	_CLS},
		{SPLIT_WORD(100), 	_NP, 	_CLS, 	_CLS, 	_CLS, 	_NP,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_NP,	_CLS,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_NP,	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_MID,   _NP,	_CLS,	_CLS}
};

sequence_t const cp_dome_panel_all_open PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(150), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(150), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_OPN, 	_OPN, 	_OPN, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_OPN, 	_OPN, 	_OPN, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(150), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,  _CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_periscope_and_antenna PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_MID, 	_CLS,   _OPN, 	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _OPN, 	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _CLS,  	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _OPN,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _OPN,  	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _OPN,  	_OPN},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_MID, 	_CLS,   _OPN,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_periscope PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_OPN,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_antenna PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN, 	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN, 	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN,  	_OPN},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN,  	_OPN},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _OPN,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_panel_all_open_long PROGMEM = //SE56
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_dome_left_arm_wave PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_right_arm_wave PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_arms_wave PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID,   _CLS,   _CLS,	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS, 	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_MID, 	_CLS,   _CLS,  	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   _NP,		_NP}
};

sequence_t const cp_dome_panel_wave2 PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_MID, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,    _NP,	_NP}
};

//
// Body Sequences
//

sequence_t const cp_body_panel_init PROGMEM = //SE00
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
		{SPLIT_WORD(130), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_all_open PROGMEM = //SE51
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP},
		{SPLIT_WORD(150), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP}, //Open Doors
		{SPLIT_WORD(150), 	_CLS, 	_NP, 	_NP, 	_NP,	_OPN, 	_OPN, 	_NP, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_NP,	_NP}, //Raise Arms open tools
		{SPLIT_WORD(50), 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CLS, 	_NP, 	_NP,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP}, //Close tools
		{SPLIT_WORD(50), 	_CLS, 	_NP, 	_NP, 	_NP,	_NP, 	_OPN, 	_NP, 	_NP,	_OPN, 	_CLS,	_CLS, 	_NP,	_NP}, //Open tools
		{SPLIT_WORD(50), 	_OPN, 	_NP, 	_NP, 	_NP,	_NP, 	_CLS, 	_NP, 	_NP,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP}, //Close tools
		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_NP,	_CLS, 	_CLS, 	_NP, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP}, //Lower Arms
		{SPLIT_WORD(200), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_NP,	_NP}, //Close Doors
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_all_open_long PROGMEM = //SE56
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(300), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_wave2 PROGMEM =
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(500), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(2000), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},	// Close Dome in between
		{SPLIT_WORD(500), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,    _NP,	_NP}
};

sequence_t const cp_body_panel_marching_ants PROGMEM = //Used in SE05
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //1
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //2
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //3
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //4
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //5
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //6
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //7
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //8
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //9
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //10
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //11
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //12
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //13
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //14
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //15
		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(100), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, // Close all
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP,	_NP,	_NP}
};

sequence_t const cp_dome_wiggle PROGMEM = //SE33
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(30), 	_OPN, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_utility_arm_open PROGMEM = //SE33
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
 };

sequence_t const cp_body_panel_all_test PROGMEM =	//SE31
{
 		// Open all doors and use all tools
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open Doors
 		{SPLIT_WORD(150), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Raise Arms open tools
 		{SPLIT_WORD(300), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open DPL (it hits tool if opened first
 		{SPLIT_WORD(50), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(50), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open tools
 		{SPLIT_WORD(50), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(50), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Open tools
 		{SPLIT_WORD(70), 	_MID, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close tools
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Lower Arms
 		{SPLIT_WORD(200), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS}, //Close Doors
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_spook PROGMEM = //SE32
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_use_saw PROGMEM = //SE33
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(170), 	_MID, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_use_interface_tool PROGMEM = //SE34
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(170), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const cp_body_panel_pingpong_Doors PROGMEM = //SE35
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     	DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(110), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(110), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(80), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(80), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(130), 	_OPN, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(130), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(200), 	_MID, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

/*
 *****
 ***** BT-1 Sequences *****
 *****
 *
 * See README.md for Servo Connections
 */

// Steinke BEGIN
sequence_t const bt_dome_panel_init PROGMEM = //SE00
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(100), 	_CLS, 	_CLS, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,	_NP,	_NP,	_NP}
};

sequence_t const bt_body_panel_use_claws PROGMEM = //SE36
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     				DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(90), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(90), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(50), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_OPN, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(120), 	_CLS, 	_CLS, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const bt_body_panel_use_right_claw PROGMEM = //SE37
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		//     				DPL		UtlArmU	UtlArmL	LBdyDr	LArm	LArmToolRBdyDr	RArm	RArmTool ChrgBay 
	 	{SPLIT_WORD(20), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(150), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(10), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_OPN,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(170), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_OPN, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS, 	_CLS,	_CLS},
 		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP}
};

sequence_t const bt_dome_danger_fire PROGMEM = //SE38
{
		//				---------------------------------------MASTER--------------------------------------------  ----SLAVE------ 
		// time				servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 
		{SPLIT_WORD(30), 	_CLS, 	_CLS, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(120), 	_OPN, 	_OPN, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(50), 	_OPN, 	_OPN, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_OPN, 	_OPN, 	_OPN, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(30), 	_OPN, 	_OPN, 	_CLS, 	_OPN,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(170), 	_OPN, 	_OPN, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(250), 	_CLS, 	_CLS, 	_MID, 	_MID,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS},
		{SPLIT_WORD(0), 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,    _NP,	_NP}
};
// Steinke END

#endif  // __PANELSEQUENCES_H__