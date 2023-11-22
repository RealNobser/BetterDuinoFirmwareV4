#ifndef __MARCDUINOSTORAGE_H__
#define __MARCDUINOSTORAGE_H__

/*
* IDEAS / ToDos
* - Configure AUX1 as input or output
* - consolidate unnecessary settings
* - modify Body mode
*/
/*
* Storage Map in EEPROM:
* 
* Address   Content
* =========|=========
*  0x00     SW-/Config-Version (40 = 4.0,41 = 4.1 ...=
*  0x01     MarcDuinoType (0-DomeMaster, 1-DomeSlave, 2-BodyMaster)
*  0x02     Startup Sound (0-none, 1-File255, 2-File254, 3-File253) // depricated, see Startup Sound Nr
*  0x03     Chatty/Silent Mode (0-Chatty, 1-Silent)
*  0x04     MP3-Player-Type (0-SparkFun, 1-DF-Mini)
*  0x05     Disable Random Sound (0-Random Sound, 1-No Random Sound + Volume off, 2-No Random Sound)
*  0x06     Slave Delay Byte 1 (Delay in ms)
*  0x07     Slave Deley Byte 2 (Delay in ms, 0-65535)
*  0x08     Number of Servos
*  0x09     Startup Sound Nr (obsoletes Startup Sound mapping)
*  0x0a     MinRandomPause in seconds (default 6s)
*  0x0b     MaxRandomPause in seconds (default 12s)
*  0x0c     Use Global or Individual Servo values (0 - global, 1 - individual)
*  0x0d     Set Adjustment Mode (panels will move to new position after individual Open/Mid/Closed Settings are changed)

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

*  0x20     Global Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x21     Servo1 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x22     Servo2 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x23     Servo3 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x24     Servo4 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x25     Servo5 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x26     Servo6 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x27     Servo7 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x28     Servo8 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x29     Servo9 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x2a     Servo10 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x2b     Servo11 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x2c     Servo12 Panel-Servo Direction (0-Normal, 1-Reverse)
*  0x2d     Servo13 Panel-Servo Direction (0-Normal, 1-Reverse)

*  0x30     Global Panel-Servo Speed (0-255)
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

*  0x40     Global Panel-Servo Open Position Degree (0-180) / Microseconds (>=544)
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

*  0x60     Global Panel-Servo Close Position Degree (0-180) / Microseconds (>=544)
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
*  0xa0     Global Holo-Servo-H Direction (0-Normal, 1-Reverse)
*  0xa1     Global Holo-Servo-V Direction (0-Normal, 1-Reverse)
*  0xa2     Servo1 Holo1-Servo-H Direction (0-Normal, 1-Reverse)
*  0xa3     Servo2 Holo1-Servo-V Direction (0-Normal, 1-Reverse)
*  0xa4     Servo3 Holo2-Servo-H Direction (0-Normal, 1-Reverse)
*  0xa5     Servo4 Holo2-Servo-V Direction (0-Normal, 1-Reverse)
*  0xa6     Servo5 Holo3-Servo-H Direction (0-Normal, 1-Reverse)
*  0xa7     Servo6 Holo3-Servo-V Direction (0-Normal, 1-Reverse)
*
*  0xb0     Global Holo-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xb2     Global Holo-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*  0xb4     Servo1 Holo1-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xb6     Servo2 Holo1-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*  0xb8     Servo3 Holo2-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xba     Servo4 Holo2-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*  0xbc     Servo5 Holo3-Servo-H Min Position Degree (0-180) / Microseconds (>=544)
*  0xbe     Servo6 Holo3-Servo-V Min Position Degree (0-180) / Microseconds (>=544)
*
*  0xc0     Global Holo-Servo-H Max Position Degree (0-180) / Microseconds (>=544)
*  0xc2     Global Holo-Servo-V Max Position Degree (0-180) / Microseconds (>=544)
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

*  0xe0     Global Holo-Servo-H Speed (0-255)
*  0xe1     Global Holo-Servo-V Speed (0-255)
*  0xe2     Servo1 Holo1-Servo-H Speed (0-255)
*  0xe3     Servo2 Holo1-Servo-V Speed (0-255)
*  0xe4     Servo3 Holo2-Servo-H Speed (0-255)
*  0xe5     Servo4 Holo2-Servo-V Speed (0-255)
*  0xe6     Servo5 Holo3-Servo-H Speed (0-255)
*  0xe7     Servo6 Holo3-Servo-V Speed (0-255)
*/

