#include "Arduino.h"

#define SLAVE_SELECT_PIN 23
#define SYNC_PIN 22
#define DATA_READY_PIN 21
#define MAX_ADC_DATA 3
#define SDO_PIN 12
#define SCLK_PIN 13

class AD7766 {
  public:
    static void Reset();
    static void Initialize();
    static void Sample();
    static uint8_t adcData[MAX_ADC_DATA];
    static uint32_t dataPointsToSample;
    static uint32_t dataCounter;
    
};
