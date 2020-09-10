

/*
*/

#include <scpiparser.h>
#include <Arduino.h>

#include "ArduinoDAQ.h"
#include "AD7766.h"

struct scpi_parser_context ctx;
char line_buffer[256];
unsigned char read_length;

void setup()
{

  /* First, initialise the parser. */
  scpi_init(&ctx);
  struct scpi_command* motor;
  struct scpi_command* sync;

  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "*IDN?", identify);
  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "MEASURE?", measure);
  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "CONFIGURE", configure);
  scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "*RST", resetDevice);
  
  sync = scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "SYNC", NULL);
  scpi_register_command2(sync, SCPI_CL_CHILD, "NUMPOINTS?", sendSyncNumPoints);
  scpi_register_command2(sync, SCPI_CL_CHILD, "DATA?", sendSyncData);

  motor = scpi_register_command2(ctx.command_tree, SCPI_CL_SAMELEVEL, "MOTOR", NULL);
  scpi_register_command2(motor, SCPI_CL_CHILD, "POSITION", setPosition);
  scpi_register_command2(motor, SCPI_CL_CHILD, "POSITION?", queryPosition);
  scpi_register_command2(motor, SCPI_CL_CHILD, "DIRECTION?", queryDirection);
  scpi_register_command2(motor, SCPI_CL_CHILD, "ROTATE", rotateMotor);
  scpi_register_command2(motor, SCPI_CL_CHILD, "ROTATE?", getMotorRotating);
  scpi_register_command2(motor, SCPI_CL_CHILD, "ENABLE", enableMotor);
  scpi_register_command2(motor, SCPI_CL_CHILD, "DISABLE", disableMotor);
  scpi_register_command2(motor, SCPI_CL_CHILD, "ENABLED?", getMotorEnabled);
  scpi_register_command2(motor, SCPI_CL_CHILD, "PERIOD", setMotorPeriod);
  scpi_register_command2(motor, SCPI_CL_CHILD, "PERIOD?", getMotorPeriod);
  /*
   * Next, we set our outputs to some default value.
   */

  Serial.begin(9600);
  AD7766::Initialize();
  pinMode(1, INPUT);
}

void loop()
{

  /* Read in a line and execute it. */
  if(Serial.available()) {
    read_length = Serial.readBytesUntil('\n', line_buffer, 256);
    if(read_length > 0)
    {
      scpi_execute_command(&ctx, line_buffer, read_length);
    }
  }
}
