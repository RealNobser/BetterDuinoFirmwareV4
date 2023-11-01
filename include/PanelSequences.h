#ifndef __PANELSEQUENCES_H__
#define __PANELSEQUENCES_H__

#include "config.h"
#include "MarcDuinoSequencer.h"

#include <avr/pgmspace.h>

#define _NP     0
#define _CLS    1
#define _OPN    2
#define _MID    3

//sequence_t const panel_all_open PROGMEM =
//sequence_t
sequence_t const seq_panel_all_open PROGMEM =
{
		//  ---------------------------------------MASTER--------------------------------------------  ----SLAVE------ -----------CONFIG-----------
		// time	servo1	servo2	servo3	servo4	servo5	servo6	servo7	servo8	servo9 servo10 servo11 servo12 servo13 speed	first 	last
		{20, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,   _CLS,  /*_CLS,	_CLS,*/	_NP,	1,		11},
		{300, 	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN, 	_OPN, 	_OPN,	_OPN, 	_OPN,   _OPN,  /*_OPN,	_OPN,*/	_NP,	1,		11},
		{150, 	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS, 	_CLS, 	_CLS,	_CLS, 	_CLS,   _CLS,  /*_CLS,	_OPN,*/	_NP,	1,		11},
		{0, 	_NP, 	_NP, 	_NP, 	_NP,	_NP, 	_NP, 	_NP, 	_NP, 	_NP,	_NP,    _NP,   /*_NP,	_NP,*/	_NP,	1,		11}
};

#endif  // __PANELSEQUENCES_H__