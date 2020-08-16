

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

SCPI_Parser my_instrument;
const int adcPin = A0;
ArduinoDAQ my_arduino(adcPin);


void setup()
{
    //my_instrument.RegisterCommand(F("*IDN?"), &Identify);

  Serial.begin(115200);
  pinMode(adcPin, INPUT);
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


/* END REQUIRED SCPI COMMANDS */
/* BEGIN DEVICE-SPECIFIC COMMANDS */





/* END DEVICE SPECIFIC COMMANDS */
