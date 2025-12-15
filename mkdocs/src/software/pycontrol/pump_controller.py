from machine import UART
from devices.uart_handler import UART_handler


class PumpController:
    def __init__(self, port, event_name, pybv1=True):
        assert port.UART is not None, "! Pump needs port with UART."

        self.uart = UART(port.UART)
        self.uart.init(115200, bits=8, parity=None, stop=1, timeout=100, rxbuf=130)

        handler = UART_handler(event_name)
        self.uart.irq(trigger=UART.IRQ_RXIDLE, handler=handler.ISR)

        # default pump settings
        for pump in ("l1", "r1", "l2", "r2"):
            self.set_flow_rate(pump, 130)
            self.set_diameter(pump, 26.7)
        self.uart.read()  # clear buffer
        self.reset()

        self.left_source = "l1"
        self.right_source = "r1"

    def _send(self, command, *payloads):
        payload_str = ";".join([command] + [str(p) for p in payloads])
        self.uart.write(f"{payload_str}\n")

    def version(self):
        self._send("version")

    def pause(self):
        self._send("pause")

    def resume(self):
        self._send("resume")

    def reset(self):
        self._send("reset")

    def end(self):
        self._send("end")

    def begin(self, number):
        self._send("begin", number)

    def calibrate_velocity(self, pump):
        self._send("calibrate_velocity", pump)

    def calibrate_volume(self, pump, factor):
        self._send("calibrate_volume", pump, factor)

    def set_flow_rate(self, pump, flow_rate):
        self._send("flow_rate", pump, flow_rate)

    def set_diameter(self, pump, diameter):
        self._send("diameter", pump, diameter)

    def infuse(self, pump, volume):
        self._send("dispense", pump, volume)

    def left_infuse(self, volume):
        self.infuse(self.left_source, volume)

    def right_infuse(self, volume):
        self.infuse(self.right_source, volume)

    def read_serial(self):
        if self.uart.any():
            return self.uart.readline().decode("utf-8").strip("\n")
        return None
