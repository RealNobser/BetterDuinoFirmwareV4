#ifndef __MDUINOBODYMASTERBT1_H__
#define __MDUINOBODYMASTERBT1_H__

#include <SendOnlySoftwareSerial.h>

#include "MDuinoDomeMasterBT1.h"

/** Command implementation
 * 
 *  SAME AS DOME MASTER, but additional sequences
 *
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *
 *	:SE30 Utility Arm open and close sequence
 *	:SE31 All Body Panels open and close sequence
 *	:SE32 All Body Doors open and wiggle close sequence
 *	:SE33 Body - Use Gripper
 *	:SE34 Body - Use Interface Tool
 *	:SE35 Body - Ping Pong Body Doors
 *	:SE36 Body - Use Claws
 *	:SE37 Body - Use right Claw
 */

class MDuinoBodyMasterBT1 : public MDuinoDomeMasterBT1
{
    public:
        MDuinoBodyMasterBT1(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift, 
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "BD Body BT-1"; }

    protected:
        void playSequenceAddons(const byte SeqNr) override;
        
};

#endif // __MDUINOBODYMASTERBT1_H__
