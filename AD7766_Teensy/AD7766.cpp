#include <SPI.h>
#include "AD7766.h"

/** Resets the AD7766 ADC as per the datasheet by pulsing the SYNC/PD pin
  * SDI - to digital pin 11 (MOSI pin)
  * CLK - to digital pin 13 (SCK pin)
  * SS - to convenient digital pin
  * DRDY - to convenient digital pin
  * SYNC/PD - to convenient digital pin
  * SDO to digital pin 12 (MISO pin)
 */
uint8_t AD7766::adcData[MAX_ADC_DATA] = {0, 0, 0};
uint32_t AD7766::dataPointsToSample = 1;
uint32_t AD7766::dataCounter = 0;

void AD7766::Reset() {
  AD7766::dataCounter = 0;
  AD7766::adcData[0] = 0;
  AD7766::adcData[1] = 0;
  AD7766::adcData[2] = 0;
  AD7766::dataPointsToSample = 1;
  digitalWrite(SYNC_PIN, LOW);
  delay(1);
  digitalWrite(SYNC_PIN, HIGH);
}

void AD7766::Sample() {
  if(AD7766::dataCounter < AD7766::dataPointsToSample) {
    AD7766::dataCounter += 1;
    AD7766::adcData[0] = SPI.transfer(0);
    AD7766::adcData[1] = SPI.transfer(0);
    AD7766::adcData[2] = SPI.transfer(0);
    Serial.write(AD7766::adcData, 3);
    //Serial.println("Sampled!");
  }
  else if(AD7766::dataCounter >= AD7766::dataPointsToSample) {
    detachInterrupt(digitalPinToInterrupt(DATA_READY_PIN));
    AD7766::dataCounter = 0;
  }
}

void AD7766::Initialize() {
  SPI.begin(); // TODO: change the SPI mode so that it is compatible with our ADC
  // SPI.setClockDivider(8);
  // clock polarity should be zero (zero means no activity, chip acts on the rising edge)
  // we want the CPHA bit to be 1, so our SPI Mode should be 1
  SPI.beginTransaction(SPISettings(12000000, MSBFIRST, SPI_MODE1));
  pinMode(DATA_READY_PIN, INPUT);
  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  pinMode(SYNC_PIN, OUTPUT);
  
  delay(100);
  digitalWrite(SLAVE_SELECT_PIN, LOW); // whenever the ADC is ready, we are ready.

  //attachInterrupt(digitalPinToInterrupt(DATA_READY_PIN), AD7766::Sample, FALLING);
  AD7766::Reset();
}
