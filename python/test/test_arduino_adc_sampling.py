import sys
import unittest
sys.path.append('source')
from shorthandTest import *
from adc_processing import *
from adc_communication import *

class TestArduinoADCSampling(unittest.TestCase):
    def testByteCount(self):
        desiredBytes = 90000
        data = getADCBytes(desiredBytes)
        actualBytes = len(data)
        self.assertEqual(actualBytes, desiredBytes,
                msg=f'Received too many bytes. Actual bytes: {actualBytes}. Desired bytes: {desiredBytes}' + \
                        f'attempt restart of the arduino.\n')


