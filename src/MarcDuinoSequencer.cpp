#include<Arduino.h>

#include "MarcDuinoSequencer.h"

MarcDuinoSequencer::MarcDuinoSequencer()
{

}

void MarcDuinoSequencer::init()
{

}

void MarcDuinoSequencer::run()
{
    if (currentSequence != nullptr)
    {
        if ((millis()-currentStepTime) > currentStepDuration)
            nextStep();
    }
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
    currentStep         = 0;

    currentStepDuration = (int)pgm_read_word(&currentSequence[currentStep][0]);
    currentStepDuration *= 10;

    currentStepTime     = millis();

    setServos();    
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

    setServos();
}

void MarcDuinoSequencer::setServos()
{
    if (currentSequence == nullptr)
        return;

    for(int i=0; i < SEQUENCE_SIZE; i++)
    {
        Serial.print((int)pgm_read_word(&currentSequence[currentStep][i]));
        Serial.print(" ");
    }
    Serial.println();
}
