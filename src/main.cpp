#include <Arduino.h>
#include "config.h"

#include <Wire.h>
#include <SendOnlySoftwareSerial.h>

#include "ServoEasing.hpp"

// SoftSerials
#ifdef DOME_MASTER
SendOnlySoftwareSerial Serial_MP3   = SendOnlySoftwareSerial(P_MP3);
SendOnlySoftwareSerial Serial_Slave = SendOnlySoftwareSerial(P_SLAVE);
#endif

#ifdef DOME_SLAVE
SendOnlySoftwareSerial Serial_Teeces  = SendOnlySoftwareSerial(P_TEECES);
SendOnlySoftwareSerial Serial_Magic   = SendOnlySoftwareSerial(P_MAGIC);
#endif

#ifdef BODY_MASTER
SendOnlySoftwareSerial Serial_MP3     = SendOnlySoftwareSerial(P_MP3);
SendOnlySoftwareSerial Serial_Slave   = SendOnlySoftwareSerial(P_SLAVE);
#endif

void setup() {
  // put your setup code here, to run once:
  // Serial Port
  Serial.begin(SERIAL_BAUD);
  while(!Serial);

  Serial.println(PRODUCT);
  Serial.println("Version " VERSION);
  Serial.println();
  Serial.println();

  // Module Communications
  #ifdef DOME_MASTER
  Serial_Slave.begin(SERIAL_SLAVE_BAUD);
  Serial_Slave.println("To Slave");

  Serial_MP3.begin(SERIAL_MP3_BAUD);
  Serial_MP3.println("To MP3");
  #endif

  #ifdef DOME_SLAVE
  Serial_Teeces.begin(SERIAL_TEECES_BAUD);
  Serial_Teeces.println("To Teeces");

  Serial_Magic.begin(SERIAÖ_MAGIC_BAUD);
  Serial_Magic.println("To Magic");
  #endif
  
  #ifdef BODY_MASTER
  Serial_Slave.begin(SERIAL_SLAVE_BAUD);
  Serial_Slave.println("To Slave");

  Serial_MP3.begin(SERIAL_MP3_BAUD);
  Serial_MP3.println("To MP3");
  #endif
  // I2C
  Wire.begin();

  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(17, LOW);
  delay(1000);
  digitalWrite(17, HIGH);
  delay(1000);
}
