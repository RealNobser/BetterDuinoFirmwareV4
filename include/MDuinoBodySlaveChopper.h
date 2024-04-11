#ifndef __MARCDUINOBODYSLAVECHOPPER_H__
#define __MARCDUINOBODYSLAVECHOPPER_H__

#include "MDuinoBodyMasterChopper.h"

/** Command implementation
 * 
 *  SAME AS BODY MASTER, but additional sequences
 *  used as Servo Extender
 *
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *
 */

class MDuinoBodySlaveChopper : public MDuinoBodyMasterChopper
{
    public:
        MDuinoBodySlaveChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift, 
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "MarcDuino Body Slave (C1-10P)"; }

    protected:
        void playSequence(const byte SeqNr) override;
        void playSequenceAddons(const byte SeqNr) override;
        
};

#endif  // __MARCDUINOBODYSLAVECHOPPER_H__