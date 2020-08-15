/*
 * Compare the speed of the Arduino's Serial communication to the native USB
 * 
 */
#include <SPI.h>
int testPin = 53;
char adcData[512];
int slaveSelectPin = 4;
int syncPin = 9; // apply a negative pulse to initiate ADC sampling
int dataReadyPin = 7; // The ADC will drive this pin
bool firstSet = false;
uint8_t dataCounter = 0;


void setup() {
  // put your setup code here, to run once:
  
  SerialUSB.begin(9600);
  SPI.begin();
  SPI.setClockDivider(8);
  pinMode(dataReadyPin, INPUT);
  pinMode(slaveSelectPin, OUTPUT);
  pinMode(syncPin, OUTPUT);
  delay(100);
  digitalWrite(slaveSelectPin, LOW); // whenever the ADC is ready, we are ready.
  
  resetADC();
  attachInterrupt(digitalPinToInterrupt(dataReadyPin), sampleADC, FALLING);

  pinMode(testPin, OUTPUT);
  digitalWrite(testPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  //adcData[0] = SPI.transfer(0);
  //adcData[1] = SPI.transfer(0);
  //adcData[2] = SPI.transfer(0);
  SerialUSB.write(adcData);
  //digitalWrite(testPin, LOW);
}

void resetADC() {
  digitalWrite(syncPin, LOW);
  delay(1);
  digitalWrite(syncPin, HIGH);
}
// right now it looks like we get stuck in an eternal interrupt loop. 
// This is unfortunate.
void sampleADC() {
  digitalWrite(testPin, !digitalRead(testPin));
  
  //detachInterrupt(digitalPinToInterrupt(dataReadyPin));
  
  //adcData[dataCounter] = SPI.transfer(0);
  //adcData[dataCounter] = SPI.transfer(0);
  //dataCounter += 3;
  adcData[dataCounter] = SPI.transfer(0);
  //attachInterrupt(digitalPinToInterrupt(dataReadyPin), sampleADC, FALLING);
  digitalWrite(testPin, !digitalRead(testPin));
  
}
