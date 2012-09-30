#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>


/* I/O Setup */
ROJoystick usb1(1);


void setup()
{
  /* Initiate comms */
  RobotOpen.begin();
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Constantly update PWM values with joystick values
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  // PWMs are automatically disabled
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
    RobotOpen.publish("theanswer", 42);
}


/* This is the main program loop that keeps comms operational
 * There's no need to touch anything here!!!
 */
void loop() {
  RobotOpen.syncDS();
  if (RobotOpen.enabled())
    enabled();
  else
    disabled();
  timedtasks();
}