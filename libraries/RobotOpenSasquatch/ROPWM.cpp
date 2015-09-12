#include "RobotOpenSQ.h"

/* Constructor */
ROPWM::ROPWM(uint8_t channel)
{
    _channel = channel;
}

void ROPWM::write(byte pwmVal) {
	RobotOpen.writePWM(_channel, pwmVal);
}

void ROPWM::attach() {
	RobotOpen.attachPWM(_channel);
}

void ROPWM::detach() {
	RobotOpen.detachPWM(_channel);
}