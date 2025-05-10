#ifndef __MDUINODOMESLAVEBT1_H__
#define __MDUINODOMESLAVEBT1_H__

#include <SendOnlySoftwareSerial.h>

#include "MDuinoDomeSlave.h"

/** Command implementation
 * 
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *
 */

class MDuinoDomeSlaveBT1 : public MDuinoDomeSlave
{
    public:
        MDuinoDomeSlaveBT1(SendOnlySoftwareSerial& Serial_Magic, SendOnlySoftwareSerial& Serial_Teeces, SERIAL_LIFT_TYPE& Serial_Lift,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "BetterDuino Dome Slave (BT-1)"; }

    protected:
        void playSequenceAddons(const byte SeqNr) override;
        
};

#endif  // __MDUINODOMESLAVEBT1_H__