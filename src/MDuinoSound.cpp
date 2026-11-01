#include "MDuinoSound.h"

MDuinoSound::MDuinoSound(SendOnlySoftwareSerial& SoundSerial, MDuinoStorage::MDuinoMP3PlayerType playerType) :
    playerType(playerType),
    SoundSerial(SoundSerial)
{
    for (uint8_t ui = 0; ui <= MAX_SOUND_BANK; ui++)
        lastSoundPlayed[ui] = 0;

    // Set default volume per player type
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            CurrentVolume = 0x20;   // Medium (0x00=max, 0x40=min)
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            CurrentVolume = 15;     // Medium (0-30)
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            CurrentVolume = 50;     // Medium (0-100)
            break;
        default:
            CurrentVolume = 0x20;
            break;
    }
}

void MDuinoSound::init()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            VolumeMid();
            break;

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
            sendDFCommand(0x09, 0x00, 0x01);    // Playback Source TF
            delay(500);
            sendDFCommand(0x07, 0x00, 0x00);    // EQ Normal
            delay(100);
            VolumeMid();
            delay(100);
            break;

#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
        {
            byte cmd[] = { 0xAA, 0x1A, 0x01, 0x00 };  // EQ-Normal
            sendDYCommand(cmd, 0x04);
            delay(100);
            VolumeMid();
            delay(100);
            break;
        }
#endif

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            VolumeMid();
            break;

        default:
            VolumeMid();
            break;
    }
}

//
// Volume Control
//

void MDuinoSound::SetVolume(const byte Volume, const bool SetAsStandard /*= true*/)
{
    if (SetAsStandard)
        CurrentVolume = Volume;

    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
        {
            byte cmd[2];
            cmd[0] = 'v';       // Volume command
            cmd[1] = Volume;    // 0x00=max, >0x40=inaudible
            SoundSerial.write(cmd, 2);
            break;
        }

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
            sendDFCommand(0x06, 0x00, Volume);  // Specify Volume (0-30)
            break;

#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
        {
            byte cmd[] = { 0xAA, 0x13, 0x01, 0x00 };
            cmd[3] = Volume;
            sendDYCommand(cmd, 0x04);
            break;
        }
#endif

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SoundSerial.printf(F("<PVV%d><PVA%d><PVB%d>"), Volume, Volume, Volume);
            break;

        default:
            break;
    }
}

void MDuinoSound::VolumeUp()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            if (CurrentVolume >= 2)
            {
                CurrentVolume -= 2; // Lower value = louder
                SetVolume(CurrentVolume);
            }
            break;

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            if (CurrentVolume < 30)
            {
                CurrentVolume += 2;
                SetVolume(CurrentVolume);
            }
            break;

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            if (CurrentVolume < 100)
            {
                CurrentVolume += 5;
                SetVolume(CurrentVolume);
            }
            break;

        default:
            break;
    }
}

void MDuinoSound::VolumeDown()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            if (CurrentVolume < 0x40)
            {
                CurrentVolume += 2; // Higher value = quieter
                SetVolume(CurrentVolume);
            }
            break;

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            if (CurrentVolume >= 2)
            {
                CurrentVolume -= 2;
                SetVolume(CurrentVolume);
            }
            break;

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            if (CurrentVolume >= 5)
            {
                CurrentVolume -= 5;
                SetVolume(CurrentVolume);
            }
            break;

        default:
            break;
    }
}

void MDuinoSound::VolumeMid()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            SetVolume(0x20);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            SetVolume(15);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SetVolume(50);
            break;
        default:
            SetVolume(0x20);
            break;
    }
}

void MDuinoSound::VolumeMax()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            SetVolume(0x00);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            SetVolume(30);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SetVolume(100);
            break;
        default:
            SetVolume(0x00);
            break;
    }
}

void MDuinoSound::VolumeMin()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            SetVolume(0x40);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
            SetVolume(5);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SetVolume(10);
            break;
        default:
            SetVolume(0x40);
            break;
    }
}

void MDuinoSound::VolumeOff()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
            SetVolume(0xff, false);
            break;
        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
#endif
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SetVolume(0, false);
            break;
        default:
            SetVolume(0xff, false);
            break;
    }
}

void MDuinoSound::VolumeStandard()
{
    SetVolume(CurrentVolume);
}

//
// Playback Control
//

