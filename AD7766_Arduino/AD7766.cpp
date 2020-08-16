/*
 * Compare the speed of the Arduino's Serial communication to the native USB
 * 
 */
#include <SPI.h>
#include "AD7766.h"
#include "SPI_register_level.h"

/** Resets the AD7766 ADC as per the datasheet by pulsing the SYNC/PD pin
 */
void AD7766::Reset() {
  digitalWrite(SYNC_PIN, LOW);
  delay(1);
  digitalWrite(SYNC_PIN, HIGH);
}

void AD7766::Sample() {
  AD7766::adcData[AD7766::dataCounter] = SPI.transfer(0); // NOTE: This is the very slow (old) code
  AD7766::dataCounter += 1;
  
  NOP64; // initial NOP to wait for the ADC data to be ready
  SPIInitiateRead();
  NOP64;
  // very hacky - just assume the data will be ready at this time, when in fact it might not.
  AD7766::adcData[AD7766::dataCounter] = SPI0->SPI_RDR;
  SPIInitiateRead();
  NOP64;
  AD7766::adcData[AD7766::dataCounter +1] = SPI0->SPI_RDR;
  SPIInitiateRead();
  NOP64;
  AD7766::adcData[AD7766::dataCounter + 2] = SPI0->SPI_RDR;
  AD7766::dataCounter += 3;
}

void AD7766::Initialize() {
  SPI.begin();
  SPI.setClockDivider(8);
  pinMode(DATA_READY_PIN, INPUT);
  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  pinMode(SYNC_PIN, OUTPUT);
  
  delay(100);
  digitalWrite(SLAVE_SELECT_PIN, LOW); // whenever the ADC is ready, we are ready.

  attachInterrupt(digitalPinToInterrupt(DATA_READY_PIN), AD7766::Sample, FALLING);
  AD7766::Reset();
}

char adcData[512];
uint8_t dataCounter = 0;

/*
void setup() {
  // put your setup code here, to run once:
  
  SerialUSB.begin(9600);
  
  
}

void loop() {
  SerialUSB.write(adcData);
}
*/
