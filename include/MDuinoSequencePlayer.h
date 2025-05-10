#ifndef __MDUINOSEQUENCEPLAYER_H__
#define __MDUINOSEQUENCEPLAYER_H__

#include "MDuinoSequencer.h"

class MDuinoSequencePlayer
{
public:
	MDuinoSequencePlayer(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr);

protected:
	MDuinoSequencer& Sequencer;
};

#ifdef R2D2
class MDuinoDomeSequencePlayerR2 : public MDuinoSequencePlayer
{
public:
	MDuinoDomeSequencePlayerR2(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};

class MDuinoBodySequencePlayerR2 : public MDuinoSequencePlayer
{
public:
	MDuinoBodySequencePlayerR2(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};
#endif

//
// -----
//
#ifdef CHOPPER
class MDuinoDomeSequencePlayerChopper : public MDuinoSequencePlayer
{
public:
	MDuinoDomeSequencePlayerChopper(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};

class MDuinoBodySequencePlayerChopper : public MDuinoSequencePlayer
{
public:
	MDuinoBodySequencePlayerChopper(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};
#endif

//
// -----
//
#ifdef BT1
class MDuinoDomeSequencePlayerBT1 : public MDuinoSequencePlayer
{
public:
	MDuinoDomeSequencePlayerBT1(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};

class MDuinoBodySequencePlayerBT1 : public MDuinoSequencePlayer
{
public:
	MDuinoBodySequencePlayerBT1(MDuinoSequencer &Sequencer);
	virtual void playSequence(const byte SeqNr) override;
};
#endif

#endif