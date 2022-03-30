//Rotary table for welding purposes with 27:1 nema motor.
#include "AccelStepper.h"
// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 5 // dir x pin
#define stepPin 2 // step x pin
#define motorInterfaceType 1
#define enablePin 8 // enable pin - tested - correct
#define startPin 9 // end stop x pin
#define analogAccelleration A0 // reset-abort pin on shield
#define analogDistance A1 // hold pin on shield
#define analogSpeed A2 // resume pin on shield
#define analogDelay A3 // coolant pin on shield

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
void setup() {
  // Set the maximum speed in steps per second:
  // stepper.setAcceleration(1000);
  pinMode(enablePin, OUTPUT);    // sets the digital pin as output
  pinMode(analogSpeed,INPUT); // this pin sets the motor rotation speed
  pinMode(analogDelay,INPUT); // this pin sets the motor delay startup time
  pinMode(analogDistance,INPUT); // this pin sets the 360deg extension
  pinMode(analogAccelleration,INPUT); // this pin sets the acceleration
  pinMode(startPin, INPUT_PULLUP);    // sets the digital pin as output
  digitalWrite(enablePin, HIGH); // disable the motor

}
void loop() {

  stepper.setAcceleration(map((analogRead(analogAccelleration)),0,1023,100,4000));
  if(!digitalRead(startPin)){
  stepper.setMaxSpeed(map((analogRead(analogSpeed)),0,1023,90,5040));			// 720pulses/rpm - maximum speed from x*60/(200*27*8) rpm to y*60/(200*27*8) rpm (60sec per minute, 200 steps per internal rev, 27:1 gearbox, 8 microsteps per step)
  delay(map((analogRead(analogDelay)),0,1023,100,20000));  						// delay in ms (from 0.1 - 60 seconds)
  digitalWrite(enablePin, LOW); 												// this enables the motor


 stepper.moveTo(100+map((analogRead(analogDistance)),0,1023,0,86400));  // 0 - 2 revolutions - 200*8*27=43200 steps per rev (200 steps per internal rev, 27:1 gearbox, 8 microsteps per step)
 stepper.runToPosition();
 stepper.setCurrentPosition(0);
 digitalWrite(enablePin, HIGH); // disable the motor
 }
}
/*

  // Set the speed in steps per second:
  //stepper.setSpeed(400);
  // Step the motor with a constant speed as set by setSpeed():
  //stepper.runSpeed();
 // EEPROM.write(addr, val); //each bite is value from 0 to 255.
#######################################
# Syntax Coloring Map For AccelStepper
#######################################

#######################################
# Datatypes (KEYWORD1)
#######################################

AccelStepper  KEYWORD1
MultiStepper  KEYWORD1

#######################################
# Methods and Functions (KEYWORD2)
#######################################

moveTo  KEYWORD2
move  KEYWORD2
run KEYWORD2
runSpeed  KEYWORD2
setMaxSpeed KEYWORD2
setAcceleration KEYWORD2
setSpeed  KEYWORD2
speed KEYWORD2
distanceToGo  KEYWORD2
targetPosition  KEYWORD2
currentPosition KEYWORD2
setCurrentPosition  KEYWORD2
runToPosition KEYWORD2
runSpeedToPosition  KEYWORD2
runToNewPosition  KEYWORD2
stop  KEYWORD2
disableOutputs  KEYWORD2
enableOutputs KEYWORD2
setMinPulseWidth  KEYWORD2
setEnablePin  KEYWORD2
setPinsInverted KEYWORD2
maxSpeed  KEYWORD2
#######################################
# Constants (LITERAL1)
#######################################



*/
