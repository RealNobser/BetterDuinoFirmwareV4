// Sound: wire protocol of all four players, '$' command vocabulary, bank/track mapping, random sound.
#include <unity.h>
#include <vector>
#include "Harness.h"

using namespace harness;
typedef MDuinoStorage::MDuinoMP3PlayerType Player;

static std::unique_ptr<Testable<DomeMasterT>> md;

void setUp() {}
void tearDown() { md.reset(); }

static void boot(Player p)
{
    md = bootMaster(p, false);
    Serial2.clearOutput();
}
static void cmd(const char* c) { md->parseCommand(c); }
static std::vector<uint8_t> mp3() { return std::vector<uint8_t>(Serial2.out.begin(), Serial2.out.end()); }
static int track(int bank, int sound) { return (bank - 1) * 25 + sound; }

// Returns the parameter bytes of all MP3 Trigger 't' (play) commands
static std::vector<int> mp3TriggerTracks()
{
    std::vector<int> t;
    auto o = mp3();
    for (size_t i = 0; i + 1 < o.size(); i++)
        if (o[i] == 't') { t.push_back(o[i + 1]); i++; }
        else if (o[i] == 'v') i++;           // skip volume byte
    return t;
}

// --- MP3 Trigger -------------------------------------------------------------------

static void test_mp3trigger_init_sets_mid_volume()
{
    md = bootMaster(Player::MP3Trigger, false);
    // boot() clears outputs after the first (factory reset) boot; init of the second boot is visible
    auto o = mp3();
    TEST_ASSERT_GREATER_OR_EQUAL(2, o.size());
    TEST_ASSERT_EQUAL_UINT8('v', o[0]);
    TEST_ASSERT_EQUAL_UINT8(0x20, o[1]);
}

static void test_mp3trigger_play_bank_sound()
{
    boot(Player::MP3Trigger);
    cmd("$312");
    auto t = mp3TriggerTracks();
    TEST_ASSERT_EQUAL(1, t.size());
    TEST_ASSERT_EQUAL_INT(track(3, 12), t[0]);
    TEST_ASSERT_EQUAL_UINT32(0, md->randomSoundInterval());   // explicit sound stops random mode
}

static void test_mp3trigger_play_next_in_bank_wraps()
{
    boot(Player::MP3Trigger);
    cmd("#MS402");                                             // bank 4 has 2 sounds
    for (int i = 0; i < 3; i++) cmd("$4");
    auto t = mp3TriggerTracks();
    TEST_ASSERT_EQUAL(3, t.size());
    TEST_ASSERT_EQUAL_INT(track(4, 1), t[0]);
    TEST_ASSERT_EQUAL_INT(track(4, 2), t[1]);
    TEST_ASSERT_EQUAL_INT(track(4, 1), t[2]);
}

static void test_mp3trigger_named_sounds()
{
    struct { const char* c; int bank, sound; } named[] = {
        {"$L", 7, 1}, {"$C", 9, 5}, {"$c", 9, 1}, {"$S", 6, 1}, {"$D", 9, 6},
        {"$W", 9, 2}, {"$w", 9, 7}, {"$M", 9, 3}, {"$i", 9, 8},
    };
    for (auto& n : named)
    {
        boot(Player::MP3Trigger);
        cmd(n.c);
        auto t = mp3TriggerTracks();
        TEST_ASSERT_EQUAL_MESSAGE(1, t.size(), n.c);
        TEST_ASSERT_EQUAL_INT_MESSAGE(track(n.bank, n.sound), t[0], n.c);
    }
}

