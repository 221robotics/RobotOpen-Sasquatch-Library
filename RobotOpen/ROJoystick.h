#ifndef ROJoystick_h
#define ROJoystick_h

#include <RobotOpen.h>


class ROJoystick
{
  public:
    ROJoystick(char);
    int getComponent(char index);

    byte leftX();
    byte leftY();
    byte rightX();
    byte rightY();
    boolean btnA();
    boolean btnB();
    boolean btnX();
    boolean btnY();
    boolean btnLShoulder();
    boolean btnRShoulder();
    byte lTrigger();
    byte rTrigger();
    boolean btnSelect();
    boolean btnStart();
    boolean btnLStick();
    boolean btnRStick();
    boolean dPadUp();
    boolean dPadDown();
    boolean dPadLeft();
    boolean dPadRight();

    
  private:
    char _index;

    int validate(char index);
};



#endif