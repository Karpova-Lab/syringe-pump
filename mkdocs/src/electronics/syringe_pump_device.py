import pyControl.hardware as _h
from machine import UART

class Syringe_pump():
    def __init__(self, port):
        assert port.UART is not None, '! Pump needs port with UART.'
        self.uart = UART(port.UART, 9600)
        self.uart.init(9600, bits=8, parity=None, stop=1, timeout=100)
        self.uart.write('C')
        self.uart.write('Z')

    def infuse(self,val):
        self.uart.write('I,{}\n'.format(val))

    def check_for_serial(self):
        if self.uart.any():
            return self.uart.readline().decode("utf-8").strip('\n')
        else:
            return None
    
    def reset_volume(self):
        self.uart.write('Z')
    
    def retract(self):
        self.uart.write('R')

    def send_animal_number(self,number):
        self.uart.write('A,{}\n'.format(number))