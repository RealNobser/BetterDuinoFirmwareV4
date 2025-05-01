#ifndef __PANEL_H__
#define __PANEL_H__

#include <VarSpeedServo.h>

class Panel
{
public:
	Panel(VarSpeedServo &Servo, const uint8_t Pin);
	Panel(VarSpeedServo &Servo, const uint8_t Pin, const uint16_t OpenPos, const uint16_t ClosedPos, const uint8_t Speed = 0);

	void attach();
	void detach();

	void open(const uint8_t speed = 0);
	void close(const uint8_t speed = 0);
	void moveMS(const uint16_t angle, const uint8_t speed, const bool storedSpeed);
	void moveDeg(const uint8_t percent, const uint8_t speed, const bool storedSpeed);
	void lock(const bool lock) { locked = lock; }

	bool isMoving();

	void setEndPositions(const uint16_t OpenPos, const uint16_t ClosedPos);
	void setOpenPos(const uint16_t Pos);
	void setClosedPos(const uint16_t Pos);
	void setSpeed(const uint8_t Speed);

protected:
	VarSpeedServo &Servo;
	uint16_t OpenPos	= 0;
	uint16_t ClosedPos	= 0;
	uint8_t Speed		= 0;
	uint8_t Pin			= 0;
	
	bool locked			= false; // Don't react on movement commands
	bool firstAttach	= true;
};

#endif // __PANEL_H__