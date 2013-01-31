
#ifndef ROBlackBox_h
#define ROBlackBox_h

#include <RobotOpen.h>



class ROBlackBoxClass {
public:
    // Log data to SD
    static void log(String data);
};

extern ROBlackBoxClass ROBlackBox;

#endif