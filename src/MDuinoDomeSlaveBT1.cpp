#include "MDuinoDomeSlaveBT1.h"

#ifdef BT1

MDuinoDomeSlaveBT1::MDuinoDomeSlaveBT1(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeSlave(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{

}

void MDuinoDomeSlaveBT1::init()
{
    MDuinoDomeSlave::init();
}

void MDuinoDomeSlaveBT1::run()
{
    MDuinoDomeSlave::run();
}

void MDuinoDomeSlaveBT1::playSequenceAddons(const byte SeqNr)
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

#endif