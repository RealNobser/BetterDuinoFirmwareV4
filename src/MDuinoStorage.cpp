#include <Arduino.h>
#include <EEPROM.h>
#include <stdio.h>

#include "MDuinoStorage.h"
#include "config.h"

MDuinoStorage::MDuinoStorage()
{

}

byte MDuinoStorage::getConfigVersion()
{
    return EEPROM.read(ADDR_MDUINOVERSION);
}

void MDuinoStorage::setConfigVersion(const byte version)
{
    EEPROM.update(ADDR_MDUINOVERSION, version);
}

MDuinoStorage::MDuinoType MDuinoStorage::getType()
{
    uint8_t value = EEPROM.read(ADDR_MDUINOTYPE);

    if (value >= (uint8_t)MDuinoType::unknown)
        return MDuinoType::unknown;
    else
        return (MDuinoType)value;
}

void MDuinoStorage::setType(const MDuinoType type)
{
    EEPROM.update(ADDR_MDUINOTYPE, (uint8_t)type);
}


MDuinoStorage::MDuinoMP3PlayerType MDuinoStorage::getMP3Player()
{
    uint8_t value = EEPROM.read(ADDR_MDUINOMP3PLAYER);

    if (value > (uint8_t)MDuinoMP3PlayerType::unknown)
        return MDuinoMP3PlayerType::unknown;
    else
        return (MDuinoMP3PlayerType)value;
}

void MDuinoStorage::setMP3Player(const MDuinoMP3PlayerType type)
{
    EEPROM.update(ADDR_MDUINOMP3PLAYER, (uint8_t)type);
}

byte MDuinoStorage::getStartupSoundNr()
{
    return EEPROM.read(ADDR_STARTUPSOUNDNR);
}

void MDuinoStorage::setStartupSoundNr(const byte SoundNr)
{
    EEPROM.update(ADDR_STARTUPSOUNDNR, SoundNr);
}

byte MDuinoStorage::getDisableRandomSound()
{
    return EEPROM.read(ADDR_DISABLERANDOMSOUND);
}

void MDuinoStorage::setDisableRandomSound(const byte DisableRandomSound)
{
    EEPROM.update(ADDR_DISABLERANDOMSOUND, DisableRandomSound);
}

byte MDuinoStorage::getMaxSound(const byte bank)
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

void MDuinoStorage::setMaxSound(const byte bank, const byte SongNr)
{
    EEPROM.update(ADDR_MAXSONGSBASE + bank, SongNr);
}

byte MDuinoStorage::getMaxRandomPause()
{
    return EEPROM.read(ADDR_MAXRANDOMPAUSE);
}

void MDuinoStorage::setMaxRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MAXRANDOMPAUSE, seconds);
}

byte MDuinoStorage::getMinRandomPause()
{
    return EEPROM.read(ADDR_MINRANDOMPAUSE);
}

void MDuinoStorage::setMinRandomPause(const byte seconds)
{
    EEPROM.update(ADDR_MINRANDOMPAUSE, seconds);
}


byte MDuinoStorage::getServoInit()
{
    return EEPROM.read(ADDR_SERVOBINITBASE);
}

void MDuinoStorage::setServoInit(const byte init)
{
    EEPROM.update(ADDR_SERVOBINITBASE, init);
}

//
// Panels / Servos
// 

byte MDuinoStorage::getServoSpeed(const byte ServoNr)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return 0;
    return EEPROM.read(ADDR_SERVOSPEEDBASE+ServoNr);
}
void MDuinoStorage::setServoSpeed(const byte ServoNr, const byte Speed)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;
    EEPROM.update(ADDR_SERVOSPEEDBASE+ServoNr, Speed);
}

void MDuinoStorage::getServoPositions(const byte ServoNr, word & OpenPosition, word & ClosedPosition)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.get(ADDR_SERVOOPENBASE+(ServoNr*2), OpenPosition);
    EEPROM.get(ADDR_SERVOCLOSEDBASE+(ServoNr*2), ClosedPosition);
}
void MDuinoStorage::setServoPositions(const byte ServoNr, const word OpenPosition, const word ClosedPosition)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.put(ADDR_SERVOOPENBASE+(ServoNr*2), OpenPosition);
    EEPROM.put(ADDR_SERVOCLOSEDBASE+(ServoNr*2), ClosedPosition);
}

