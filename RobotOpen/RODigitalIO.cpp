
#include "RobotOpen.h"

/* Constructor */
RODigitalIO::RODigitalIO(uint8_t channel, uint8_t mode)
{
    _channel = channel;
    setMode(mode);
}

void RODigitalIO::on() {
	RobotOpen.writeDigital(_channel, HIGH);
}

void RODigitalIO::off() {
	RobotOpen.writeDigital(_channel, LOW);
}

boolean RODigitalIO::read() {
	if (_channel < 3) {
		return ((digitalRead(47+_channel) == HIGH) ? true : false);
    }
    else {
        return ((digitalRead(51+_channel) == HIGH) ? true : false);
    }
}

void RODigitalIO::pullUp() {
	RobotOpen.setPullup(_channel, true);
}

void RODigitalIO::allowFloat() {
	RobotOpen.setPullup(_channel, false);
}

void RODigitalIO::setMode(uint8_t mode) {
	if (mode == INPUT) {
		RobotOpen.makeInput(_channel);
	} else {
		RobotOpen.makeOutput(_channel);
	}
}