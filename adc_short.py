# This is a workaround as we cannot achieve real-time transmission with the
# arduino, so we have to save the data to internal RAM first and then stop recording data,
# and then transmit it.
import serial
import numpy as np
import time
import matplotlib.pyplot as plt

maxBytes = 90000
byteCounter = 0
dataBuffer = np.zeros(maxBytes + 1020)

arduino = serial.Serial()
arduino.port = '/dev/cu.usbmodem14141'
arduino.baudrate = 7372800
startTime = time.perf_counter()
arduino.open()
randomString=b'ENDTRANSACTION';

bytesWritten = arduino.write(b'y')

while byteCounter < maxBytes-1:
    bytesAvailable = arduino.in_waiting
    dataBuffer[byteCounter:byteCounter+bytesAvailable] = \
            np.frombuffer(arduino.read_until(randomString, size=bytesAvailable), dtype='uint8')
    byteCounter += bytesAvailable
    print(byteCounter)

print(f'Final byte count: {byteCounter}')

arduino.close()
adcValues = np.zeros(int(maxBytes/3))
for i in range(int(maxBytes/3)):
   adcValues[i] = dataBuffer[3*i]*256*256 + dataBuffer[3*i+1]*256 + dataBuffer[3*i+2]

endTime = time.perf_counter()
deltaTime = endTime - startTime
byteRate = maxBytes / deltaTime
bitRate = byteRate * 8

print(f'Byte Rate: {byteRate}')
print(f'Bitrate: {bitRate}')
np.savetxt('arduino_raw_data.csv', dataBuffer, delimiter=',')
np.savetxt('adc_values.csv', adcValues, delimiter=',')
plt.plot(adcValues)
plt.show()
