#include "Arduino.h"
#include <Vrekrer_scpi_parser.h>

/** Base class that implements communication to and from an external Serial or USB interface via
 *  SCPI and also implements communication to and from the ADC
*/
class ArduinoDAQ {
	public:
    SCPI_Parser myInstrument;
		ArduinoDAQ();
    void ProcessInput(Stream& interface, char* terminationCharacters);
    static void Identify(SCPI_Commands, SCPI_Parameters, Stream&);
    
};
