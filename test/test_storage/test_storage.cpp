// EEPROM storage: factory defaults, documented address map, bounds, and all '#' setup commands.
#include <unity.h>
#include <set>
#include "Harness.h"

using namespace harness;
typedef MDuinoStorage::MDuinoType Type;
typedef MDuinoStorage::MDuinoMP3PlayerType Player;

static std::unique_ptr<Testable<DomeMasterT>> md;
static MDuinoStorage storage;

void setUp() { md = bootMaster(Player::MP3Trigger, false); EEPROM.clearCounters(); }
void tearDown() { md.reset(); }

static void cmd(const char* c) { md->parseCommand(c); }

// --- factory defaults ------------------------------------------------------------

static void test_first_boot_performs_factory_reset_and_reboot()
{
    resetHardware();
    Testable<DomeMasterT> t;
    TEST_ASSERT_TRUE(causesReset([&] { t.init(); }));
    TEST_ASSERT_EQUAL_UINT8(CONFIG_VERSION, EEPROM.read(ADDR_MDUINOVERSION));
}

static void test_factory_defaults()
{
    resetHardware();
    {
        Testable<DomeMasterT> t;
        causesReset([&] { t.init(); });
    }
    TEST_ASSERT_TRUE(Type::DomeMaster == storage.getType());
    TEST_ASSERT_TRUE(Player::MP3Trigger == storage.getMP3Player());
    TEST_ASSERT_EQUAL_UINT8(255, storage.getStartupSoundNr());
    TEST_ASSERT_EQUAL_UINT8(0, storage.getDisableRandomSound());
    TEST_ASSERT_FALSE(storage.getEchoMode());
    TEST_ASSERT_EQUAL_UINT8(MINRANDOMPAUSE, storage.getMinRandomPause());
    TEST_ASSERT_EQUAL_UINT8(MAXRANDOMPAUSE, storage.getMaxRandomPause());
    TEST_ASSERT_EQUAL_UINT8(1, storage.getServoInit());

    const byte maxSounds[] = {0, 19, 18, 7, 4, 3, 3, 3, 6, 8};
    for (byte b = 1; b <= MAX_SOUND_BANK; b++)
        TEST_ASSERT_EQUAL_UINT8(maxSounds[b], storage.getMaxSound(b));

    for (byte s = 1; s <= MAX_MARCUDINOSERVOS; s++)
    {
        word o = 0, c = 0;
        storage.getServoPositions(s, o, c);
        TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, o);
        TEST_ASSERT_EQUAL_UINT16(PANEL_CLS, c);
        TEST_ASSERT_EQUAL_UINT8(0, storage.getServoSpeed(s));
    }
    for (byte h = 1; h <= MAX_MDUINOHOLOS; h++)
    {
        word hmin, hmax, vmin, vmax;
        storage.getHoloPositions(h, hmin, hmax, vmin, vmax);
        TEST_ASSERT_EQUAL_UINT16(HOLO_MIN, hmin);
        TEST_ASSERT_EQUAL_UINT16(HOLO_MAX, hmax);
        TEST_ASSERT_EQUAL_UINT16(HOLO_MIN, vmin);
        TEST_ASSERT_EQUAL_UINT16(HOLO_MAX, vmax);
        TEST_ASSERT_TRUE(storage.getHoloLightHighActive(h));
        TEST_ASSERT_FALSE(storage.getHoloNeoPixel(h));
        TEST_ASSERT_EQUAL_UINT8(7, storage.getHoloLEDs(h));
    }
}

static void test_second_boot_does_not_reset()
{
    Testable<DomeMasterT> t;
    TEST_ASSERT_FALSE(causesReset([&] { t.init(); }));
}

static void test_config_version_mismatch_triggers_factory_reset()
{
    storage.setServoPositions(3, 1111, 2222);
    EEPROM.write(ADDR_MDUINOVERSION, CONFIG_VERSION - 1);
    Testable<DomeMasterT> t;
    TEST_ASSERT_TRUE(causesReset([&] { t.init(); }));
    word o, c;
    storage.getServoPositions(3, o, c);
    TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, o);
}

