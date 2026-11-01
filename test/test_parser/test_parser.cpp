// Command parsing: MDuinoBase::separateCommand, setup command parsing and the serial/I2C line assembly.
#include <unity.h>
#include "Harness.h"

using namespace harness;

static std::unique_ptr<Testable<DomeMasterT>> md;

void setUp() { md = bootMaster(MDuinoStorage::MDuinoMP3PlayerType::MP3Trigger, false); }   // no :SE00 at boot -> servos detached
void tearDown() { md.reset(); }

// --- separateCommand --------------------------------------------------------

static void test_separate_minimal_command()
{
    char cmd[3] = {0};
    unsigned int p = 99, ext = 99;
    TEST_ASSERT_TRUE(md->separate(":SE05", cmd, p, ext));
    TEST_ASSERT_EQUAL_STRING("SE", cmd);
    TEST_ASSERT_EQUAL_UINT(5, p);
}

static void test_separate_with_extension()
{
    char cmd[3] = {0};
    unsigned int p = 0, ext = 0;
    TEST_ASSERT_TRUE(md->separate(":MV011500", cmd, p, ext));
    TEST_ASSERT_EQUAL_STRING("MV", cmd);
    TEST_ASSERT_EQUAL_UINT(1, p);
    TEST_ASSERT_EQUAL_UINT(1500, ext);
}

static void test_separate_rejects_short_commands()
{
    char cmd[3] = {0};
    unsigned int p = 0, ext = 0;
    TEST_ASSERT_FALSE(md->separate("", cmd, p, ext));
    TEST_ASSERT_FALSE(md->separate(":", cmd, p, ext));
    TEST_ASSERT_FALSE(md->separate(":SE", cmd, p, ext));
    TEST_ASSERT_FALSE(md->separate(":SE0", cmd, p, ext));
}

// Regression: param_ext[16] overflowed for commands longer than 21 characters
static void test_separate_longest_possible_command_no_overflow()
{
    char cmd[3] = {0};
    unsigned int p = 0, ext = 0;
    std::string longest = "#SO01" + std::string(SERIALBUFFERSIZE - 1 - 5, '7');   // 23 chars
    TEST_ASSERT_EQUAL(SERIALBUFFERSIZE - 1, longest.size());
    TEST_ASSERT_TRUE(md->separate(longest.c_str(), cmd, p, ext));   // ASan would abort on overflow
    TEST_ASSERT_EQUAL_STRING("SO", cmd);
    TEST_ASSERT_EQUAL_UINT(1, p);
}

static void test_separate_extension_exactly_16_chars()
{
    char cmd[3] = {0};
    unsigned int p = 0, ext = 0;
    std::string c = ":MV01" + std::string("0000000000001500");   // 16 char extension (previously no NUL)
    TEST_ASSERT_TRUE(md->separate(c.c_str(), cmd, p, ext));
    TEST_ASSERT_EQUAL_UINT(1500, ext);
}

static void test_separate_garbage_numbers()
{
    char cmd[3] = {0};
    unsigned int p = 7, ext = 7;
    TEST_ASSERT_TRUE(md->separate(":SEab", cmd, p, ext));
    TEST_ASSERT_EQUAL_UINT(0, p);
    TEST_ASSERT_TRUE(md->separate(":SE-1", cmd, p, ext));
    TEST_ASSERT_EQUAL_UINT(65535, p & 0xFFFF);  // atoi(-1) -> unsigned wrap, must be rejected by range checks
}

// --- serial line assembly (MDuinoBase::run) ------------------------------------

static void test_serial_command_executes_on_cr()
{
    md->sendSerial(":OP01");
    TEST_ASSERT_FALSE(Servo[1].attached());     // not yet terminated
    md->sendSerial("\r");
    TEST_ASSERT_TRUE(Servo[1].attached());
}

static void test_serial_lf_is_ignored()
{
    md->sendSerial(":OP02\r\n:OP03\n\r");
    TEST_ASSERT_TRUE(Servo[2].attached());
    TEST_ASSERT_TRUE(Servo[3].attached());
}

