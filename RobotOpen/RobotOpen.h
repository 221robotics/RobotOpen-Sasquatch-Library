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



/* GAMEPAD MAPPING */
#define ANALOG_LEFTX 0x00;
#define ANALOG_LEFTY 0x01;
#define ANALOG_RIGHTX 0x02;
#define ANALOG_RIGHTY 0x03;
#define LEFT_STICK_BTN 0x04;
#define RIGHT_STICK_BTN 0x05;
#define DPAD 0x06;
#define BTN_1 0x07;
#define BTN_2 0x08;
#define BTN_3 0x09;
#define BTN_4 0x0A;
#define LEFT_SHOULDER 0x0B;
#define RIGHT_SHOULDER 0x0C;
#define LEFT_TRIGGER 0x0D;
#define RIGHT_TRIGGER 0x0E;
#define START_BTN 0x0F;
#define SELECT_BTN 0x10;
#define AUX_BTN 0x11;

/* MOBILE MAPPING */
#define ANALOG_LEFTX 0x00;
#define ANALOG_LEFTY 0x01;
#define ANALOG_RIGHTX 0x02;
#define ANALOG_RIGHTY 0x03;
#define BTN_1 0x04;
#define BTN_2 0x05;
#define BTN_3 0x06;
#define BTN_4 0x07;
#define BTN_5 0x08;
#define BTN_6 0x09;
#define BTN_7 0x0A;
#define BTN_8 0x0B;
#define ACCEL_X 0x0C;
#define ACCEL_Y 0x0D;
#define ACCEL_Z 0x0E;
#define GYRO_X 0x0F;
#define GYRO_Y 0x10;
#define GYRO_Z 0x11;



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

    // Log data to DS
    static void log(char *data);
    
    // There is a feedback packet ready to send
    static void outgoingDS();
    
    // Tells us if the robot is enabled
    static boolean enabled();

    // Overloaded calls to publish back data
    static boolean publishToDS(char *id, boolean val);
    static boolean publishToDS(char *id, char val);
    static boolean publishToDS(char *id, int val);
    static boolean publishToDS(char *id, long val);
    static boolean publishToDS(char *id, float val);

private:
    // Dumps data back to the DS
    static void publishDS();

    static void sendStatusPacket();
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