static void test_unknown_type_in_eeprom_is_reported_unknown()
{
    EEPROM.write(ADDR_MDUINOTYPE, 0x77);
    TEST_ASSERT_TRUE(Type::unknown == storage.getType());
    EEPROM.write(ADDR_MDUINOMP3PLAYER, 0x77);
    TEST_ASSERT_TRUE(Player::unknown == storage.getMP3Player());
}

// --- documented address map (include/MDuinoStorage.h) -----------------------------

static void test_address_map_servos()
{
    for (byte s = 1; s <= MAX_MARCUDINOSERVOS; s++)
    {
        storage.setServoPositions(s, 600 + s, 2300 - s);
        storage.setServoSpeed(s, 100 + s);
        TEST_ASSERT_EQUAL_UINT16(600 + s, EEPROM.word16(0x40 + 2 * s));
        TEST_ASSERT_EQUAL_UINT16(2300 - s, EEPROM.word16(0x60 + 2 * s));
        TEST_ASSERT_EQUAL_UINT8(100 + s, EEPROM.read(0x30 + s));
    }
}

static void test_address_map_holos()
{
    for (byte h = 1; h <= MAX_MDUINOHOLOS; h++)
    {
        storage.setHoloPositions(h, 700 + h, 1700 + h, 800 + h, 1800 + h);
        TEST_ASSERT_EQUAL_UINT16(700 + h, EEPROM.word16(0xb0 + 4 * h));
        TEST_ASSERT_EQUAL_UINT16(800 + h, EEPROM.word16(0xb2 + 4 * h));
        TEST_ASSERT_EQUAL_UINT16(1700 + h, EEPROM.word16(0xc0 + 4 * h));
        TEST_ASSERT_EQUAL_UINT16(1800 + h, EEPROM.word16(0xc2 + 4 * h));

        storage.setHoloServoSpeed(h, 10 + h, 20 + h);
        TEST_ASSERT_EQUAL_UINT8(10 + h, EEPROM.read(0xe0 + 2 * h));
        TEST_ASSERT_EQUAL_UINT8(20 + h, EEPROM.read(0xe1 + 2 * h));

        storage.setHoloLightHighActive(h, false);
        TEST_ASSERT_EQUAL_UINT8(0, EEPROM.read(0xd0 + h));
        storage.setHoloNeoPixel(h, true);
        TEST_ASSERT_EQUAL_UINT8(1, EEPROM.read(0xd3 + h));
        storage.setHoloLEDs(h, 12 + h);
        TEST_ASSERT_EQUAL_UINT8(12 + h, EEPROM.read(0xd6 + h));
    }
}

static void test_address_map_misc()
{
    storage.setType(Type::BodyMaster);           TEST_ASSERT_EQUAL_UINT8(2, EEPROM.read(0x01));
    storage.setMP3Player(Player::Vocalizer);     TEST_ASSERT_EQUAL_UINT8(2, EEPROM.read(0x04));
    storage.setDisableRandomSound(2);            TEST_ASSERT_EQUAL_UINT8(2, EEPROM.read(0x05));
    storage.setStartupSoundNr(42);               TEST_ASSERT_EQUAL_UINT8(42, EEPROM.read(0x06));
    storage.setMinRandomPause(3);                TEST_ASSERT_EQUAL_UINT8(3, EEPROM.read(0x0a));
    storage.setMaxRandomPause(30);               TEST_ASSERT_EQUAL_UINT8(30, EEPROM.read(0x0b));
    storage.setEchoMode(true);                   TEST_ASSERT_EQUAL_UINT8(1, EEPROM.read(0x0c));
    for (byte b = 1; b <= MAX_SOUND_BANK; b++)
    {
        storage.setMaxSound(b, b + 10);
        TEST_ASSERT_EQUAL_UINT8(b + 10, EEPROM.read(0x10 + b));
    }
}