//
// Holos / Servos
//
bool MDuinoStorage::getHoloNeoPixel(const byte HoloNr)
{
    bool value = false;

    if (HoloNr > MAX_MDUINOHOLOS)
        return false;

    EEPROM.get(ADDR_HOLOLIGHTBASE + 3 + HoloNr, value);
    return value;
}
void MDuinoStorage::setHoloNeoPixel(const byte HoloNr, const bool NeoPixel)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    if (HoloNr == 0)
    {
        EEPROM.put(ADDR_HOLOLIGHTBASE + 3 + 1, NeoPixel);
        EEPROM.put(ADDR_HOLOLIGHTBASE + 3 + 2, NeoPixel);
        EEPROM.put(ADDR_HOLOLIGHTBASE + 3 + 3, NeoPixel);
    }
    else
        EEPROM.put(ADDR_HOLOLIGHTBASE + 3 + HoloNr, NeoPixel);
}

byte MDuinoStorage::getHoloLEDs(const byte HoloNr)
{
    uint8_t value = 7;

    if (HoloNr > MAX_MDUINOHOLOS)
        return 0;

    value = EEPROM.read(ADDR_HOLOLIGHTBASE + 6 + HoloNr);
    return value;
}
void MDuinoStorage::setHoloLEDs(const byte HoloNr, const byte LEDs)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    EEPROM.update(ADDR_HOLOLIGHTBASE + 6 + HoloNr, LEDs);
}

void MDuinoStorage::getHoloServoSpeed(const byte HoloNr, byte & HSpeed, byte & VSpeed)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    EEPROM.get(ADDR_HOLOSPEEDBASE+(HoloNr*2), HSpeed);
    EEPROM.get(ADDR_HOLOSPEEDBASE+1+(HoloNr*2), VSpeed);
}
void MDuinoStorage::setHoloServoSpeed(const byte HoloNr, const byte HSpeed, const byte VSpeed)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOSPEEDBASE+(HoloNr*2), HSpeed);
    EEPROM.put(ADDR_HOLOSPEEDBASE+1+(HoloNr*2), VSpeed);
}

void MDuinoStorage::getHoloPositions(const byte HoloNr, word & HMin, word & HMax, word & VMin, word & VMax)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    EEPROM.get(ADDR_HOLOMINBASE+(HoloNr*4), HMin);
    EEPROM.get(ADDR_HOLOMINBASE+2+(HoloNr*4), VMin);
    EEPROM.get(ADDR_HOLOMAXBASE+(HoloNr*4), HMax);
    EEPROM.get(ADDR_HOLOMAXBASE+2+(HoloNr*4), VMax);
}
void MDuinoStorage::setHoloPositions(const byte HoloNr, const word HMin, const word HMax, const word VMin, const word VMax)
{
    if (HoloNr > MAX_MDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOMINBASE+(HoloNr*4), HMin);
    EEPROM.put(ADDR_HOLOMINBASE+2+(HoloNr*4), VMin);
    EEPROM.put(ADDR_HOLOMAXBASE+(HoloNr*4), HMax);
    EEPROM.put(ADDR_HOLOMAXBASE+2+(HoloNr*4), VMax);
}

bool MDuinoStorage::getHoloLightHighActive(const byte HoloNr)
{
    bool HighActive = true;

    if (HoloNr > MAX_MDUINOHOLOS)
        return HighActive;

    EEPROM.get(ADDR_HOLOLIGHTBASE+HoloNr, HighActive);
    return HighActive;
}

void MDuinoStorage::setHoloLightHighActive(const byte HoloNr, const bool HighActive)
{
    if (HoloNr > MAX_MDUINOHOLOS)
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

#ifdef DEBUG_MSG
void MDuinoStorage::dumpToSerial(const byte Address)
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
#endif