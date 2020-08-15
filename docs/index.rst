.. Arduino SCPI documentation master file, created by
   sphinx-quickstart on Thu Aug 13 18:22:21 2020.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Arduino SCPI Instrument for AD7766
====================================
Often I will use my Arduino to communicate with an ADC, process the information, and send that to a PC. However, rather than building a custom communication interface each time, this software allows for the communication from PC to arduino using `SCPI commands
<https://en.wikipedia.org/wiki/Standard_Commands_for_Programmable_Instruments>`_ using an `SCPI Parser
<https://github.com/Vrekrer/Vrekrer_scpi_parser>`_ written by Verkrer. As an example, I use this to communicate with an Analog Devices AD7766 128kSps ADC and send the information to the Arduino Serial monitor.


.. toctree::
   :maxdepth: 2
   :caption: Contents:

   api/library_root

Features
-------------
- Arduino communication with external ADC (AD7766) via SPI
- The interface is not currently SCPI compliant, but implements identification and reset commands.
- Uses [Vrekrer\_SCPI|\_Parser](https://github.com/Vrekrer/Vrekrer_scpi_parser)
- Documented here, on readthedocs

Getting Started
-----------------
I assume you know how to use git. If not, you can download the files you need directly off the git website. I also assume you are familiar with the Arduino and Arduino IDE and have it installed on your PC. 

This library relies on an SCPI parser developed by Vrekrer. Download this repository:

.. code-block:: bash

    git clone https://github.com/Vrekrer/Vrekrer_scpi_parser.git

Next, create a folder in your Arduino libraries folder (I'm on a mac, so mine is located at ``~/Documents/Arduino/libraries/``) called ``Vrekrer_scpi_parser``, and place the two files in the "src" directory of the repository you just downloaded into that folder.

Once those files are there, you have installed all the dependencies needed for this project! Now, you can download this project:

.. code-block:: bash

    git clone https://github.com/edmundsj/AD7766_Arduino.git

The Arduino sketch is located in the "AD7766_Arduino" folder. Open the .ino file inside this sketch, and upload it to the Arduino you are using (mine was tested on an Arduino Uno and will be tested an an Arduino Due). 

Example Use
------------
If you open the Serial monitor, you can now type SCPI commands, they will be parsed, and the Arduino will respond to them. For example typing

.. code-block:: bash

    measure?

Will cause the Arduino to perform a measurement on the ADC, store the value internally, and print that back to the serial monitor. You can also fetch previously-measured data using:

.. code-block:: bash
    
    fetch?

Additionally, you can configure the Arduino to take multiple measurements, let's say we want 10 measurements:

.. code-block:: bash

    configure 10

If you want to bring the Arduino back to its original state after booting up, you can do that with the reset command:

.. code-block:: bash

    *rst


Indices and tables
==================

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`
