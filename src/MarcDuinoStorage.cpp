#include <Arduino.h>
#include <EEPROM.h>
#include <stdio.h>

#include "MarcDuinoStorage.h"

MarcDuinoStorage::MarcDuinoStorage()
{

}

MarcDuinoStorage::MarcDuinoType MarcDuinoStorage::getType()
{
    uint8_t value = EEPROM.read(ADDR_MARCDUINOTYPE);
    if (value > MarcDuinoType::Unknown)
        return MarcDuinoType::Unknown;
    else
        return (MarcDuinoType)value;
}

void MarcDuinoStorage::setType(const MarcDuinoType type)
{
    EEPROM.update(ADDR_MARCDUINOTYPE, type);
}


void MarcDuinoStorage::dumpToSerial()
{
    for (unsigned int uiAddress=0; uiAddress < EEPROM.length(); uiAddress+=8)
    {
        char content[256];
        sprintf(content, "%04X: %02X %02X %02X %02X %02X %02X %02X %02X", uiAddress, EEPROM.read(uiAddress), EEPROM.read(uiAddress+1), EEPROM.read(uiAddress+2), EEPROM.read(uiAddress+3), EEPROM.read(uiAddress+4), EEPROM.read(uiAddress+5), EEPROM.read(uiAddress+6), EEPROM.read(uiAddress+7));
      	Serial.println(content);
    }
}
