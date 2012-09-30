
#include "RobotOpen.h"

/* Constructor */
ROJoystick::ROJoystick(char index)
{
    _index = index;
}

int ROJoystick::getComponent(char componentIndex) {
    return validate(componentIndex);
}

int ROJoystick::validate(char componentIndex) {
    char *joy = RobotOpen.getJoystick(_index);

    if (joy == 0 || componentIndex > 17)
        return -1;
    else
        return joy[componentIndex];
}