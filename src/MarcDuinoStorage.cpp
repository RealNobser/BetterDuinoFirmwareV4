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
    if (value > MarcDuinoType::UnknownMarcDuino)
        return MarcDuinoType::UnknownMarcDuino;
    else
        return (MarcDuinoType)value;
}

void MarcDuinoStorage::setType(const MarcDuinoType type)
{
    EEPROM.update(ADDR_MARCDUINOTYPE, type);
}


MarcDuinoStorage::MarcDuinoMP3PlayerType MarcDuinoStorage::getMP3Player()
{
    uint8_t value = EEPROM.read(ADDR_MARCDUINOMP3PLAYER);
    if (value > MarcDuinoMP3PlayerType::UnknownPlayer)
        return MarcDuinoMP3PlayerType::UnknownPlayer;
    else
        return (MarcDuinoMP3PlayerType)value;
}

void MarcDuinoStorage::setMP3Player(const MarcDuinoMP3PlayerType type)
{
    EEPROM.update(ADDR_MARCDUINOMP3PLAYER, type);
}


byte MarcDuinoStorage::getStartupSound()
{
    uint8_t value = EEPROM.read(ADDR_STARTUPSOUND);
    switch (value)
    {
    case 0:
        return 0;
        break;
    case 1:
        return 255;
        break;
    case 2:
        return 254;
        break;
    case 3:
        return 253;
        break;
    default:
        return 255;
        break;
    }
}

void MarcDuinoStorage::setStartupSound(const byte SoundNr)
{
    switch (SoundNr)
    {
    case 0:
        EEPROM.update(ADDR_STARTUPSOUND, 0);
        break;
    case 1:
        EEPROM.update(ADDR_STARTUPSOUND, 255);
        break;
    case 2:
        EEPROM.update(ADDR_STARTUPSOUND, 254);
        break;
    case 3:
        EEPROM.update(ADDR_STARTUPSOUND, 253);
        break;
    default:
        EEPROM.update(ADDR_STARTUPSOUND, 255);
        break;
    }
}

byte MarcDuinoStorage::getStartupSoundNr()
{
    uint8_t value = EEPROM.read(ADDR_STARTUPSOUNDNR);
    return value;
}

void MarcDuinoStorage::setStartupSoundNr(const byte SoundNr)
{
    EEPROM.update(ADDR_STARTUPSOUNDNR, SoundNr);
}

byte MarcDuinoStorage::getDisableRandomSound()
{
    uint8_t value = EEPROM.read(ADDR_DISABLERANDOMSOUND);
    return value;
}

void MarcDuinoStorage::setDisableRandomSound(const byte DisableRandomSound)
{
    EEPROM.update(ADDR_DISABLERANDOMSOUND, DisableRandomSound);
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
