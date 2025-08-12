# type: ignore
import board
import busio
import interface
import time
from pump import enable_drivers, Direction, r1, l1, r2, l2
from screen import gui

VERSION = "2025-08-05"
RETRACT_VOLUME = 70_000  # µL
SMALL_INCREMENT = 50  # µL
LARGE_INCREMENT = 500  # µL
HOLD_TIME = 0.75  # seconds

uart = busio.UART(board.TX, board.RX, baudrate=115200, timeout=0.1)

motors_enabled = False
limit_pressed = False
disengage_when_idle = True
hold_complete = False
knob_increment_volume = LARGE_INCREMENT
volume_in_progress = 0


# these are the default settings for the pumps
pump_settings = {
    "l2": {"syringe_id_mm": 26.7, "flow_rate": 110},
    "l1": {"syringe_id_mm": 26.7, "flow_rate": 110},
    "r1": {"syringe_id_mm": 26.7, "flow_rate": 110},
    "r2": {"syringe_id_mm": 26.7, "flow_rate": 110},
}

active_pumps = [l1, r1, r2, l2]

for pump in active_pumps:
    pump.syringe_id_mm = pump_settings[pump.name]["syringe_id_mm"]
    pump.flow_rate = pump_settings[pump.name]["flow_rate"]
    pump.stop()


def refresh_labels(pump):
    gui.size_lbl.text = str(pump.syringe_id_mm)
    gui.flow_rate_lbl.text = str(pump.flow_rate)
    gui.title_lbl.text = pump.name


def cycle_pumps():
    while True:
        for pump in active_pumps:
            refresh_labels(pump)
            yield pump


active_pumps_iterator = cycle_pumps()
current_pump = next(active_pumps_iterator)
refresh_labels(current_pump)


def process_uart():
    # uart commands received from pyControl or web interface
    uart_msg = uart.readline()
    if uart_msg:
        cmd, *data = "".join([chr(b) for b in uart_msg[:-1]]).split(";")
        print("\nuart:", uart_msg, "\tparsed: ", cmd, data)
        # commands only
        if cmd in ("version", "begin", "end", "reset"):
            return (f"uart_{cmd}", ())
        # commands with 1 data item
        elif cmd in ("settings", "calibrate_velocity", "stop"):
            pump_name = data[0]
            value = eval(pump_name)
            return (f"uart_{cmd}", (value))
        # commands with 2 data items
        elif cmd in ("dispense", "diameter", "flow_rate", "calibrate_volume"):
            pump_name, value = data
            if cmd in ("dispense", "flow_rate"):
                value = int(value)
            elif cmd in ("diameter", "calibrate_volume"):
                value = float(value)
            return (f"uart_{cmd}", (eval(pump_name), value))
    else:
        return None


def process_buttons():
    global hold_complete
    interface.read_buttons()
    if interface.top_btn.was_pressed:  # top button
        interface.top_btn.clear()
        return ("btn", "top")
    elif interface.middle_btn.was_pressed:  # middle button
        interface.middle_btn.clear()
        return ("btn", "middle")
    elif interface.bottom_btn.was_pressed:  # bottom button
        interface.bottom_btn.clear()
        return ("btn", "bottom")
    elif not interface.knob.btn.value:  # knob button
        hold_start = time.monotonic()
        while not interface.knob.btn.value:
            if not hold_complete and time.monotonic() - hold_start > HOLD_TIME:
                hold_complete = True
                return ("btn", "knob_held")
        if not hold_complete:
            return ("btn", "knob_pressed")
        else:
            hold_complete = False
    return None


def check_limit_switches():
    global limit_pressed
    limits_reached = []
    for pump in active_pumps:
        if pump.pull_limit_reached:
            pump.bounce(Direction.PUSH)
            limits_reached.append(("limit", pump.name + "_pull"))
        elif pump.push_limit_reached:
            pump.bounce(Direction.PULL)
            limits_reached.append(("limit", pump.name + "_push"))
    if limits_reached:
        gui.background.fill(3)
        limit_pressed = True
    elif limit_pressed:  # coming from pressed i.e. limit was just released
        limit_pressed = False
        gui.background.fill(0)
    return limits_reached


def process_knob_turn():
    if step_change := interface.knob.read():
        return ("knob_turn", step_change)
    return None


