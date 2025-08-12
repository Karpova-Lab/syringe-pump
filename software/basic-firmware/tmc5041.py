import board
import digitalio
import struct
import registers as r
from adafruit_bus_device.spi_device import SPIDevice


class MotorID:
    ONE = 0
    TWO = 1


class TMC5041:
    def __init__(self, enable_pin, cs_pin):
        self.spi_device = SPIDevice(
            board.SPI(), digitalio.DigitalInOut(cs_pin), polarity=1, phase=1
        )

        self.drv_enable = digitalio.DigitalInOut(enable_pin)
        self.drv_enable.direction = digitalio.Direction.OUTPUT
        self.enabled = True

        self.configure_gconf(poscmp_enable=1)

        self.m1 = Motor(self, MotorID.ONE)
        self.m2 = Motor(self, MotorID.TWO)

    @property
    def enabled(self):
        return not self.drv_enable.value  # active low

    @enabled.setter
    def enabled(self, do_enable):
        if not isinstance(do_enable, bool):
            raise ValueError("Enable must be set to a boolean value.")
        self.drv_enable.value = not do_enable  # active low

    def read_register(self, address):
        with self.spi_device as spi:
            bytes_read = bytearray(5)  # 40 bits = 5 bytes
            to_write = bytearray([address]) + bytearray(4)
            spi.write_readinto(to_write, bytes_read)  # 32 bits of dummy data

            return bytes_read

    def write_register(self, address, data):
        with self.spi_device as spi:
            bytes_read = bytearray(5)  # 40 bits = 5 bytes
            to_write = bytearray([address | 0x80]) + struct.pack(">i", data)
            spi.write_readinto(to_write, bytes_read)

    def configure_gconf(
        self,
        poscmp_enable=0,
        test_mode=0,
        shaft1=0,
        shaft2=0,
        lock_gconf=0,
    ):
        gconf = (
            lock_gconf << 10
            | shaft2 << 9
            | shaft1 << 8
            | test_mode << 7
            | poscmp_enable << 3
        )
        self.write_register(r.GCONF, gconf)

    def get_register_data(self, reg_address, num_bits, signed=False):
        val = int.from_bytes(self.read_register(reg_address), "big") & (2**num_bits - 1)
        if signed:
            if val & (1 << (num_bits - 1)):
                val -= 2**num_bits
        return val

    @property
    def gconf(self):
        return self.get_register_data(r.GCONF, 11)