#define ADDR_MARCDUINOVERSION   0x00
#define ADDR_MARCDUINOTYPE      0x01
#define ADDR_STARTUPSOUND       0x02
#define ADDR_CHATTYMODE         0x03
#define ADDR_MARCDUINOMP3PLAYER 0x04
#define ADDR_DISABLERANDOMSOUND 0x05
#define ADDR_STARTUPSOUNDNR     0x06

#define ADDR_MINRANDOMPAUSE     0x0a
#define ADDR_MAXRANDOMPAUSE     0x0b
#define ADDR_INDIVIDUALS        0x0c
#define ADDR_ADJUSTMENT         0x0d

#define ADDR_MAXSONGSBASE       0x10

#define ADDR_SERVODIRBASE       0x20
#define ADDR_SERVOSPEEDBASE     0x30
#define ADDR_SERVOOPENBASE      0x40
#define ADDR_SERVOCLOSEDBASE    0x60
// #define ADDR_SERVOMIDBASE       0x80     // depricated, removed in future version

#define ADDR_HOLODIRBASE        0xa0
#define ADDR_HOLOMINBASE        0xb0
#define ADDR_HOLOMAXBASE        0xc0
#define ADDR_HOLOLIGHTBASE      0xd0
#define ADDR_HOLOSPEEDBASE      0xe0

class MarcDuinoStorage
{
    public:
        enum MarcDuinoType
        {
            DomeMaster          = 0,
            DomeSlave           = 1,
            BodyMaster          = 2,
            UnknownMarcDuino    = 3
        };

        enum MarcDuinoMP3PlayerType
        {
            MP3Trigger      = 0,
            DFPlayer        = 1,
            Vocalizer       = 2,
            UnknownPlayer   = 3
        };
    public:
        MarcDuinoStorage();

        byte getConfigVersion();
        void setConfigVersion(const byte Version);

        MarcDuinoType getType();
        void setType(const MarcDuinoType Type);

        MarcDuinoMP3PlayerType getMP3Player();
        void setMP3Player(const MarcDuinoMP3PlayerType Type);

        byte getStartupSound();
        void setStartupSound(const byte SoundNr);

        // NEW: store SoundNr directly without old mapping
        byte getStartupSoundNr();
        void setStartupSoundNr(const byte SoundNr);

        bool getChattyMode();
        void setChattyMode(const bool on = true);

        byte getDisableRandomSound();
        void setDisableRandomSound(const byte DisableRandomSound);

        byte getMaxSound(const byte Bank);
        void setMaxSound(const byte Bank, const byte SoundNr);

        byte getMaxRandomPause();
        void setMaxRandomPause(const byte Seconds);

        byte getMinRandomPause();
        void setMinRandomPause(const byte Seconds);

        void setIndividualSettings(const byte choice);
        byte getIndividualSettings();

        //
        // Panels / Servos
        //

        byte getServoDirection(const byte ServoNr);                         // ServoNr 1-11, ServoNr=0 - Global, Direction 0-Normal / 1- Reverse
        void setServoDirection(const byte ServoNr, const byte Direction);   // ServoNr 1-11, ServoNr=0 - Global, Direction 0-Normal / 1- Reverse

        byte getServoSpeed(const byte ServoNr);                             // ServoNr 1-11, ServoNr=0 - Global, Speed 0-255
        void setServoSpeed(const byte ServoNr, const byte Speed);           // ServoNr 1-11, ServoNr=0 - Global, Speed 0-255

        void getServoPositions(const byte ServoNr, word & OpenPosition, word & ClosedPosition);         // ServoNr 1-11, ServoNr=0 - Global, Position 0-180 deg / >544 Microseconds
        void setServoPositions(const byte ServoNr, const word OpenPosition, const word ClosedPosition); // ServoNr 1-11, ServoNr=0 - Global, Position 0-180 deg / >544 Microseconds

        //
        // Holos / Servos

        void getHoloDirection(const byte HoloNr, byte & HDirection, byte & VDirection);
        void setHoloDirection(const byte HoloNr, const byte HDirection, const byte VDirection);

        void getHoloServoSpeed(const byte HoloNr, byte & HSpeed, byte & VSpeed);
        void setHoloServoSpeed(const byte HoloNr, const byte HSpeed, const byte VSpeed);

        void getHoloPositions(const byte HoloNr, word & HMin, word & HMax, word & VMin, word & VMax);
        void setHoloPositions(const byte HoloNr, const word HMin, const word HMax, const word VMin, const word VMax);

        bool getHoloLightHighActive(const byte HoloNr);
        void setHoloLightHighActive(const byte HoloNr, const bool HighActive);

        bool getAdjustmentMode();
        void setAdjustmentMode(const bool on);

        void dumpToSerial(const byte Address);
};

#endif // __MARCDUINOSTORAGE_H__