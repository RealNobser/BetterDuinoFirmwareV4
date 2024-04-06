#include "MDuinoDomeMasterBT1.h"
#include "PanelSequences.h"

MDuinoDomeMasterBT1::MDuinoDomeMasterBT1(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeMaster(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{

}

void MDuinoDomeMasterBT1::init()
{
    MDuinoDomeMaster::init();
}

void MDuinoDomeMasterBT1::run()
{
    MDuinoDomeMaster::run();
}

void MDuinoDomeMasterBT1::playSequence(const byte SeqNr)
{
    Sequencer.stopSequence();
    Sequencer.clearSequence();
    
    switch (SeqNr)
    {
    case 0: // CLOSE ALL PANELS
        //Sequencer.loadSequence(bt_dome_panel_init, SEQ_SIZE(cp_dome_panel_init));
        Sequencer.setServoSpeed(MDuinoSequencer::fast);
        break;
    case 38: // Fire dome rockets
        Sequencer.loadSequence(bt_dome_danger_fire, SEQ_SIZE(bt_dome_danger_fire));
        Sequencer.setServoSpeed(MDuinoSequencer::fast);
        break;           
    default:
        break;         
    }
    playSequenceAddons(SeqNr);
}

void MDuinoDomeMasterBT1::playSequenceAddons(const byte SeqNr)
{
    // Also forward to Slave
    Serial_Slave.printf(F(":SE%2u\r"), SeqNr);

    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    // No speicals besides panel movement
    switch (SeqNr)
    {
    case 38: // Fire dome rockets
        parseCommand("@0T5");       // Scream Display
        parseCommand("*F004");      // HP Flicker for 4 seconds
        break;           
        default:
        break;
    }

    // Finally GOOOOO
    Sequencer.startSequence();
}