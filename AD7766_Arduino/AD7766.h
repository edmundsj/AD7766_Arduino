#ifndef SCPI_parser_h
#define SCPI_parser_h

// Maximun size of commnad tree and number of parameters
#ifndef SCPI_ARRAY_SYZE
#define SCPI_ARRAY_SYZE 6
#endif 

#ifndef SCPI_MAX_TOKENS
#define SCPI_MAX_TOKENS 15
#endif 

// Maximun number of registered commands 
#ifndef SCPI_MAX_COMMANDS
#define SCPI_MAX_COMMANDS 20
#endif 

#include "Arduino.h"
#include <Vrekrer_SCPI_Parser.h>

/** */
class AD7766 {
	public:
		AD7766();
}
