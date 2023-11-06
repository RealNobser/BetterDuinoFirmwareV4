#include"MarcDuinoBodyMaster.h"

MarcDuinoBodyMaster::MarcDuinoBodyMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13):
    MarcDuinoDomeMaster(Serial_Slave, Serial_MP3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13)
{

}

void MarcDuinoBodyMaster::init()
{
    MarcDuinoDomeMaster::init();
}

void MarcDuinoBodyMaster::run()
{
    MarcDuinoDomeMaster::run();
}

void MarcDuinoBodyMaster::playSequenceAddons(const unsigned int SeqNr)
{
    // Also forward to Slave
    Serial_Slave.printf(F(":SE%2d\r"), SeqNr);

    // Disable Servo detach during Animations
    ServoBuzzIntervall = 0;
    Sequencer.addSequenceCompletionCallback(sequenceCallbackBuzz);

    switch (SeqNr)
    {
        case 30:
            parseCommand("*MF04");      // Magic Flicker for 4 seconds
        break;    
        case 31:
        break;    
        case 32:
        break;    
        case 33:
        break;    
        case 34:
        break;    
        case 35:
        break;    
    }

    // Finally GOOOOO
    Sequencer.startSequence();
}