
#include "RobotOpen.h"

/* Constructor */
ROAnalog::ROAnalog(uint8_t channel)
{
    _channel = channel;
}

int ROAnalog::read() {
	if (_channel < 12)
		return analogRead(_channel);
	else
		return 0;
}