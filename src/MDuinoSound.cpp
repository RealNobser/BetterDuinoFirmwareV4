#include "MDuinoSound.h"

MDuinoSound::MDuinoSound()
{
}

void MDuinoSound::VolumeStandard()
{
	SetVolume(CurrentVolume);
}

void MDuinoSound::Play(const byte BankNr, const byte SoundNr)
{
	byte CalcSoundNr = 0;
	CalcSoundNr = (BankNr - 1) * 25 + SoundNr;
	Play(CalcSoundNr);
}

///////////

MDuinoSoundMP3Trigger::MDuinoSoundMP3Trigger(SendOnlySoftwareSerial &SoundSerial) : SoundSerial(SoundSerial)
{
	CurrentVolume = 0x20; // Medium Volume
}

void MDuinoSoundMP3Trigger::init()
{
	VolumeMid();
}

void MDuinoSoundMP3Trigger::SetVolume(const byte Volume, const bool SetAsStandard /*= true*/)
{
	byte cmd[2];

	cmd[0] = 'v';	 // Volume
	cmd[1] = Volume; // The VS1053 volume will be set to the value n.
					 // Per the VS1053 datasheet, maximum volume is 0x00, and values
					 // much above 0x40 are too low to be audible.

	if (SetAsStandard)
		CurrentVolume = Volume;

	SoundSerial.write(cmd, 2);
}