static void test_setters_reject_out_of_range_indices()
{
    EEPROM.clearCounters();
    storage.setServoPositions(MAX_MARCUDINOSERVOS + 1, 1, 2);
    storage.setServoSpeed(MAX_MARCUDINOSERVOS + 1, 1);
    storage.setHoloPositions(MAX_MDUINOHOLOS + 1, 1, 2, 3, 4);
    storage.setHoloServoSpeed(MAX_MDUINOHOLOS + 1, 1, 2);
    storage.setHoloLightHighActive(MAX_MDUINOHOLOS + 1, false);
    storage.setHoloNeoPixel(MAX_MDUINOHOLOS + 1, true);
    storage.setHoloLEDs(MAX_MDUINOHOLOS + 1, 3);
    storage.setServoPositions(255, 1, 2);
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.totalWrites);
}

static void test_get_max_sound_sanitizes_values()
{
    EEPROM.write(0x13, 200);
    TEST_ASSERT_EQUAL_UINT8(1, storage.getMaxSound(3));     // > 25 -> 1
    TEST_ASSERT_EQUAL_UINT8(1, storage.getMaxSound(10));    // invalid bank -> 1
}

static void test_update_does_not_rewrite_unchanged_values()
{
    storage.setServoPositions(4, 1234, 1900);
    EEPROM.clearCounters();
    storage.setServoPositions(4, 1234, 1900);
    storage.setStartupSoundNr(storage.getStartupSoundNr());
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.totalWrites);
}

// --- '#' setup commands ---------------------------------------------------------------

static void test_cmd_servo_open_close_speed_swap()
{
    word o, c;
    cmd("#SO051234");
    storage.getServoPositions(5, o, c);
    TEST_ASSERT_EQUAL_UINT16(1234, o);
    TEST_ASSERT_EQUAL_UINT16(PANEL_CLS, c);

    cmd("#SC050900");
    storage.getServoPositions(5, o, c);
    TEST_ASSERT_EQUAL_UINT16(900, c);

    cmd("#SW05");
    storage.getServoPositions(5, o, c);
    TEST_ASSERT_EQUAL_UINT16(900, o);
    TEST_ASSERT_EQUAL_UINT16(1234, c);

    cmd("#SP050100");
    TEST_ASSERT_EQUAL_UINT8(100, storage.getServoSpeed(5));
}

static void test_cmd_servo_init()
{
    cmd("#SI00");
    TEST_ASSERT_EQUAL_UINT8(0, storage.getServoInit());
    cmd("#SI01");
    TEST_ASSERT_EQUAL_UINT8(1, storage.getServoInit());
}

static void test_cmd_holo_positions()
{
    word hmin, hmax, vmin, vmax;
    cmd("#HO021800");
    cmd("#HC020800");
    cmd("#VO021700");
    cmd("#VC020900");
    storage.getHoloPositions(2, hmin, hmax, vmin, vmax);
    TEST_ASSERT_EQUAL_UINT16(800, hmin);
    TEST_ASSERT_EQUAL_UINT16(1800, hmax);
    TEST_ASSERT_EQUAL_UINT16(900, vmin);
    TEST_ASSERT_EQUAL_UINT16(1700, vmax);
}

static void test_cmd_sound_settings()
{
    cmd("#SS123");                  // 6 char form
    TEST_ASSERT_EQUAL_UINT8(123, storage.getStartupSoundNr());
    cmd("#SQ01");
    TEST_ASSERT_EQUAL_UINT8(1, storage.getDisableRandomSound());
    cmd("#SQ03");                   // invalid -> unchanged
    TEST_ASSERT_EQUAL_UINT8(1, storage.getDisableRandomSound());
    cmd("#SX20");
    TEST_ASSERT_EQUAL_UINT8(20, storage.getMaxRandomPause());
    cmd("#SY03");
    TEST_ASSERT_EQUAL_UINT8(3, storage.getMinRandomPause());
}

