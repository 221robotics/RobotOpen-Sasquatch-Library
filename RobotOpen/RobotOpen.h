/*
  RobotOpen.h - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, October 16, 2011.
*/

#ifndef RobotOpen_h
#define RobotOpen_h

#include "Arduino.h"

#include <WebSocket.h>

// Solenoid Constants
#define ON 0xFF
#define OFF 0x00

// D-PAD Constants
#define UP 0x3F
#define UP_LEFT 0x1F
#define UP_RIGHT 0x5F
#define DOWN 0xBF
#define DOWN_LEFT 0xDF
#define DOWN_RIGHT 0x9F
#define LEFT 0xFF
#define RIGHT 0x7F

// Joystick modifiers
#define INVERT 1
#define NORMAL 0



typedef struct {
   unsigned int length;
   unsigned int payloadIndex;
} bundleInfo;


class RobotOpenClass {
public:
    // Fire up the RobotOpen object and get things running
    static void begin();
    
    // Check for fresh data
    static void pollDS();
    
    // There is a feedback packet ready to send
    static void outgoingDS();
    
    // Tells us if the robot is enabled
    static boolean enabled();

private:
    // Dumps data back to the DS
    static void publishDS();
};

extern RobotOpenClass RobotOpen;

class USBJoystick
{
  public:
    USBJoystick(unsigned char);
    int getIndex(int index);
    unsigned int makePWM(int index, char mode);
    boolean getBtn(int index, char mode);
    boolean getDpad(unsigned char compare, char mode);
    
  private:
    unsigned char _bundleID;
};

#endif