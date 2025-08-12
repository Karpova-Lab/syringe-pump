import time
import rotaryio
from digitalio import DigitalInOut, Direction, Pull
import pins as p


class Knob:
    def __init__(self, pin1, pin2):
        self.encoder = rotaryio.IncrementalEncoder(pin1, pin2)
        self.last_pos = self.encoder.position

        self.btn = DigitalInOut(p.ENC_BTN)
        self.btn.direction = Direction.INPUT
        self.btn.pull = Pull.UP

    def read(self):
        last_pos = self.last_pos
        self.last_pos = self.encoder.position
        return self.encoder.position - last_pos


class Button:
    def __init__(self, pin, pull, label):
        self.label = label
        self.was_pressed = False
        self.btn = DigitalInOut(pin)
        self.btn.direction = Direction.INPUT
        self.btn.pull = pull
        if pull == Pull.UP:
            self.pressed_value = False
        else:
            self.pressed_value = True

    def wait_for_release(self):
        while self.btn.value == self.pressed_value:
            time.sleep(0.1)

    def read_btn(self, debug=False):
        if self.btn.value == self.pressed_value:
            if debug:
                print(f"{self.label} pressed....", end="")
            self.wait_for_release()
            if debug:
                print("released")
            self.was_pressed = True

    def clear(self):
        self.was_pressed = False


# Uncomment depending on what direction of rotation you want to correspond to the positive increment
knob = Knob(p.ENC_A, p.ENC_B)  # CW:+, CCW:-
# knob = Knob(p.ENC_B, p.ENC_A) # CW:-, CCW:+

top_btn = Button(p.TOP_BTN, Pull.UP, "top")
middle_btn = Button(p.MDL_BTN, Pull.DOWN, "middle")
bottom_btn = Button(p.BTM_BTN, Pull.DOWN, "bottom")


def read_buttons():
    for btn in [top_btn, middle_btn, bottom_btn]:
        btn.read_btn()