static void test_serial_empty_lines_are_ignored()
{
    Serial1.clearOutput();
    md->sendSerial("\r\r\r");
    TEST_ASSERT_EQUAL_STRING("", Serial1.out.c_str());
}

// Regression: the tail of an overlong line was executed as a separate command
static void test_serial_overlong_line_tail_is_discarded()
{
    std::string smuggle = "@1M" + std::string(SERIALBUFFERSIZE - 3, 'A') + ":OP01\r";
    md->sendSerial(smuggle);
    TEST_ASSERT_FALSE_MESSAGE(Servo[1].attached(), "tail of overlong line must not be executed");

    // next regular line works again
    md->sendSerial(":OP04\r");
    TEST_ASSERT_TRUE(Servo[4].attached());
}

static void test_serial_overlong_setup_command_cannot_factory_reset()
{
    std::string smuggle = "@1M" + std::string(SERIALBUFFERSIZE - 3, 'A') + "#RS01\r";
    TEST_ASSERT_FALSE(causesReset([&] { md->sendSerial(smuggle); }));
}

static void test_serial_command_of_max_length_is_executed()
{
    // 23 chars + CR fits exactly
    std::string cmd = ":OP05" + std::string(SERIALBUFFERSIZE - 1 - 5, ' ') + "\r";
    md->sendSerial(cmd);
    TEST_ASSERT_TRUE(Servo[5].attached());
}

// --- I2C slave receive path ----------------------------------------------------

static void test_i2c_without_callback_receives_nothing()
{
    // Without Wire.onReceive (registered in main.cpp) the AVR core drops slave data
    Wire.onReceiveCb = nullptr;
    md->sendWire(":OP06\r");
    TEST_ASSERT_FALSE(Servo[6].attached());
}

static void onRx(int) {}

static void test_i2c_command_executes()
{
    Wire.onReceive(onRx);
    md->sendWire(":OP06\r");
    TEST_ASSERT_TRUE(Servo[6].attached());
}

static void test_i2c_overlong_line_tail_is_discarded()
{
    Wire.onReceive(onRx);
    md->sendWire("@1M" + std::string(SERIALBUFFERSIZE - 3, 'A') + ":OP07\r");
    TEST_ASSERT_FALSE(Servo[7].attached());
    md->sendWire(":OP08\r");
    TEST_ASSERT_TRUE(Servo[8].attached());
}

static void test_i2c_empty_command_ignored()
{
    Wire.onReceive(onRx);
    Serial1.clearOutput();
    md->sendWire("\r");
    TEST_ASSERT_EQUAL_STRING("", Serial1.out.c_str());
}

// --- echo mode ------------------------------------------------------------------

static void test_echo_mode_echoes_input()
{
    md->sendSerial("#EC01\r");
    TEST_ASSERT_TRUE(md->isEchoMode());
    Serial.clearOutput();
    md->sendSerial(":OP01\r");
    TEST_ASSERT_EQUAL_STRING(":OP01\r\n", Serial.out.c_str());
    md->sendSerial("#EC00\r");
    TEST_ASSERT_FALSE(md->isEchoMode());
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_separate_minimal_command);
    RUN_TEST(test_separate_with_extension);
    RUN_TEST(test_separate_rejects_short_commands);
    RUN_TEST(test_separate_longest_possible_command_no_overflow);
    RUN_TEST(test_separate_extension_exactly_16_chars);
    RUN_TEST(test_separate_garbage_numbers);
    RUN_TEST(test_serial_command_executes_on_cr);
    RUN_TEST(test_serial_lf_is_ignored);
    RUN_TEST(test_serial_empty_lines_are_ignored);
    RUN_TEST(test_serial_overlong_line_tail_is_discarded);
    RUN_TEST(test_serial_overlong_setup_command_cannot_factory_reset);
    RUN_TEST(test_serial_command_of_max_length_is_executed);
    RUN_TEST(test_i2c_without_callback_receives_nothing);
    RUN_TEST(test_i2c_command_executes);
    RUN_TEST(test_i2c_overlong_line_tail_is_discarded);
    RUN_TEST(test_i2c_empty_command_ignored);
    RUN_TEST(test_echo_mode_echoes_input);
    return UNITY_END();
}
