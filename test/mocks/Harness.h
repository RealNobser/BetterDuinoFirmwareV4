// Test harness: constructs firmware role objects against the mocks and exposes internals.
#ifndef TEST_HARNESS_H
#define TEST_HARNESS_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SendOnlySoftwareSerial.h>
#include <VarSpeedServo.h>
#include <memory>
#include <string>
#include <utility>

#include "config.h"
#include "MDuinoStorage.h"
#include "Panel.h"
#include "Holo.h"

#if defined(R2D2)
#include "MDuinoDomeMasterR2.h"
#include "MDuinoDomeSlaveR2.h"
#include "MDuinoBodyMasterR2.h"
typedef MDuinoDomeMasterR2 DomeMasterT;
typedef MDuinoDomeSlaveR2  DomeSlaveT;
typedef MDuinoBodyMasterR2 BodyMasterT;
#elif defined(CHOPPER)
#include "MDuinoDomeMasterChopper.h"
#include "MDuinoDomeSlaveChopper.h"
#include "MDuinoBodyMasterChopper.h"
typedef MDuinoDomeMasterChopper DomeMasterT;
typedef MDuinoDomeSlaveChopper  DomeSlaveT;
typedef MDuinoBodyMasterChopper BodyMasterT;
#elif defined(BT1)
#include "MDuinoDomeMasterBT1.h"
#include "MDuinoDomeSlaveBT1.h"
#include "MDuinoBodyMasterBT1.h"
typedef MDuinoDomeMasterBT1 DomeMasterT;
typedef MDuinoDomeSlaveBT1  DomeSlaveT;
typedef MDuinoBodyMasterBT1 BodyMasterT;
#endif

namespace harness
{
    // Same wiring as src/main.cpp
    extern SendOnlySoftwareSerial Serial1;  // Slave (Master) / Magic Panel (Slave)
    extern SendOnlySoftwareSerial Serial2;  // MP3 (Master) / Teeces (Slave)
    extern VarSpeedServo Servo[12];         // index 1..11 used

    void onReset();                         // replacement for resetFunc(): throws mock::Reset
    void resetHardware();                   // all mocks back to power-on state (EEPROM erased)
    void clearOutputs();                    // clear captured serial output
}

// Exposes protected internals of any role class for white-box tests.
template <class Base>
class Testable : public Base
{
public:
    Testable()
        : Base(harness::Serial1, harness::Serial2, Serial,
               harness::Servo[1], harness::Servo[2], harness::Servo[3], harness::Servo[4], harness::Servo[5],
               harness::Servo[6], harness::Servo[7], harness::Servo[8], harness::Servo[9], harness::Servo[10],
               harness::Servo[11])
    {
        this->resetFunc = &harness::onReset;
    }

    using Base::parseCommand;           // protected in the role classes
    using Base::processSetupCommand;
    bool separate(const char* command, char* cmd, unsigned int& p, unsigned int& p_ext)
    {
        return this->separateCommand(command, cmd, p, p_ext);
    }

    MDuinoSequencer& sequencer() { return this->Sequencer; }
    MDuinoStorage& storage() { return this->Storage; }
    unsigned long servoBuzzInterval() { return this->ServoBuzzIntervall; }
    bool isEchoMode() { return this->echoMode; }
    unsigned long aux1Duration() { return this->AUX1Duration; }

    // Only instantiated (and therefore only required to compile) where used
    Panel* panel(int i) { return this->Panels[i]; }
    Holo* holo(int i) { return this->Holos[i]; }
    MDuinoSound* sound() { return this->Sound; }
    unsigned long randomSoundInterval() { return this->RandomSoundIntervall; }
    unsigned long magicPanelInterval() { return this->MagicPanelInterval; }

    // Feed one line through the real serial receive path (MDuinoBase::run)
    void sendSerial(const std::string& line)
    {
        Serial.inject(line);
        while (Serial.available())
            this->run();
    }
    // Feed bytes through the I2C slave receive path
    void sendWire(const std::string& line)
    {
        Wire.receiveAsSlave(line);
        while (Wire.available())
            this->run();
    }
    // Let the main loop run for `ms` of virtual time
    void pump(unsigned long ms, unsigned long step = 10)
    {
        for (unsigned long t = 0; t < ms; t += step)
        {
            mock::advance(step);
            this->run();
        }
    }
};

namespace harness
{
    // Boots a role object like a real board: first boot on erased EEPROM performs the factory
    // reset (and "reboots"), then the role/player type is stored and the board boots again.
    template <class T>
    std::unique_ptr<Testable<T>> boot(MDuinoStorage::MDuinoType type,
                                      MDuinoStorage::MDuinoMP3PlayerType player = MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger,
                                      bool servoInit = true)
    {
        resetHardware();
        {
            std::unique_ptr<Testable<T>> first(new Testable<T>());
            try { first->init(); } catch (mock::Reset&) {}
        }
        MDuinoStorage storage;
        storage.setType(type);
        storage.setMP3Player(player);
        storage.setServoInit(servoInit ? 1 : 0);
        storage.setStartupSoundNr(0);   // avoid 3 s startup delay in most tests
        clearOutputs();

        std::unique_ptr<Testable<T>> t(new Testable<T>());
        t->init();
        return t;
    }

    inline std::unique_ptr<Testable<DomeMasterT>> bootMaster(MDuinoStorage::MDuinoMP3PlayerType p = MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger, bool servoInit = true)
    { return boot<DomeMasterT>(MDuinoStorage::MDuinoType::DomeMaster, p, servoInit); }
    inline std::unique_ptr<Testable<DomeSlaveT>> bootSlave(bool servoInit = true)
    { return boot<DomeSlaveT>(MDuinoStorage::MDuinoType::DomeSlave, MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger, servoInit); }
    inline std::unique_ptr<Testable<BodyMasterT>> bootBody(bool servoInit = true)
    { return boot<BodyMasterT>(MDuinoStorage::MDuinoType::BodyMaster, MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger, servoInit); }

    // Runs `fn` and reports whether it triggered a (soft) reset
    template <class F> bool causesReset(F fn)
    {
        try { fn(); } catch (mock::Reset&) { return true; }
        return false;
    }
}

#endif // TEST_HARNESS_H
