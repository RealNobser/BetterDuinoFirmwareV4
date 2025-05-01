#include "MDuinoDomeMasterR2.h"
#include "MDuinoSequencePlayer.h"

MDuinoDomeMasterR2::MDuinoDomeMasterR2(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeMaster(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{
    SequencePlayer = new MDuinoDomeSequencePlayerR2(Sequencer);
}

void MDuinoDomeMasterR2::init()
{
    MDuinoDomeMaster::init();
    Serial_Slave.print(F("#MD01\r"));   // Force Slave board to be in Dome Slave Mode
}

void MDuinoDomeMasterR2::run()
{
    MDuinoDomeMaster::run();
}

void MDuinoDomeMasterR2::playSequenceAddons(const byte SeqNr)
{
    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        break;
    case 1:  // SCREAM
        parseCommand("$S");         // Scream Sound
        parseCommand("@0T5");       // Scream Display
        parseCommand("*MF04");      // Magic Flicker for 4 seconds
        parseCommand("*F004");      // HP Flicker for 4 seconds
        break;
    case 2: // WAVE
        parseCommand("*H004");      // flash holos for 4 seconds
        parseCommand("$213");		// happy sound
        break;
    case 3: // MOODY FAST WAVE
        parseCommand("@0T2");       // flash display ...
        parseCommand("@0W4");       // ... for 4 seconds
        parseCommand("*F004");      // HP Flicker for 4 seconds
        parseCommand("$34");		// moody sound
        break;
    case 4: // OPEN WAVE
        parseCommand("*H005");      // flash holos for 5 seconds
        parseCommand("$36");		// long happy sound
        break;
    case 5: // Beep Cantina (R2 beeping the cantina, panels doing marching ants)
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        parseCommand("@0T92");      // spectrum display
        parseCommand("*HP17");      // HPs flash for 17 seconds
        parseCommand("$c");         // beeping cantina sound
        parseCommand("%T52");	    // Magic Panel in VU Mode
        break;
    case 6: // SHORT CIRCUIT / FAINT
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        //EXT1On(4); // Turn on Smoke for 4 seconds  Do first so there's smoke when the panels open.
        parseCommand("$F");         // Faint sound
        parseCommand("@0T4");       // short circuit display ...
        parseCommand("@0W10");      // ... for 10 seconds 
        parseCommand("*MF10");      // Magic Panel Flicker for 10 seconds
        parseCommand("*F010");      // HPs flicker 10 seconds
        break;
    case 7: // Cantina (Orchestral Cantina, Rhythmic Panels)
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        parseCommand("$C");         // Cantina sound        
        parseCommand("@0T92");      // spectrum display
        parseCommand("*F046");      // HPs flicker 46 seconds        
        parseCommand("%T52");	    // Magic Panel in VU Mode        
        break;
    case 8: // LEIA
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("*RC01"); 	    // HP 01 in RC mode
        parseCommand("$L");         // Leia message sound  
        parseCommand("*F134");      // front holos flicker for 34 sec 
        parseCommand("@0T6");       // Leia display
        parseCommand("%T22");	    // HP in Cylon Row Scan mode       
        break;
    case 9:	// DISCO
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        parseCommand("@0T92");      // spectrum display
        parseCommand("*F099");      // HPs flicker as long as possible   
        parseCommand("%T52");	    // Magic Panel in VU Mode
        parseCommand("$D");         // disco music
        break;
    case 10: // QUIET   sounds off, holo stop, panel closed
        Sequencer.addSequenceCompletionCallback(sequenceCallbackJedi);
        parseCommand("*ST00");  // all holos to stop
        parseCommand("$s");		// stop sounds
        // stop_command(0);					// all panels off RC        
        break;
    case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
        // init_jedi();						// JEDI back to default
        parseCommand("*RD00\r");			// all HPs to random
        parseCommand("$R");					// random sounds mode
        //stop_command(0);					// all panels off RC and closed
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
        //init_jedi();						// JEDI back to default
        parseCommand("*ST00\r");			// all HPs to stop
        parseCommand("$R");					// random sounds mode
        // stop_command(0);					// all panels off RC and closed
        break;
    case 14: // EXCITED	random sounds, holos movement, holo lights on, panels closed
        // init_jedi();						// JEDI back to default
        parseCommand("*RD00\r");			// all HPs to random
        parseCommand("*ON00\r");			// all HPs lights on
        parseCommand("$R");					// random sounds mode
        //stop_command(0);					// all panels off RC and closed
        break;

    case 15: // SCREAM no panels: sound + lights but no panels
        Sequencer.addSequenceCompletionCallback(sequenceCallbackResetMP);
        parseCommand("$S");	 				// code for scream sound
        parseCommand("@0T5\r");				// scream display
        parseCommand("*F003\r");			// holos flicker for 4 seconds
        parseCommand("*MF04\r");			// magic panel on for 4 seconds
        break;
    case 16: // Panel Wiggle
        parseCommand("@0T5\r");				// scream display
        break;
    default:
        break;
    }
    // Finally GOOOOO
    Sequencer.startSequence();
}
