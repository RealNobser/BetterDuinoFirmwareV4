// MDuinoSequencer: PROGMEM table stepping, timing, servo speeds, completion callbacks.
#include <unity.h>
#include <new>
#include "Harness.h"
#include "MDuinoSequencer.h"

using namespace harness;

// White-box access to protected sequencer state
class SeqProbe : public MDuinoSequencer
{
public:
    using MDuinoSequencer::MDuinoSequencer;
    byte speed() { return servoSpeed; }
    byte callbackCount() { return CompletionCallbacksNr; }
};

//                              time               P1    P2    P3    P4   P5..P13
sequence_t const test_seq PROGMEM = {
    {SPLIT_WORD(10),  _OPN, _CLS, _MID, _NP,  _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP},   // 100 ms
    {SPLIT_WORD(20),  _CLS, _OPN, _NP,  25,   _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP},   // 200 ms
    {SPLIT_WORD(0),   _NP,  _NP,  _NP,  _NP,  _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP, _NP},
};

static Panel* panels[5];
static SeqProbe* seq;
static int callbackHits;
static int callbackOrder[8];

static void cbA(MDuinoBase*) { callbackOrder[callbackHits++] = 1; }
static void cbB(MDuinoBase*) { callbackOrder[callbackHits++] = 2; }

void setUp()
{
    resetHardware();
    callbackHits = 0;
    panels[0] = nullptr;
    for (int i = 1; i <= 4; i++)
        panels[i] = new Panel(Servo[i], (uint8_t)(i + 1), 1000, 2000);   // open 1000, closed 2000
    seq = new SeqProbe(nullptr);
    seq->init();
    seq->setPanels(panels, 5);
    seq->setPanelRange(1, 4);
}

void tearDown()
{
    delete seq;
    for (int i = 1; i <= 4; i++) delete panels[i];
}

static void run(unsigned long ms)
{
    for (unsigned long t = 0; t < ms; t++) { mock::advance(1); seq->run(); }
}

static void test_first_step_applied_on_start()
{
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    TEST_ASSERT_TRUE(seq->isActive());
    TEST_ASSERT_EQUAL_UINT16(1000, Servo[1].value);    // _OPN
    TEST_ASSERT_EQUAL_UINT16(2000, Servo[2].value);    // _CLS
    TEST_ASSERT_EQUAL_UINT16(1500, Servo[3].value);    // _MID
    TEST_ASSERT_FALSE(Servo[4].attached());            // _NP -> untouched / detached
}

static void test_steps_advance_after_duration()
{
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    run(100);
    TEST_ASSERT_EQUAL_UINT16(1000, Servo[1].value);    // still step 0 (strictly greater than duration)
    run(2);
    TEST_ASSERT_EQUAL_UINT16(2000, Servo[1].value);    // step 1
    TEST_ASSERT_EQUAL_UINT16(1000, Servo[2].value);
    TEST_ASSERT_EQUAL_UINT16(1750, Servo[4].value);    // 25 % open
}

static void test_np_detaches_idle_servo_but_not_moving_one()
{
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    Servo[3].moving = true;
    run(102);                                          // step 1: P3 = _NP while moving
    TEST_ASSERT_TRUE(Servo[3].attached());
    Servo[3].moving = false;
    run(202);                                          // step 2: P3 = _NP, idle
    TEST_ASSERT_FALSE(Servo[3].attached());
}

static void test_sequence_ends_and_fires_callbacks_once()
{
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->addSequenceCompletionCallback(cbA);
    seq->addSequenceCompletionCallback(cbB);
    seq->startSequence();
    run(1000);
    TEST_ASSERT_FALSE(seq->isActive());
    TEST_ASSERT_EQUAL_INT(2, callbackHits);
    TEST_ASSERT_EQUAL_INT(1, callbackOrder[0]);
    TEST_ASSERT_EQUAL_INT(2, callbackOrder[1]);
    run(1000);
    TEST_ASSERT_EQUAL_INT(2, callbackHits);            // not again
}

static void test_stop_sequence_ends_at_next_step()
{
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->addSequenceCompletionCallback(cbA);
    seq->startSequence();
    seq->stopSequence();
    run(102);
    TEST_ASSERT_FALSE(seq->isActive());
    TEST_ASSERT_EQUAL_INT(1, callbackHits);
}

static void test_start_without_sequence_is_noop()
{
    seq->startSequence();
    TEST_ASSERT_FALSE(seq->isActive());
    run(100);
    TEST_ASSERT_EQUAL_UINT(0, Servo[1].writeCount);
}

static void test_load_sequence_clears_previous_callbacks()
{
    seq->addSequenceCompletionCallback(cbA);
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    TEST_ASSERT_EQUAL_UINT8(0, seq->callbackCount());
    seq->startSequence();
    run(1000);
    TEST_ASSERT_EQUAL_INT(0, callbackHits);
}

static void test_callback_limit()
{
    for (int i = 0; i < MAX_SEQUENCE_COMPLETION_CALLBACKS + 3; i++)
        seq->addSequenceCompletionCallback(cbA);
    TEST_ASSERT_EQUAL_UINT8(MAX_SEQUENCE_COMPLETION_CALLBACKS, seq->callbackCount());
}

