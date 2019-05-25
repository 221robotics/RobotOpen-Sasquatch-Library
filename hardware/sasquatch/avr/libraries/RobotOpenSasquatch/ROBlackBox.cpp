#include "RobotOpenSQ.h"

// Class constructor
ROBlackBoxClass ROBlackBox;



void ROBlackBoxClass::log(String data) {
    RobotOpen.logToSD(data);
}