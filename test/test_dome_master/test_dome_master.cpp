// Dome Master: panel commands, ranges, forwarding to the slave, servo buzz handling, AUX1, dome lift.
#include <unity.h>
#include "Harness.h"

using namespace harness;
typedef MDuinoStorage::MDuinoMP3PlayerType Player;

static std::unique_ptr<Testable<DomeMasterT>> md;

void setUp() { md = bootMaster(Player::MP3Trigger, false); clearOutputs(); }
void tearDown() { md.reset(); }

static void cmd(const char* c) { md->parseCommand(c); }
static std::string& slaveOut() { return Serial1.out; }

static bool anyServoTouched()
{
    for (int i = 1; i <= 11; i++)
        if (Servo[i].writeCount || Servo[i].attachCount) return true;
    return false;
}

// --- boot -----------------------------------------------------------------------

static void test_boot_forces_slave_mode_and_inits_panels()
{
    md = bootMaster(Player::MP3Trigger, true);      // servo init enabled (factory default)
    TEST_ASSERT_TRUE(slaveOut().find("#MD01\r") != std::string::npos);
    TEST_ASSERT_TRUE(slaveOut().find(":SE00\r") != std::string::npos);   // slave closes its panels too
#ifdef CHOPPER
    const int last = 10;                            // Chopper init table leaves servo 11 untouched (_NP)
#else
    const int last = 11;
#endif
    md->pump(30000);                                // init tables may be staggered over several steps
    TEST_ASSERT_FALSE(md->sequencer().isActive());
    for (int i = 1; i <= last; i++)
        TEST_ASSERT_GREATER_THAN_MESSAGE(0, Servo[i].writeCount, "SE00 at boot must address all master panels");
}

static void test_boot_uses_correct_pins()
{
    const uint8_t pins[] = {0, P_SERVO_01, P_SERVO_02, P_SERVO_03, P_SERVO_04, P_SERVO_05, P_SERVO_06,
                            P_SERVO_07, P_SERVO_08, P_SERVO_09, P_SERVO_10, P_SERVO_11};
    cmd(":OP00");
    for (int i = 1; i <= 11; i++)
        TEST_ASSERT_EQUAL_UINT8(pins[i], Servo[i].pin);
}

// --- open/close/lock ------------------------------------------------------------------

static void test_open_close_single_panel_uses_eeprom_positions()
{
    cmd("#SO031100");
    cmd("#SC031900");
    cmd(":OP03");
    TEST_ASSERT_EQUAL_UINT16(1100, Servo[3].value);
    cmd(":CL03");
    TEST_ASSERT_EQUAL_UINT16(1900, Servo[3].value);
}

static void test_open_close_use_stored_per_panel_speed()
{
    cmd("#SP030120");
    cmd("#SP040030");
    cmd(":OP03");
    TEST_ASSERT_EQUAL_UINT8(120, Servo[3].speed);
    cmd(":CL03");
    TEST_ASSERT_EQUAL_UINT8(120, Servo[3].speed);
    cmd(":OP00");                                   // group commands use each panel's own speed
    TEST_ASSERT_EQUAL_UINT8(120, Servo[3].speed);
    TEST_ASSERT_EQUAL_UINT8(30, Servo[4].speed);
    TEST_ASSERT_EQUAL_UINT8(0, Servo[5].speed);     // factory default 0 = full speed
}

static void test_open_all_also_opens_slave()
{
    cmd(":OP00");
    for (int i = 1; i <= 11; i++) TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[i].value);
    TEST_ASSERT_EQUAL_STRING(":OP00\r", slaveOut().c_str());
}

static void test_close_all()
{
    cmd(":OP00");
    cmd(":CL00");
    for (int i = 1; i <= 11; i++) TEST_ASSERT_EQUAL_UINT16(PANEL_CLS, Servo[i].value);
}

static void test_open_top_and_bottom_groups()
{
    cmd(":OP14");                                    // top: 7..11
    for (int i = 1; i <= 6; i++) TEST_ASSERT_FALSE(Servo[i].attached());
    for (int i = 7; i <= 11; i++) TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[i].value);
    cmd(":OP15");                                    // bottom: 1..6
    for (int i = 1; i <= 6; i++) TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[i].value);
}

