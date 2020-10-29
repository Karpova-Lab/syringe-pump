from pyControl.utility import *
from devices import *
import pyControl.hardware as _h

# Instantiate Devices.
board   = Breakout_1_2()
pump    = Syringe_pump(board.port_3)
button  = _h.Digital_input(board.button,rising_event='button_release',falling_event='button_press',pull='up')

states= [
    'waiting_for_poke',
    ]

events = [
    'poke_in',
    'poke_out',
    'button_press'
    ]

##### Configurable Variables #######
v.pump_volume = 250 # microliters

initial_state = 'waiting_for_poke'

def run_start():
    pump.reset_volume()

def waiting_for_poke(event):
    if event == 'button_press':
        pump.infuse(v.pump_volume)

def all_states(event):
    # the syringe pump will send a serial message if it runs out of reward (if it hits the limit switch).
    # with every event, regardless of what state we're in, check if the pump has reached its limit.
    message_from_pump = pump.check_for_serial()
    if message_from_pump: # if the pump has reached its limit, stop the task
        print("Pump is empty. Stopping the task")
        stop_framework()