#include<Arduino.h>

#include "MarcDuinoSequencer.h"
#include "config.h"

MarcDuinoSequencer::MarcDuinoSequencer()
{

}

void MarcDuinoSequencer::init()
{
    setServoSpeed(fast);    // filling array
}

void MarcDuinoSequencer::run()
{
    if (currentSequence != nullptr)
    {
        if ((millis()-currentStepTime) > currentStepDuration)
            nextStep();
    }
}

void MarcDuinoSequencer::setPanels(Panel** Panels, const unsigned int PanelCount)
{
    this->Panels    = Panels;
    this->PanelCount= PanelCount;
}

void MarcDuinoSequencer::setPanelRange(const unsigned int MinPanel, const unsigned int MaxPanel)
{
    this->MinPanel = MinPanel;
    this->MaxPanel = MaxPanel;
}

void MarcDuinoSequencer::loadSequence(sequence_t_ptr Seq, const unsigned int Steps)
{   
    clearSequence();

    Serial.println(Steps);

    currentSequence         = Seq;
    currentSequenceSteps    = Steps;
    currentStep             = 0;
}

void MarcDuinoSequencer::clearSequence()
{
    currentStep         = 0;
    currentSequence     = nullptr;
    currentSequenceSteps= 0;

    currentStepTime     = 0;
    currentStepDuration = 0;
}

void MarcDuinoSequencer::startSequence()
{
    if (currentSequence == nullptr)
        return;

    currentStep         = 0;

    currentStepDuration = (int)pgm_read_word(&currentSequence[currentStep][0]);
    currentStepDuration *= 10;

    currentStepTime     = millis();

    movePanels();
}

void MarcDuinoSequencer::stopSequence()
{

}

void MarcDuinoSequencer::pauseSequence()
{

}

void MarcDuinoSequencer::resumeSequence()
{

}

void MarcDuinoSequencer::nextStep()
{
    if (currentStep < (currentSequenceSteps-1))
        currentStep++;
    else
    {
        clearSequence();
        return;
    }

    currentStepDuration = (int)pgm_read_word(&currentSequence[currentStep][0]);
    currentStepDuration *= 10;

    currentStepTime     = millis();

    movePanels();
}

void MarcDuinoSequencer::movePanels()
{
    unsigned int firstPanel = 0;
    unsigned int lastPanel = 0;

    if (currentSequence == nullptr)
        return;

    firstPanel  = (unsigned int)pgm_read_word(&currentSequence[currentStep][SEQUENCE_SIZE-2]);
    lastPanel   = (unsigned int)pgm_read_word(&currentSequence[currentStep][SEQUENCE_SIZE-1]);

    // Limit to Panels, that can be accessed
    if (firstPanel < MinPanel)
        firstPanel = MinPanel;
    
    if (lastPanel > MaxPanel)
        lastPanel = MaxPanel;

    for(unsigned int panel = firstPanel; panel <= lastPanel; panel++)
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
    #ifdef DEBUG_MSG
    Serial.println();
    for(int i=0; i < SEQUENCE_SIZE; i++)
    {
        Serial.print((unsigned int)pgm_read_word(&currentSequence[currentStep][i]));
        Serial.print(F(" "));
    }
    Serial.println();
    #endif

}

void MarcDuinoSequencer::setServoSpeed(speed_t speed)
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
