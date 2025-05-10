#ifndef __MDUINODOMEMASTERCHOPPER_H__
#define __MDUINODOMEMASTERCHOPPER_H__

#include <SendOnlySoftwareSerial.h>

#include "MDuinoDomeMaster.h"

/** Command implementation
 * 
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *
 * 
 */

class MDuinoDomeMasterChopper : public MDuinoDomeMaster
{
    public:
        MDuinoDomeMasterChopper(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "BetterDuino Dome Master (C1-10P)"; }

    protected:
        void playSequenceAddons(const byte SeqNr) override;
        
};

#endif  // __MDUINOBODYMASTERCHOPPER_H__