#include"MarcDuinoBodyMaster.h"

MarcDuinoBodyMaster::MarcDuinoBodyMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11):
    MarcDuinoBase(Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11),
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

    // Soft Serials
    #ifdef DEBUG
    Serial_Slave.println("To Slave");
    Serial_MP3.println("To MP3");
    #endif
}

void MarcDuinoBodyMaster::run()
{
    MarcDuinoBase::run();
}

void MarcDuinoBodyMaster::checkEEPROM()
{
    
}

void MarcDuinoBodyMaster::parseCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("Command(Body): ");
    Serial.println((char*)command);
    #endif

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