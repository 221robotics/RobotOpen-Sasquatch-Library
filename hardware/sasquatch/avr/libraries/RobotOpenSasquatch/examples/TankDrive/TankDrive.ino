#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Servo.h>
#include <EEPROM.h>
#include <RobotOpenSQ.h>



/* I/O Setup */
ROJoystick usb1(1);         // Joystick #1
ROEncoder leftEncoder(0);   // Encoder Channel 0
ROEncoder rightEncoder(1);  // Encoder Channel 1
ROPWM leftDrive(0);
ROPWM rightDrive(1);


void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Constantly update PWM values with joystick values
  // Analog sticks feed back values from 0-255
  // 255 - usb1.leftY() to invert a drive
  leftDrive.write(usb1.leftY());
  rightDrive.write(usb1.rightY());
}


/* This is called while the robot is disabled
 * All outputs are automatically disabled (PWM, Solenoid, Digital Outs)
 */
void disabled() {
  // safety code
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RODashboard.publish("Left Encoder", leftEncoder.read());
  RODashboard.publish("Right Encoder", rightEncoder.read());
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}