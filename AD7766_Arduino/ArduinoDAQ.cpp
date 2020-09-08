#include "ArduinoDAQ.h"
#include "Arduino.h"
#include <Vrekrer_scpi_parser.h>
  
int ArduinoDAQ::adcPin;
uint8_t ArduinoDAQ::adcData[MAX_NUMBER_MEASUREMENTS];
uint8_t ArduinoDAQ::operationRegister;
uint8_t ArduinoDAQ::questionableStatusRegister;
uint8_t ArduinoDAQ::errorEventQueue;
int ArduinoDAQ::numberADCMeasurements;

/** Arduino DAQ Constructor */
ArduinoDAQ::ArduinoDAQ(const int adcPin) {
  
  pinMode(ArduinoDAQ::adcPin, INPUT);
  ArduinoDAQ::numberADCMeasurements = 1;
  ArduinoDAQ::operationRegister = 0;
  ArduinoDAQ::questionableStatusRegister = 0;
  ArduinoDAQ::errorEventQueue = 0;
  
  this->myInstrument = SCPI_Parser();
  this->myInstrument.RegisterCommand(F("*IDN?"), &ArduinoDAQ::Identify);
  this->myInstrument.RegisterCommand(F("*RST"), &Reset);
  this->myInstrument.RegisterCommand(F("*CLS"), &Clear);

  this->myInstrument.SetCommandTreeBase("");
  this->myInstrument.RegisterCommand("MEASure?", &measureADCData);
  this->myInstrument.RegisterCommand("CONFigure", &configureADC);
  this->myInstrument.RegisterCommand("FETCh?", &fetchADCData);
}

/** Wrapper for SCPI ProcessInput function.
@param interface: address (?) of Stream interface (i.e. Serial, SerialUSB) 
@param terminationCharacters: string of expected characters at the end of every SCPI command
*/
void ArduinoDAQ::ProcessInput(Stream &interface, char* terminationCharacters) {
  this->myInstrument.ProcessInput(interface, terminationCharacters);
}

/** Required SCPI Identify query, executed by sending *IDN? to the device */
void ArduinoDAQ::Identify(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  interface.println(F("Vrekrer,Arduino SCPI Dimmer,#00,v0.4"));
}

/** Resets all ADC settings, data, and status/error bytes to their default values */
void ArduinoDAQ::Reset(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  for(int i = 0; i < MAX_NUMBER_MEASUREMENTS; i++) {
    ArduinoDAQ::adcData[i] = 0;
  }
  ArduinoDAQ::numberADCMeasurements = 1;
  ArduinoDAQ::operationRegister = 0;
  ArduinoDAQ::questionableStatusRegister = 0;
  ArduinoDAQ::errorEventQueue = 0;
}

/** Clears all the status/error registers of the device */
void ArduinoDAQ::Clear(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  operationRegister = 0;
  questionableStatusRegister = 0;
  errorEventQueue = 0;
}

/* Configures the number of ADC measurements we want to take */
void ArduinoDAQ::configureADC(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  ArduinoDAQ::numberADCMeasurements = constrain(String(parameters[0]).toInt(), 1, MAX_NUMBER_MEASUREMENTS);
}

/* Iniates ADC measurements and returns the data over the specified interface */
void ArduinoDAQ::measureADCData(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  interface.write('#');
  for(int i=0; i < numberADCMeasurements; i++) {
    adcData[i] = analogRead(adcPin);
    interface.write(adcData[i]);
  }
}

/* Fetches previously-measured ADC data stored in the internal buffer */
void ArduinoDAQ::fetchADCData(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  interface.write('#');
  for(int i=0; i < numberADCMeasurements; i++) {
    interface.write(adcData[i]);
  }
}
