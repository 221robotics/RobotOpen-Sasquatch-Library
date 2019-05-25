#include "RobotOpenSQ.h"

/* Constructor */
ROJoystick::ROJoystick(char index)
{
    _index = index;
}

byte ROJoystick::leftX() {
	return validate(0, true);
}
byte ROJoystick::leftY() {
	return validate(1, true);
}
byte ROJoystick::rightX() {
	return validate(2, true);
}
byte ROJoystick::rightY() {
	return validate(3, true);
}
boolean ROJoystick::btnA() {
	return (validate(4, false) > 0);
}
boolean ROJoystick::btnB() {
	return (validate(5, false) > 0);
}
boolean ROJoystick::btnX() {
	return (validate(6, false) > 0);
}
boolean ROJoystick::btnY() {
	return (validate(7, false) > 0);
}
boolean ROJoystick::btnLShoulder() {
	return (validate(8, false) > 0);
}
boolean ROJoystick::btnRShoulder() {
	return (validate(9, false) > 0);
}
byte ROJoystick::lTrigger() {
	return validate(10, false);
}
byte ROJoystick::rTrigger() {
	return validate(11, false);
}
boolean ROJoystick::btnSelect() {
	return (validate(12, false) > 0);
}
boolean ROJoystick::btnStart() {
	return (validate(13, false) > 0);
}
boolean ROJoystick::btnLStick() {
	return (validate(14, false) > 0);
}
boolean ROJoystick::btnRStick() {
	return (validate(15, false) > 0);
}
boolean ROJoystick::dPadUp() {
	return (validate(16, false) > 0);
}
boolean ROJoystick::dPadDown() {
	return (validate(17, false) > 0);
}
boolean ROJoystick::dPadLeft() {
	return (validate(18, false) > 0);
}
boolean ROJoystick::dPadRight() {
	return (validate(19, false) > 0);
}
byte ROJoystick::auxOne() {
	return validate(20, false);
}
byte ROJoystick::auxTwo() {
	return validate(21, false);
}
byte ROJoystick::auxThree() {
	return validate(22, false);
}
byte ROJoystick::auxFour() {
	return validate(23, false);
}




byte ROJoystick::validate(char componentIndex, boolean neutralOnError) {
    char *joy = RobotOpen.getJoystick(_index);

    if (joy == 0 || componentIndex > 23) {
    	if (neutralOnError)
    		return 127;
    	else
    		return 0;
    } else {
    	return joy[componentIndex];
    }
}