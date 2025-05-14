#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "MDuinoStorage.h"

#if defined(R2D2)
#include "MDuinoDomeMasterR2.h"
#include "MDuinoDomeSlaveR2.h"
#include "MDuinoBodyMasterR2.h"
#elif defined(CHOPPER)
#include "MDuinoDomeMasterChopper.h"
#include "MDuinoDomeSlaveChopper.h"
#include "MDuinoBodyMasterChopper.h"
#elif defined(BT1)
#include "MDuinoDomeMasterBT1.h"
#include "MDuinoDomeSlaveBT1.h"
#include "MDuinoBodyMasterBT1.h"
#endif

MDuinoBase *MDuino = nullptr;

// Initialize common ressources in main (due to interrupts and globals)

SendOnlySoftwareSerial Serial1(P_SERIAL1); // Slave or Magic
SendOnlySoftwareSerial Serial2(P_SERIAL2); // MP3 or Teeces
#ifdef SEPARATE_DOMELIFT
SendOnlySoftwareSerial Serial3(P_AUX1); // DomeLift separate Serial
#else
#define Serial3 Serial
#endif

// 11 Servos per Board
VarSpeedServo Servo1;
VarSpeedServo Servo2;
VarSpeedServo Servo3;
VarSpeedServo Servo4;
VarSpeedServo Servo5;
VarSpeedServo Servo6;
VarSpeedServo Servo7;
VarSpeedServo Servo8;
VarSpeedServo Servo9;
VarSpeedServo Servo10;
VarSpeedServo Servo11;

#ifdef INCLUDE_I2C_SLAVE
void I2C_Callback(int count)
{
    // MarcDuinio->I2C_Callback();
    #ifdef DEBUG_MSG
    Serial.print("\rI2C\r");
    #endif
}
#endif

void setup()
{
    // put your setup code here, to run once:
    // Serial Port
    Serial.begin(SERIAL_BAUD);
    while (!Serial);

    // I2C - Master
    #ifdef INCLUDE_CLASSIC_I2C_SUPPORT
    Wire.begin();
    #endif

    MDuinoStorage Storage;
    MDuinoStorage::MDuinoType type = Storage.getType();

    switch (type)
    {
    #ifdef INCLUDE_DOME_MASTER
    case MDuinoStorage::MDuinoType::DomeMaster:
        #if defined(R2D2)
        MDuino = new MDuinoDomeMasterR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoDomeMasterChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoDomeMasterBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_DOME_MASTER);
        Wire.onReceive(I2C_Callback);
        #endif
        break;
    #endif
    #ifdef INCLUDE_DOME_SLAVE
    case MDuinoStorage::MDuinoType::DomeSlave:
        #if defined(R2D2)
        MDuino = new MDuinoDomeSlaveR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoDomeSlaveChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoDomeSlaveBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_DOME_SLAVE);
        Wire.onReceive(I2C_Callback);
        #endif
        break;
    #endif
    #ifdef INCLUDE_BODY_MASTER
    case MDuinoStorage::MDuinoType::BodyMaster:
        #if defined(R2D2)
        MDuino = new MDuinoBodyMasterR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoBodyMasterChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoBodyMasterBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_BODY_MASTER);
        Wire.onReceive(I2C_Callback);
        #endif
        break;
    #endif
    case MDuinoStorage::MDuinoType::unknown:
    default:
        #ifdef INCLUDE_DOME_MASTER

        #if defined(R2D2)
        MDuino = new MDuinoDomeMasterR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoDomeMasterChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoDomeMasterBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        Storage.setType(MDuinoStorage::MDuinoType::DomeMaster);
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_DOME_MASTER);
        Wire.onReceive(I2C_Callback);
        #endif

        #elif defined(INCLUDE_DOME_SLAVE)

        #if defined(R2D2)
        MDuino = new MDuinoDomeSlaveR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoDomeSlaveChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoDomeSlaveBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_DOME_SLAVE);
        Wire.onReceive(I2C_Callback);
        #endif

        #elif defined(INCLUDE_BODY_MASTER)

        #if defined(R2D2)
        MDuino = new MDuinoBodyMasterR2(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(CHOPPER)
        MDuino = new MDuinoBodyMasterChopper(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #elif defined(BT1)
        MDuino = new MDuinoBodyMasterBT1(Serial1, Serial2, Serial3, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11);
        #else
        #error Please include at least one astromech type in config.h
        #endif
        #ifdef INCLUDE_I2C_SLAVE
        Wire.begin(I2C_BODY_MASTER);
        Wire.onReceive(I2C_Callback);
        #endif
        #else
        #error Please include at least one role type in config.h
        #endif

        break;
    }

    MDuino->init();

    Serial.printf(F("%s\r\nV%s\r\n\r\n"), MDuino->getProductName(), VERSION);
}

void loop()
{
    // put your main code here, to run repeatedly:
    MDuino->run();
}
