#include <Arduino.h>

#include "MDuinoSequencePlayer.h"
#include "PanelSequences.h"

MDuinoSequencePlayer::MDuinoSequencePlayer(MDuinoSequencer &Sequencer) : 
	Sequencer(Sequencer)
{
}

void MDuinoSequencePlayer::playSequence(const byte SeqNr)
{
	Sequencer.stopSequence();
	Sequencer.clearSequence();
}

// ----------
#ifdef R2D2
MDuinoDomeSequencePlayerR2::MDuinoDomeSequencePlayerR2(MDuinoSequencer &Sequencer) : 
	MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoDomeSequencePlayerR2::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

	switch (SeqNr)
	{
	case 0: // CLOSE ALL PANELS
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 1:	 // SCREAM
	case 51: // Panel only Version
		Sequencer.loadSequence(panel_all_open, SEQ_SIZE(panel_all_open));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 2:	 // WAVE
	case 52: // Panel only Version
		Sequencer.loadSequence(panel_wave, SEQ_SIZE(panel_wave));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 3:	 // MOODY FAST WAVE
	case 53: // Panel only Version
		Sequencer.loadSequence(panel_fast_wave, SEQ_SIZE(panel_fast_wave));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 4:	 // OPEN WAVE
	case 54: // Panel only Version
		Sequencer.loadSequence(panel_open_close_wave, SEQ_SIZE(panel_open_close_wave));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 5:	 // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
	case 55: // Panel only Version
		Sequencer.loadSequence(panel_marching_ants, SEQ_SIZE(panel_marching_ants));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 6:	 // SHORT CIRCUIT / FAINT
	case 56: // Panel only Version
		Sequencer.loadSequence(panel_all_open_long, SEQ_SIZE(panel_all_open_long));
		Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
		break;
	case 7:	 // Cantina (Orchestral Cantina, Rhythmic Panels)
	case 57: // Panel only Version
		Sequencer.loadSequence(panel_dance, SEQ_SIZE(panel_dance));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 8:														  // LEIA
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init)); // Close panels
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 9:																	  // DISCO
		Sequencer.loadSequence(panel_long_disco, SEQ_SIZE(panel_long_disco)); // 6:26 seconds sequence
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 10: // QUIET   sounds off, holo stop, panel closed
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		// stop_command(0);					// all panels off RC
		break;
	case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		// stop_command(0);					// all panels off RC and closed
		break;
	case 12: // TOP PIE PANELS RC
		/*
		rc_command(7);
		rc_command(8);
		rc_command(9);
		rc_command(10);
		*/
		break;
	case 13: // AWAKE	random sounds, holos off, panels closed
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		// stop_command(0);					// all panels off RC and closed
		break;
	case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
		Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		// stop_command(0);					// all panels off RC and closed
		break;

	case 15: // SCREAM no panels: sound + lights but no panels
		break;
	case 16: // Panel Wiggle
		Sequencer.loadSequence(panel_wiggle, SEQ_SIZE(panel_wiggle));
		Sequencer.setServoSpeed(MDuinoSequencer::medium);
		break;

	case 58: // Panel Wave Bye Bye
		Sequencer.loadSequence(panel_bye_bye_wave, SEQ_SIZE(panel_bye_bye_wave));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	default:
		break;
	}
}

// ----------

MDuinoBodySequencePlayerR2::MDuinoBodySequencePlayerR2(MDuinoSequencer &Sequencer) : MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoBodySequencePlayerR2::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

	switch (SeqNr)
	{
	case 0: // CLOSE ALL PANELS
		Sequencer.loadSequence(body_panel_init, SEQ_SIZE(body_panel_init));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 1: // SCREAM
	case 51:
		Sequencer.loadSequence(body_panel_all_open, SEQ_SIZE(body_panel_all_open));
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;
	case 2: // WAVE
	case 52:
		Sequencer.loadSequence(body_panel_wave, SEQ_SIZE(body_panel_wave));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 6: // SHORT CIRCUIT / FAINT
	case 56:
		Sequencer.loadSequence(body_panel_all_open_long, SEQ_SIZE(body_panel_all_open_long));
		Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
		break;
	case 8: // LEIA
	case 10:
	case 11:
	case 13:
	case 14:
		Sequencer.loadSequence(body_panel_init, SEQ_SIZE(body_panel_init)); // Close panels
		Sequencer.setServoSpeed(MDuinoSequencer::slow);
		break;

	//
	// 16 - 29 reserved for dome reagrding Eebel
	//

	//
	// Body Sequences
	//
	case 30: // Utility ARM open and close sequence
		Sequencer.loadSequence(body_utility_arms_open, SEQ_SIZE(body_utility_arms_open));
		Sequencer.setServoSpeed(MDuinoSequencer::medium);
		break;
	case 31: // All Body Panels open and close sequence
		Sequencer.loadSequence(body_panel_all_test, SEQ_SIZE(body_panel_all_test));
		Sequencer.setServoSpeed(MDuinoSequencer::medium);
		break;
	case 32: // All Body Doors open and wiggle close sequence
		Sequencer.loadSequence(body_panel_spook, SEQ_SIZE(body_panel_spook));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 33: // Body - Use Gripper
		Sequencer.loadSequence(body_panel_use_gripper, SEQ_SIZE(body_panel_use_gripper));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 34: // Body - Use Interface Tool
		Sequencer.loadSequence(body_panel_use_interface_tool, SEQ_SIZE(body_panel_use_interface_tool));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	case 35: // Body - Ping Pong Body Doors
		Sequencer.loadSequence(body_panel_pingpong_Doors, SEQ_SIZE(body_panel_pingpong_Doors));
		Sequencer.setServoSpeed(MDuinoSequencer::full);
		break;
	default:
		break;
	}
}
#endif

