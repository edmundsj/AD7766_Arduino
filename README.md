# Arduino SCPI Instrument for AD7766
This contains an Arduino sketch for communicating with the AD7766 via SPI and communicating with a PC using [SCPI commands](https://en.wikipedia.org/wiki/Standard_Commands_for_Programmable_Instruments). 

## Features
- Arduino communication with external ADC (AD7766) via SPI
- Python interface requests data from the arduino using standard SCPI commands
- Data stored in numpy arrays and written to .csv files
- The interface *attempts* to be SCPI complaint (Vol 1 Section 4) of [SCPI Standard](https://www.ivifoundation.org/docs/scpi-99.pdf) 
- Uses [Vrekrer\_SCPI|\_Parser](https://github.com/Vrekrer/Vrekrer_scpi_parser)
- Documented on readthedocs [link](https://pythonarduino-ad7766.readthedocs.io/en/latest/index.html)

## Getting Started
I assume you know how to use git. If not, you can download the files you need directly off the git website. I also assume you are familiar with the Arduino and Arduino IDE and have it installed on your PC.

This library relies on an SCPI parser developed by Vrekrer. Download this repository:

```
git clone https://github.com/Vrekrer/Vrekrer_scpi_parser.git
```

Next, create a folder in your Arduino libraries folder (I'm on a mac, so mine is located at `~/Documents/Arduino/libraries/) called `Vrekrer_scpi_parser`, and place the two files in the "src" directory of the repository you just downloaded into that folder.

Once those files are there, you have installed all the dependencies needed for this project! Now, you can download this project:

```
git clone https://github.com/edmundsj/AD7766_Arduino.git
```

The Arduino sketch is located in the "AD7766_Arduino" folder. Open the .ino file inside this sketch, and upload it to the Arduino you are using (mine was tested on an Arduino Uno and will be tested an an Arduino Due).