class Motor:
    def __init__(self, driver, motor_id, steps_per_rev=200):
        self.driver = driver
        self.motor_id = motor_id
        self.steps_per_rev = steps_per_rev

        # configure
        self.setup_stealchop()
        self.set_current(hold=1, run=30, delay=10)
        self.configure_switches(stop_l_enable=True, stop_r_enable=True, swap_lr=True)

        self.position = self.x_actual  # initialize position to current position

    def write(self, reg_address, data, offset=0x20):
        if self.motor_id == MotorID.ONE:
            address_to_write = reg_address
        else:
            address_to_write = reg_address + offset

        self.driver.write_register(address_to_write, data)

    def read(self, reg_address, offset=0x20):
        if self.motor_id == MotorID.ONE:
            address_to_read = reg_address
        else:
            address_to_read = reg_address + offset

        self.driver.read_register(address_to_read)  # throw away
        return self.driver.read_register(address_to_read)

    def setup_stealchop(self):
        # recommended stealthchop settings p.67 of datasheet
        self.configure_pwm(pwm_ampl=255, pwm_grad=1, pwm_freq=1)
        self.write(r.VCOOLTHRS, 999_999)
        self.write(r.VHIGH, 999_999)
        self.configure_chop(toff=4, tbl=2, hstrt=4, hend=0)

    def configure_switches(
        self,
        stop_l_enable=0,
        stop_r_enable=0,
        pol_stop_l=0,
        pol_stop_r=0,
        swap_lr=0,
        latch_l_active=0,
        latch_l_inactive=0,
        latch_r_active=0,
        latch_r_inactive=0,
        sg_stop=0,
        en_soft_stop=0,
    ):
        sw_mode = (
            en_soft_stop << 11
            | sg_stop << 10
            | latch_r_inactive << 8
            | latch_r_active << 7
            | latch_l_inactive << 6
            | latch_l_active << 5
            | swap_lr << 4
            | pol_stop_r << 3
            | pol_stop_l << 2
            | stop_r_enable << 1
            | stop_l_enable
        )
        self.write(r.SW_MODE, sw_mode)

    def configure_pwm(
        self,
        pwm_ampl=0,
        pwm_grad=0,
        pwm_freq=0,
        pwm_autoscale=0,
        freewheel=0,
    ):
        pwm_conf = (
            freewheel << 20
            | pwm_autoscale << 18
            | pwm_freq << 16
            | pwm_grad << 8
            | pwm_ampl
        )
        self.write(r.PWM_CONF, pwm_conf, offset=0x08)

    def configure_chop(
        self,
        toff=0,
        hstrt=0,
        hend=0,
        fd=0,
        disfdcc=0,
        rndtf=0,
        chm=0,
        tbl=0,
        vsense=0,
        vhighfs=0,
        vhighchm=0,
        mres=0,
        diss2g=0,
    ):
        chop_conf = (
            diss2g << 30
            | mres << 24
            | vhighchm << 19
            | vhighfs << 18
            | vsense << 17
            | tbl << 15
            | chm << 14
            | rndtf << 13
            | disfdcc << 12
            | fd << 11
            | hend << 7
            | hstrt << 4
            | toff
        )

        self.write(r.CHOP_CONF, chop_conf, offset=0x10)

    def configure_ramp(
        self,
        a1,  # 0-65,535 µsteps/t^2
        v1,  # 1-1,048,575 µsteps/t or 0 to disable A1 and D1 phases
        amax,  # 0-65,535 µsteps/t^2
        vmax,  # 0-8,8388,096 µsteps/t^2
        dmax,  # 0-65,535 µsteps/t^2
        d1,  # 1-65,535 µsteps/t^2
        vstop=10,  # 0-262,143
    ):
        self.write(r.A1, a1)
        self.write(r.V1, v1)
        self.write(r.AMAX, amax)
        self.write(r.VMAX, vmax)
        self.write(r.DMAX, dmax)
        self.write(r.D1, d1)
        self.write(r.VSTOP, vstop)
        self.write(r.RAMPMODE, 0)  # 0=position mode

    def set_current(
        self,
        hold,  # 0=1/32...31=32/32
        run,  # 0=1/32...31=32/32
        delay,  # 0=instant power down, 1-15 delay per current reduction step in multiple of 2^18 clocks
    ):
        current_config = delay << 16 | run << 8 | hold
        self.write(r.IHOLD_IRUN, current_config)

    #### registers ####
    def get_register_data(self, reg_address, num_bits, signed=False):
        val = int.from_bytes(self.read(reg_address), "big") & (2**num_bits - 1)
        if signed:
            if val & (1 << (num_bits - 1)):
                val -= 2**num_bits
        return val

    @property
    def x_actual(self):
        return self.get_register_data(r.XACTUAL, 32, signed=True)

    @property
    def x_target(self):
        return self.get_register_data(r.XTARGET, 32, signed=True)

    @x_target.setter
    def x_target(self, value):
        self.write(r.XTARGET, value)

    @property
    def position(self):  # alias for x_actual
        return self.x_actual

    @position.setter
    def position(self, value):  # alias for x_target
        self.x_target = value

    @property
    def sw_mode_reg(self):
        return self.get_register_data(r.SW_MODE, 11)

    @property
    def vzero(self):
        data = self.get_register_data(r.RAMP_STAT, 14)
        return data & 0x200 == 0x200

    @property
    def stop_r_status(self):
        data = self.get_register_data(r.RAMP_STAT, 14)
        return data & 0x1 == 0x1

    @property
    def stop_l_status(self):
        data = self.get_register_data(r.RAMP_STAT, 14)
        return data & 0x2 == 0x2
