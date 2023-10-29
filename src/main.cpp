#include <Arduino.h>
#include "config.h"
#include "MarcDuinos.h"

#ifdef DOME_MASTER
MarcDuinoDomeMaster MarcDuino;
#endif

#ifdef DOME_SLAVE
MarcDuinoDomeSlave MarcDuino;
#endif

#ifdef BODY_MASTER
MarcDuinoBody MarcDuino;
#endif



void setup() {
  // put your setup code here, to run once:
  // Serial Port
  Serial.begin(SERIAL_BAUD);
  while(!Serial);

  Serial.println(PRODUCT);
  Serial.println("Version " VERSION);
  Serial.println();

  MarcDuino.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  MarcDuino.run();
}