static void test_mp3trigger_volume_commands()
{
    boot(Player::MP3Trigger);
    cmd("$f");
    auto o = mp3();
    TEST_ASSERT_EQUAL_UINT8('v', o[o.size() - 2]);
    TEST_ASSERT_EQUAL_UINT8(0x00, o.back());                   // max
    cmd("$p");
    TEST_ASSERT_EQUAL_UINT8(0x40, mp3().back());               // min
    cmd("$m");
    TEST_ASSERT_EQUAL_UINT8(0x20, mp3().back());               // mid
    cmd("$-");
    TEST_ASSERT_EQUAL_UINT8(0x22, mp3().back());               // down = larger attenuation
    cmd("$+");
    TEST_ASSERT_EQUAL_UINT8(0x20, mp3().back());
    cmd("$O");
    TEST_ASSERT_EQUAL_UINT8(0xFF, mp3().back());               // off
    TEST_ASSERT_EQUAL_UINT32(0, md->randomSoundInterval());
}

static void test_mp3trigger_stop()
{
    boot(Player::MP3Trigger);
    cmd("$s");
    TEST_ASSERT_EQUAL_UINT8('O', mp3().back());
}

// Regression: bank 0 / sound > 25 wrapped to unrelated track numbers
static void test_invalid_bank_or_sound_plays_nothing()
{
    const char* bad[] = {"$0", "$000", "$005", "$999", "$126", "$X", "$?"};
    for (auto b : bad)
    {
        boot(Player::MP3Trigger);
        cmd(b);
        TEST_ASSERT_EQUAL_MESSAGE(0, mp3TriggerTracks().size(), b);
    }
}

static void test_highest_valid_track()
{
    boot(Player::MP3Trigger);
    cmd("$925");
    auto t = mp3TriggerTracks();
    TEST_ASSERT_EQUAL(1, t.size());
    TEST_ASSERT_EQUAL_INT(225, t[0]);
}

static void test_invalid_lengths_ignored()
{
    boot(Player::MP3Trigger);
    cmd("$");
    cmd("$12345");
    TEST_ASSERT_EQUAL(0, mp3TriggerTracks().size());
}

// --- DF Player ----------------------------------------------------------------------

static bool dfFrameValid(const std::vector<uint8_t>& o, size_t at, uint8_t command, uint8_t param)
{
    if (at + 10 > o.size()) return false;
    if (o[at] != 0x7E || o[at + 1] != 0xFF || o[at + 2] != 0x06 || o[at + 9] != 0xEF) return false;
    if (o[at + 3] != command || o[at + 6] != param) return false;
    uint16_t sum = 0;
    for (int i = 1; i <= 6; i++) sum += o[at + i];
    uint16_t chk = (uint16_t)((o[at + 7] << 8) | o[at + 8]);
    return (uint16_t)(sum + chk) == 0;
}

static void test_dfplayer_play_frame()
{
    boot(Player::DFPlayer);
    cmd("$312");
    auto o = mp3();
    TEST_ASSERT_EQUAL(20, o.size());                           // volume frame + play frame
    TEST_ASSERT_TRUE(dfFrameValid(o, 0, 0x06, 15));
    TEST_ASSERT_TRUE(dfFrameValid(o, 10, 0x12, track(3, 12)));
}

static void test_dfplayer_init_and_stop()
{
    md = bootMaster(Player::DFPlayer, false);
    auto o = mp3();
    TEST_ASSERT_TRUE(dfFrameValid(o, 0, 0x09, 0x01));          // source TF
    TEST_ASSERT_TRUE(dfFrameValid(o, 10, 0x07, 0x00));         // EQ normal
    TEST_ASSERT_TRUE(dfFrameValid(o, 20, 0x06, 15));           // volume mid
    Serial2.clearOutput();
    cmd("$s");
    o = mp3();
    TEST_ASSERT_TRUE(dfFrameValid(o, o.size() - 10, 0x16, 0x00));
}

// --- DY Player ----------------------------------------------------------------------

