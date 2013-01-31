#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <Servo.h>
#include <RobotOpen.h>



/* DS Joystick Setup */
ROJoystick usb1(1);
ROEncoder myEnc(0);
ROPWM leftDrive(0);
ROPWM rightDrive(1);
ROSolenoid giantArm(0);
RODigitalIO connectedLED(0, OUTPUT);
ROAnalog an0(0);
ROAnalog an1(1);


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
  leftDrive.write(usb1.leftY());
  rightDrive.write(usb1.rightY());
  giantArm.on();
  connectedLED.on();
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
  RODashboard.publish("Analog 0", an0.read());
  RODashboard.publish("Analog 1", an1.read());
  RODashboard.publish("Encoder 0", myEnc.read());
  RODashboard.publish("Uptime Seconds", ROStatus.uptimeSeconds());
  RODashboard.debug("Some debug data...");
  ROBlackBox.log("Some SD card data.");
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}