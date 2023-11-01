#include <Arduino.h>
#include <EEPROM.h>
#include <stdio.h>

#include "MarcDuinoStorage.h"
#include "config.h"

MarcDuinoStorage::MarcDuinoStorage()
{

}

byte MarcDuinoStorage::getConfigVersion()
{
    return EEPROM.read(ADDR_MARCDUINOVERSION);
}

void MarcDuinoStorage::setConfigVersion(const byte version)
{
    EEPROM.update(ADDR_MARCDUINOVERSION, version);
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

bool MarcDuinoStorage::getChattyMode()
{
    uint8_t value = EEPROM.read(ADDR_CHATTYMODE);
    if (value == 0)
        return true;
    else if (value == 1)
        return false;
    else
    {
        setChattyMode();
        return true;
    }
}

void MarcDuinoStorage::setChattyMode(const bool on/* = true*/)
{
    if (on)
        EEPROM.update(ADDR_CHATTYMODE, 0x00);
    else
        EEPROM.update(ADDR_CHATTYMODE, 0x01);
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

byte MarcDuinoStorage::getMaxSound(const byte bank)
{
    uint8_t value = 0;
    
    if (bank > MAX_SOUND_BANK)
        return 1;   // Invalid Bank, but one will be there

    value = EEPROM.read(ADDR_MAXSONGSBASE + bank);

    // One bank has the maximum of 25 Songs
    if (value > MAX_BANK_SOUND)
        return 1;   // Invalid Sound, but one will be there
    else
        return value;
}

void MarcDuinoStorage::setMaxSound(const byte bank, const byte SongNr)
{
    EEPROM.update(ADDR_MAXSONGSBASE + bank, SongNr);
}

byte MarcDuinoStorage::getMaxRandomPause()
{
    uint8_t value = 0;
    value = EEPROM.read(ADDR_MAXRANDOMPAUSE);
    return value;
}

void MarcDuinoStorage::setMaxRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MAXRANDOMPAUSE, seconds);
}

byte MarcDuinoStorage::getMinRandomPause()
{
    uint8_t value = 0;
    value = EEPROM.read(ADDR_MINRANDOMPAUSE);
    return value;
}

void MarcDuinoStorage::setMinRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MINRANDOMPAUSE, seconds);
}

byte MarcDuinoStorage::getServoDirection(const byte ServoNr)
{
    uint8_t value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    value = EEPROM.read(ADDR_SERVODIRBASE+ServoNr);
    return value;
}

void MarcDuinoStorage::setServoDirection(const byte ServoNr, const byte Direction)
{
    if ((ServoNr > MAX_MARCUDINOSERVOS) || (Direction > 1))
        return;
    EEPROM.update(ADDR_SERVODIRBASE+ServoNr, Direction);
}

byte MarcDuinoStorage::getServoSpeed(const byte ServoNr)
{
    uint8_t value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    value = EEPROM.read(ADDR_SERVOSPEEDBASE+ServoNr);
    return value;
}

void MarcDuinoStorage::setServoSpeed(const byte ServoNr, const byte Speed)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;
    EEPROM.update(ADDR_SERVOSPEEDBASE+ServoNr, Speed);
}

byte MarcDuinoStorage::getServoOpenPosDeg(const byte ServoNr)
{
    uint8_t value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    value = EEPROM.read(ADDR_SERVOOPENBASE+ServoNr);
    return value;
}

void MarcDuinoStorage::setServoOpenPosDeg(const byte ServoNr, const byte Position)
{
    if ((ServoNr > MAX_MARCUDINOSERVOS) || (Position > 180))
        return;
    EEPROM.update(ADDR_SERVOOPENBASE+ServoNr, Position);
}

byte MarcDuinoStorage::getServoCosedPosDeg(const byte ServoNr)
{
    uint8_t value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    value = EEPROM.read(ADDR_SERVOCLOSEDBASE+ServoNr);
    return value;
}

void MarcDuinoStorage::setServoClosedPosDeg(const byte ServoNr, const byte Position)
{
    if ((ServoNr > MAX_MARCUDINOSERVOS) || (Position > 180))
        return;
    EEPROM.update(ADDR_SERVOCLOSEDBASE+ServoNr, Position);
}

byte MarcDuinoStorage::getServoMidPosDeg(const byte ServoNr)
{
    uint8_t value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    value = EEPROM.read(ADDR_SERVOMIDBASE+ServoNr);
    return value;
}

void MarcDuinoStorage::setServoMidPosDeg(const byte ServoNr, const byte Position)
{
    if ((ServoNr > MAX_MARCUDINOSERVOS) || (Position > 180))
        return;
    EEPROM.update(ADDR_SERVOMIDBASE+ServoNr, Position);
}

void MarcDuinoStorage::dumpToSerial()
{
    for (unsigned int uiAddress=0; uiAddress < EEPROM.length(); uiAddress+=8)
    {
        char content[128];
        sprintf(content, "%04X: %02X %02X %02X %02X %02X %02X %02X %02X", uiAddress, EEPROM.read(uiAddress), EEPROM.read(uiAddress+1), EEPROM.read(uiAddress+2), EEPROM.read(uiAddress+3), EEPROM.read(uiAddress+4), EEPROM.read(uiAddress+5), EEPROM.read(uiAddress+6), EEPROM.read(uiAddress+7));
      	Serial.println(content);
    }
}
