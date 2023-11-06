#ifndef __MARCDUINOBODYMASTER_H__
#define __MARCDUINOBODYMASTER_H__

#include <SendOnlySoftwareSerial.h>

#include "MarcDuinoDomeMaster.h"

/** Command implementation
 * 
 *  SAME AS DOME MASTER, but additional sequences
 *
 *	Sequences details (see sequence_command, panel sequence matrices defined in panel_sequences.h)
 *
 *	:SE30
 *	:SE31
 *	:SE32
 *	:SE33
 *	:SE34
 *	:SE35
 
 */

class MarcDuinoBodyMaster : public MarcDuinoDomeMaster
{
    public:
        MarcDuinoBodyMaster(SendOnlySoftwareSerial& Serial_Slave, SendOnlySoftwareSerial& Serial_MP3,
            VarSpeedServo& Servo1, VarSpeedServo& Servo2, VarSpeedServo& Servo3, VarSpeedServo& Servo4, VarSpeedServo& Servo5, 
            VarSpeedServo& Servo6, VarSpeedServo& Servo7, VarSpeedServo& Servo8, VarSpeedServo& Servo9, VarSpeedServo& Servo10, 
            VarSpeedServo& Servo11, VarSpeedServo& Servo12, VarSpeedServo& Servo13);

        virtual void init() override;
        virtual void run() override;

        virtual const char* getProductName() override { return "MarcDuino Body Master"; }
        // virtual void parseCommand(const char* command) override;

    protected:
        void playSequenceAddons(const unsigned int SeqNr) override;
        
};

#endif // __MARCDUINOBODYMASTER_H__
