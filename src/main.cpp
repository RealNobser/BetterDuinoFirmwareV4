#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "MDuinoBase.h"
#include "MDuinoDome.h"
#include "MDuinoDomeMaster.h"
#include "MDuinoDomeSlave.h"
#include "MDuinoBodyMaster.h"
#include "MDuinoStorage.h"

MDuinoBase* MarcDuino = nullptr;

// Initialize common ressources in main (due to interrupts and globals)

SendOnlySoftwareSerial Serial1(P_SERIAL1);  // Slave or Magic
SendOnlySoftwareSerial Serial2(P_SERIAL2);  // MP3 or Teeces

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
VarSpeedServo Servo12;
VarSpeedServo Servo13;

void setup() {
  // put your setup code here, to run once:
  // Serial Port
  Serial.begin(SERIAL_BAUD);
  while(!Serial);

  // I2C - Master
  Wire.begin();

  MDuinoStorage Storage;

  #if defined(DEDICATED_FIRMWARE)
    #if defined(DEDICATED_MASTER)
      MarcDuino = new MDuinoDomeMaster(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
    #elif defined(DEDICATED_SLAVE)
      MarcDuino = new MDuinoDomeSlave(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
    #elif defined (DEDICATED_BODY)    
      MarcDuino = new MDuinoBodyMaster(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
    #endif
  #else

  MDuinoStorage::MDuinoType type;
  type = Storage.getType();

  switch (type)
  {
    case MDuinoStorage::DomeMaster:
      MarcDuino = new MDuinoDomeMaster(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
      break;
    case MDuinoStorage::DomeSlave:
      MarcDuino = new MDuinoDomeSlave(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
      break;
  #ifdef INCLUDE_BODY_MASTER
    case MDuinoStorage::BodyMaster:
      MarcDuino = new MDuinoBodyMaster(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
      break;
  #endif
    case MDuinoStorage::UnknownMarcDuino:
    default:
      MarcDuino = new MDuinoDomeMaster(Serial1, Serial2, Servo1, Servo2, Servo3, Servo4, Servo5, Servo6, Servo7, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13);
      Storage.setType(MDuinoStorage::DomeMaster);    
      break;
  }
  
  #endif
  
  MarcDuino->init();

  Serial.printf(F("%s\r\nVersion %s\r\n\r\n"), MarcDuino->getProductName(), VERSION);
}

void loop() {
  // put your main code here, to run repeatedly:
  MarcDuino->run();
}
