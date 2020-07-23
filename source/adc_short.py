# This is a workaround as we cannot achieve real-time transmission with the
# arduino, so we have to save the data to internal RAM first and then stop recording data,
# and then transmit it. 
# NOTE: should be run from the main directory.
import serial
import numpy as np
import time
import matplotlib.pyplot as plt
import sys
import scipy.signal.windows
sys.path.append('source')
from adc_processing import *
from adc_communication import *

maxBytes = 90000
samplingFrequency = 125 # 125kHz is the actual measured sampling rate, correct within 1Hz.
samplingPeriod = 1 / samplingFrequency

startSystemTime = time.perf_counter()
dataBuffer = getADCBytes(maxBytes=maxBytes) # Gets data from our ADC
endSystemTime = time.perf_counter()
deltaSystemTime = endSystemTime - startSystemTime

# Print byte rate / bit rate to the screen
numberBytes = len(dataBuffer)
byteRate = maxBytes / deltaSystemTime
bitRate = byteRate * 8
print(f'Final byte count: {numberBytes}. Data rate of {byteRate} MBps / {bitRate} Mbps')

adcValues = np.zeros(int(maxBytes/3))
for i in range(int(maxBytes/3)-1):
    adcValues[i] = twosToInteger(dataBuffer[3*i:3*i+3])

# NOTE: not sure if this should be 5 or 10
# convert from integer counts to voltage
adcValues = countToVoltage(adcValues)
adcValues = adcValues[10:-10] # strip out the first few and final data points, they are often corrupted (why?)
numberSamples = len(adcValues)
samplingTimes = samplingPeriod * np.arange(0, numberSamples, 1)
frequencies = samplingFrequency / numberSamples * np.arange(0, numberSamples, 1)

zeroMeanData = adcValues - np.mean(adcValues)
fftData = 10*np.log10(np.square(np.abs(np.fft.fft(zeroMeanData))))
fftData -= np.max(fftData)
signalAmplitudeVpp = 0.05
signalFrequency = 1
fftData += 20*np.log10(signalAmplitudeVpp)

hanningWindow = scipy.signal.windows.hann(numberSamples)
hanningFilteredData = zeroMeanData * hanningWindow
hanningFFTData = np.square(np.abs(np.fft.fft(hanningFilteredData)))
hanningFFTData = 10*np.log10(hanningFFTData)
hanningFFTData -= np.max(hanningFFTData)
hanningFFTData += 20*np.log10(signalAmplitudeVpp)

np.savetxt('data/arduino_raw_data.csv', dataBuffer, delimiter=',')
np.savetxt('data/adc_values.csv', adcValues, delimiter=',')

samplingWindow = samplingPeriod * numberSamples
#theoreticalPSD = np.square(np.sinc((frequencies-signalFrequency)* samplingWindow))
theoreticalPSD = np.square(np.abs(np.fft.fft(hanningWindow)))
theoreticalPSD = 10*np.log10(theoreticalPSD)
theoreticalPSD += 20*np.log10(signalAmplitudeVpp)

fig, axes = plt.subplots(1, 2)
axes[0].plot(samplingTimes, 1000*zeroMeanData)
axes[0].set_xlabel('time (ms)')
axes[0].set_ylabel('voltage (mV)')
axes[0].set_xlim(0, 5)

axes[1].plot(frequencies[1:], hanningFFTData[1:], 'b')
axes[1].set_xlabel('frequency (kHz)')
axes[1].set_ylabel('amplitude/power (dBV)')
axes[1].set_ylim(-180, 0)
axes[1].set_xlim(0, 64)
axes[1].plot(frequencies[1:], theoreticalPSD[1:], 'g')
plt.show()
