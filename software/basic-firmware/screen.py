import board
import displayio  # https://learn.adafruit.com/circuitpython-display-support-using-displayio/ui-quickstart
from adafruit_display_text.label import Label
from adafruit_bitmap_font import bitmap_font

# anchoring example: https://docs.circuitpython.org/projects/display_text/en/latest/examples.html#anchored-position

LARGE_FONT = bitmap_font.load_font("fonts/72_bold.bdf")
MEDIUM_FONT = bitmap_font.load_font("fonts/32_bold.bdf")
SMALL_FONT = bitmap_font.load_font("fonts/28_reg.bdf")

WHITE = 0xFFFFFF
YELLOW = 0x999900
GREEN = 0x6CF542
RED = 0xFF0000
GREY = 0xAAAAAA
DARK_GREY = 0x444444
ORANGE = 0xFF9A00
BLUE = 0x00DEFF
BLACK = 0x000000


class GUI(displayio.Group):
    def __init__(self):
        super().__init__()

        # backgrounds
        self.background = displayio.Bitmap(board.DISPLAY.width, board.DISPLAY.height, 3)
        mypal = displayio.Palette(4)
        mypal[0] = BLACK
        mypal[1] = ORANGE
        mypal[2] = GREEN
        mypal[3] = RED
        self.append(displayio.TileGrid(self.background, pixel_shader=mypal))

        padding = 10

        # top left, top center, top right
        TL = (0, padding)
        TC = (board.DISPLAY.width / 2, padding)
        TR = (board.DISPLAY.width - padding, padding)

        # middle left, middle center, middle right
        ML = (0, board.DISPLAY.height / 2)
        MC = (board.DISPLAY.width / 2, board.DISPLAY.height / 2)
        MR = (board.DISPLAY.width - padding, board.DISPLAY.height / 2)

        # bottom left, bottom center, bottom right
        BL = (0, board.DISPLAY.height - padding)
        BC = (board.DISPLAY.width / 2, board.DISPLAY.height - padding)
        BR = (board.DISPLAY.width - padding, board.DISPLAY.height - padding)

        # title label
        self.title_lbl = Label(SMALL_FONT, text="", color=WHITE)
        self.title_lbl.anchored_position = TC
        self.title_lbl.anchor_point = (0.5, 0)
        self.append(self.title_lbl)

        self.middle_lbl = Label(SMALL_FONT, text="size", color=BLUE)
        self.middle_lbl.anchored_position = ML
        self.middle_lbl.anchor_point = (0, 0.5)
        self.append(self.middle_lbl)

        # size label
        self.size_lbl = Label(SMALL_FONT, color=BLUE)
        self.size_lbl.anchored_position = MR
        self.size_lbl.anchor_point = (1, 0.5)
        self.append(self.size_lbl)

        self.bottom_lbl = Label(SMALL_FONT, text="rate", color=GREEN)
        self.bottom_lbl.anchored_position = BL
        self.bottom_lbl.anchor_point = (0, 1)
        self.append(self.bottom_lbl)

        # flow rate label
        self.flow_rate_lbl = Label(SMALL_FONT, color=GREEN)
        self.flow_rate_lbl.anchored_position = BR
        self.flow_rate_lbl.anchor_point = (1, 1)
        self.append(self.flow_rate_lbl)

        self.pre_session()

    #### state UIs ####
    def pre_session(self):
        self.background.fill(0)
        board.DISPLAY.refresh()

    def running(self):
        self.background.fill(1)
        board.DISPLAY.refresh()


gui = GUI()
board.DISPLAY.root_group = gui