static void test_cmd_max_sound_per_bank()
{
    cmd("#MS325");
    TEST_ASSERT_EQUAL_UINT8(25, storage.getMaxSound(3));
    EEPROM.clearCounters();
    cmd("#MS026");                  // bank 0 invalid
    cmd("#MS126");                  // > 25 invalid
    cmd("#MSA05");
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.totalWrites);
}

static void test_cmd_holo_light_flags()
{
    cmd("#HL20");
    TEST_ASSERT_FALSE(storage.getHoloLightHighActive(2));
    TEST_ASSERT_TRUE(storage.getHoloLightHighActive(1));
    cmd("#HL00");                   // all
    for (byte h = 1; h <= 3; h++) TEST_ASSERT_FALSE(storage.getHoloLightHighActive(h));
    cmd("#HN31");
    TEST_ASSERT_TRUE(storage.getHoloNeoPixel(3));
}

static void test_cmd_holo_leds()
{
    cmd("#HX020012");
    TEST_ASSERT_EQUAL_UINT8(12, storage.getHoloLEDs(2));
}

// Regression: #HX00 wrote to 0xd6 = NeoPixel flag of Holo 3
static void test_cmd_holo_leds_zero_does_not_clobber_neopixel_flag()
{
    TEST_ASSERT_FALSE(storage.getHoloNeoPixel(3));
    cmd("#HX000001");
    TEST_ASSERT_FALSE(storage.getHoloNeoPixel(3));
    TEST_ASSERT_EQUAL_UINT8(0, EEPROM.read(0xd6));
}

static void test_cmd_board_mode_sets_type_and_reboots()
{
    TEST_ASSERT_TRUE(causesReset([] { cmd("#MD01"); }));
    TEST_ASSERT_TRUE(Type::DomeSlave == storage.getType());
    TEST_ASSERT_TRUE(causesReset([] { cmd("#MD02"); }));
    TEST_ASSERT_TRUE(Type::BodyMaster == storage.getType());
    TEST_ASSERT_FALSE(causesReset([] { cmd("#MD03"); }));     // invalid
    TEST_ASSERT_TRUE(Type::BodyMaster == storage.getType());
}

static void test_cmd_mp3_player_sets_type_and_reboots()
{
    TEST_ASSERT_TRUE(causesReset([] { cmd("#MP03"); }));
    TEST_ASSERT_TRUE(Player::DYPlayer == storage.getMP3Player());
    TEST_ASSERT_FALSE(causesReset([] { cmd("#MP04"); }));     // invalid
    TEST_ASSERT_TRUE(Player::DYPlayer == storage.getMP3Player());
}

static void test_cmd_reboot_and_factory_reset()
{
    cmd("#SO011111");
    TEST_ASSERT_TRUE(causesReset([] { cmd("#RS00"); }));
    word o, c;
    storage.getServoPositions(1, o, c);
    TEST_ASSERT_EQUAL_UINT16(1111, o);                         // plain reboot keeps settings

    TEST_ASSERT_TRUE(causesReset([] { cmd("#RS01"); }));
    storage.getServoPositions(1, o, c);
    TEST_ASSERT_EQUAL_UINT16(PANEL_OPN, o);                    // factory reset
}

static void test_cmd_invalid_setup_commands_write_nothing()
{
    EEPROM.clearCounters();
    const char* invalid[] = {"#", "#S", "#SO", "#SO0", "#ZZ01", "#XX0012", "#MSxyz", "#SQ99", "#zz123"};
    for (auto c : invalid)
        TEST_ASSERT_FALSE(causesReset([&] { cmd(c); }));
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.totalWrites);
}

