#include "MDuinoDomeMasterChopper.h"
#include "PanelSequences.h"

MDuinoDomeMasterChopper::MDuinoDomeMasterChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13):
    MDuinoDomeMaster(Serial_Slave, Serial_MP3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13)
{

}

void MDuinoDomeMasterChopper::init()
{
    MDuinoDomeMaster::init();
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
    case 1: // Dome Arms Wave Animation
        Sequencer.loadSequence(cp_dome_arms_wave, SEQ_SIZE(cp_dome_arms_wave));
        Sequencer.setServoSpeed(MDuinoSequencer::slow);
        break;
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