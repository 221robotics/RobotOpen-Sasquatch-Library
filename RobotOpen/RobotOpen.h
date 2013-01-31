/*
  RobotOpen.h - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#ifndef RobotOpen_h
#define RobotOpen_h

#include "Arduino.h"
#include <ROJoystick.h>
#include <ROEncoder.h>
#include <ROPWM.h>
#include <RODashboard.h>
#include <ROSolenoid.h>
#include <ROBlackBox.h>
#include <RODigitalIO.h>
#include <ROAnalog.h>
#include <ROStatus.h>
#include "IPAddress.h"


// Solenoid Constants
#define ON 0xFF
#define OFF 0x00

typedef void LoopCallback();


class RobotOpenClass {
public:
    // Set the IP address that the Robot controller will have
    static void setIP(IPAddress newIP);

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

    // Log to SD card
    static void logToSD(String);

    // Overloaded calls to publish back data
    static boolean publish(String id, unsigned char val);
    static boolean publish(String id, int val);
    static boolean publish(String id, long val);
    static boolean publish(String id, float val);

    static char* getJoystick(char index);

    static void writePWM(byte channel, byte pwmVal);
    static void writeSolenoid(byte channel, uint8_t state);
    static void writeDigital(byte channel, uint8_t state);
    static void makeOutput(byte channel);
    static void makeInput(byte channel);
    static void setPullup(byte channel, boolean pullUp);

private:
    // Dumps data back to the DS
    static void publishDS();

    // This gets called once when the robot becomes disconnected or disabled
    static void onDisable();

    // Parse out a DS packet
    static void parsePacket();

    // Grab UDP data
    static void handleData();
    
    // CRC16 checksum function
    static unsigned int calc_crc16(unsigned char *buf, unsigned short len);
};

extern RobotOpenClass RobotOpen;

#endif