#include "MarcDuinoSound.h"

MarcDuinoSound::MarcDuinoSound()
{

}

void MarcDuinoSound::Play(const byte BankNr, const byte SoundNr)
{
    byte CalcSoundNr = 0;
    CalcSoundNr = (BankNr-1)*25 + SoundNr;
    Play(CalcSoundNr);
}

///////////

MarcDuinoSoundMP3Trigger::MarcDuinoSoundMP3Trigger(SendOnlySoftwareSerial& SoundSerial) :
    SoundSerial(SoundSerial)
{
    CurrentVolume = 0x20;   // Medium Volume   
}

void MarcDuinoSoundMP3Trigger::SetVolume(const byte Volume)
{
    byte cmd[2];

    cmd[0] = 'v';       // Volume
    cmd[1] = Volume;    // The VS1053 volume will be set to the value n. 
                        // Per the VS1053 datasheet, maximum volume is 0x00, and values 
                        // much above 0x40 are too low to be audible.  

    CurrentVolume = Volume;
    SoundSerial.write(cmd, 2);
}

void MarcDuinoSoundMP3Trigger::VolumeUp()
{
    if (CurrentVolume >= 2)
    {
        CurrentVolume -= 2;
        SetVolume(CurrentVolume);
    }
}

void MarcDuinoSoundMP3Trigger::VolumeDown()
{
    if (CurrentVolume < 0x40)
    {
        CurrentVolume += 2;
        SetVolume(CurrentVolume);
    }
}

void MarcDuinoSoundMP3Trigger::VolumeMid()
{
    SetVolume(0x20);
}

void MarcDuinoSoundMP3Trigger::VolumeMax()
{
    SetVolume(0x00);
}

void MarcDuinoSoundMP3Trigger::VolumeMin()
{
    SetVolume(0x40);
}

void MarcDuinoSoundMP3Trigger::VolumeOff()
{
    SetVolume(0xff);
}

void MarcDuinoSoundMP3Trigger::Play(const byte SoundNr)
{
    byte cmd[2];

    cmd[0] = 't';       // trigger
    cmd[1] = SoundNr;   // sound “NNNxxxx.MP3”

    SoundSerial.write(cmd, 2);
}

void MarcDuinoSoundMP3Trigger::Stop()
{
    byte cmd[1] = {'O'};  // ATTENTION: This is Start/Stop, not only Stop
    SoundSerial.write(cmd, 1);
}

void MarcDuinoSoundMP3Trigger::Quiet(const bool on/* = true*/)
{
    byte cmd[2];

    cmd[0] = 'Q';       // trigger
    if (on)
        cmd[1] = '1';
    else
        cmd[1] = '0';

    SoundSerial.write(cmd, 2);
}


///////////

MarcDuinoSoundDFPlayer::MarcDuinoSoundDFPlayer(SendOnlySoftwareSerial& SoundSerial) :
    SoundSerial(SoundSerial)
{
    CurrentVolume = 15;   // Medium Volume
}

void MarcDuinoSoundDFPlayer::SetVolume(const byte Volume)
{

    CurrentVolume = Volume;

}

void MarcDuinoSoundDFPlayer::VolumeUp()
{
    if (CurrentVolume < 30)
    {
        CurrentVolume += 2;
        SetVolume(CurrentVolume);
    }    
}

void MarcDuinoSoundDFPlayer::VolumeDown()
{
    if (CurrentVolume >= 2)
    {
        CurrentVolume -= 2;
        SetVolume(CurrentVolume);
    }
}

void MarcDuinoSoundDFPlayer::VolumeMid()
{
    SetVolume(15);
}

void MarcDuinoSoundDFPlayer::VolumeMax()
{
    SetVolume(30);
}

void MarcDuinoSoundDFPlayer::VolumeMin()
{
    SetVolume(5);
}

void MarcDuinoSoundDFPlayer::VolumeOff()
{
    SetVolume(0);
}

void MarcDuinoSoundDFPlayer::Play(const byte SoundNr)
{

}

void MarcDuinoSoundDFPlayer::Stop()
{
    
}

void MarcDuinoSoundDFPlayer::Quiet(const bool on/* = true*/)
{

}


//////////


MarcDuinoSoundVocalizer::MarcDuinoSoundVocalizer(SendOnlySoftwareSerial& SoundSerial) :
    SoundSerial(SoundSerial)
{

}

void MarcDuinoSoundVocalizer::SetVolume(const byte Volume)
{

}

void MarcDuinoSoundVocalizer::VolumeUp()
{

}

void MarcDuinoSoundVocalizer::VolumeDown()
{

}

void MarcDuinoSoundVocalizer::VolumeMid()
{

}

void MarcDuinoSoundVocalizer::VolumeMax()
{

}

void MarcDuinoSoundVocalizer::VolumeMin()
{

}

void MarcDuinoSoundVocalizer::VolumeOff()
{

}

void MarcDuinoSoundVocalizer::Play(const byte SoundNr)
{

}

void MarcDuinoSoundVocalizer::Stop()
{
    
}

void MarcDuinoSoundVocalizer::Quiet(const bool on/* = true*/)
{

}
