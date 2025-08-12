import board
# https://learn.adafruit.com/esp32-s3-reverse-tft-feather/pinouts

DRIVER_1_ENABLE = board.A4
DRIVER_1_CS = board.A5

DRIVER_2_ENABLE = board.D10
DRIVER_2_CS = board.D9

ENC_A = board.A2
ENC_B = board.A3

TOP_BTN = board.D0
MDL_BTN = board.D1
BTM_BTN = board.D2
ENC_BTN = board.D11


import digitalio
# On controller boards < v5.8, limit switches are connected to DIO.
# Pull them down to avoid floating.

L1_PUSH = board.D13
L1_PULL = board.D12
L2_PUSH = board.A0
L2_PULL = board.A1

R1_PUSH = board.SDA
R1_PULL = board.SCL
R2_PUSH = board.D5
R2_PULL = board.D6

for pin in [
    L1_PUSH,
    L1_PULL,
    L2_PUSH,
    L2_PULL,
    R1_PUSH,
    R1_PULL,
    R2_PUSH,
    R2_PULL,
]:
    limit = digitalio.DigitalInOut(pin)
    limit.direction = digitalio.Direction.INPUT
    limit.pull = digitalio.Pull.DOWN
