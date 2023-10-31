#ifndef __MARCDUINOSTORAGE_H__
#define __MARCDUINOSTORAGE_H__
/*
* Storage Map in EEPROM:
* 
* Address   Content
* =========|=========
*  0        SW-Version (40 = 4.0,41 = 4.1 ...=
*  1        MarcDuinoType (0-DomeMaster, 1-DomeSlave, 2-BodyMaster)
*  2        Startup Sound (0-none, 1-File255, 2-File254, 3-File253) // depricated, see Startup Sound Nr
*  3        Chatty/Silent Mode (0-Chatty, 1-Silent)
*  4        MP3-Player-Type (0-SparkFun, 1-DF-Mini)
*  5        Disable Random Sound (0-Random Sound, 1-No Random Sound + Volume off, 2-No Random Sound)
*  6        Slave Delay Byte 1 (Delay in ms)
*  7        Slave Deley Byte 2 (Delay in ms, 0-65535)
*  8        Number of Servos
*  9        Startup Sound Nr (obsoletes Startup Sound mapping)

*  10       Global Servo Direction (0-Normal, 1-Reverse)
*  11       Servo1 Servo Direction (0-Normal, 1-Reverse)
*  12       Servo2 Servo Direction (0-Normal, 1-Reverse)
*  13       Servo3 Servo Direction (0-Normal, 1-Reverse)
*  14       Servo4 Servo Direction (0-Normal, 1-Reverse)
*  15       Servo5 Servo Direction (0-Normal, 1-Reverse)
*  16       Servo6 Servo Direction (0-Normal, 1-Reverse)
*  17       Servo7 Servo Direction (0-Normal, 1-Reverse)
*  18       Servo8 Servo Direction (0-Normal, 1-Reverse)
*  19       Servo9 Servo Direction (0-Normal, 1-Reverse)
*  20       Servo10 Servo Direction (0-Normal, 1-Reverse)
*  21       Servo11 Servo Direction (0-Normal, 1-Reverse)

*  30       Global Servo Speed (0-255)
*  31       Servo1 Servo Speed (0-255)
*  32       Servo2 Servo Speed (0-255)
*  33       Servo3 Servo Speed (0-255)
*  34       Servo4 Servo Speed (0-255)
*  35       Servo5 Servo Speed (0-255)
*  36       Servo6 Servo Speed (0-255)
*  37       Servo7 Servo Speed (0-255)
*  38       Servo8 Servo Speed (0-255)
*  39       Servo9 Servo Speed (0-255)
*  40       Servo10 Servo Speed (0-255)
*  41       Servo11 Servo Speed (0-255)

*  50       Global Servo Open Position (0-180)
*  51       Servo1 Servo Open Position (0-180)
*  52       Servo2 Servo Open Position (0-180)
*  53       Servo3 Servo Open Position (0-180)
*  54       Servo4 Servo Open Position (0-180)
*  55       Servo5 Servo Open Position (0-180)
*  56       Servo6 Servo Open Position (0-180)
*  57       Servo7 Servo Open Position (0-180)
*  58       Servo8 Servo Open Position (0-180)
*  59       Servo9 Servo Open Position (0-180)
*  60       Servo10 Servo Open Position (0-180)
*  61       Servo11 Servo Open Position (0-180)

*  70       Global Servo Close Position (0-180)
*  71       Servo1 Servo Close Position (0-180)
*  72       Servo2 Servo Close Position (0-180)
*  73       Servo3 Servo Close Position (0-180)
*  74       Servo4 Servo Close Position (0-180)
*  75       Servo5 Servo Close Position (0-180)
*  76       Servo6 Servo Close Position (0-180)
*  77       Servo7 Servo Close Position (0-180)
*  78       Servo8 Servo Close Position (0-180)
*  79       Servo9 Servo Close Position (0-180)
*  80       Servo10 Servo Close Position (0-180)
*  81       Servo11 Servo Close Position (0-180)

*/

#define ADDR_MARCDUINOVERSION   0x00
#define ADDR_MARCDUINOTYPE      0x01
#define ADDR_STARTUPSOUND       0x02

#define ADDR_MARCDUINOMP3PLAYER 0x04
#define ADDR_DISABLERANDOMSOUND 0x05
#define ADDR_STARTUPSOUNDNR     0x06

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

        MarcDuinoType getType();
        void setType(const MarcDuinoType type);

        MarcDuinoMP3PlayerType getMP3Player();
        void setMP3Player(const MarcDuinoMP3PlayerType type);

        byte getStartupSound();
        void setStartupSound(const byte SoundNr);

        // NEW: store SoundNr directly without old mapping
        byte getStartupSoundNr();
        void setStartupSoundNr(const byte SoundNr);

        byte getDisableRandomSound();
        void setDisableRandomSound(const byte DisableRandomSound);

        void dumpToSerial();
};

#endif // __MARCDUINOSTORAGE_H__