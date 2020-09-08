#include <Arduino.h>

class StepperMotor {
  public:
    StepperMotor();
    void Rotate(int);
    int motorPosition;
    int motorDirection;
    void Enable(void);
    void Disable(void);
    void Reset(void);
    void setMotorSpeed(int);
    uint32_t motorPeriod;
    bool motorEnabled;
    uint32_t stepsRemaining;
  private:
    const int directionPin = 1;
    const int stepPin = 2;
    const int sleepPin = 3;
    const int resetPin = 4;
    const int ms1Pin = 5;
    const int ms2Pin = 6;
    const int ms3Pin = 7;
    const int enablePin = 8;
    const int vddPin = 9;
    const int motorEnablePin = 10;
};
