#ifndef __MDUINOSTORAGE_H__
#define __MDUINOSTORAGE_H__

#include <Arduino.h>
#include "config.h"

/*
* IDEAS / ToDos
* - Configure AUX1 as input or output
* - modify Body mode
*/
/*
* Storage Map in EEPROM:
* 
* Address   Content
* =========|=========
*  0x00     SW-/Config-Version (40 = 4.0,41 = 4.1 ...=
*  0x01     MDuinoType (0-DomeMaster, 1-DomeSlave, 2-BodyMaster)
*  0x02     
*  0x03     
*  0x04     MP3-Player-Type (0-SparkFun, 1-DF-Mini, 2-Vocalizer)
*  0x05     Disable Random Sound (0-Random Sound, 1-No Random Sound + Volume off, 2-No Random Sound)
*  0x06     Slave Delay Byte 1 (Delay in ms, 0-255) (default 0ms)
*  0x07     
*  0x08     Number of Servos (default 13)
*  0x09     Startup Sound Nr (default 255)
*  0x0a     MinRandomPause in seconds (default 6s)
*  0x0b     MaxRandomPause in seconds (default 12s)
*  0x0c     Serial Echo Mode     
*  0x0d

*  0x10
*  0x11     Max Sounds Bank 1 (1-25)
*  0x12     Max Sounds Bank 2 (1-25)
*  0x13     Max Sounds Bank 3 (1-25)
*  0x14     Max Sounds Bank 4 (1-25)
*  0x15     Max Sounds Bank 5 (1-25)
*  0x16     Max Sounds Bank 6 (1-25)
*  0x17     Max Sounds Bank 7 (1-25)
*  0x18     Max Sounds Bank 8 (1-25)
*  0x19     Max Sounds Bank 9 (1-25)

*  0x20     
*  0x21     
*  0x22     
*  0x23     
*  0x24     
*  0x25     
*  0x26     
*  0x27     
*  0x28     
*  0x29     
*  0x2a     
*  0x2b     
*  0x2c     
*  0x2d     

*  0x30     
*  0x31     Servo1 Panel-Servo Speed (0-255)
*  0x32     Servo2 Panel-Servo Speed (0-255)
*  0x33     Servo3 Panel-Servo Speed (0-255)
*  0x34     Servo4 Panel-Servo Speed (0-255)
*  0x35     Servo5 Panel-Servo Speed (0-255)
*  0x36     Servo6 Panel-Servo Speed (0-255)
*  0x37     Servo7 Panel-Servo Speed (0-255)
*  0x38     Servo8 Panel-Servo Speed (0-255)
*  0x39     Servo9 Panel-Servo Speed (0-255)
*  0x3a     Servo10 Panel-Servo Speed (0-255)
*  0x3b     Servo11 Panel-Servo Speed (0-255)
*  0x3c     Servo12 Panel-Servo Speed (0-255)
*  0x3d     Servo13 Panel-Servo Speed (0-255)

*  0x40     
*  0x42     Servo1 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x44     Servo2 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x46     Servo3 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x48     Servo4 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x4a     Servo5 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x4c     Servo6 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x4e     Servo7 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x50     Servo8 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x52     Servo9 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x54     Servo10 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x56     Servo11 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x58     Servo12 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
*  0x5a     Servo13 Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)

*  0x60     
*  0x62     Servo1 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x64     Servo2 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x66     Servo3 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x68     Servo4 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x6a     Servo5 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x6c     Servo6 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x6e     Servo7 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x70     Servo8 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x72     Servo9 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x74     Servo10 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x76     Servo11 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x78     Servo12 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
*  0x7a     Servo13 Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)

*  mid position maybe deprecated
*  0x80 - 0x9f free now
*
*  0xa0     
*  0xa1     
*  0xa2     
*  0xa3     
*  0xa4     
*  0xa5     
*  0xa6     
*  0xa7     
*
*  0xb0
*  0xb2
*  0xb4     Servo1 Holo1-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xb6     Servo2 Holo1-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*  0xb8     Servo3 Holo2-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xba     Servo4 Holo2-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*  0xbc     Servo5 Holo3-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xbe     Servo6 Holo3-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*
*  0xc0
*  0xc2
*  0xc4     Servo1 Holo1-Servo-H Max Position Degree (0-180) / Microseconds (>=544)
*  0xc6     Servo2 Holo1-Servo-V Max Position Degree (0-180) / Microseconds (>=544)
*  0xc8     Servo3 Holo2-Servo-H Max Position Degree (0-180) / Microseconds (>=544)
*  0xca     Servo4 Holo2-Servo-V Max Position Degree (0-180) / Microseconds (>=544)
*  0xcc     Servo5 Holo3-Servo-H Max Position Degree (0-180) / Microseconds (>=544)
*  0xce     Servo6 Holo3-Servo-V Max Position Degree (0-180) / Microseconds (>=544)
*
*  0xd1     Holo1 Light High Active (=1) or Low Active (=0)
*  0xd2     Holo2 Light High Active (=1) or Low Active (=0)
*  0xd3     Holo3 Light High Active (=1) or Low Active (=0)
*  0xd4     Holo1 Light Type (false - Standard; true - Neopixel)
*  0xd5     Holo2 Light Type (false - Standard; true - Neopixel)
*  0xd6     Holo3 Light Type (false - Standard; true - Neopixel)
*  0xd7     Holo1 Neopixel LEDs (default 7)
*  0xd8     Holo2 Neopixel LEDs (default 7)
*  0xd9     Holo3 Neopixel LEDs (default 7)

*  0xe0 
*  0xe1 
*  0xe2     Servo1 Holo1-Servo-H Speed (0-255)
*  0xe3     Servo2 Holo1-Servo-V Speed (0-255)
*  0xe4     Servo3 Holo2-Servo-H Speed (0-255)
*  0xe5     Servo4 Holo2-Servo-V Speed (0-255)
*  0xe6     Servo5 Holo3-Servo-H Speed (0-255)
*  0xe7     Servo6 Holo3-Servo-V Speed (0-255)
*/

