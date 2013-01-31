#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Servo.h>
#include <RobotOpen.h>
#include <ROEncoder.h>



/* DS Joystick Setup */
ROJoystick usb1(1);
ROEncoder myEnc(0);


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
  RobotOpen.writePWM(0, usb1.leftY());
  RobotOpen.writePWM(1, usb1.rightY());
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  // safety code
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RobotOpen.publish("Analog 0", analogRead(0));
  RobotOpen.publish("Analog 1", analogRead(1));
  RobotOpen.publish("Encoder 0", myEnc.read());
  RobotOpen.log("some debug data...");
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}