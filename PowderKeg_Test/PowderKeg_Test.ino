#include "ROPins.h"
#include <Servo.h>



Servo myservo; 

void setup() {
  // set RO pin modes
  roPinMode(0, OUTPUT);  // DIO0 on board
  roPinMode(1, INPUT);   // DIO1 on board
  
  // attach servo
  myservo.attach(PWM3);  // PWM3 on board
  
  // enable solenoid
  roEnableSolenoid(2);   // S2 on board
}

void loop() {
  // write to DIO0
  roPinWrite(0, HIGH);
  
  // read from DIO1
  if (roPinRead(1))
    Serial.println("DIO1 is high");
  
  // set servo value between 0-180
  myservo.write(90);
  
  // turn on solenoid S2
  roSolenoidWrite(2, HIGH);
  
  int sensorValOne = analogRead(AI0);
  
  int sensorValTwo = analogRead(AI4);
  
  // battery monitoring value
  int batteryVoltage = analogRead(BMC);
}
