#include"MarcDuinoBodyMaster.h"

MarcDuinoBodyMaster::MarcDuinoBodyMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13):
    MarcDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13),
    Serial_Slave(Serial_Slave),
    Serial_MP3(Serial_MP3)
{
  Serial_Slave.begin(SERIAL_SLAVE_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
  while(!Serial_Slave);

  Serial_MP3.begin(SERIAL_MP3_BAUD); // TODO: Depends on Board Type (Master, Slave, Body)
  while(!Serial_MP3);
}

void MarcDuinoBodyMaster::init()
{
    MarcDuinoBase::init();
}

void MarcDuinoBodyMaster::run()
{
    MarcDuinoBase::run();
}

void MarcDuinoBodyMaster::parseCommand(const char* command)
{
    switch (command[0])
    {
    case ':':
        break;
    case '*':
        break;
    case '@':
        break;
    case '$':
        break;
    case '!':
        break;
    case '%':
        break;
    case '#':
        break;    
    default:
        break;
    }        
}

void MarcDuinoBodyMaster::playSequenceAddons(const unsigned int SeqNr)
{
}