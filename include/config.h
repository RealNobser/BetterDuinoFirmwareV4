#ifndef __CONFIG_H__
#define __CONFIG_H__

// #define DEBUG_MSG            // Additional Log Messages to Serial
#define INCLUDE_BODY_MASTER  // Uncomment to include Body Controller in combined firmware


// #define DEDICATED_FIRMWARE   // Separate Hex Files for Master/Slave/Body
// Choose one:
// #define DEDICATED_MASTER
// #define DEDICATED_SLAVE
// #define DEDICATED_BODY

#define SERIAL_BAUD         9600
#define SERIAL_SLAVE_BAUD   9600
#define SERIAL_MP3_BAUD     9600
#define SERIAL_TEECES_BAUD  2400
#define SERIAL_MAGIC_BAUD   9600

#define SERIALBUFFERSIZE    16

#define HEARTBEAT_MILLIS    1000

#define MINRANDOMPAUSE 6        // In Seconds!
#define MAXRANDOMPAUSE 12       // In Seconds!

#define MAX_SOUND_BANK  9
#define MAX_BANK_SOUND  25

// Original Marcduino Default Values
#define PANEL_OPN   1000 // Open
#define PANEL_CLS   2000 // Closed

#define HOLO_MIN    1000
#define HOLO_MAX    2000

#define SERVO_SPEED_FULL        0
#define SERVO_SPEED_FAST        255
#define SERVO_SPEED_MEDIUM      175
#define SERVO_SPEED_SLOW        100
#define SERVO_SPEED_SUPER_SLOW  50

#define SERVO_BUZZ_MILLIS       2000

// #define DIGITAL_JEDI

// DO NOT EDIT BELOW THIS LINE UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
// ------------------------------------------------

//
// Module Specific stuff
//
#define VERSION         "4.1.0"
#define HW_VERSION      "1.5.3"
#define CONFIG_VERSION  41

#define MAX_MARCUDINOSERVOS 13
#define MAX_SEQUENCE_COMPLETION_CALLBACKS 5
#define MAX_MARCDUINOHOLOS  3

// Panel Sequence Position. No PWM value any more! Don't touch here!
// Will be opening level in percent in the future
#define _NP     255
#define _CLS    0
#define _OPN    100

// Generic GPIOs
#define P_I2C_SCL   19
#define P_I2C_SDA   18
#define P_LED2      17
#define P_RC_IN      8
#define P_SERIAL1   14
#define P_SERIAL2   15
#define P_AUX1      16

// Dome Master
#define P_SERVO_01  2
#define P_SERVO_02  3
#define P_SERVO_03  4
#define P_SERVO_04  5
#define P_SERVO_05  6
#define P_SERVO_06  9
#define P_SERVO_07  10
#define P_SERVO_08  11
#define P_SERVO_09  12
#define P_SERVO_10  13
#define P_SERVO_11  7
#define I2C_DOME_MASTER

// Dome Slave
#define P_HPF_V     2
#define P_HPF_H     3
#define P_HPR_V     4
#define P_HPR_H     5
#define P_HPT_V     6
#define P_HPT_H     9
#define P_FL        10
#define P_RL        11
#define P_TL        12
#define P_SERVO_12  13
#define P_SERVO_13  7
#define I2C_DOME_SLAVE

// Body Master
#define P_DPL            2
#define P_UTIL_ARM_U     3 
#define P_UTIL_ARM_L     4
#define P_LEFT_BDY_DR    5
#define P_LEFT_ARM       6
#define P_LEFT_ARM_TOOL  9
#define P_RIGHT_BDY_DR   10
#define P_RIGHT_ARM      11
#define P_RIGHT_ARM_TOOL 12
#define P_CHRG_BAY_DR    13
#define P_RFU            7
#define I2C_BODY_MASTER

#endif // __CONFIG_H__