#include "MDuinoDomeMasterChopper.h"
#include "PanelSequences.h"

#ifdef CHOPPER

MDuinoDomeMasterChopper::MDuinoDomeMasterChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11):
    MDuinoDomeMaster(Serial_Slave, Serial_MP3, Serial_Lift, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11)
{
    SequencePlayer = new MDuinoDomeSequencePlayerChopper(Sequencer);
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

void MDuinoDomeMasterChopper::playSequenceAddons(const byte SeqNr)
{
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

#endif