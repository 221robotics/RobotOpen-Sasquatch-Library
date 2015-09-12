#ifndef ROStatus_h
#define ROStatus_h

#include "RobotOpenSQ.h"



class ROStatusClass {
public:
    static float batteryReading();

	static boolean isEnabled();

	static int uptimeSeconds();

};

extern ROStatusClass ROStatus;

#endif