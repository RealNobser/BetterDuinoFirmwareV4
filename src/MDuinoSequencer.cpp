#include<Arduino.h>

#include "MDuinoSequencer.h"
#include "config.h"

MDuinoSequencer::MDuinoSequencer(MDuinoBase* instance)
    : instance(instance)
{
    clearSequenceCompletionCallbacks();
    for(unsigned int i=0; i < SEQUENCE_SIZE; i++)
        servoSpeed[i]=0;
}

void MDuinoSequencer::init()
{
    setServoSpeed(fast);    // filling array
}

void MDuinoSequencer::run()
{
    if (currentSequence != nullptr)
    {
        if ((millis()-currentStepTime) > currentStepDuration)
            nextStep();
    }
}

void MDuinoSequencer::setPanels(Panel** Panels, const unsigned int PanelCount)
{
    this->Panels    = Panels;
    this->PanelCount= PanelCount;
}

void MDuinoSequencer::setPanelRange(const unsigned int MinPanel, const unsigned int MaxPanel)
{
    this->MinPanel = MinPanel;
    this->MaxPanel = MaxPanel;
}

void MDuinoSequencer::loadSequence(sequence_t_ptr Seq, const unsigned int Steps)
{   
    clearSequence();

    currentSequence         = Seq;
    currentSequenceSteps    = Steps;
    currentStep             = 0;
}

void MDuinoSequencer::clearSequence()
{
    currentStep         = 0;
    currentSequence     = nullptr;
    currentSequenceSteps= 0;

    currentStepTime     = 0;
    currentStepDuration = 0;

    CompletionCallbacksNr = 0;

    clearSequenceCompletionCallbacks();    
}

void MDuinoSequencer::startSequence()
{
    if (currentSequence == nullptr)
        return;

    currentStep         = 0;

    currentStepDuration = (int)pgm_read_word(&currentSequence[currentStep][0]);
    currentStepDuration *= 10;

    currentStepTime     = millis();

    movePanels();
}

void MDuinoSequencer::stopSequence()
{

}

void MDuinoSequencer::pauseSequence()
{

}

void MDuinoSequencer::resumeSequence()
{

}

void MDuinoSequencer::nextStep()
{
    if (currentStep < (currentSequenceSteps-1))
        currentStep++;
    else
    {
        // End Sequence Callbacks
        for(unsigned int i=0; i < CompletionCallbacksNr; i++)
            seq_completion_callback[i](instance);
        
        clearSequence();
        return;
    }

    currentStepDuration = (int)pgm_read_word(&currentSequence[currentStep][0]);
    currentStepDuration *= 10;

    currentStepTime     = millis();

    movePanels();
}

void MDuinoSequencer::movePanels()
{
    if (currentSequence == nullptr)
        return;

    for(unsigned int panel = MinPanel; panel <= MaxPanel; panel++)
    {
        unsigned int Position = _NP;
        Position = (unsigned int)pgm_read_word(&currentSequence[currentStep][panel]);
        switch (Position)
        {
        case _OPN:
            Panels[panel]->open(servoSpeed[panel]);
            break;
        case _CLS:
            Panels[panel]->close(servoSpeed[panel]);
            break;
        case _MID:
            // TODO:!
            break;
        case _NP:
            Panels[panel]->detach();
            break;
        default:
            break;
        }
    }
}

void MDuinoSequencer::setServoSpeed(speed_t speed)
{
    byte set_speed = SERVO_SPEED_FULL;

    if (speed == custom)
    {
        // Need Storage access
    }

    switch (speed)
    {
    case full:
        set_speed = SERVO_SPEED_FULL;
        break;
    case fast:
        set_speed = SERVO_SPEED_FAST;
        break;
    case medium:
        set_speed = SERVO_SPEED_MEDIUM;
        break;
    case slow:
        set_speed = SERVO_SPEED_SLOW;
        break;
    case super_slow:
        set_speed = SERVO_SPEED_SUPER_SLOW;
        break;
    default:
        set_speed = SERVO_SPEED_FULL;
        break;
    }

    for(int i=0; i < SEQUENCE_SIZE; i++)
    {
        servoSpeed[i] = set_speed;
    }
}


void MDuinoSequencer::addSequenceCompletionCallback(void(*usercallback)(MDuinoBase*))
{
    if (CompletionCallbacksNr >= MAX_SEQUENCE_COMPLETION_CALLBACKS)
        return; // Ignore additional Callbacks

    seq_completion_callback[CompletionCallbacksNr] = usercallback;
    CompletionCallbacksNr++;
}

void MDuinoSequencer::clearSequenceCompletionCallbacks()
{
    for (unsigned int i = 0; i < MAX_SEQUENCE_COMPLETION_CALLBACKS; i++)
        seq_completion_callback[CompletionCallbacksNr] = nullptr;
}
