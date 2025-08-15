# an example task that controls a left and right syringe pump

from pyControl.utility import v, print

######### Breakout 1.2 #########
from devices import PumpController, Breakout_1_2

board = Breakout_1_2()
# Pump controller should be connected to a UART port (either 1,3, or 4)
syringes = PumpController(board.port_4, "pump_msg_received")

######### Breakout dseries 1.6 #########
# from devices import PumpController, Breakout_dseries_1_6

# board = Breakout_dseries_1_6()
# # Pump controller should be connected to a UART port (either 8,10,11 or 12)
# syringes = PumpController(board.port_11, "pump_msg_received", pybv1=False)

states = ["single_state"]
events = [
    "configure_pumps",
    "left_infuse",
    "right_infuse",
    "both_infuse",
    "full_retract",
    "pump_msg_received",
]

v.infusion_volume = 5_000  # uL
v.left_flow_rate = 90  # mL/min
v.right_flow_rate = 90  # mL/min
v.left_id_mm = 26.7
v.right_id_mm = 21.7

v.custom_controls_dialog = "syringepump_gui"

initial_state = "single_state"


def run_start():
    configure_pumps()
    syringes.begin(7897)
    syringes.version()


def run_end():
    syringes.end()


def single_state(event):
    if event == "left_infuse":
        syringes.left_infuse(v.infusion_volume)
    elif event == "right_infuse":
        syringes.right_infuse(v.infusion_volume)
    elif event == "both_infuse":
        syringes.left_infuse(v.infusion_volume)
        syringes.right_infuse(v.infusion_volume)
    elif event == "configure_pumps":
        configure_pumps()
    elif event == "full_retract":
        syringes.left_infuse(-60_000)
        syringes.right_infuse(-60_000)
    elif event == "pump_msg_received":
        pump_msg = syringes.read_serial()
        if pump_msg is not None:
            print(pump_msg)


def configure_pumps():
    syringes.set_diameter(syringes.left_source, v.left_id_mm)
    syringes.set_flow_rate(syringes.left_source, v.left_flow_rate)
    syringes.set_diameter(syringes.right_source, v.right_id_mm)
    syringes.set_flow_rate(syringes.right_source, v.right_flow_rate)