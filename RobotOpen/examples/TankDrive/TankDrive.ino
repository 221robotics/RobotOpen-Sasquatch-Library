#include <SPI.h>
#include <Ethernet.h>
#include <RobotOpen.h>
#include <Servo.h>


/* DS Joystick Setup */
ROJoystick usb1(1);

// setup a servo
Servo myservo;

void setup()
{
  /* Initiate comms */
  RobotOpen.begin(&enabled, &disabled, &timedtasks);

  myservo.attach(9);
}


/* This is your primary robot loop - all of your code
 * should live here that allows the robot to operate
 */
void enabled() {
  // Constantly update PWM values with joystick values
  myservo.write(map(usb1.rightY(), 0, 255, 0, 180));
}


/* This is called while the robot is disabled
 * You must make sure to set all of your outputs
 * to safe/disable values here
 */
void disabled() {
  myservo.write(90);
}


/* This loop ALWAYS runs - only place code here that can run during a disabled state
 * This is also a good spot to put driver station publish code
 */
void timedtasks() {
  RobotOpen.publish("right-y", usb1.rightY());
}


// !!! DO NOT MODIFY !!!
void loop() {
  RobotOpen.syncDS();
}