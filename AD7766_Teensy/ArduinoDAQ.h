#include "Arduino.h"
#include <scpiparser.h>
#define MAX_NUMBER_MEASUREMENTS 1000

/** Base class that implements communication to and from an external Serial or USB interface via
* According to the SCPI specification, the measurement process is broken down into several stages.
* First, there is configuration of the measurement done via the CONFigure command. The INITiate then
* physically performs the measurement, and FETCh? does any necessary postprocessing and returns the data.
* I will implement MEASURE, CONFigure, and FETCH, as I don't see a purpose to implement INITiate or READ.
*/
scpi_error_t identify(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t measure(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t configure(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t resetDevice(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t sendSyncNumPoints(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t sendSyncData(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t setPosition(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t queryPosition(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t setDirection(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t queryDirection(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t rotateMotor(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t getMotorRotating(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t disableMotor(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t enableMotor(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t getMotorEnabled(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t setMotorPeriod(struct scpi_parser_context* context, struct scpi_token* command);
scpi_error_t getMotorPeriod(struct scpi_parser_context* context, struct scpi_token* command);

void interruptRotate(void);
