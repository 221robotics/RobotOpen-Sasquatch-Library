/*
  RobotOpen.h - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#ifndef RobotOpen_h
#define RobotOpen_h

#include "Arduino.h"
#include <ROJoystick.h>

// Solenoid Constants
#define ON 0xFF
#define OFF 0x00

typedef void LoopCallback();


class RobotOpenClass {
public:
    // Fire up the RobotOpen object and get things running
    static void begin(LoopCallback *enabledCallback, LoopCallback *disabledCallback, LoopCallback *timedtasksCallback);
    
    // Exchange data with DS
    static void syncDS();

    // Log data to DS
    static void log(String data);
    
    // Tells us if the robot is enabled
    static boolean enabled();

    // How many joysticks are being received
    static int numJoysticks();

    // Overloaded calls to publish back data
    static boolean publish(String id, boolean val);
    static boolean publish(String id, char val);
    static boolean publish(String id, int val);
    static boolean publish(String id, long val);
    static boolean publish(String id, float val);

    static char* getJoystick(char index);

private:
    // Dumps data back to the DS
    static void publishDS();

    // Parse out a DS packet
    static void parsePacket();

    // Grab UDP data
    static void handleData();

    // Dumps status info back to DS
    static void sendStatusPacket();
    
    // CRC16 checksum function
    static unsigned int calc_crc16(unsigned char *buf, unsigned short len);
};

extern RobotOpenClass RobotOpen;

#endif