def enable_motors(do_enable):
    global motors_enabled, volume_in_progress
    enable_drivers(do_enable)
    motors_enabled = do_enable
    if not do_enable:
        volume_in_progress = 0


def all_motors_idle():
    for pump in active_pumps:
        if not pump.is_idle:
            return False
    return True


def retract_all():
    enable_motors(True)
    for pump in active_pumps:
        pump.dispense(-RETRACT_VOLUME)


############################## states ##############################
def goto(state):
    global current_state
    current_state("exit", None)
    current_state = state
    current_state("entry", None)


# this code runs no matter which state we are in
def all_states(event, data):
    if event == "limit":
        print(f"{data} limit reached!")
        uart.write(f"{data} limit reached!\n")
    elif event == "uart_version":
        uart.write(f"pump_firmware_version:{VERSION}\n")
    elif event == "uart_settings":
        pump = data
        uart.write(f"{pump.name}={pump.settings}\n")
    elif event == "uart_dispense":
        pump, volume = data
        pump.dispense(int(volume))
        enable_motors(True)
    elif event == "uart_diameter":
        pump, diameter = data
        pump.syringe_id_mm = float(diameter)
        refresh_labels(pump)
    elif event == "uart_flow_rate":
        pump, flow_rate = data
        pump.flow_rate = int(flow_rate)
        if pump.name == current_pump.name:
            refresh_labels(pump)
    elif event == "uart_stop":
        pump = data
        pump.stop()
    elif event == "uart_calibrate_velocity":
        pump = data
        pump.calibrate_velocity()
        uart.write(
            f"{pump.name} velocity_calibration_factor: {pump.velocity_calibration_factor}\n"
        )
    elif event == "uart_calibrate_volume":
        print("calibrated volume!!!")
        pump, factor = data
        pump.calibrate_volume(float(factor))
        uart.write(
            f"{pump.name} volume_calibration_factor: {pump.volume_calibration_factor}\n"
        )


def pre_session(event, data):
    if event == "entry":
        global \
            disengage_when_idle, \
            current_pump, \
            knob_increment_volume, \
            volume_in_progress
        disengage_when_idle = True
        gui.pre_session()
    # button and knob events
    elif event == "btn":
        if data == "top":
            current_pump = next(active_pumps_iterator)
        elif data == "middle":
            if current_pump.syringe_id_mm == 21.7:
                current_pump.syringe_id_mm = 26.7
            else:
                current_pump.syringe_id_mm = 21.7
            refresh_labels(current_pump)
        elif data == "bottom":
            if current_pump.flow_rate == 110:
                current_pump.flow_rate = 50
            else:
                current_pump.flow_rate = 110
            refresh_labels(current_pump)
        elif data == "knob_held":
            gui.title_lbl.text = "retracting"
            enable_motors(True)
            current_pump.dispense(-RETRACT_VOLUME)
        elif data == "knob_pressed":
            current_pump.stop()
    elif event == "knob_turn":
        new_volume = knob_increment_volume * data
        volume_in_progress += new_volume
        gui.title_lbl.text = (
            f"{'+' if volume_in_progress > 0 else ''}{volume_in_progress / 1000} mL"
        )
        if not motors_enabled:
            enable_motors(True)
        current_pump.dispense(new_volume)
    # uart events
    elif event == "uart_begin":
        goto(running)


def running(event, data):
    if event == "entry":
        global disengage_when_idle, current_pump
        disengage_when_idle = False
        enable_motors(True)
        gui.running()
    # button and knob events
    elif event == "btn":
        if data == "top":
            goto(pre_session)
    # uart events
    elif event == "uart_end":
        goto(pre_session)
    # limit events
    elif event == "limit":
        goto(pre_session)


######################### main loop #########################

event_queue = []
enable_motors(False)
current_state = pre_session
goto(current_state)

while True:
    if uart_event := process_uart():
        event_queue.append(uart_event)

    if pressed_event := process_buttons():
        event_queue.append(pressed_event)

    if knob_event := process_knob_turn():
        event_queue.append(knob_event)

    if motors_enabled:
        if all_motors_idle() and disengage_when_idle:
            enable_motors(False)
            refresh_labels(current_pump)

    if limit_events := check_limit_switches():
        for event in limit_events:
            event_queue.append(event)

    while event_queue:
        event_with_data = event_queue.pop(0)
        all_states(*event_with_data)
        current_state(*event_with_data)