#define ADDR_MDUINOVERSION      0x00
#define ADDR_MDUINOTYPE         0x01
#define ADDR_MDUINOMP3PLAYER    0x04
#define ADDR_DISABLERANDOMSOUND 0x05
#define ADDR_STARTUPSOUNDNR     0x06

#define ADDR_MINRANDOMPAUSE     0x0a
#define ADDR_MAXRANDOMPAUSE     0x0b
#define ADDR_ECHOMODE           0x0c

#define ADDR_MAXSONGSBASE       0x10

#define ADDR_SERVODIRBASE       0x20
#define ADDR_SERVOSPEEDBASE     0x30
#define ADDR_SERVOOPENBASE      0x40
#define ADDR_SERVOCLOSEDBASE    0x60

#define ADDR_SERVOBINITBASE      0x80

#define ADDR_HOLODIRBASE        0xa0
#define ADDR_HOLOMINBASE        0xb0
#define ADDR_HOLOMAXBASE        0xc0
#define ADDR_HOLOLIGHTBASE      0xd0
#define ADDR_HOLOSPEEDBASE      0xe0

class MDuinoStorage
{
    public:
        enum class MDuinoType
        {
            DomeMaster = 0,
            DomeSlave,
            BodyMaster,
            unknown,
        };

        enum class MDuinoMP3PlayerType
        {
            MP3Trigger      = 0,
            DFPlayer        = 1,
            Vocalizer       = 2,
            DYPlayer        = 3,
            unknown         = 4
        };
        
    public:
        MDuinoStorage();

        byte getConfigVersion();
        void setConfigVersion(const byte Version);

        MDuinoType getType();
        void setType(const MDuinoType Type);

        MDuinoMP3PlayerType getMP3Player();
        void setMP3Player(const MDuinoMP3PlayerType Type);

        byte getStartupSoundNr();
        void setStartupSoundNr(const byte SoundNr);

        byte getDisableRandomSound();
        void setDisableRandomSound(const byte DisableRandomSound);

        byte getMaxSound(const byte Bank);
        void setMaxSound(const byte Bank, const byte SoundNr);

        byte getMaxRandomPause();
        void setMaxRandomPause(const byte Seconds);

        byte getMinRandomPause();
        void setMinRandomPause(const byte Seconds);

        byte getServoInit();
        void setServoInit(const byte init);

        //
        // Panels / Servos
        //

        byte getServoSpeed(const byte ServoNr);                             // ServoNr 1-11, ServoNr=0 - Global, Speed 0-255
        void setServoSpeed(const byte ServoNr, const byte Speed);           // ServoNr 1-11, ServoNr=0 - Global, Speed 0-255

        void getServoPositions(const byte ServoNr, word & OpenPosition, word & ClosedPosition);         // ServoNr 1-11, ServoNr=0 - Global, Position 0-180 deg / >544 Microseconds
        void setServoPositions(const byte ServoNr, const word OpenPosition, const word ClosedPosition); // ServoNr 1-11, ServoNr=0 - Global, Position 0-180 deg / >544 Microseconds

        //
        // Holos / Servos
        bool getHoloNeoPixel(const byte HoloNr);
        void setHoloNeoPixel(const byte HoloNr, const bool NeoPixel);

        void getHoloServoSpeed(const byte HoloNr, byte & HSpeed, byte & VSpeed);
        void setHoloServoSpeed(const byte HoloNr, const byte HSpeed, const byte VSpeed);

        void getHoloPositions(const byte HoloNr, word & HMin, word & HMax, word & VMin, word & VMax);
        void setHoloPositions(const byte HoloNr, const word HMin, const word HMax, const word VMin, const word VMax);

        bool getHoloLightHighActive(const byte HoloNr);
        void setHoloLightHighActive(const byte HoloNr, const bool HighActive);

        byte getHoloLEDs(const byte HoloNr);
        void setHoloLEDs(const byte HoloNr, const byte LEDs);

        bool getEchoMode();
        void setEchoMode(const bool echoMode);

        #ifdef DEBUG_MSG
        void dumpToSerial(const byte Address);
        #endif
};

#endif // __MDUINOSTORAGE_H__