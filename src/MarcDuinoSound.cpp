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

void MarcDuinoSoundMP3Trigger::init()
{
    VolumeMid();
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

void MarcDuinoSoundDFPlayer::init()
{
    SoundSerial.flush();

    sendCommand(0x09, 0x00, 0x01);  // Playback Source TF
    delay(500);
    sendCommand(0x07, 0x00, 0x01);  // EQ pop
    delay(100);
    VolumeMid();
    delay(100);
}

void MarcDuinoSoundDFPlayer::SetVolume(const byte Volume)
{
    CurrentVolume = Volume;
    sendCommand(0x06, 0x00, Volume);    // Specify Volume (0-30)
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
    sendCommand(0x12, 0x00, SoundNr);      // Playback
}

void MarcDuinoSoundDFPlayer::Stop()
{
    sendCommand(0x16, 0x00, 0x00);  
}

void MarcDuinoSoundDFPlayer::Quiet(const bool on/* = true*/)
{

}

void MarcDuinoSoundDFPlayer::sendCommand(const byte Command, const byte Param1, const byte Param2) 
{

	// Calculate the checksum
	unsigned int checkSum = -(0xFF + 0x06 + Command + 0x00 + Param1 + Param2);

	// Construct the command line
	byte commandBuffer[10] = { 0x7E, 0xFF, 0x06, Command, 0x00, Param1, Param2,
			highByte(checkSum), lowByte(checkSum), 0xEF };

    SoundSerial.write(commandBuffer, 10);

	// Delay needed between successive commands
	// delay(30);
}

//////////


MarcDuinoSoundVocalizer::MarcDuinoSoundVocalizer(SendOnlySoftwareSerial& SoundSerial) :
    SoundSerial(SoundSerial)
{
    // Init 
    SoundSerial.flush();
    CurrentVolume = 50;   // Medium Volume
}

void MarcDuinoSoundVocalizer::init()
{
    VolumeMid();
}

void MarcDuinoSoundVocalizer::SetVolume(const byte Volume)
{
    SoundSerial.printf("<PVV%d>", Volume);  // Vocaliser
    SoundSerial.printf("<PVA%d>", Volume);  // Wav Channel A
    SoundSerial.printf("<PVB%d>", Volume);  // Wav Channel B
}

void MarcDuinoSoundVocalizer::VolumeUp()
{
    if (CurrentVolume < 100)
    {
        CurrentVolume += 5;
        SetVolume(CurrentVolume);
    }    
}

void MarcDuinoSoundVocalizer::VolumeDown()
{
    if (CurrentVolume >= 5)
    {
        CurrentVolume -= 5;
        SetVolume(CurrentVolume);
    }
}

void MarcDuinoSoundVocalizer::VolumeMid()
{
    SetVolume(50);
}

void MarcDuinoSoundVocalizer::VolumeMax()
{
    SetVolume(100);
}

void MarcDuinoSoundVocalizer::VolumeMin()
{
    SetVolume(10);
}

void MarcDuinoSoundVocalizer::VolumeOff()
{
    SetVolume(0);
}

void MarcDuinoSoundVocalizer::Play(const byte SoundNr)
{
    SoundSerial.printf("<CA%04d>", SoundNr);
}

void MarcDuinoSoundVocalizer::Stop()
{
    SoundSerial.printf("<PSV>");
}

void MarcDuinoSoundVocalizer::Quiet(const bool on/* = true*/)
{

}

void MarcDuinoSoundVocalizer::Muse()
{
    SoundSerial.print("<MM>");
}

void MarcDuinoSoundVocalizer::Overload()
{
    SoundSerial.print("<SE>");
}