void MDuinoSoundMP3Trigger::VolumeUp()
{
	if (CurrentVolume >= 2)
	{
		CurrentVolume -= 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundMP3Trigger::VolumeDown()
{
	if (CurrentVolume < 0x40)
	{
		CurrentVolume += 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundMP3Trigger::VolumeMid()
{
	SetVolume(0x20);
}

void MDuinoSoundMP3Trigger::VolumeMax()
{
	SetVolume(0x00);
}

void MDuinoSoundMP3Trigger::VolumeMin()
{
	SetVolume(0x40);
}

void MDuinoSoundMP3Trigger::VolumeOff()
{
	SetVolume(0xff, false);
}

void MDuinoSoundMP3Trigger::Play(const byte SoundNr)
{
	byte cmd[2];

	cmd[0] = 't';	  // trigger
	cmd[1] = SoundNr; // sound “NNNxxxx.MP3”

	SoundSerial.write(cmd, 2);
}

void MDuinoSoundMP3Trigger::Stop()
{
	byte cmd[1] = {'O'}; // ATTENTION: This is Start/Stop, not only Stop
	SoundSerial.write(cmd, 1);
}

void MDuinoSoundMP3Trigger::Quiet(const bool on /* = true*/)
{
	byte cmd[2];

	cmd[0] = 'Q'; // trigger
	if (on)
		cmd[1] = '1';
	else
		cmd[1] = '0';

	SoundSerial.write(cmd, 2);
}

///////////

MDuinoSoundDFPlayer::MDuinoSoundDFPlayer(SendOnlySoftwareSerial &SoundSerial) : SoundSerial(SoundSerial)
{
	CurrentVolume = 15; // Medium Volume
}

void MDuinoSoundDFPlayer::init()
{
	SoundSerial.flush();

	sendCommand(0x09, 0x00, 0x01); // Playback Source TF
	delay(500);
	sendCommand(0x07, 0x00, 0x00); // EQ Normal
	delay(100);
	VolumeMid();
	delay(100);
}

void MDuinoSoundDFPlayer::SetVolume(const byte Volume, const bool SetAsStandard /*= true*/)
{
	if (SetAsStandard)
		CurrentVolume = Volume;

	sendCommand(0x06, 0x00, Volume); // Specify Volume (0-30)
}

void MDuinoSoundDFPlayer::VolumeUp()
{
	if (CurrentVolume < 30)
	{
		CurrentVolume += 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundDFPlayer::VolumeDown()
{
	if (CurrentVolume >= 2)
	{
		CurrentVolume -= 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundDFPlayer::VolumeMid()
{
	SetVolume(15);
}

void MDuinoSoundDFPlayer::VolumeMax()
{
	SetVolume(30);
}

void MDuinoSoundDFPlayer::VolumeMin()
{
	SetVolume(5);
}

void MDuinoSoundDFPlayer::VolumeOff()
{
	SetVolume(0, false);
}

void MDuinoSoundDFPlayer::Play(const byte SoundNr)
{
	sendCommand(0x12, 0x00, SoundNr); // Playback
}

void MDuinoSoundDFPlayer::Stop()
{
	sendCommand(0x16, 0x00, 0x00);
}

void MDuinoSoundDFPlayer::Quiet(const bool on /* = true*/)
{
}

void MDuinoSoundDFPlayer::sendCommand(const byte Command, const byte Param1, const byte Param2)
{

	// Calculate the checksum
	unsigned int checkSum = -(0xFF + 0x06 + Command + 0x00 + Param1 + Param2);

	// Construct the command line
	byte commandBuffer[10] = { 0x7E, 0xFF, 0x06, Command, 0x00, Param1, Param2,
							  highByte(checkSum), lowByte(checkSum), 0xEF };

	SoundSerial.write(commandBuffer, 10);
	SoundSerial.flush();

	// Delay needed between successive commands
	delay(100);
}

//////////

MDuinoSoundVocalizer::MDuinoSoundVocalizer(SendOnlySoftwareSerial &SoundSerial) : SoundSerial(SoundSerial)
{
	// Init
	SoundSerial.flush();
	CurrentVolume = 50; // Medium Volume
}

void MDuinoSoundVocalizer::init()
{
	VolumeMid();
}

void MDuinoSoundVocalizer::SetVolume(const byte Volume, const bool SetAsStandard /*= true*/)
{
	if (SetAsStandard)
		CurrentVolume = Volume;

	SoundSerial.printf(F("<PVV%d>"), Volume); // Vocaliser
	SoundSerial.printf(F("<PVA%d>"), Volume); // Wav Channel A
	SoundSerial.printf(F("<PVB%d>"), Volume); // Wav Channel B
}

void MDuinoSoundVocalizer::VolumeUp()
{
	if (CurrentVolume < 100)
	{
		CurrentVolume += 5;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundVocalizer::VolumeDown()
{
	if (CurrentVolume >= 5)
	{
		CurrentVolume -= 5;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundVocalizer::VolumeMid()
{
	SetVolume(50);
}

void MDuinoSoundVocalizer::VolumeMax()
{
	SetVolume(100);
}

void MDuinoSoundVocalizer::VolumeMin()
{
	SetVolume(10);
}

void MDuinoSoundVocalizer::VolumeOff()
{
	SetVolume(0, false);
}

void MDuinoSoundVocalizer::Play(const byte SoundNr)
{
	SoundSerial.printf(F("<CA%04d>"), SoundNr);
}

void MDuinoSoundVocalizer::Stop()
{
	SoundSerial.print(F("<PSV>"));
}

void MDuinoSoundVocalizer::Quiet(const bool on /* = true*/)
{
}

void MDuinoSoundVocalizer::Muse()
{
	SoundSerial.print(F("<MM>"));
}

void MDuinoSoundVocalizer::Overload()
{
	SoundSerial.print(F("<SE>"));
}

///////////

MDuinoSoundDYPlayer::MDuinoSoundDYPlayer(SendOnlySoftwareSerial &SoundSerial) : SoundSerial(SoundSerial)
{
	CurrentVolume = 15; // Medium Volume
}

void MDuinoSoundDYPlayer::init()
{
	byte cmd[] = { 0xAA, 0x1A, 0x01, 0x00 }; // EQ-Normal

	SoundSerial.flush();

	sendCommand(cmd, 0x04);

	delay(100);
	VolumeMid();
	delay(100);
}

void MDuinoSoundDYPlayer::SetVolume(const byte Volume, const bool SetAsStandard /*= true*/)
{
	byte cmd[4] = { 0xAA, 0x13, 0x01, 0x00 }; // Set Volume, Specify Volume (0-30)

	cmd[3] = Volume;

	if (SetAsStandard)
		CurrentVolume = Volume;

	sendCommand(cmd, 0x04);
}

void MDuinoSoundDYPlayer::VolumeUp()
{
	if (CurrentVolume < 30)
	{
		CurrentVolume += 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundDYPlayer::VolumeDown()
{
	if (CurrentVolume >= 2)
	{
		CurrentVolume -= 2;
		SetVolume(CurrentVolume);
	}
}

void MDuinoSoundDYPlayer::VolumeMid()
{
	SetVolume(15);
}

void MDuinoSoundDYPlayer::VolumeMax()
{
	SetVolume(30);
}

void MDuinoSoundDYPlayer::VolumeMin()
{
	SetVolume(5);
}

void MDuinoSoundDYPlayer::VolumeOff()
{
	SetVolume(0, false);
}

void MDuinoSoundDYPlayer::Play(const byte SoundNr)
{
	byte cmd[5] = { 0xAA, 0x07, 0x02, 0x00, 0x00 };	// Play specific Song

	cmd[4] = SoundNr;

	sendCommand(cmd, 0x05);
}

void MDuinoSoundDYPlayer::Stop()
{
	byte cmd[3] = { 0xAA, 0x04, 0x00 };
	sendCommand(cmd, 0x03);
}

void MDuinoSoundDYPlayer::Quiet(const bool on /* = true*/)
{
	byte cmd[3] = { 0xAA, 0x10, 0x00 };
	sendCommand(cmd, 0x03);
}

void MDuinoSoundDYPlayer::sendCommand(const byte *Command, const byte len)
{
	// Calculte Checksum
	uint8_t sum = 0;
	for (uint8_t i = 0; i < len; i++)
		sum = sum + Command[i];

	// Write Commeand
	SoundSerial.write(Command, len);
	// Write Checksum
	SoundSerial.write(sum);
	SoundSerial.flush();

	// Delay needed between successive commands
	delay(100);
}