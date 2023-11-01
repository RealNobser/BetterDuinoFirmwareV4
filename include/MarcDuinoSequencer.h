#ifndef __MARCDUINOSEQUENCER_H__
#define __MARCDUINOSEQUENCER_H__

#include "config.h"

#define SEQ_SIZE(A) (sizeof(A) / sizeof(A[0]))
#define SEQUENCE_SIZE (MAX_MARCUDINOSERVOS + 4)

typedef int16_t sequence_t[][SEQUENCE_SIZE];
typedef int16_t (*sequence_t_ptr)[SEQUENCE_SIZE];

class MarcDuinoSequencer
{
    public:
        MarcDuinoSequencer();
        void init();
        void run();

        void loadSequence(sequence_t_ptr Seq, const unsigned int Steps);
        void clearSequence();
        void startSequence();
        void stopSequence();
        void pauseSequence();
        void resumeSequence();

    protected:
        unsigned int    currentStep = 0;
        sequence_t_ptr  currentSequence = nullptr;

        unsigned int    currentSequenceSteps = 0;

        unsigned long   currentStepTime = 0;
        unsigned long   currentStepDuration = 0;

        void nextStep();
        void setServos();
};

#endif // __MARCDUINOSEQUENCER_H__