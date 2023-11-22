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
    return EEPROM.read(ADDR_STARTUPSOUNDNR);
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
    return EEPROM.read(ADDR_DISABLERANDOMSOUND);
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
    return EEPROM.read(ADDR_MAXRANDOMPAUSE);
}

void MarcDuinoStorage::setMaxRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MAXRANDOMPAUSE, seconds);
}

byte MarcDuinoStorage::getMinRandomPause()
{
    return EEPROM.read(ADDR_MINRANDOMPAUSE);
}

void MarcDuinoStorage::setMinRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MINRANDOMPAUSE, seconds);
}

void MarcDuinoStorage::setIndividualSettings(const byte choice)
{
    if (choice > 1)
        return;
    EEPROM.update(ADDR_INDIVIDUALS, choice);
}

byte MarcDuinoStorage::getIndividualSettings()
{
    return EEPROM.read(ADDR_INDIVIDUALS);
}

//
// Panels / Servos
// 
byte MarcDuinoStorage::getServoDirection(const byte ServoNr)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    return EEPROM.read(ADDR_SERVODIRBASE+ServoNr);
}   
void MarcDuinoStorage::setServoDirection(const byte ServoNr, const byte Direction)
{
    if ((ServoNr > MAX_MARCUDINOSERVOS) || (Direction > 1))
        return;
    EEPROM.update(ADDR_SERVODIRBASE+ServoNr, Direction);
}

byte MarcDuinoStorage::getServoSpeed(const byte ServoNr)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    return EEPROM.read(ADDR_SERVOSPEEDBASE+ServoNr);
}
void MarcDuinoStorage::setServoSpeed(const byte ServoNr, const byte Speed)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;
    EEPROM.update(ADDR_SERVOSPEEDBASE+ServoNr, Speed);
}

void MarcDuinoStorage::getServoPositions(const byte ServoNr, word & OpenPosition, word & ClosedPosition)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.get(ADDR_SERVOOPENBASE+(ServoNr*2), OpenPosition);
    EEPROM.get(ADDR_SERVOCLOSEDBASE+(ServoNr*2), ClosedPosition);
}
void MarcDuinoStorage::setServoPositions(const byte ServoNr, const word OpenPosition, const word ClosedPosition)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.put(ADDR_SERVOOPENBASE+(ServoNr*2), OpenPosition);
    EEPROM.put(ADDR_SERVOCLOSEDBASE+(ServoNr*2), ClosedPosition);
}

//
// Holos / Servos
//
void MarcDuinoStorage::getHoloDirection(const byte HoloNr, byte & HDirection, byte & VDirection)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.get(ADDR_HOLODIRBASE+(HoloNr*2), HDirection);
    EEPROM.get(ADDR_HOLODIRBASE+1+(HoloNr*2), VDirection);
}
void MarcDuinoStorage::setHoloDirection(const byte HoloNr, const byte HDirection, const byte VDirection)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLODIRBASE+(HoloNr*2), HDirection);
    EEPROM.put(ADDR_HOLODIRBASE+1+(HoloNr*2), VDirection);
}

void MarcDuinoStorage::getHoloServoSpeed(const byte HoloNr, byte & HSpeed, byte & VSpeed)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.get(ADDR_HOLOSPEEDBASE+(HoloNr*2), HSpeed);
    EEPROM.get(ADDR_HOLOSPEEDBASE+1+(HoloNr*2), VSpeed);
}
void MarcDuinoStorage::setHoloServoSpeed(const byte HoloNr, const byte HSpeed, const byte VSpeed)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOSPEEDBASE+(HoloNr*2), HSpeed);
    EEPROM.put(ADDR_HOLOSPEEDBASE+1+(HoloNr*2), VSpeed);
}

void MarcDuinoStorage::getHoloPositions(const byte HoloNr, word & HMin, word & HMax, word & VMin, word & VMax)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.get(ADDR_HOLOMINBASE+(HoloNr*4), HMin);
    EEPROM.get(ADDR_HOLOMINBASE+2+(HoloNr*4), VMin);
    EEPROM.get(ADDR_HOLOMAXBASE+(HoloNr*4), HMax);
    EEPROM.get(ADDR_HOLOMAXBASE+2+(HoloNr*4), VMax);
}
void MarcDuinoStorage::setHoloPositions(const byte HoloNr, const word HMin, const word HMax, const word VMin, const word VMax)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOMINBASE+(HoloNr*4), HMin);
    EEPROM.put(ADDR_HOLOMINBASE+2+(HoloNr*4), VMin);
    EEPROM.put(ADDR_HOLOMAXBASE+(HoloNr*4), HMax);
    EEPROM.put(ADDR_HOLOMAXBASE+2+(HoloNr*4), VMax);
}

bool MarcDuinoStorage::getHoloLightHighActive(const byte HoloNr)
{
    bool HighActive = true;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return HighActive;

    EEPROM.get(ADDR_HOLOLIGHTBASE+HoloNr, HighActive);
    return HighActive;
}

void MarcDuinoStorage::setHoloLightHighActive(const byte HoloNr, const bool HighActive)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;
        
    if (HoloNr == 0)
    {
        EEPROM.put(ADDR_HOLOLIGHTBASE+1, HighActive);
        EEPROM.put(ADDR_HOLOLIGHTBASE+2, HighActive);
        EEPROM.put(ADDR_HOLOLIGHTBASE+3, HighActive);
    }
    else
        EEPROM.put(ADDR_HOLOLIGHTBASE+HoloNr, HighActive);
}

bool MarcDuinoStorage::getAdjustmentMode()
{
    return (EEPROM.read(ADDR_ADJUSTMENT) == 0x01);
}

void MarcDuinoStorage::setAdjustmentMode(const bool on)
{
    if (on)
        EEPROM.write(ADDR_ADJUSTMENT, 0x01);
    else
        EEPROM.write(ADDR_ADJUSTMENT, 0x00);
}

void MarcDuinoStorage::dumpToSerial(const byte Address)
{
    Serial.printf(F("%04X: %02X\r\n"), Address, EEPROM.read(Address));
    /*
    for (unsigned int uiAddress=0; uiAddress < EEPROM.length(); uiAddress+=8)
    {
        char content[128];
        sprintf(content, "%04X: %02X %02X %02X %02X %02X %02X %02X %02X", uiAddress, EEPROM.read(uiAddress), EEPROM.read(uiAddress+1), EEPROM.read(uiAddress+2), EEPROM.read(uiAddress+3), EEPROM.read(uiAddress+4), EEPROM.read(uiAddress+5), EEPROM.read(uiAddress+6), EEPROM.read(uiAddress+7));
      	Serial.println(content);
    }
    */
}
