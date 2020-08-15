

/*
Vrekrer_scpi_parser library.
SCPI Dimmer example.
Demonstrates the control of the brightness of a LED using SCPI commands.
Hardware required:
A LED attached to digital pin 9
or a resistor from pin 9 to pin 13 to use the built-in LED
Commands:
  *IDN?
    Gets the instrument's identification string
  SYSTem:LED:BRIGhtness <value>
    Sets the LED's brightness to <value>
    Valid values : 0 (OFF) to 10 (Full brightness)
  SYSTem:LED:BRIGhtness?
    Queries the current LED's brightness value
  SYSTem:LED:BRIGhtness:INCrease
    Increases the LED's brightness value by one
  SYSTem:LED:BRIGhtness:DECrease
    Decreases the LED's brightness value by one
*/


#include "Arduino.h"
#include "ArduinoDAQ.h"
#include <Vrekrer_scpi_parser.h>

#define MAX_NUMBER_MEASUREMENTS 100

SCPI_Parser my_instrument;
ArduinoDAQ my_arduino;
int brightness = 0;
const int ledPin = 9;
const int adcPin = A0;
const int intensity[11] = {0, 3, 5, 9, 15, 24, 38, 62, 99, 159, 255};
int8_t operationRegister = 0;
uint8_t questionableStatusRegister = 0;
uint8_t errorEventQueue = 0;
uint16_t adcData[MAX_NUMBER_MEASUREMENTS];
int numberADCMeasurements = 1;


void setup()
{
    //my_instrument.RegisterCommand(F("*IDN?"), &Identify);
    my_instrument.RegisterCommand(F("*RST"), &Reset);
    my_instrument.RegisterCommand(F("*CLS"), &Clear);

    my_instrument.SetCommandTreeBase("");
    my_instrument.RegisterCommand("MEASure?", &measureADCData);
    my_instrument.RegisterCommand("CONFigure", &configureADC);
    my_instrument.RegisterCommand("FETCh?", &fetchADCData);

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(adcPin, INPUT);
  pinMode(LED_BUILTIN, INPUT);
  analogWrite(ledPin, 0);
}

void loop()
{
  my_arduino.ProcessInput(Serial, "\n");
}

/* BEGIN REQUIRED SCPI COMMANDS */
/*
void Identify(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  interface.println(F("Vrekrer,Arduino SCPI Dimmer,#00,v0.4"));
}
*/
void Reset(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  brightness = 0;
  analogWrite(ledPin, intensity[brightness]);
}

void Clear(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  operationRegister = 0;
  questionableStatusRegister = 0;
  errorEventQueue = 0;
}

/* END REQUIRED SCPI COMMANDS */
/* BEGIN DEVICE-SPECIFIC COMMANDS */


/** According to the SCPI specification, the measurement process is broken down into several stages.
// First, there is configuration of the measurement done via the CONFigure command. The INITiate then
physically performs the measurement, and FETCh? does any necessary postprocessing and returns the data.
I will implement MEASURE, CONFigure, and FETCH, as I don't see a purpose to implement INITiate or READ.
*/

/* Configures the number of ADC measurements we want to take */
void configureADC(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  numberADCMeasurements = constrain(String(parameters[0]).toInt(), 1, MAX_NUMBER_MEASUREMENTS);
}

/* Iniates ADC measurements and returns the data over the specified interface */
void measureADCData(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  for(int i=0; i < numberADCMeasurements; i++) {
    adcData[i] = analogRead(adcPin);
    interface.println(adcData[i]);
  }
}

/* Fetches previously-measured ADC data */
void fetchADCData(SCPI_Commands commands, SCPI_Parameters parameters, Stream& interface) {
  for(int i=0; i < numberADCMeasurements; i++) {
    interface.println(adcData[i]);
  }
}
/* END DEVICE SPECIFIC COMMANDS */