void MDuinoSound::Play(const byte SoundNr)
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
        {
            byte cmd[2];
            cmd[0] = 't';          // trigger
            cmd[1] = SoundNr;      // sound "NNNxxxx.MP3"
            SoundSerial.write(cmd, 2);
            break;
        }

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
            sendDFCommand(0x12, 0x00, SoundNr); // Playback
            break;

#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
        {
            byte cmd[] = { 0xAA, 0x07, 0x02, 0x00, 0x00 };
            cmd[4] = SoundNr;
            sendDYCommand(cmd, 0x05);
            break;
        }
#endif

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SoundSerial.printf(F("<CA%04d>"), SoundNr);
            break;

        default:
            break;
    }
}

void MDuinoSound::Play(const byte BankNr, const byte SoundNr)
{
    if ((BankNr == 0) || (BankNr > MAX_SOUND_BANK) || (SoundNr > MAX_BANK_SOUND))
        return;	// would wrap to a wrong track number
    byte CalcSoundNr = (BankNr - 1) * 25 + SoundNr;
    lastSoundPlayed[BankNr] = SoundNr;
    Play(CalcSoundNr);
}

void MDuinoSound::PlayNext(const byte BankNr, const byte MaxSoundNr)
{
    lastSoundPlayed[BankNr] = lastSoundPlayed[BankNr] + 1;

    if (lastSoundPlayed[BankNr] > MaxSoundNr)
        lastSoundPlayed[BankNr] = 1;

    Play(BankNr, lastSoundPlayed[BankNr]);
}

void MDuinoSound::Stop()
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
        {
            byte cmd[1] = {'O'};    // ATTENTION: This is Start/Stop, not only Stop
            SoundSerial.write(cmd, 1);
            break;
        }

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
            sendDFCommand(0x16, 0x00, 0x00);
            break;

#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
        {
            byte cmd[] = { 0xAA, 0x04, 0x00 };
            sendDYCommand(cmd, 0x03);
            break;
        }
#endif

        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
            SoundSerial.print(F("<PSV>"));
            break;

        default:
            break;
    }
}

void MDuinoSound::Quiet(const bool on /*= true*/)
{
    switch (playerType)
    {
        case MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger:
        {
            byte cmd[2];
            cmd[0] = 'Q';
            cmd[1] = on ? '1' : '0';
            SoundSerial.write(cmd, 2);
            break;
        }

#ifdef INCLUDE_DY_PLAYER
        case MDuinoStorage::MDuinoMP3PlayerType::DYPlayer:
        {
            byte cmd[] = { 0xAA, 0x10, 0x00 };
            sendDYCommand(cmd, 0x03);
            break;
        }
#endif

        case MDuinoStorage::MDuinoMP3PlayerType::DFPlayer:
        case MDuinoStorage::MDuinoMP3PlayerType::Vocalizer:
        default:
            // Not supported
            break;
    }
}

//
// Vocalizer-specific commands
//

void MDuinoSound::Muse()
{
    if (playerType == MDuinoStorage::MDuinoMP3PlayerType::Vocalizer)
        SoundSerial.print(F("<MM>"));
}

void MDuinoSound::Overload()
{
    if (playerType == MDuinoStorage::MDuinoMP3PlayerType::Vocalizer)
        SoundSerial.print(F("<SE>"));
}

//
// Protocol Helpers
//

void MDuinoSound::sendDFCommand(const byte Command, const byte Param1, const byte Param2)
{
    // Calculate the checksum
    unsigned int checkSum = -(0xFF + 0x06 + Command + 0x00 + Param1 + Param2);

    // Construct the command line
    byte commandBuffer[10] = { 0x7E, 0xFF, 0x06, Command, 0x00, Param1, Param2,
                              highByte(checkSum), lowByte(checkSum), 0xEF };

    SoundSerial.write(commandBuffer, 10);

    // Delay needed between successive commands
    delay(100);
}

#ifdef INCLUDE_DY_PLAYER
void MDuinoSound::sendDYCommand(const byte* Command, const byte len)
{
    // Calculate Checksum
    uint8_t sum = 0;
    for (uint8_t i = 0; i < len; i++)
        sum = sum + Command[i];

    // Write Command
    SoundSerial.write(Command, len);
    // Write Checksum
    SoundSerial.write(sum);

    // Delay needed between successive commands
    delay(100);
}
#endif