#ifdef CHOPPER
MDuinoDomeSequencePlayerChopper::MDuinoDomeSequencePlayerChopper(MDuinoSequencer &Sequencer) : 
	MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoDomeSequencePlayerChopper::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

	switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        Sequencer.loadSequence(cp_dome_panel_init, SEQ_SIZE(cp_dome_panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 1:  // SCREAM
    case 51: // Panel only Version
        Sequencer.loadSequence(cp_dome_panel_all_open, SEQ_SIZE(cp_dome_panel_all_open));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 2:
        Sequencer.loadSequence(cp_dome_periscope_and_antenna, SEQ_SIZE(cp_dome_periscope_and_antenna));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 3:
        Sequencer.loadSequence(cp_dome_periscope, SEQ_SIZE(cp_dome_periscope));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 4:
        Sequencer.loadSequence(cp_dome_panel_wave2, SEQ_SIZE(cp_dome_panel_wave2));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 6: // SHORT CIRCUIT / FAINT
    case 56:// Panel only Version
        Sequencer.loadSequence(cp_dome_panel_all_open_long, SEQ_SIZE(cp_dome_panel_all_open_long));
        Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
        break;		
    case 7:
        break;
    case 8:
        Sequencer.loadSequence(cp_dome_antenna, SEQ_SIZE(cp_dome_antenna));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 11:
        Sequencer.loadSequence(panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 12:
        Sequencer.loadSequence(cp_dome_left_arm_wave, SEQ_SIZE(cp_dome_left_arm_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 13:
        Sequencer.loadSequence(cp_dome_right_arm_wave, SEQ_SIZE(cp_dome_right_arm_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 14: // Dome Arms Wave Animation
        Sequencer.loadSequence(cp_dome_arms_wave, SEQ_SIZE(cp_dome_arms_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;

    //
    // 30+ : body sequences only
    //

    //
    // 50+ : sound sequences only
    //
    default:
        break;         
    }
}


MDuinoBodySequencePlayerChopper::MDuinoBodySequencePlayerChopper(MDuinoSequencer &Sequencer) : MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoBodySequencePlayerChopper::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

    switch (SeqNr)
    {
    case 0:     // CLOSE ALL PANELS
        Sequencer.loadSequence(cp_body_panel_init, SEQ_SIZE(cp_body_panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 1:  // SCREAM
    case 51: // Panel only Version
        Sequencer.loadSequence(cp_body_panel_all_open, SEQ_SIZE(cp_body_panel_all_open));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 4:     // Wave 2 (open progressively all panels, then close one by one)
    case 54:
        Sequencer.loadSequence(cp_body_panel_wave2, SEQ_SIZE(cp_body_panel_wave2));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 6:     // SHORT CIRCUIT / FAINT
    case 56:
        Sequencer.loadSequence(cp_body_panel_all_open_long, SEQ_SIZE(cp_body_panel_all_open_long));
        Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
        break;
    case 7:     // Cantina Dance
        Sequencer.loadSequence(cp_body_panel_marching_ants, SEQ_SIZE(cp_body_panel_marching_ants));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 16:    // Dome wiggle, multiple times
        Sequencer.loadSequence(cp_dome_wiggle, SEQ_SIZE(cp_dome_wiggle));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    //
    // Body Sequences
    //
    case 30:    // Utility ARM open and close sequence
        Sequencer.loadSequence(cp_body_utility_arm_open, SEQ_SIZE(cp_body_utility_arm_open));
        Sequencer.setServoSpeed(MDuinoSequencer::medium);
        break;
    case 31:    // All Body Panels open and close sequence
        Sequencer.loadSequence(cp_body_panel_all_test, SEQ_SIZE(cp_body_panel_all_test));
        Sequencer.setServoSpeed(MDuinoSequencer::medium);
        break;
    case 32:    // All Body Doors open and wiggle close sequence
        Sequencer.loadSequence(cp_body_panel_spook, SEQ_SIZE(cp_body_panel_spook));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 33:    // Body - Use Saw
        Sequencer.loadSequence(cp_body_panel_use_saw, SEQ_SIZE(cp_body_panel_use_saw));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 34:    // Body - Use Interface Tool
        Sequencer.loadSequence(cp_body_panel_use_interface_tool, SEQ_SIZE(cp_body_panel_use_interface_tool));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 35:    // Body - Ping Pong Body Doors
        Sequencer.loadSequence(cp_body_panel_pingpong_Doors, SEQ_SIZE(cp_body_panel_pingpong_Doors));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    default:
        break;         
    }
}
#endif

#ifdef BT1
MDuinoDomeSequencePlayerBT1::MDuinoDomeSequencePlayerBT1(MDuinoSequencer &Sequencer) : 
	MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoDomeSequencePlayerBT1::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        Sequencer.loadSequence(bt_dome_panel_init, SEQ_SIZE(bt_dome_panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::fast);
        break;
    case 38: // Fire dome rockets
        Sequencer.loadSequence(bt_dome_danger_fire, SEQ_SIZE(bt_dome_danger_fire));
        Sequencer.setServoSpeed(MDuinoSequencer::fast);
        break;           
    default:
        break;         
    }
}



MDuinoBodySequencePlayerBT1::MDuinoBodySequencePlayerBT1(MDuinoSequencer &Sequencer) : 
	MDuinoSequencePlayer(Sequencer)
{
}

void MDuinoBodySequencePlayerBT1::playSequence(const byte SeqNr)
{
	MDuinoSequencePlayer::playSequence(SeqNr);

    
    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        Sequencer.loadSequence(body_panel_init, SEQ_SIZE(panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 1:  // SCREAM
    case 51:
        Sequencer.loadSequence(body_panel_all_open, SEQ_SIZE(body_panel_all_open));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
    case 2: // WAVE
    case 52:
        Sequencer.loadSequence(body_panel_wave, SEQ_SIZE(body_panel_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 6: // SHORT CIRCUIT / FAINT
    case 56:
        Sequencer.loadSequence(body_panel_all_open_long, SEQ_SIZE(body_panel_all_open_long));
        Sequencer.setServoSpeed(MDuinoSequencer::super_slow);
        break;
    case 8: // LEIA
    case 10:
    case 11:
    case 13:
    case 14:
        Sequencer.loadSequence(body_panel_init, SEQ_SIZE(body_panel_init));	// Close panels
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;

    // 
    // 16 - 29 reserved for dome reagrding Eebel
    //

    //
    // Body Sequences
    //
    case 30: // Utility ARM open and close sequence
        Sequencer.loadSequence(body_utility_arms_open, SEQ_SIZE(body_utility_arms_open));
        Sequencer.setServoSpeed(MDuinoSequencer::medium);
        break;
    case 31: // All Body Panels open and close sequence
        Sequencer.loadSequence(body_panel_all_test, SEQ_SIZE(body_panel_all_test));
        Sequencer.setServoSpeed(MDuinoSequencer::medium);
        break;
    case 32: // All Body Doors open and wiggle close sequence
        Sequencer.loadSequence(body_panel_spook, SEQ_SIZE(body_panel_spook));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 33: //Body - Use Gripper
        Sequencer.loadSequence(body_panel_use_gripper, SEQ_SIZE(body_panel_use_gripper));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 34: //Body - Use Interface Tool
        Sequencer.loadSequence(body_panel_use_interface_tool, SEQ_SIZE(body_panel_use_interface_tool));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 35: //Body - Ping Pong Body Doors
        Sequencer.loadSequence(body_panel_pingpong_Doors, SEQ_SIZE(body_panel_pingpong_Doors));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 36: //Body - Use Claws, two gripper arms mod
        Sequencer.loadSequence(bt_body_panel_use_claws, SEQ_SIZE(bt_body_panel_use_claws));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;
    case 37: //Body - Use right claw, no interface arm
        Sequencer.loadSequence(bt_body_panel_use_right_claw, SEQ_SIZE(bt_body_panel_use_right_claw));
        Sequencer.setServoSpeed(MDuinoSequencer::full);
        break;    
    default:
        break;         
    }
}
#endif