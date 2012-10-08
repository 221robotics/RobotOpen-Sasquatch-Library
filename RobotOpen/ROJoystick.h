#ifndef ROJoystick_h
#define ROJoystick_h

#include <RobotOpen.h>

// D-PAD Constants
#define UP 0x3F
#define UP_LEFT 0x1F
#define UP_RIGHT 0x5F
#define DOWN 0xBF
#define DOWN_LEFT 0xDF
#define DOWN_RIGHT 0x9F
#define LEFT 0xFF
#define RIGHT 0x7F

class ROJoystick
{
  public:
    ROJoystick(char);
    int getComponent(char index);

    byte leftX();
    byte leftY();
    byte rightX();
    byte rightY();
    boolean btnLStick();
    boolean btnRStick();
    byte dPad();
    boolean btn1();
    boolean btn2();
    boolean btn3();
    boolean btn4();
    boolean btn5();
    boolean btn6();
    boolean btn7();
    boolean btn8();
    boolean btnLShoulder();
    boolean btnRShoulder();
    byte lTrigger();
    byte rTrigger();
    boolean btnStart();
    boolean btnSelect();
    boolean btnAux();
    byte accelX();
    byte accelY();
    byte accelZ();
    byte gyroX();
    byte gyroY();
    byte gyroZ();
    
  private:
    char _index;

    int validate(char index);
};



#endif