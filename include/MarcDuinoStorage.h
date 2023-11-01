#ifndef __MARCDUINOSTORAGE_H__
#define __MARCDUINOSTORAGE_H__
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

*  0x20     Global Servo Direction (0-Normal, 1-Reverse)
*  0x21     Servo1 Servo Direction (0-Normal, 1-Reverse)
*  0x22     Servo2 Servo Direction (0-Normal, 1-Reverse)
*  0x23     Servo3 Servo Direction (0-Normal, 1-Reverse)
*  0x24     Servo4 Servo Direction (0-Normal, 1-Reverse)
*  0x25     Servo5 Servo Direction (0-Normal, 1-Reverse)
*  0x26     Servo6 Servo Direction (0-Normal, 1-Reverse)
*  0x27     Servo7 Servo Direction (0-Normal, 1-Reverse)
*  0x28     Servo8 Servo Direction (0-Normal, 1-Reverse)
*  0x29     Servo9 Servo Direction (0-Normal, 1-Reverse)
*  0x2a     Servo10 Servo Direction (0-Normal, 1-Reverse)
*  0x2b     Servo11 Servo Direction (0-Normal, 1-Reverse)

*  0x30     Global Servo Speed (0-255)
*  0x31     Servo1 Servo Speed (0-255)
*  0x32     Servo2 Servo Speed (0-255)
*  0x33     Servo3 Servo Speed (0-255)
*  0x34     Servo4 Servo Speed (0-255)
*  0x35     Servo5 Servo Speed (0-255)
*  0x36     Servo6 Servo Speed (0-255)
*  0x37     Servo7 Servo Speed (0-255)
*  0x38     Servo8 Servo Speed (0-255)
*  0x39     Servo9 Servo Speed (0-255)
*  0x3a     Servo10 Servo Speed (0-255)
*  0x3b     Servo11 Servo Speed (0-255)

*  0x40     Global Servo Open Position Degree (0-180)
*  0x41     Servo1 Servo Open Position Degree (0-180)
*  0x42     Servo2 Servo Open Position Degree (0-180)
*  0x43     Servo3 Servo Open Position Degree (0-180)
*  0x44     Servo4 Servo Open Position Degree (0-180)
*  0x45     Servo5 Servo Open Position Degree (0-180)
*  0x46     Servo6 Servo Open Position Degree (0-180)
*  0x47     Servo7 Servo Open Position Degree (0-180)
*  0x48     Servo8 Servo Open Position Degree (0-180)
*  0x49     Servo9 Servo Open Position Degree (0-180)
*  0x4a     Servo10 Servo Open Position Degree (0-180)
*  0x4b     Servo11 Servo Open Position Degree (0-180)

*  0x50     Global Servo Close Position Degree (0-180)
*  0x51     Servo1 Servo Close Position Degree (0-180)
*  0x52     Servo2 Servo Close Position Degree (0-180)
*  0x53     Servo3 Servo Close Position Degree (0-180)
*  0x54     Servo4 Servo Close Position Degree (0-180)
*  0x55     Servo5 Servo Close Position Degree (0-180)
*  0x56     Servo6 Servo Close Position Degree (0-180)
*  0x57     Servo7 Servo Close Position Degree (0-180)
*  0x58     Servo8 Servo Close Position Degree (0-180)
*  0x59     Servo9 Servo Close Position Degree (0-180)
*  0x5a     Servo10 Servo Close Position Degree (0-180)
*  0x5b     Servo11 Servo Close Position Degree (0-180)

*  0x60     Global Servo Mid Position Degree (0-180)
*  0x61     Servo1 Servo Mid Position Degree (0-180)
*  0x62     Servo2 Servo Mid Position Degree (0-180)
*  0x63     Servo3 Servo Mid Position Degree (0-180)
*  0x64     Servo4 Servo Mid Position Degree (0-180)
*  0x65     Servo5 Servo Mid Position Degree (0-180)
*  0x66     Servo6 Servo Mid Position Degree (0-180)
*  0x67     Servo7 Servo Mid Position Degree (0-180)
*  0x68     Servo8 Servo Mid Position Degree (0-180)
*  0x69     Servo9 Servo Mid Position Degree (0-180)
*  0x6a     Servo10 Servo Mid Position Degree (0-180)
*  0x6b     Servo11 Servo Mid Position Degree (0-180)
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

#define ADDR_MAXSONGSBASE       0x10

#define ADDR_SERVODIRBASE       0x20
#define ADDR_SERVOSPEEDBASE     0x30
#define ADDR_SERVOOPENBASE      0x40
#define ADDR_SERVOCLOSEDBASE    0x50
#define ADDR_SERVOMIDBASE       0x60

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

        byte getServoDirection(const byte ServoNr);                         // ServoNr 1-1, ServoNr=0 - Global, Direction 0-Normal / 1- Reverse
        void setServoDirection(const byte ServoNr, const byte Direction);   // ServoNr 1-1, ServoNr=0 - Global, Direction 0-Normal / 1- Reverse

        byte getServoSpeed(const byte ServoNr);                             // ServoNr 1-1, ServoNr=0 - Global, Speed 0-255
        void setServoSpeed(const byte ServoNr, const byte Speed);           // ServoNr 1-1, ServoNr=0 - Global, Speed 0-255

        byte getServoOpenPosDeg(const byte ServoNr);                        // ServoNr 1-1, ServoNr=0 - Global, Position 0-180
        void setServoOpenPosDeg(const byte ServoNr, const byte Position);   // ServoNr 1-1, ServoNr=0 - Global, Posution 0-180

        byte getServoCosedPosDeg(const byte ServoNr);                       // ServoNr 1-1, ServoNr=0 - Global, Position 0-180
        void setServoClosedPosDeg(const byte ServoNr, const byte Position); // ServoNr 1-1, ServoNr=0 - Global, Posution 0-180

        byte getServoMidPosDeg(const byte ServoNr);                         // ServoNr 1-1, ServoNr=0 - Global, Position 0-180
        void setServoMidPosDeg(const byte ServoNr, const byte Position);    // ServoNr 1-1, ServoNr=0 - Global, Posution 0-180

        void dumpToSerial();
};

#endif // __MARCDUINOSTORAGE_H__