#include "MDuinoDomeMasterChopper.h"
#include "PanelSequences.h"

MDuinoDomeMasterChopper::MDuinoDomeMasterChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeMaster(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{

}

void MDuinoDomeMasterChopper::init()
{
    MDuinoDomeMaster::init();
    Serial_Slave.print(F("#MD01\r"));   // Force Slave board to be in Dome Slave Mode
}

void MDuinoDomeMasterChopper::run()
{
    MDuinoDomeMaster::run();
}

void MDuinoDomeMasterChopper::playSequence(const byte SeqNr)
{
    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
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
    playSequenceAddons(SeqNr);
}

void MDuinoDomeMasterChopper::playSequenceAddons(const byte SeqNr)
{
    // Also forward to Slave
    Serial_Slave.printf(F(":SE%2u\r"), SeqNr);

    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    // No specials besides panel movement
    // Just one at the moment
    switch (SeqNr)
    {
    case 1:
        parseCommand("$113");		// 0013
        break;
    case 6:
        parseCommand("$101");		// 0001
        break;
    case 7:
        parseCommand("$805");		// 0180
        break;
    case 11: // WIDE AWAKE	random sounds, holos on random, panels closed
        parseCommand("$R");			// random sounds mode
        break;        
    case 15:
        parseCommand("$113");		// 0013
        break;
    case 61:
        parseCommand("$804");		// 0179
        break;
    case 62:
        parseCommand("$807");		// 0182
        break;
    case 63:
        parseCommand("$809");		// 0184
        break;
    case 64:
        parseCommand("$812");		// 0187
        break;
    case 65:
        parseCommand("$813");		// 0188
        break;
    case 66:
        parseCommand("$814");		// 0189
        break;
    case 67:
        parseCommand("$815");		// 0190
        break;
    case 68:
        parseCommand("$816");		// 0191
        break;
    default:
        break;
    }

    // Finally GOOOOO
    Sequencer.startSequence();
}