static void test_slave_panels_are_forwarded()
{
    cmd(":OP12");
    cmd(":CL13");
    cmd(":MV121400");
    TEST_ASSERT_EQUAL_STRING(":OP12\r:CL13\r:MV121400\r", slaveOut().c_str());
    TEST_ASSERT_FALSE(anyServoTouched());
}

static void test_invalid_panel_numbers_are_ignored()
{
    const char* c[] = {":OP16", ":OP99", ":CL16", ":LK99", ":UL50", ":ST77", ":OP-1"};
    for (auto x : c) cmd(x);
    TEST_ASSERT_FALSE(anyServoTouched());
}

// Documented behaviour (as in the original MarcDuino firmware): non-numeric parameters parse as 0 = "all"
static void test_non_numeric_panel_parameter_means_all()
{
    cmd(":OPxx");
    for (int i = 1; i <= 11; i++) TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[i].value);
}

static void test_lock_prevents_movement_until_unlock()
{
    cmd(":LK04");
    cmd(":OP04");
    TEST_ASSERT_FALSE(Servo[4].attached());
    cmd(":UL04");
    cmd(":OP04");
    TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, Servo[4].value);
}

static void test_lock_all_and_unlock_all()
{
    cmd(":LK00");
    cmd(":OP00");
    TEST_ASSERT_FALSE(anyServoTouched());
    cmd(":UL00");
    cmd(":OP00");
    TEST_ASSERT_TRUE(Servo[11].attached());
}

static void test_stop_detaches_servo()
{
    cmd(":OP05");
    cmd(":ST05");
    TEST_ASSERT_FALSE(Servo[5].attached());
    cmd(":OP00");
    cmd(":ST00");
    for (int i = 1; i <= 11; i++) TEST_ASSERT_FALSE(Servo[i].attached());
    TEST_ASSERT_TRUE(slaveOut().find(":ST00\r") != std::string::npos);
}

// --- :MV move command ---------------------------------------------------------------

static void test_move_panel_to_absolute_position_with_stored_speed()
{
    cmd("#SP060077");
    cmd(":MV061234");
    TEST_ASSERT_EQUAL_UINT16(1234, Servo[6].value);
    TEST_ASSERT_EQUAL_UINT8(77, Servo[6].speed);
}

// Regression: :MV00 dereferenced Panels[0] == nullptr
static void test_move_panel_zero_does_not_crash()
{
    cmd(":MV00");
    cmd(":MV001500");
    TEST_ASSERT_FALSE(anyServoTouched());
}

static void test_move_invalid_panel_ignored()
{
    cmd(":MV141500");
    cmd(":MV991500");
    TEST_ASSERT_FALSE(anyServoTouched());
}

// --- forwarding ------------------------------------------------------------------------

static void test_holo_display_and_alt_holo_commands_are_forwarded()
{
    cmd("*ON00");
    cmd("@0T5");
    cmd("%T00");
    TEST_ASSERT_EQUAL_STRING("*ON00\r@0T5\r%T00\r", slaveOut().c_str());
}

static void test_raw_forward_strips_prefix()
{
    cmd(">HELLO");
    TEST_ASSERT_EQUAL_STRING("HELLO\r", slaveOut().c_str());
}

static void test_sequence_command_is_forwarded()
{
    cmd(":SE00");
    TEST_ASSERT_TRUE(slaveOut().find(":SE00\r") == 0);
}

static void test_dome_lift_command_goes_to_lift_serial()
{
    Serial.clearOutput();
    cmd(":LI01");
    TEST_ASSERT_EQUAL_STRING(":LI01\r", Serial.out.c_str());     // SERIAL_LIFT_TYPE defaults to Serial
}

static void test_unknown_prefix_ignored()
{
    cmd("?XX00");
    cmd("XYZ");
    TEST_ASSERT_EQUAL_STRING("", slaveOut().c_str());
    TEST_ASSERT_FALSE(anyServoTouched());
}

// --- servo buzz handling ------------------------------------------------------------

static void test_idle_servos_are_detached_after_buzz_interval()
{
    cmd(":OP02");
    TEST_ASSERT_TRUE(Servo[2].attached());
    md->pump(SERVO_BUZZ_MILLIS + 100);
    TEST_ASSERT_FALSE(Servo[2].attached());
}

static void test_moving_servos_are_not_detached()
{
    cmd(":OP02");
    Servo[2].moving = true;
    md->pump(SERVO_BUZZ_MILLIS + 100);
    TEST_ASSERT_TRUE(Servo[2].attached());
}

