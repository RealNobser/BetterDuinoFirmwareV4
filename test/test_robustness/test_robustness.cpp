// Robustness: exhaustive command sweeps, random fuzzing of the serial/I2C input path and all sequence
// numbers on every role. Runs under AddressSanitizer/UBSan: any out-of-bounds access, null dereference
// or undefined behaviour aborts the test binary.
#include <unity.h>
#include "Harness.h"

using namespace harness;

static const char PREFIXES[] = ":*@$!%#&>";
static const char* PARAMS[] = {"00", "01", "03", "05", "11", "12", "13", "14", "15", "16", "50", "99", "-1", "ab", "  "};
static const char* EXTS[] = {"", "0", "1500", "65535", "99999999", "255000000200", "-1"};

static void onRx(int) {}

void setUp() {}
void tearDown() {}

template <class T>
static void sweep(T& board)
{
    char line[32];
    unsigned long executed = 0;
    for (const char* pre = PREFIXES; *pre; pre++)
    {
        for (char a = 'A'; a <= 'Z'; a++)
        {
            for (char b = 'A'; b <= 'Z'; b++)
            {
                for (auto p : PARAMS)
                {
                    for (auto e : EXTS)
                    {
                        snprintf(line, sizeof(line), "%c%c%c%s%s", *pre, a, b, p, e);
                        if (line[1] == 'R' && line[2] == 'S') continue;       // reboot commands: separate test
                        causesReset([&] { board.parseCommand(line); });
                        executed++;
                    }
                }
            }
        }
        mock::advance(5);
        board.run();
    }
    // guard against the sweep silently doing nothing (9 prefixes x 26 x 26 x params x exts, minus RS)
    TEST_ASSERT_GREATER_THAN_UINT32(600000UL, executed);
}

template <class T>
static void checkHealthy(T& board)
{
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.outOfRange);
    board.pump(5000, 50);     // main loop keeps running after the sweep
}

static void test_sweep_dome_master()
{
    auto b = bootMaster();
    sweep(*b);
    checkHealthy(*b);
}

static void test_sweep_dome_slave()
{
    auto b = bootSlave();
    sweep(*b);
    checkHealthy(*b);
}

static void test_sweep_body_master()
{
    auto b = bootBody();
    sweep(*b);
    checkHealthy(*b);
}

// Lower-case and digit command letters (e.g. sound shortcuts, holo H0..H3/F0..F3)
template <class T>
static void sweepShort(T& board)
{
    char line[16];
    for (const char* pre = PREFIXES; *pre; pre++)
        for (int c1 = 32; c1 < 127; c1++)
            for (int c2 = 32; c2 < 127; c2 += 3)
            {
                snprintf(line, sizeof(line), "%c%c%c05", *pre, c1, c2);
                causesReset([&] { board.parseCommand(line); });
                snprintf(line, sizeof(line), "%c%c", *pre, c1);
                causesReset([&] { board.parseCommand(line); });
                snprintf(line, sizeof(line), "%c%c%c", *pre, c1, c2);
                causesReset([&] { board.parseCommand(line); });
            }
}

static void test_sweep_short_commands_all_roles()
{
    { auto b = bootMaster(); sweepShort(*b); checkHealthy(*b); }
    { auto b = bootSlave();  sweepShort(*b); checkHealthy(*b); }
    { auto b = bootBody();   sweepShort(*b); checkHealthy(*b); }
}

// Random bytes (including CR/LF, NUL and high bytes) through the real receive paths
template <class T>
static void fuzz(T& board, uint32_t seed, int lines)
{
    uint32_t s = seed;
    auto rnd = [&s]() { s = s * 1664525u + 1013904223u; return s >> 8; };
    Wire.onReceive(onRx);
    for (int i = 0; i < lines; i++)
    {
        std::string line;
        int len = rnd() % 40;
        line += PREFIXES[rnd() % (sizeof(PREFIXES) - 1)];
        for (int k = 0; k < len; k++)
        {
            uint32_t r = rnd() % 100;
            char c;
            if (r < 50) c = '0' + rnd() % 10;
            else if (r < 80) c = 'A' + rnd() % 26;
            else if (r < 85) c = '\r';
            else if (r < 88) c = '\n';
            else c = (char)(rnd() & 0xFF);
            line += c;
        }
        line += '\r';
        if ((line[1] == 'R' && line[2] == 'S')) continue;
        causesReset([&] {
            if (rnd() & 1) board.sendSerial(line);
            else board.sendWire(line);
        });
        if ((i % 64) == 0) { mock::advance(100); board.run(); }
    }
}

static void test_fuzz_all_roles()
{
    { auto b = bootMaster(); fuzz(*b, 1, 20000); checkHealthy(*b); }
    { auto b = bootSlave();  fuzz(*b, 2, 20000); checkHealthy(*b); }
    { auto b = bootBody();   fuzz(*b, 3, 20000); checkHealthy(*b); }
}

// Every sequence number must terminate, stay inside its PROGMEM table, and leave buzz handling on.
template <class T>
static void allSequences(T& board)
{
    for (int s = 0; s <= 99; s++)
    {
        char line[8];
        snprintf(line, sizeof(line), ":SE%02d", s);
        board.parseCommand(line);
        board.pump(7UL * 60UL * 1000UL, 50);   // longest sequence (R2 disco) is 6:26 min
        TEST_ASSERT_FALSE_MESSAGE(board.sequencer().isActive(), line);
        TEST_ASSERT_EQUAL_UINT32_MESSAGE(SERVO_BUZZ_MILLIS, board.servoBuzzInterval(), line);
    }
}

static void test_all_sequences_dome_master() { auto b = bootMaster(); allSequences(*b); }
static void test_all_sequences_dome_slave()  { auto b = bootSlave();  allSequences(*b); }
static void test_all_sequences_body_master() { auto b = bootBody();   allSequences(*b); }

static void test_reboot_commands()
{
    auto b = bootMaster();
    TEST_ASSERT_TRUE(causesReset([&] { b->parseCommand("#RS00"); }));
    TEST_ASSERT_TRUE(causesReset([&] { b->parseCommand("#RS01"); }));
    TEST_ASSERT_TRUE(causesReset([&] { b->parseCommand("#RS99"); }));
}

static void test_long_runtime_with_random_sounds()
{
    auto b = bootMaster();
    b->parseCommand("$R");
    b->parseCommand("*RD00");
    b->pump(10UL * 60UL * 1000UL, 100);       // 10 minutes
    TEST_ASSERT_EQUAL_UINT32(0, EEPROM.outOfRange);
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_sweep_dome_master);
    RUN_TEST(test_sweep_dome_slave);
    RUN_TEST(test_sweep_body_master);
    RUN_TEST(test_sweep_short_commands_all_roles);
    RUN_TEST(test_fuzz_all_roles);
    RUN_TEST(test_all_sequences_dome_master);
    RUN_TEST(test_all_sequences_dome_slave);
    RUN_TEST(test_all_sequences_body_master);
    RUN_TEST(test_reboot_commands);
    RUN_TEST(test_long_runtime_with_random_sounds);
    return UNITY_END();
}
