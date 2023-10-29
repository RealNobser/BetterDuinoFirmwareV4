
#include "MarcDuinoBase.h"

MarcDuinoBase::MarcDuinoBase(VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
                             VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, VarSpeedServo& Servo11) :
    Servo1(Servo1), Servo2(Servo2), Servo3(Servo3), Servo4(Servo4), Servo5(Servo5), 
    Servo6(Servo6), Servo7(Servo7), Servo8(Servo8), Servo9(Servo9), Servo10(Servo10), Servo11(Servo11) 
{

}

void MarcDuinoBase::init()
{
    // I2C
    // Wire.begin();

    // HeartBeat-LED
    pinMode(P_LED2, OUTPUT);
    digitalWrite(P_LED2, HeartBeatStatus);

    HeartBeatMillis = millis();

    memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
}

void MarcDuinoBase::run()
{
    // Read Serial
    if (Serial.available())
    {
        unsigned char c = Serial.read();
        SerialBuffer[BufferIndex++] = c;
        if ((c == '\r') || (BufferIndex == SERIALBUFFERSIZE))   // Command complete or buffer full
        {
            SerialBuffer[BufferIndex-1] = 0x00; // ensure proper termination
            parseCommand(SerialBuffer);
            memset(SerialBuffer, 0x00, SERIALBUFFERSIZE);
            BufferIndex = 0;
        }
    }

    // Heartbeat
    if ((millis() - HeartBeatMillis) > HEARTBEAT_MILLIS)
    {
        toggleHeartBeat();
        HeartBeatMillis = millis();
    }
}

void MarcDuinoBase::toggleHeartBeat()
{
    #ifdef DEBUG
    // Serial.print(".");
    #endif

    if (HeartBeatStatus == LOW)
      HeartBeatStatus = HIGH;
    else
      HeartBeatStatus = LOW;

    digitalWrite(P_LED2, HeartBeatStatus);
}

void MarcDuinoBase::processSetupCommand(const char* command)
{
    #ifdef DEBUG
    Serial.print("SetupCommand(Base): ");
    Serial.println((char*)command);
    #endif
}
