#include "ArduinoDAQ.h"
#include "Arduino.h"
#include <Vrekrer_scpi_parser.h>
  

/** SCPI String Array Constructor */
ArduinoDAQ::ArduinoDAQ() {
  this->myInstrument = SCPI_Parser();
  this->myInstrument.RegisterCommand(F("*IDN?"), &ArduinoDAQ::Identify);
}

/** Wrapper for SCPI ProcessInput function.
@param interface: address (?) of Stream interface (i.e. Serial, SerialUSB) 
@param terminationCharacters: string of expected characters at the end of every SCPI command */
void ArduinoDAQ::ProcessInput(Stream &interface, char* terminationCharacters) {
  this->myInstrument.ProcessInput(interface, terminationCharacters);
}

/** Required SCPI Identify query, executed by sending *IDN? to the device */
static void ArduinoDAQ::Identify(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  interface.println(F("Vrekrer,Arduino SCPI Dimmer,#00,v0.4"));
}
