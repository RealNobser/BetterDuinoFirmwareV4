#ifndef __MDUINOSEQUENCER_H__
#define __MDUINOSEQUENCER_H__

#include "config.h"
#include "Panel.h"

// Classic Code

#define SPLIT_WORD(A) (A & 0xFF), ((A >> 8) & 0xFF)

#define SEQ_SIZE(A) (sizeof(A) / sizeof(A[0]))
#define SEQUENCE_SIZE (MAX_MARCUDINOSERVOS + 2) // 13 Servos (1 Byte each) plus Timer (2 bytes)

/*
typedef const unsigned int sequence_t[][SEQUENCE_SIZE];
typedef const unsigned int (*sequence_t_ptr)[SEQUENCE_SIZE];
*/
typedef const byte sequence_t[][SEQUENCE_SIZE];
typedef const byte (*sequence_t_ptr)[SEQUENCE_SIZE];

// Forward Declaration for Callbacks
class MDuinoBase;

class MDuinoSequencer
{
    public:
        enum speed_t {
            custom = 0,
            full,
            fast,
            medium,
            slow,
            super_slow
        };

        explicit MDuinoSequencer(MDuinoBase* instance);
        
        void init();
        void run();
        void setPanels(Panel** Panels, const byte PanelCount);
        void setPanelRange(const byte MinPanel, const byte MaxPanel);
        void loadSequence(sequence_t_ptr Seq, const unsigned int Steps);
        void clearSequence();
        void startSequence();
        void stopSequence();
        void pauseSequence();
        void resumeSequence();

        void setServoSpeed(speed_t speed);
        void addSequenceCompletionCallback(void(*usercallback)(MDuinoBase*));
        void clearSequenceCompletionCallbacks();

    protected:
        MDuinoBase*     instance    = nullptr;
        Panel**         Panels      = nullptr;
        byte            PanelCount  = 0;
        byte            MinPanel    = 0;
        byte            MaxPanel    = 0;

        unsigned int    currentStep = 0;
        sequence_t_ptr  currentSequence = nullptr;

        unsigned int    currentSequenceSteps = 0;

        unsigned long   currentStepTime = 0;
        unsigned int    currentStepDuration = 0;

        void nextStep();
        void movePanels();

        byte servoSpeed[SEQUENCE_SIZE];

        void(*seq_completion_callback[MAX_SEQUENCE_COMPLETION_CALLBACKS])(MDuinoBase*); // Maximum 5 Sequence Completion Callbacks
        byte CompletionCallbacksNr = 0;

};

#endif // __MDUINOSEQUENCER_H__