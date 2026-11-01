// Body Master: role identity, panel handling and body sequences.
#include <unity.h>
#include <cstring>
#include "Harness.h"

using namespace harness;

static std::unique_ptr<Testable<BodyMasterT>> bm;

void setUp() { bm = bootBody(false); clearOutputs(); }
void tearDown() { bm.reset(); }

static void cmd(const char* c) { bm->parseCommand(c); }

static void test_product_name_identifies_body()
{
    TEST_ASSERT_NOT_NULL(strstr(bm->getProductName(), "Body"));
}

static void test_body_pins()
{
    const uint8_t pins[] = {0, P_DPL, P_UTIL_ARM_U, P_UTIL_ARM_L, P_LEFT_BDY_DR, P_LEFT_ARM, P_LEFT_ARM_TOOL,
                            P_RIGHT_BDY_DR, P_RIGHT_ARM, P_RIGHT_ARM_TOOL, P_CHRG_BAY_DR, P_RFU};
    cmd(":OP00");
    for (int i = 1; i <= 11; i++)
        TEST_ASSERT_EQUAL_UINT8(pins[i], Servo[i].pin);
}

// Regression: :MV00 dereferenced Panels[0] == nullptr (Body Master inherits the Dome Master panel code)
static void test_move_panel_zero_does_not_crash()
{
    cmd(":MV001500");
    for (int i = 1; i <= 11; i++) TEST_ASSERT_EQUAL_UINT(0, Servo[i].writeCount);
    cmd(":MV011500");
    TEST_ASSERT_EQUAL_UINT16(1500, Servo[1].value);
}

// SE00 (panel init) runs on every boot by default. Guards the BT1 init table being played with its own
// row count (it used SEQ_SIZE(panel_init) - same size by coincidence; ASan would catch a mismatch).
static void test_boot_panel_init_sequence_runs_to_completion()
{
    bm = bootBody(true);
    TEST_ASSERT_TRUE(bm->sequencer().isActive());
    bm->pump(30000);
    TEST_ASSERT_FALSE(bm->sequencer().isActive());
#ifdef CHOPPER
    TEST_ASSERT_EQUAL_UINT16((PANEL_OPN + PANEL_CLS) / 2, Servo[1].value);   // Chopper: DPL to _MID
    const int first = 2;
#else
    const int first = 1;
#endif
    for (int i = first; i <= 11; i++)
        TEST_ASSERT_EQUAL_UINT16(PANEL_CLS, Servo[i].value);
    TEST_ASSERT_EQUAL_UINT32(SERVO_BUZZ_MILLIS, bm->servoBuzzInterval());
}

#ifdef R2D2
static void test_r2_body_sequences_move_panels()
{
    const int seqs[] = {30, 31, 32, 33, 34, 35};
    for (int s : seqs)
    {
        for (int i = 1; i <= 11; i++) Servo[i].writeCount = 0;
        char buf[8];
        snprintf(buf, sizeof(buf), ":SE%02d", s);
        cmd(buf);
        unsigned writes = 0;
        bm->pump(120000, 20);
        for (int i = 1; i <= 11; i++) writes += Servo[i].writeCount;
        TEST_ASSERT_GREATER_THAN_MESSAGE(0, writes, buf);
        TEST_ASSERT_FALSE_MESSAGE(bm->sequencer().isActive(), buf);
    }
}
#endif

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_product_name_identifies_body);
    RUN_TEST(test_body_pins);
    RUN_TEST(test_move_panel_zero_does_not_crash);
    RUN_TEST(test_boot_panel_init_sequence_runs_to_completion);
#ifdef R2D2
    RUN_TEST(test_r2_body_sequences_move_panels);
#endif
    return UNITY_END();
}
