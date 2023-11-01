#ifndef __CONFIG_H__
#define __CONFIG_H__

// #define DEBUG_MSG   // Additional Log Messages to Serial

#define SERIAL_BAUD         9600
#define SERIAL_SLAVE_BAUD   9600
#define SERIAL_MP3_BAUD     9600
#define SERIAL_TEECES_BAUD  9600
#define SERIAL_MAGIC_BAUD   9600

#define SERIALBUFFERSIZE    256

#define HEARTBEAT_MILLIS    1000

#define MINRANDOMPAUSE 6        // In Seconds!
#define MAXRANDOMPAUSE 12       // In Seconds!

#define MAX_SOUND_BANK  9
#define MAX_BANK_SOUND  25

// Original Marcduino Default Values
#define PANEL_OPN 1000 // Open
#define PANEL_MID 1750 // Mid Open
#define PANEL_CLS 2000 // Closed

// DO NOT EDIT BELOW THIS LINE
// ------------------------------------------------

//
// Module Specific stuff
//
#define VERSION         "4.0.0"
#define HW_VERSION      "1.5.3"
#define CONFIG_VERSION  40

#define MAX_MARCUDINOSERVOS 11

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
#define MAX_PANELS  11
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
#define P_TL
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


// #define P_MP3            15  // Same as above
// #define P_SLAVE          14  // Same as above

#endif // __CONFIG_H__