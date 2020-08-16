#include "Arduino.h"

#define SLAVE_SELECT_PIN 4
#define SYNC_PIN 9
#define DATA_READY_PIN 7
#define MAX_ADC_DATA

class AD7766 {
  public:
    void beginReadingData();
    void Reset();
    void Initialize();
    static void Sample();
    static uint8_t adcData[MAX_ADC_DATA];
    static uint32_t dataCounter;
    
};