// Sweep all setup commands with all 2-digit parameters (and a large extension) and verify every
// EEPROM write lands inside the documented storage map.
static void test_setup_commands_only_write_documented_addresses()
{
    std::set<int> allowed = {0x00, 0x01, 0x04, 0x05, 0x06, 0x0a, 0x0b, 0x0c, 0x80};
    for (int a = 0x10; a <= 0x19; a++) allowed.insert(a);                 // max sounds (bank 0: global slot)
    for (int a = 0x30; a <= 0x3d; a++) allowed.insert(a);                 // servo speeds (0 = global)
    for (int a = 0x40; a <= 0x5b; a++) allowed.insert(a);                 // open positions
    for (int a = 0x60; a <= 0x7b; a++) allowed.insert(a);                 // closed positions
    for (int a = 0xb0; a <= 0xcf; a++) allowed.insert(a);                 // holo min/max (0 = global)
    for (int a = 0xd1; a <= 0xd9; a++) allowed.insert(a);                 // holo light flags / LEDs
    for (int a = 0xe0; a <= 0xe7; a++) allowed.insert(a);                 // holo speeds

    const char* cmds[] = {"SO", "SC", "SP", "SW", "SI", "HO", "HC", "VO", "VC", "SQ", "SX", "SY", "HL", "HN", "HX", "EC"};
    EEPROM.clearCounters();
    for (auto c : cmds)
    {
        for (int p = 0; p < 100; p++)
        {
            char buf[24];
            snprintf(buf, sizeof(buf), "#%s%02d65535", c, p);
            cmd(buf);
            snprintf(buf, sizeof(buf), "#%s%02d", c, p);
            cmd(buf);
        }
    }
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.outOfRange);
    for (int a = 0; a < EEPROMClass::SIZE; a++)
    {
        if (EEPROM.writes[a] == 0) continue;
        char msg[64];
        snprintf(msg, sizeof(msg), "undocumented EEPROM write at 0x%02x", a);
        TEST_ASSERT_TRUE_MESSAGE(allowed.count(a) == 1, msg);
    }
}

static void test_master_forwards_setup_commands_except_board_mode()
{
    Serial1.clearOutput();
    cmd("#SO121500");
    TEST_ASSERT_EQUAL_STRING("#SO121500\r", Serial1.out.c_str());
    Serial1.clearOutput();
    causesReset([] { cmd("#MD02"); });
    TEST_ASSERT_EQUAL_STRING("", Serial1.out.c_str());
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_boot_performs_factory_reset_and_reboot);
    RUN_TEST(test_factory_defaults);
    RUN_TEST(test_second_boot_does_not_reset);
    RUN_TEST(test_config_version_mismatch_triggers_factory_reset);
    RUN_TEST(test_unknown_type_in_eeprom_is_reported_unknown);
    RUN_TEST(test_address_map_servos);
    RUN_TEST(test_address_map_holos);
    RUN_TEST(test_address_map_misc);
    RUN_TEST(test_setters_reject_out_of_range_indices);
    RUN_TEST(test_get_max_sound_sanitizes_values);
    RUN_TEST(test_update_does_not_rewrite_unchanged_values);
    RUN_TEST(test_cmd_servo_open_close_speed_swap);
    RUN_TEST(test_cmd_servo_init);
    RUN_TEST(test_cmd_holo_positions);
    RUN_TEST(test_cmd_sound_settings);
    RUN_TEST(test_cmd_max_sound_per_bank);
    RUN_TEST(test_cmd_holo_light_flags);
    RUN_TEST(test_cmd_holo_leds);
    RUN_TEST(test_cmd_holo_leds_zero_does_not_clobber_neopixel_flag);
    RUN_TEST(test_cmd_board_mode_sets_type_and_reboots);
    RUN_TEST(test_cmd_mp3_player_sets_type_and_reboots);
    RUN_TEST(test_cmd_reboot_and_factory_reset);
    RUN_TEST(test_cmd_invalid_setup_commands_write_nothing);
    RUN_TEST(test_setup_commands_only_write_documented_addresses);
    RUN_TEST(test_master_forwards_setup_commands_except_board_mode);
    return UNITY_END();
}
