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

word MarcDuinoStorage::getServoOpenPos(const byte ServoNr)
{
    word value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return value;
    EEPROM.get(ADDR_SERVOOPENBASE+(ServoNr*2), value);
    return value;
}
void MarcDuinoStorage::setServoOpenPos(const byte ServoNr, const word Position)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.put(ADDR_SERVOOPENBASE+(ServoNr*2), Position);
}

word MarcDuinoStorage::getServoClosedPos(const byte ServoNr)
{
    word value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return value;
    EEPROM.get(ADDR_SERVOCLOSEDBASE+(ServoNr*2), value);
    return value;
}
void MarcDuinoStorage::setServoClosedPos(const byte ServoNr, const word Position)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.put(ADDR_SERVOCLOSEDBASE+(ServoNr*2), Position);
}

word MarcDuinoStorage::getServoMidPos(const byte ServoNr)
{
    word value = 0;
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return value;
    EEPROM.get(ADDR_SERVOMIDBASE+(ServoNr*2), value);
    return value;
}
void MarcDuinoStorage::setServoMidPos(const byte ServoNr, const word Position)
{
    if (ServoNr > MAX_MARCUDINOSERVOS)
        return;

    EEPROM.put(ADDR_SERVOMIDBASE+(ServoNr*2), Position);
}



byte MarcDuinoStorage::getHoloHDirection(const byte HoloNr)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return 0;

    return EEPROM.read(ADDR_HOLODIRBASE+(HoloNr*2));        

}
void MarcDuinoStorage::setHoloHDirection(const byte HoloNr, const byte Direction)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.update(ADDR_HOLODIRBASE+(HoloNr*2), Direction);
}

byte MarcDuinoStorage::getHoloVDirection(const byte HoloNr)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return 0;

    return EEPROM.read((ADDR_HOLODIRBASE+1)+(HoloNr*2));        
}
void MarcDuinoStorage::setHoloVDirection(const byte HoloNr, const byte Direction)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.update((ADDR_HOLODIRBASE+1)+(HoloNr*2), Direction);
}

word MarcDuinoStorage::getHoloHMinPos(const byte HoloNr)
{
    word value = 0;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return value;

    EEPROM.get(ADDR_HOLOMINBASE+(HoloNr*2), value);

    return value;

}
void MarcDuinoStorage::setHoloHMinPos(const byte HoloNr, const word Position)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOMINBASE+(HoloNr*2), Position);
}

word MarcDuinoStorage::getHoloHMaxPos(const byte HoloNr)
{
    word value = 0;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return value;

    EEPROM.get(ADDR_HOLOMAXBASE+(HoloNr*2), value);

    return value;  
}
void MarcDuinoStorage::setHoloHMaxPos(const byte HoloNr, const word Position)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put(ADDR_HOLOMAXBASE+(HoloNr*2), Position);
}

word MarcDuinoStorage::getHoloVMinPos(const byte HoloNr)
{
    word value = 0;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return value;

    EEPROM.get((ADDR_HOLOMINBASE+1)+(HoloNr*2), value);

    return value;
}
void MarcDuinoStorage::setHoloVMinPos(const byte HoloNr, const word Position)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put((ADDR_HOLOMINBASE+1)+(HoloNr*2), Position);
}

word MarcDuinoStorage::getHoloVMaxPos(const byte HoloNr)
{
    word value = 0;

    if (HoloNr > MAX_MARCDUINOHOLOS)
        return value;

    EEPROM.get((ADDR_HOLOMAXBASE+1)+(HoloNr*2), value);

    return value;
}
void MarcDuinoStorage::setHoloVMaxPos(const byte HoloNr, const word Position)
{
    if (HoloNr > MAX_MARCDUINOHOLOS)
        return;

    EEPROM.put((ADDR_HOLOMAXBASE+1)+(HoloNr*2), Position);
}

bool MarcDuinoStorage::getHoloLightHighActive(const byte HoloNr)
{
    bool HighActive = true;
    EEPROM.get(ADDR_HOLOLIGHTBASE+HoloNr, HighActive);
    return HighActive;
}

void MarcDuinoStorage::setHoloLightHighActive(const byte HoloNr, const bool HighActive)
{
    if (HoloNr > 3)
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
