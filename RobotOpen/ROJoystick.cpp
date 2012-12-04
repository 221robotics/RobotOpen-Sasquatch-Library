
#include "RobotOpen.h"

/* Constructor */
ROJoystick::ROJoystick(char index)
{
    _index = index;
}

int ROJoystick::getComponent(char componentIndex) {
	if (componentIndex > 0 && componentIndex < 19)
    	return validate(componentIndex-1);
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
boolean ROJoystick::btn1() {
	return (validate(4) > 0);
}
boolean ROJoystick::btn2() {
	return (validate(5) > 0);
}
boolean ROJoystick::btn3() {
	return (validate(6) > 0);
}
boolean ROJoystick::btn4() {
	return (validate(7) > 0);
}
boolean ROJoystick::btn5() {
	return (validate(8) > 0);
}
boolean ROJoystick::btn6() {
	return (validate(9) > 0);
}
boolean ROJoystick::btn7() {
	return (validate(10) > 0);
}
boolean ROJoystick::btn8() {
	return (validate(11) > 0);
}
boolean ROJoystick::btnLStick() {
	return (validate(8) > 0);
}
boolean ROJoystick::btnRStick() {
	return (validate(9) > 0);
}
byte ROJoystick::dPad() {
	if (validate(10) != -1)
		return validate(10) & 0xFF;
	else
		return 0;
}
boolean ROJoystick::btnLShoulder() {
	return (validate(11) > 0) & 0xFF;
}
boolean ROJoystick::btnRShoulder() {
	return (validate(12) > 0) & 0xFF;
}
byte ROJoystick::lTrigger() {
	if (validate(13) != -1)
		return validate(13) & 0xFF;
	else
		return 0;
}
byte ROJoystick::rTrigger() {
	if (validate(14) != -1)
		return validate(14) & 0xFF;
	else
		return 0;
}
boolean ROJoystick::btnStart() {
	return (validate(15) > 0);
}
boolean ROJoystick::btnSelect() {
	return (validate(16) > 0);
}
boolean ROJoystick::btnAux() {
	return (validate(17) > 0);
}
byte ROJoystick::accelX() {
	if (validate(12) != -1)
		return validate(12) & 0xFF;
	else
		return 0;
}
byte ROJoystick::accelY() {
	if (validate(13) != -1)
		return validate(13) & 0xFF;
	else
		return 0;
}
byte ROJoystick::accelZ() {
	if (validate(14) != -1)
		return validate(14) & 0xFF;
	else
		return 0;
}
byte ROJoystick::gyroX() {
	if (validate(15) != -1)
		return validate(15) & 0xFF;
	else
		return 0;
}
byte ROJoystick::gyroY() {
	if (validate(16) != -1)
		return validate(16) & 0xFF;
	else
		return 0;
}
byte ROJoystick::gyroZ() {
	if (validate(17) != -1)
		return validate(17) & 0xFF;
	else
		return 0;
}

int ROJoystick::validate(char componentIndex) {
    char *joy = RobotOpen.getJoystick(_index);

    if (joy == 0 || componentIndex > 17)
        return -1;
    else
        return joy[componentIndex];
}