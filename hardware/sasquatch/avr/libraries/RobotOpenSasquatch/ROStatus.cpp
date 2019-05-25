#include "RobotOpenSQ.h"

// Class constructor
ROStatusClass ROStatus;



float ROStatusClass::batteryReading() {
	// sasquatch has a 1/6 voltage divider on BMC pin
    return ((analogRead(12) * (5.0 / 1023.0)) * 6);
}

boolean ROStatusClass::isEnabled() {
    return RobotOpen.enabled();
}

int ROStatusClass::uptimeSeconds() {
    return (int)(millis()/1000);
}