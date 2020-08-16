#include "Arduino.h"
#include <Vrekrer_scpi_parser.h>
#define MAX_NUMBER_MEASUREMENTS 1000

/** Base class that implements communication to and from an external Serial or USB interface via
* According to the SCPI specification, the measurement process is broken down into several stages.
* First, there is configuration of the measurement done via the CONFigure command. The INITiate then
* physically performs the measurement, and FETCh? does any necessary postprocessing and returns the data.
* I will implement MEASURE, CONFigure, and FETCH, as I don't see a purpose to implement INITiate or READ.
*/
class ArduinoDAQ {
	public:
    static int adcPin;
    static uint8_t operationRegister;
    static uint8_t questionableStatusRegister;
    static uint8_t errorEventQueue;
    static uint8_t adcData[MAX_NUMBER_MEASUREMENTS];
    static int numberADCMeasurements;
    
    SCPI_Parser myInstrument;
		ArduinoDAQ(const int);
    void ProcessInput(Stream& interface, char* terminationCharacters);
    static void Identify(SCPI_Commands, SCPI_Parameters, Stream&);
    static void Reset(SCPI_Commands, SCPI_Parameters, Stream&);
    static void Clear(SCPI_Commands, SCPI_Parameters, Stream&);
    static void configureADC(SCPI_Commands, SCPI_Parameters, Stream&);
    static void measureADCData(SCPI_Commands, SCPI_Parameters, Stream&);
    static void fetchADCData(SCPI_Commands, SCPI_Parameters, Stream&);
    
};