static void test_buzz_disabled_during_sequence_and_restored_afterwards()
{
    cmd(":SE00");
    TEST_ASSERT_EQUAL_UINT32(0, md->servoBuzzInterval());
    md->pump(60000);
    TEST_ASSERT_FALSE(md->sequencer().isActive());
    TEST_ASSERT_EQUAL_UINT32(SERVO_BUZZ_MILLIS, md->servoBuzzInterval());
}

// Regression: sequence numbers without panel table left buzz handling disabled forever
static void test_buzz_restored_for_sequence_without_panel_table()
{
    cmd(":SE99");
    TEST_ASSERT_FALSE(md->sequencer().isActive());
    TEST_ASSERT_EQUAL_UINT32(SERVO_BUZZ_MILLIS, md->servoBuzzInterval());
#ifdef R2D2
    cmd(":SE15");                                    // R2: "scream, no panels"
    TEST_ASSERT_EQUAL_UINT32(SERVO_BUZZ_MILLIS, md->servoBuzzInterval());
#endif
}

// --- AUX1 -------------------------------------------------------------------------------

static void test_aux1_timed()
{
    cmd(":EO05");
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_AUX1]);
    md->pump(4900);
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_AUX1]);
    md->pump(200);
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_AUX1]);
}

static void test_aux1_permanent_on_and_off()
{
    cmd(":EO99");
    md->pump(200000, 1000);
    TEST_ASSERT_EQUAL_UINT8(HIGH, mock::pinStates[P_AUX1]);
    cmd(":EO00");
    TEST_ASSERT_EQUAL_UINT8(LOW, mock::pinStates[P_AUX1]);
}

// Regression: Duration*1000 overflowed 16 bit (70 s became 4.4 s)
static void test_aux1_long_duration_no_overflow()
{
    cmd(":EO70");
    TEST_ASSERT_EQUAL_UINT32(70000UL, md->aux1Duration());
}

// --- heartbeat --------------------------------------------------------------------------

static void test_heartbeat_led_toggles()
{
    uint8_t before = mock::pinStates[P_LED2];
    md->pump(HEARTBEAT_MILLIS + 20);
    TEST_ASSERT_NOT_EQUAL(before, mock::pinStates[P_LED2]);
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_boot_forces_slave_mode_and_inits_panels);
    RUN_TEST(test_boot_uses_correct_pins);
    RUN_TEST(test_open_close_single_panel_uses_eeprom_positions);
    RUN_TEST(test_open_close_use_stored_per_panel_speed);
    RUN_TEST(test_open_all_also_opens_slave);
    RUN_TEST(test_close_all);
    RUN_TEST(test_open_top_and_bottom_groups);
    RUN_TEST(test_slave_panels_are_forwarded);
    RUN_TEST(test_invalid_panel_numbers_are_ignored);
    RUN_TEST(test_non_numeric_panel_parameter_means_all);
    RUN_TEST(test_lock_prevents_movement_until_unlock);
    RUN_TEST(test_lock_all_and_unlock_all);
    RUN_TEST(test_stop_detaches_servo);
    RUN_TEST(test_move_panel_to_absolute_position_with_stored_speed);
    RUN_TEST(test_move_panel_zero_does_not_crash);
    RUN_TEST(test_move_invalid_panel_ignored);
    RUN_TEST(test_holo_display_and_alt_holo_commands_are_forwarded);
    RUN_TEST(test_raw_forward_strips_prefix);
    RUN_TEST(test_sequence_command_is_forwarded);
    RUN_TEST(test_dome_lift_command_goes_to_lift_serial);
    RUN_TEST(test_unknown_prefix_ignored);
    RUN_TEST(test_idle_servos_are_detached_after_buzz_interval);
    RUN_TEST(test_moving_servos_are_not_detached);
    RUN_TEST(test_buzz_disabled_during_sequence_and_restored_afterwards);
    RUN_TEST(test_buzz_restored_for_sequence_without_panel_table);
    RUN_TEST(test_aux1_timed);
    RUN_TEST(test_aux1_permanent_on_and_off);
    RUN_TEST(test_aux1_long_duration_no_overflow);
    RUN_TEST(test_heartbeat_led_toggles);
    return UNITY_END();
}
