#include "MDuinoBodyMasterChopper.h"
#include "PanelSequences.h"

MDuinoBodyMasterChopper::MDuinoBodyMasterChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeMasterChopper(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{

}

void MDuinoBodyMasterChopper::init()
{
    MDuinoDomeMasterChopper::init();
    // Serial_Slave.print(F("#MD03\r"));   // Force Slave board to be in Body Slave Mode
}

void MDuinoBodyMasterChopper::run()
{
    MDuinoDomeMasterChopper::run();
}

void MDuinoBodyMasterChopper::playSequence(const byte SeqNr)
{
    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
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
    playSequenceAddons(SeqNr);
}

void MDuinoBodyMasterChopper::playSequenceAddons(const byte SeqNr)
{
    // Also forward to Slave
    Serial_Slave.printf(F(":SE%2u\r"), SeqNr);

    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    // No speicals besides panel movement
    // Just one at the moment
    /*
    switch (SeqNr)
    {
        default:
        break;
    }
    */

    // Finally GOOOOO
    Sequencer.startSequence();
}