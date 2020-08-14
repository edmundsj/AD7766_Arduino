# Arduino / Python Interface for AD7766
This contains an Arduino sketch for communicating with the AD7766 via SPI and communicating with a PC using [SCPI commands](https://en.wikipedia.org/wiki/Standard_Commands_for_Programmable_Instruments). 

## Features
- Arduino communication with external ADC (AD7766) via SPI
- Python interface requests data from the arduino using standard SCPI commands
- Data stored in numpy arrays and written to .csv files
- The interface *attempts* to be SCPI complaint (Vol 1 Section 4) of [SCPI Standard](https://www.ivifoundation.org/docs/scpi-99.pdf) 

## Arduino Implementation
The arduino-specific code and documentation lives in the AD7766\_Arduino folder.

## Python Communication
The python modules to communicate with the ADC via SCPI over USB, along with the relevant documentation live in the python folder. 
