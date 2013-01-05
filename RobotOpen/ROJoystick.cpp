
#include "RobotOpen.h"

/* Constructor */
ROJoystick::ROJoystick(char index)
{
    _index = index;
}

int ROJoystick::getComponent(char componentIndex) {
	if (componentIndex >= 0 && componentIndex <= 19)
    	return validate(componentIndex);
    else
    	return -1;
}

byte ROJoystick::leftX() {
	if (validate(0) != -1)
		return validate(0) & 0xFF;
	else
		return 127;
}
byte ROJoystick::leftY() {
	if (validate(1) != -1)
		return validate(1) & 0xFF;
	else
		return 127;
}
byte ROJoystick::rightX() {
	if (validate(2) != -1)
		return validate(2) & 0xFF;
	else
		return 127;
}
byte ROJoystick::rightY() {
	if (validate(3) != -1)
		return validate(3) & 0xFF;
	else
		return 127;
}
boolean ROJoystick::btnA() {
	return (validate(4) > 0);
}
boolean ROJoystick::btnB() {
	return (validate(5) > 0);
}
boolean ROJoystick::btnX() {
	return (validate(6) > 0);
}
boolean ROJoystick::btnY() {
	return (validate(7) > 0);
}
boolean ROJoystick::btnLShoulder() {
	return (validate(8) > 0);
}
boolean ROJoystick::btnRShoulder() {
	return (validate(9) > 0);
}
byte ROJoystick::lTrigger() {
	if (validate(10) != -1)
		return validate(10) & 0xFF;
	else
		return 0;
}
byte ROJoystick::rTrigger() {
	if (validate(11) != -1)
		return validate(11) & 0xFF;
	else
		return 0;
}
boolean ROJoystick::btnSelect() {
	return (validate(12) > 0);
}
boolean ROJoystick::btnStart() {
	return (validate(13) > 0);
}
boolean ROJoystick::btnLStick() {
	return (validate(14) > 0);
}
boolean ROJoystick::btnRStick() {
	return (validate(15) > 0);
}
boolean ROJoystick::dPadUp() {
	return (validate(16) > 0);
}
boolean ROJoystick::dPadDown() {
	return (validate(17) > 0);
}
boolean ROJoystick::dPadLeft() {
	return (validate(18) > 0);
}
boolean ROJoystick::dPadRight() {
	return (validate(19) > 0);
}




int ROJoystick::validate(char componentIndex) {
    char *joy = RobotOpen.getJoystick(_index);

    if (joy == 0 || componentIndex > 19)
        return -1;
    else
        return joy[componentIndex];
}