static void test_dyplayer_play_frame()
{
    boot(Player::DYPlayer);
    cmd("$312");
    auto o = mp3();
    // volume: AA 13 01 vol sum, play: AA 07 02 00 nr sum
    TEST_ASSERT_EQUAL(11, o.size());
    const uint8_t vol[] = {0xAA, 0x13, 0x01, 15};
    for (int i = 0; i < 4; i++) TEST_ASSERT_EQUAL_UINT8(vol[i], o[i]);
    TEST_ASSERT_EQUAL_UINT8((uint8_t)(0xAA + 0x13 + 0x01 + 15), o[4]);
    const uint8_t play[] = {0xAA, 0x07, 0x02, 0x00, (uint8_t)track(3, 12)};
    uint8_t sum = 0;
    for (int i = 0; i < 5; i++) { TEST_ASSERT_EQUAL_UINT8(play[i], o[5 + i]); sum += play[i]; }
    TEST_ASSERT_EQUAL_UINT8(sum, o[10]);
}

// --- Vocalizer ----------------------------------------------------------------------

static void test_vocalizer_play()
{
    boot(Player::Vocalizer);
    cmd("$312");
    TEST_ASSERT_TRUE(Serial2.out.find("<CA0062>") != std::string::npos);
}

static void test_vocalizer_has_vocalizer()
{
    boot(Player::Vocalizer);
    TEST_ASSERT_TRUE(md->sound()->hasVocalizer());
    boot(Player::MP3Trigger);
    TEST_ASSERT_FALSE(md->sound()->hasVocalizer());
}

// --- alt sound / random -------------------------------------------------------------

static void test_alt_sound_is_passed_through()
{
    boot(Player::MP3Trigger);
    cmd("!t\x05");
    TEST_ASSERT_EQUAL_STRING("t\x05\r", Serial2.out.c_str());
}

static void test_random_sound_plays_periodically()
{
    boot(Player::MP3Trigger);
    cmd("$R");
    md->pump((MAXRANDOMPAUSE + 1) * 1000UL * 3, 100);
    auto t = mp3TriggerTracks();
    TEST_ASSERT_GREATER_OR_EQUAL(3, t.size());
    for (int n : t)
    {
        TEST_ASSERT_GREATER_OR_EQUAL(1, n);
        TEST_ASSERT_LESS_OR_EQUAL(track(5, 25), n);            // random uses banks 1..5
    }
}

static void test_random_sound_disabled_by_setting()
{
    boot(Player::MP3Trigger);
    cmd("#SQ02");
    cmd("$R");
    md->pump(60000, 100);
    TEST_ASSERT_EQUAL(0, mp3TriggerTracks().size());
}

static void test_startup_sound()
{
    resetHardware();
    {
        Testable<DomeMasterT> first;
        causesReset([&] { first.init(); });
    }
    MDuinoStorage().setStartupSoundNr(201);
    MDuinoStorage().setServoInit(0);
    Serial2.clearOutput();
    md.reset(new Testable<DomeMasterT>());
    md->init();
    auto t = mp3TriggerTracks();
    TEST_ASSERT_EQUAL(1, t.size());
    TEST_ASSERT_EQUAL_INT(201, t[0]);
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_mp3trigger_init_sets_mid_volume);
    RUN_TEST(test_mp3trigger_play_bank_sound);
    RUN_TEST(test_mp3trigger_play_next_in_bank_wraps);
    RUN_TEST(test_mp3trigger_named_sounds);
    RUN_TEST(test_mp3trigger_volume_commands);
    RUN_TEST(test_mp3trigger_stop);
    RUN_TEST(test_invalid_bank_or_sound_plays_nothing);
    RUN_TEST(test_highest_valid_track);
    RUN_TEST(test_invalid_lengths_ignored);
    RUN_TEST(test_dfplayer_play_frame);
    RUN_TEST(test_dfplayer_init_and_stop);
    RUN_TEST(test_dyplayer_play_frame);
    RUN_TEST(test_vocalizer_play);
    RUN_TEST(test_vocalizer_has_vocalizer);
    RUN_TEST(test_alt_sound_is_passed_through);
    RUN_TEST(test_random_sound_plays_periodically);
    RUN_TEST(test_random_sound_disabled_by_setting);
    RUN_TEST(test_startup_sound);
    return UNITY_END();
}