// Regression: clearSequenceCompletionCallbacks() indexed with the counter instead of the loop
// variable (writing past the array when full) and never reset the counter.
static void test_clear_callbacks_when_full()
{
    for (int i = 0; i < MAX_SEQUENCE_COMPLETION_CALLBACKS; i++)
        seq->addSequenceCompletionCallback(cbA);
    seq->clearSequenceCompletionCallbacks();
    TEST_ASSERT_EQUAL_UINT8(0, seq->callbackCount());

    seq->addSequenceCompletionCallback(cbB);
    TEST_ASSERT_EQUAL_UINT8(1, seq->callbackCount());
}

// Regression: servoSpeed[] was only initialised for MinPanel..MaxPanel, which are still 0 when
// init() runs -> entries 1..13 kept heap garbage (no clearing after a soft reset).
// Now a single member with a default initializer.
static void test_servo_speeds_initialised_independent_of_panel_range()
{
    alignas(SeqProbe) unsigned char raw[sizeof(SeqProbe)];
    memset(raw, 0xAA, sizeof(raw));                    // simulate dirty heap
    SeqProbe* dirty = new (raw) SeqProbe(nullptr);
    dirty->init();                                     // before setPanelRange(), like MDuinoBase::init()
    TEST_ASSERT_EQUAL_UINT8(SERVO_SPEED_FAST, dirty->speed());
    dirty->~SeqProbe();
}

static void test_set_servo_speed_variants()
{
    struct { MDuinoSequencer::speed_t s; byte v; } map[] = {
        {MDuinoSequencer::speed_t::full, SERVO_SPEED_FULL},
        {MDuinoSequencer::speed_t::fast, SERVO_SPEED_FAST},
        {MDuinoSequencer::speed_t::medium, SERVO_SPEED_MEDIUM},
        {MDuinoSequencer::speed_t::slow, SERVO_SPEED_SLOW},
        {MDuinoSequencer::speed_t::super_slow, SERVO_SPEED_SUPER_SLOW},
        {MDuinoSequencer::speed_t::custom, SERVO_SPEED_FULL},
        {MDuinoSequencer::speed_t::unknown, SERVO_SPEED_FULL},
    };
    for (auto& m : map)
    {
        seq->setServoSpeed(m.s);
        TEST_ASSERT_EQUAL_UINT8(m.v, seq->speed());
    }
}

static void test_sequence_uses_sequencer_speed()
{
    seq->setServoSpeed(MDuinoSequencer::speed_t::slow);
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    TEST_ASSERT_EQUAL_UINT8(SERVO_SPEED_SLOW, Servo[1].speed);
}

static void test_custom_speed_uses_per_panel_stored_speed()
{
    panels[1]->setSpeed(11);
    panels[2]->setSpeed(22);
    panels[3]->setSpeed(33);
    seq->setServoSpeed(MDuinoSequencer::speed_t::custom);
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    TEST_ASSERT_EQUAL_UINT8(11, Servo[1].speed);
    TEST_ASSERT_EQUAL_UINT8(22, Servo[2].speed);
    TEST_ASSERT_EQUAL_UINT8(33, Servo[3].speed);
    TEST_ASSERT_EQUAL_UINT16(1500, Servo[3].value);    // positions unchanged by custom speed
}

static void test_non_custom_speed_overrides_stored_speed()
{
    panels[1]->setSpeed(11);
    seq->setServoSpeed(MDuinoSequencer::speed_t::custom);
    seq->setServoSpeed(MDuinoSequencer::speed_t::medium);   // switching back clears custom mode
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    TEST_ASSERT_EQUAL_UINT8(SERVO_SPEED_MEDIUM, Servo[1].speed);
}

static void test_millis_rollover()
{
    mock::setMillis(0xFFFFFFFFUL - 50);
    seq->loadSequence(test_seq, SEQ_SIZE(test_seq));
    seq->startSequence();
    run(102);                                          // wraps around 0
    TEST_ASSERT_EQUAL_UINT16(2000, Servo[1].value);    // reached step 1 correctly
}

int main(int, char**)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_step_applied_on_start);
    RUN_TEST(test_steps_advance_after_duration);
    RUN_TEST(test_np_detaches_idle_servo_but_not_moving_one);
    RUN_TEST(test_sequence_ends_and_fires_callbacks_once);
    RUN_TEST(test_stop_sequence_ends_at_next_step);
    RUN_TEST(test_start_without_sequence_is_noop);
    RUN_TEST(test_load_sequence_clears_previous_callbacks);
    RUN_TEST(test_callback_limit);
    RUN_TEST(test_clear_callbacks_when_full);
    RUN_TEST(test_servo_speeds_initialised_independent_of_panel_range);
    RUN_TEST(test_set_servo_speed_variants);
    RUN_TEST(test_sequence_uses_sequencer_speed);
    RUN_TEST(test_custom_speed_uses_per_panel_stored_speed);
    RUN_TEST(test_non_custom_speed_overrides_stored_speed);
    RUN_TEST(test_millis_rollover);
    return UNITY_END();
}
