/*
  RobotOpen.h - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#ifndef RobotOpen_h
#define RobotOpen_h

#include "Arduino.h"
#include <WebSocket.h>

// Solenoid Constants
#define ON 0xFF
#define OFF 0x00



class RobotOpenClass {
public:
    // Fire up the RobotOpen object and get things running
    static void begin();
    
    // Exchange data with DS
    static void syncDS();

    // Log data to DS
    static void log(String data);
    
    // Tells us if the robot is enabled
    static boolean enabled();

    // How many joysticks are being received
    static int numJoysticks();

    // Overloaded calls to publish back data
    static boolean publishToDS(String id, boolean val);
    static boolean publishToDS(String id, char val);
    static boolean publishToDS(String id, int val);
    static boolean publishToDS(String id, long val);
    static boolean publishToDS(String id, float val);

    static char* getJoystick(char index);

private:
    // Dumps data back to the DS
    static void publishDS();

    // Dumps status info back to DS
    static void sendStatusPacket();
};

extern RobotOpenClass RobotOpen;

#endif