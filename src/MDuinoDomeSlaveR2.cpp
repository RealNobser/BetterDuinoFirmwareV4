
#include "MDuinoDomeSlaveR2.h"
#include "PanelSequences.h"

MDuinoDomeSlaveR2::MDuinoDomeSlaveR2(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    MDuinoDomeSlave(Serial_Magic, Serial_Teeces, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{
    SequencePlayer = new MDuinoDomeSequencePlayerR2(Sequencer);
}

void MDuinoDomeSlaveR2::init()
{
    MDuinoDomeSlave::init();
}

void MDuinoDomeSlaveR2::run()
{
    MDuinoDomeSlave::run();
}

void MDuinoDomeSlaveR2::playSequenceAddons(const byte SeqNr)
{
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