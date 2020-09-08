#include "StepperMotor.h"
#include <Arduino.h>
#include <elapsedMillis.h>
IntervalTimer motorTimer;

StepperMotor::StepperMotor(void) {
  this->stepsRemaining = 0;
  
  pinMode(this->vddPin, OUTPUT);
  pinMode(this->directionPin, OUTPUT); 
  pinMode(this->stepPin, OUTPUT);
  pinMode(this->sleepPin, OUTPUT);
  pinMode(this->enablePin, OUTPUT);
  pinMode(this->resetPin, OUTPUT);
  pinMode(this->ms3Pin, OUTPUT);
  pinMode(this->ms2Pin, OUTPUT);
  pinMode(this->ms1Pin, OUTPUT);
  pinMode(this->motorEnablePin, OUTPUT);
  this->Reset();
  
}
void StepperMotor::beginRotation(int rotationSteps) {
  if(rotationSteps < 0) {
    this->motorDirection = 1;
    digitalWrite(this->directionPin, HIGH);
    rotationSteps *= -1;
    
  }
  else {
    this->motorDirection = 0;
    digitalWrite(this->directionPin, LOW);
  }
  this->stepsRemaining = rotationSteps;
}

void StepperMotor::Rotate(int rotationSteps) {
  this->motorPosition += rotationSteps;
  if(rotationSteps < 0) {
    this->motorDirection = 1;
    digitalWrite(this->directionPin, HIGH);
    rotationSteps *= -1;
    
  }
  else {
    this->motorDirection = 0;
    digitalWrite(this->directionPin, LOW);
  }
  
  for(int i=0; i<rotationSteps; i++) {
    digitalWrite(this->stepPin, LOW);
    delay(this->motorPeriod);
    digitalWrite(this->stepPin, HIGH);
  }
}

void StepperMotor::Disable() {
  digitalWrite(this->enablePin, HIGH);
  this->motorEnabled = 0;
}

void StepperMotor::Enable() {
  digitalWrite(this->enablePin, LOW);
  this->motorEnabled = 1;
}

void StepperMotor::Reset() {
  this->motorPosition = 0;
  this->motorDirection = 0;
  this->motorPeriod = 2;
  this->motorEnabled = 1;
  digitalWrite(this->vddPin, HIGH);
  
  this->Enable();
  
  digitalWrite(this->ms3Pin, HIGH); // use the finest possible (1/16 step) microstepping
  digitalWrite(this->ms2Pin, HIGH);
  digitalWrite(this->ms1Pin, HIGH);

  digitalWrite(this->directionPin, this->motorDirection);
  digitalWrite(this->stepPin, HIGH);
  
  digitalWrite(this->enablePin, LOW); // enable is active low
  digitalWrite(this->sleepPin, HIGH); // sleep is active low
  digitalWrite(this->resetPin, HIGH); // reset is active low
  digitalWrite(this->resetPin, LOW); // reset the controller
  digitalWrite(this->resetPin, HIGH);
}
