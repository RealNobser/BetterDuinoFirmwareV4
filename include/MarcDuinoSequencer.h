#ifndef __MARCDUINOSEQUENCER_H__
#define __MARCDUINOSEQUENCER_H__

#include "config.h"
#include "Panel.h"

#define SEQ_SIZE(A) (sizeof(A) / sizeof(A[0]))
#define SEQUENCE_SIZE (MAX_MARCUDINOSERVOS + 4)

typedef const unsigned int sequence_t[][SEQUENCE_SIZE];
typedef const unsigned int (*sequence_t_ptr)[SEQUENCE_SIZE];

class MarcDuinoSequencer
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

        MarcDuinoSequencer();
        
        void init();
        void run();
        void setPanels(Panel** Panels, const unsigned int PanelCount);
        void setPanelRange(const unsigned int MinPanel, const unsigned int MaxPanel);
        void loadSequence(sequence_t_ptr Seq, const unsigned int Steps);
        void clearSequence();
        void startSequence();
        void stopSequence();
        void pauseSequence();
        void resumeSequence();

        void setServoSpeed(speed_t speed);

    protected:
        Panel**         Panels      = nullptr;
        unsigned int    PanelCount  = 0;
        unsigned int    MinPanel    = 0;
        unsigned int    MaxPanel    = 0;

        unsigned int    currentStep = 0;
        sequence_t_ptr  currentSequence = nullptr;

        unsigned int    currentSequenceSteps = 0;

        unsigned long   currentStepTime = 0;
        unsigned long   currentStepDuration = 0;

        void nextStep();
        void movePanels();

        byte servoSpeed[SEQUENCE_SIZE];
};

#endif // __MARCDUINOSEQUENCER_H__