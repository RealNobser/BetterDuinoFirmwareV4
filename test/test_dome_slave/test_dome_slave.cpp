// Dome Slave: holoprojectors (light, movement, timers), magic panel, Teeces display, slave panels 12/13.
#include <unity.h>
#include "Harness.h"

using namespace harness;

static std::unique_ptr<Testable<DomeSlaveT>> sl;

void setUp() { sl = bootSlave(false); clearOutputs(); }
void tearDown() { sl.reset(); }

static void cmd(const char* c) { sl->parseCommand(c); }
static std::string& magicOut() { return Serial1.out; }
static std::string& teecesOut() { return Serial2.out; }

static const uint8_t lightPin[] = {0, P_FL, P_RL, P_TL};
static VarSpeedServo& hServo(int h) { return Servo[2 * h - 1]; }
static VarSpeedServo& vServo(int h) { return Servo[2 * h]; }

static bool anyServoTouched()
{
    for (int i = 1; i <= 11; i++)
        if (Servo[i].writeCount || Servo[i].attachCount) return true;
    return false;
}

// --- holo lights -------------------------------------------------------------------

static void test_holo_lights_off_after_boot()
{
    for (int h = 1; h <= 3; h++)
    {
        TEST_ASSERT_EQUAL_UINT8(OUTPUT, mock::pinModes[lightPin[h]]);
        TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[lightPin[h]]);
    }
}

static void test_holo_light_on_off_single_and_all()
{
    cmd("*ON02");
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_RL]);
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_FL]);
    cmd("*OF02");
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_RL]);
    cmd("*ON00");
    for (int h = 1; h <= 3; h++) TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[lightPin[h]]);
    cmd("*OF00");
    for (int h = 1; h <= 3; h++) TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[lightPin[h]]);
}

static void test_holo_light_low_active()
{
    cmd("#HL10");                                 // Holo1 low active, applied on next boot
    TEST_ASSERT_FALSE(MDuinoStorage().getHoloLightHighActive(1));
    sl.reset(new Testable<DomeSlaveT>());         // reboot with current EEPROM
    sl->init();
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_FL]);   // off == HIGH
    sl->parseCommand("*ON01");
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_FL]);
}

static void test_holo_timed_on()
{
    cmd("*H105");                                 // Holo1 on for 5 s
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_FL]);
    sl->pump(4900, 50);
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_FL]);
    sl->pump(300, 50);
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_FL]);
}

static void test_holo_flicker_toggles_and_ends()
{
    cmd("*F102");
    int toggles = 0;
    uint8_t last = mock::pinStates[P_FL];
    for (int i = 0; i < 150; i++)
    {
        sl->pump(10, 10);
        if (mock::pinStates[P_FL] != last) { toggles++; last = mock::pinStates[P_FL]; }
    }
    TEST_ASSERT_GREATER_THAN(2, toggles);
    sl->pump(2000, 50);
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_FL]);
}

static void test_holo_invalid_numbers_ignored()
{
    cmd("*ON09");
    cmd("*OF55");
    cmd("*CH07");
    cmd("*RD99");                                 // > 3 means "all" for movement control
    cmd("*ST00");
    for (int h = 1; h <= 3; h++) TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[lightPin[h]]);
}

// --- holo movement -----------------------------------------------------------------

static void test_holo_center()
{
    cmd("*CH02");
    TEST_ASSERT_EQUAL_UINT16((HOLO_MIN + HOLO_MAX) / 2, hServo(2).value);
    TEST_ASSERT_EQUAL_UINT16((HOLO_MIN + HOLO_MAX) / 2, vServo(2).value);
    TEST_ASSERT_FALSE(hServo(1).attached());
}

static void test_holo_move_horizontal_only()
{
    cmd("*MH011600");
    TEST_ASSERT_EQUAL_UINT16(1600, hServo(1).value);
    TEST_ASSERT_EQUAL_UINT(0, vServo(1).writeCount);
}

static void test_holo_move_vertical_only()
{
    cmd("*MV031300");
    TEST_ASSERT_EQUAL_UINT16(1300, vServo(3).value);
    TEST_ASSERT_EQUAL_UINT(0, hServo(3).writeCount);
}

// Regression: *MV00 / *MH00 dereferenced Holos[0] == nullptr
static void test_holo_move_zero_and_out_of_range_do_not_crash()
{
    cmd("*MV00");
    cmd("*MV001500");
    cmd("*MH001500");
    cmd("*MV041500");
    cmd("*MH991500");
    TEST_ASSERT_FALSE(anyServoTouched());
}

static void test_holo_random_movement_and_stop()
{
    cmd("*RD01");
    sl->pump(20000, 50);
    unsigned writes = hServo(1).writeCount + vServo(1).writeCount;
    TEST_ASSERT_GREATER_THAN(0, writes);
    TEST_ASSERT_EQUAL_UINT(0, hServo(2).writeCount);

    cmd("*HD01");                                 // stop movement
    unsigned before = hServo(1).writeCount;
    sl->pump(20000, 50);
    TEST_ASSERT_LESS_OR_EQUAL(before + 1, hServo(1).writeCount);
}

