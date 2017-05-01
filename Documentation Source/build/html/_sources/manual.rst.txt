==========
User Guide
==========

.. include:: isogrk1.txt


Pinout
======
+----------+-------+-----------------------------------------+
| RJ45 Pin | Label | Description                             |
+==========+=======+=========================================+
| 1        | B     | HIGH when syringe is retracting.        |
+----------+-------+-----------------------------------------+
| 2        | C     | HIGH-LOW pulse begins retraction        |
+----------+-------+-----------------------------------------+
| 3        | A     | Motor turns when pin is HIGH            |
+----------+-------+-----------------------------------------+
| 4        | *5V   | Provides power to Atmega328             |
+----------+-------+-----------------------------------------+
| 5        | *GND  |                                         |
+----------+-------+-----------------------------------------+
| 6        | *12V  | Provides power for Stepper Motor Driver |
+----------+-------+-----------------------------------------+
| 7        | *3V   | Provides power for OLED Display         |
+----------+-------+-----------------------------------------+
| 8        | D     |                                         |
+----------+-------+-----------------------------------------+

*Required

Manual Mode
===========
The pump can be conrtolled by the buttons on the left side of the OLED display

+--------+----------------------------+--------------------------------+
| Button | Click                      | Hold                           |
+========+============================+================================+
| A      | Push 0.1 mL                | Pushes at a rate of 1.3 mL/sec |
+--------+----------------------------+--------------------------------+
| B      | Pull 0.5 mL                | Pulls at a rate of 1.3 mL/sec  |
+--------+----------------------------+--------------------------------+
| C      | Retracts fully             |                                |
+--------+----------------------------+--------------------------------+
| Reset  | Resets the microcontroller |                                |
+--------+----------------------------+--------------------------------+

Electronic Mode
===============
Advance
-------
Providing a "High" TTL pulse to pin 3 of the RJ45 will cause the stepper motor to advance at a rate of 1 step per 2 milliseconds. Pullling the same pin back "Low" will stop the motor.
You can use the form below to calculate the duration of the high pulse in order to deliver a target amount of liquid for a given size syringe.

.. raw:: html
  :file: rewardCalc.html

Retract
-------
Providing a "High" TTL pulse to pin 2 of the RJ45 will cause the pump to enter retraction mode. It will retract the syringe until the reed switch detects the magnet.
