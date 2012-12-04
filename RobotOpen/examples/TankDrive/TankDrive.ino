#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <RobotOpen.h>
#include <Servo.h>


/* DS Joystick Setup */
ROJoystick usb1(1);

// setup a servo
Servo lDrive;
Servo rDrive;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Attach PWM Outputs
  lDrive.attach(5);
  rDrive.attach(6);

  // Constantly update PWM values with joystick values
  lDrive.write(map(usb1.leftY(), 0, 255, 0, 180));
  rDrive.write(map(usb1.rightY(), 0, 255, 180, 0));
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  lDrive.detach();
  rDrive.detach();
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RobotOpen.publish("left-y", usb1.leftY());
  RobotOpen.publish("right-y", usb1.rightY());
  RobotOpen.log("some debug data...");
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}