#ifndef ROJoystick_h
#define ROJoystick_h

#include <RobotOpen.h>



class ROJoystick
{
  public:
    ROJoystick(char);
    int getComponent(char index);
    
  private:
    char _index;

    int validate(char index);
};



#endif
