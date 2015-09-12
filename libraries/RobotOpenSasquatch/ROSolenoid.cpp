#include "RobotOpenSQ.h"

/* Constructor */
ROSolenoid::ROSolenoid(uint8_t channel)
{
    _channel = channel;
}

void ROSolenoid::on() {
	RobotOpen.writeSolenoid(_channel, HIGH);
}

void ROSolenoid::off() {
	RobotOpen.writeSolenoid(_channel, LOW);
}