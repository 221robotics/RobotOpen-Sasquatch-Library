
#include "RobotOpen.h"

/* Constructor */
ROPWM::ROPWM(uint8_t channel)
{
    _channel = channel;
}

void ROPWM::write(byte pwmVal) {
	RobotOpen.writePWM(_channel, pwmVal);
}