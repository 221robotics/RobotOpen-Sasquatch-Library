#include "RobotOpen.h"

// Class constructor
ROStatusClass ROStatus;



int ROStatusClass::batteryReading() {
    return analogRead(12);
}

boolean ROStatusClass::isEnabled() {
    return RobotOpen.enabled();
}

int ROStatusClass::uptimeSeconds() {
    return (int)(millis()/1000);
}