#ifndef __MDUINOSOUND_H__
#define __MDUINOSOUND_H__

#include <Arduino.h>
#include <SendOnlySoftwareSerial.h>
#include "config.h"
#include "MDuinoStorage.h"

/***********************************************************
 *  On the MP3, there are a maximum of 255 sound files
 *  They must be named NNN-xxxx.mp3
 *  Where NNN = 001 to 255
 *  The numbering ranges are predetermined, 25 sounds per
 *  bank category
 *       Bank 1: gen sounds, numbered 001 to 025
 *       Bank 2: chat sounds, numbered 026 to 050
 *       Bank 3: happy sounds, numbered 051 to 075
 *       Bank 4: sad sounds, numbered 076 to 100
 *       Bank 5: whistle sounds, numbered 101 to 125
 *       Bank 6: scream sounds, numbered 126 to 150
 *       Bank 7: Leia sounds, numbered 151 to 175
 *       Bank 8: sing sounds (deprecated, not used by R2 Touch), numberer 176 to 200
 *       Bank 9: mus sounds, numbered 201 t0 225
 *
 *  The pre-made R2 sound library contains only a few non-copyrighted music sounds.
 *  Sound 202, 203 and 205 are "beeped music" place-holders, meant to be replaced with the
 *  original score of Star Wars, Empire March, and Cantina respectively
 *
 *  If you add your own sounds in Bank 9, make sure you update the last variable
 *  MP3_BANK9_SOUNDS below to reflect the total number of sounds
 *
 ***********************************************************/

	/////////////COMMAND VOCABULARY///////////
	// Play sound command by bank/sound numbers
	// $xyy
	// x=bank number
	// yy=sound number. If none, next sound is played in the bank
	//
	// Other commands
	// $c
	// where c is a command character
	// R - random from 4 first banks
	// O - sound off
	// L - Leia message (bank 7 sound 1)
	// C - Cantina music (bank 9 sound 5)
	// c - Beep cantina (bank 9 sound 1)
	// S - Scream (bank 6 sound 1)
	// F - Faint/Short Circuit (bank 6 sound 3)
	// D - Disco (bank 9 sound 6)
	// s - stop sounds
	// + - volume up
	// - - volume down
	// m - volume mid
	// f - volume max
	// p - volume min
	// W - Star Wars music (bank 9 sound 2)
	// M - Imperial March (bank 9 sound 3)
	//
	///////////////////////////////////////////////

class MDuinoSound
{
    public:
        // Single concrete class - no virtual functions, no vtable overhead.
        // Uses MDuinoStorage::MDuinoMP3PlayerType as internal type discriminator.
        MDuinoSound(SendOnlySoftwareSerial& SoundSerial, MDuinoStorage::MDuinoMP3PlayerType playerType);

        void init();

        void SetVolume(const byte Volume, const bool SetAsStandard = true);
        void VolumeUp();
        void VolumeDown();
        void VolumeMid();
        void VolumeMax();
        void VolumeMin();
        void VolumeOff();

        void Play(const byte SoundNr);
        void Stop();
        void Quiet(const bool on = true);

        bool hasVocalizer() { return (playerType == MDuinoStorage::MDuinoMP3PlayerType::Vocalizer); }
        void Muse();
        void Overload();

        // Shared logic (unchanged)
        void VolumeStandard();
        void Play(const byte BankNr, const byte SoundNr);
        void PlayNext(const byte BankNr, const byte MaxSoundNr);

    private:
        MDuinoStorage::MDuinoMP3PlayerType playerType;
        SendOnlySoftwareSerial& SoundSerial;
        byte CurrentVolume = 0;
        uint8_t lastSoundPlayed[MAX_SOUND_BANK+1];

        // Protocol helpers
        void sendDFCommand(const byte Command, const byte Param1, const byte Param2);
#ifdef INCLUDE_DY_PLAYER
        void sendDYCommand(const byte* Command, const byte len);
#endif
};

#endif // __MDUINOSOUND_H__
