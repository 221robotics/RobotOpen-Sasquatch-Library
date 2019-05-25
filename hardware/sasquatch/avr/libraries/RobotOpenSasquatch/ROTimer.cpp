#include "RobotOpenSQ.h"

/* Constructor */
ROTimer::ROTimer()
{
	_millisExpire = 0;
	_timerSet = false;
}

void ROTimer::queue(unsigned int duration) {
	_millisExpire = millis() + duration;
	_timerSet = true;
}

boolean ROTimer::ready() {
	if ((millis() > _millisExpire) && _timerSet) {
		_timerSet = false;
		return true;
	} else {
		return false;
	}
}