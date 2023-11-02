#include<Arduino.h>

#include "MarcDuinoSequencer.h"
#include "config.h"

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

void MarcDuinoSequencer::setPanels(Panel** Panels, const unsigned int PanelNr)
{
    this->Panels = Panels;
    this->PanelNr = PanelNr;
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

    for(unsigned int panel = firstPanel; panel <= lastPanel; panel++)
    {
        unsigned int Position = _NP;
        Position = (unsigned int)pgm_read_word(&currentSequence[currentStep][panel]);
        switch (Position)
        {
        case _OPN:
            Panels[panel]->open();
            break;
        case _CLS:
            Panels[panel]->close();
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
