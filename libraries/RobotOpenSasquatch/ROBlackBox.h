#ifndef ROBlackBox_h
#define ROBlackBox_h

#include "RobotOpenSQ.h"



class ROBlackBoxClass {
public:
    // Log data to SD
    static void log(String data);
};

extern ROBlackBoxClass ROBlackBox;

#endif