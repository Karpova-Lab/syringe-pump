import time
from tmc5041 import TMC5041
import pins as p
from math import pi


class Direction:
    PUSH = -1
    PULL = 1


class Pump:
    def __init__(self, name, motor, lead_mm):
        self.name = name
        self.motor = motor
        self.lead_mm = lead_mm
        self.velocity_calibration_factor = 1.378
        self.volume_calibration_factor = 1.0  # target/measured
        self.knob_increment = 500  # µL

        self._flow_rate = None
        self._syringe_id_mm = None
        self._steps_per_µL = None

        self.target = self.motor.x_actual

    def configure(self):
        if None in (
            self._syringe_id_mm,
            self._flow_rate,
        ):
            return False

        # get steps per µL
        syringe_cross_area = pi * self._syringe_id_mm**2 / 4.0 / 100.0  # cm^2
        microsteps_per_rev = self.motor.steps_per_rev * 256
        vol_per_rev = self.lead_mm / 10.0 * syringe_cross_area  # mL
        self._steps_per_µL = (
            microsteps_per_rev / vol_per_rev / 1000.0 * self.volume_calibration_factor
        )  # steps/µL

        adjusted_velocity = int(
            self.flow_rate
            * 1000.0
            / 60
            * self._steps_per_µL
            * self.velocity_calibration_factor
        )
        if adjusted_velocity > 180_000:
            max_flow_rate_12v = (
                180_000 / self.velocity_calibration_factor / self._steps_per_µL / 1000.0 * 60
            )
            print(
                f"Warning: dispense velocity may be too high.\nEither increase syringe diameter or reduce flow rate to below {int(max_flow_rate_12v) - 1} mL/min"
            )

        self.motor.configure_ramp(
            a1=0,
            v1=0,
            amax=5_000,
            vmax=adjusted_velocity,
            dmax=5_000,
            d1=1,
            vstop=10,
        )
        return f"{self.name}:{self.motor.steps_per_rev},{self.lead_mm},{self._flow_rate},{self._syringe_id_mm},{self.velocity_calibration_factor},{self.volume_calibration_factor}\n"

    @property
    def settings(self):
        return {
            "steps_per_rev": self.motor.steps_per_rev,
            "lead_mm": self.lead_mm,
            "flow_rate": self._flow_rate,
            "syringe_id_mm": self._syringe_id_mm,
            "velocity_calibration_factor": self.velocity_calibration_factor,
            "volume_calibration_factor": self.volume_calibration_factor,
        }

    @property
    def syringe_id_mm(self):
        return self._syringe_id_mm

    @syringe_id_mm.setter
    def syringe_id_mm(self, value):
        self._syringe_id_mm = value
        self.configure()

    @property
    def flow_rate(self):
        return self._flow_rate

    @flow_rate.setter
    def flow_rate(self, value):
        self._flow_rate = value
        self.configure()

    @property
    def pull_limit_reached(self):
        return self.motor.stop_l_status

    @property
    def push_limit_reached(self):
        return self.motor.stop_r_status

    @property
    def is_idle(self):
        return self.motor.vzero

    ###### action methods ######
    def dispense(self, volume):
        if self._steps_per_µL is None:
            raise Exception(f"{self.name} is not configured")

        steps_to_add = volume * self._steps_per_µL * Direction.PUSH
        self.target = int(self.target + steps_to_add)
        self.motor.position = self.target

    def stop(self):
        self.motor.position = self.motor.position
        self.target = self.motor.position

    def bounce(self, direction):
        bounce_distance = int(self._steps_per_µL * 1_000)  # bounce 1 mL
        self.target = self.motor.position + bounce_distance * direction
        self.motor.position = self.target

    def calibrate_velocity(self):  # p.72 of datasheet
        pre_calibration_flow_rate = self.flow_rate
        target_velocity = 50_000
        calibration_flow_rate = (
            target_velocity
            / 1000.0
            * 60
            / self._steps_per_µL
            / self.velocity_calibration_factor
        )
        self.flow_rate = calibration_flow_rate

        print(f"{self.name} calibrating velocity")
        self.motor.x_target = self.motor.position - target_velocity * 10

        accel_duration = 1.0  # seconds
        max_vel_duration = 4.0  # seconds
        time.sleep(accel_duration)  # give time to accelerate
        pos1 = self.motor.position
        time.sleep(max_vel_duration)
        pos2 = self.motor.position
        self.stop()

        actual_velocity = (pos2 - pos1) / max_vel_duration
        self.velocity_calibration_factor = target_velocity / actual_velocity * -1
        self.flow_rate = pre_calibration_flow_rate
        print(f"{self.name} velocity_calibration_factor: {self.velocity_calibration_factor}")
        print(self.configure())

    def calibrate_volume(self, factor):
        self.volume_calibration_factor = factor
        self.configure()


d1 = TMC5041(p.DRIVER_1_ENABLE, p.DRIVER_1_CS)
d2 = TMC5041(p.DRIVER_2_ENABLE, p.DRIVER_2_CS)


def enable_drivers(do_enable):
    d1.enabled = do_enable
    d2.enabled = do_enable


l2 = Pump(
    name="l2",
    motor=d2.m2,
    lead_mm=2,
)

l1 = Pump(
    name="l1",
    motor=d1.m2,
    lead_mm=2,
)

r1 = Pump(
    name="r1",
    motor=d1.m1,
    lead_mm=2,
)

r2 = Pump(
    name="r2",
    motor=d2.m1,
    lead_mm=2,
)