// --- magic panel -------------------------------------------------------------------

static void test_magic_panel_on_off()
{
    cmd("*MO99");
    TEST_ASSERT_EQUAL_STRING("T1\r", magicOut().c_str());
    cmd("*MO00");
    TEST_ASSERT_EQUAL_STRING("T1\rT0\r", magicOut().c_str());
}

static void test_magic_panel_timer()
{
    cmd("*MO05");
    sl->pump(4900, 100);
    TEST_ASSERT_TRUE(magicOut().find("T0\r") == std::string::npos);
    sl->pump(300, 100);
    TEST_ASSERT_TRUE(magicOut().find("T0\r") != std::string::npos);
}

// Regression: param * 1000 overflowed 16 bit (signed for *MO -> ~49 days, wrapped for *MF)
static void test_magic_panel_long_durations_no_overflow()
{
    cmd("*MO40");
    TEST_ASSERT_EQUAL_UINT32(40000UL, sl->magicPanelInterval());
    cmd("*MF70");
    TEST_ASSERT_EQUAL_UINT32(70000UL, sl->magicPanelInterval());
    TEST_ASSERT_TRUE(magicOut().find("T42\r") != std::string::npos);
}

// --- display ----------------------------------------------------------------------

static void test_display_commands_go_to_teeces_stripped()
{
    cmd("@0T5");
    cmd("!1MHELLO");
    TEST_ASSERT_EQUAL_STRING("0T5\r1MHELLO\r", teecesOut().c_str());
}

static void test_sound_commands_are_ignored()
{
    cmd("$312");
    TEST_ASSERT_EQUAL_STRING("", teecesOut().c_str());
    TEST_ASSERT_EQUAL_STRING("", magicOut().c_str());
}

// --- slave panels 12/13 ------------------------------------------------------------

static void test_slave_panels_open_close()
{
    cmd(":OP12");
    TEST_ASSERT_EQUAL_UINT8(P_SERVO_12, Servo[10].pin);
    TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[10].value);
    cmd(":OP00");
    TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[11].value);
    cmd(":CL13");
    TEST_ASSERT_EQUAL_UINT16(PANEL_CLS, Servo[11].value);
}

static void test_slave_panels_use_stored_speed()
{
    cmd("#SP130077");
    cmd(":OP13");
    TEST_ASSERT_EQUAL_UINT8(77, Servo[11].speed);
    cmd(":CL13");
    TEST_ASSERT_EQUAL_UINT8(77, Servo[11].speed);
}

static void test_slave_master_panel_numbers_ignored()
{
    cmd(":OP05");
    cmd(":CL01");
    cmd(":LK11");
    TEST_ASSERT_FALSE(anyServoTouched());
}

// Regression: on the slave only Panels[12..13] exist; :MV00..:MV11 dereferenced nullptr
static void test_slave_move_non_existing_panels_does_not_crash()
{
    for (int p = 0; p <= 11; p++)
    {
        char buf[16];
        snprintf(buf, sizeof(buf), ":MV%02d1500", p);
        cmd(buf);
    }
    TEST_ASSERT_FALSE(anyServoTouched());
    cmd(":MV131400");
    TEST_ASSERT_EQUAL_UINT16(1400, Servo[11].value);
}

// --- role switch ------------------------------------------------------------------

static void test_slave_accepts_board_mode_command()
{
    TEST_ASSERT_TRUE(causesReset([] { cmd("#MD00"); }));
    TEST_ASSERT_TRUE(MDuinoStorage::MDuinoType::DomeMaster == MDuinoStorage().getType());
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_holo_lights_off_after_boot);
    RUN_TEST(test_holo_light_on_off_single_and_all);
    RUN_TEST(test_holo_light_low_active);
    RUN_TEST(test_holo_timed_on);
    RUN_TEST(test_holo_flicker_toggles_and_ends);
    RUN_TEST(test_holo_invalid_numbers_ignored);
    RUN_TEST(test_holo_center);
    RUN_TEST(test_holo_move_horizontal_only);
    RUN_TEST(test_holo_move_vertical_only);
    RUN_TEST(test_holo_move_zero_and_out_of_range_do_not_crash);
    RUN_TEST(test_holo_random_movement_and_stop);
    RUN_TEST(test_magic_panel_on_off);
    RUN_TEST(test_magic_panel_timer);
    RUN_TEST(test_magic_panel_long_durations_no_overflow);
    RUN_TEST(test_display_commands_go_to_teeces_stripped);
    RUN_TEST(test_sound_commands_are_ignored);
    RUN_TEST(test_slave_panels_open_close);
    RUN_TEST(test_slave_panels_use_stored_speed);
    RUN_TEST(test_slave_master_panel_numbers_ignored);
    RUN_TEST(test_slave_move_non_existing_panels_does_not_crash);
    RUN_TEST(test_slave_accepts_board_mode_command);
    return UNITY_END();
}
