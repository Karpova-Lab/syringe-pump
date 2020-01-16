:github_url: https://github.com/Karpova-Lab/syringe-pump

===========
User Manual 
===========

.. include:: isogrk1.txt

pyControl Operation
===================


The syringe board can be used as pyControl device. It's pinout is compatible with pyControl `behavior ports <https://pycontrol.readthedocs.io/en/latest/user-guide/hardware/#behaviour-ports>`_. The pump must be plugged into a port that has a serial UART. On `Breakout board 1.2 <https://pycontrol.readthedocs.io/en/latest/user-guide/hardware/#breakout-board-12>`_,  this can be ports 1, 3 or 4. On `D-series Breakout Board 1.4 <https://karpova-lab.github.io/pyControl-D-Series-Breakout/index.html#>`_, this can be ports 8, 10, 11 or 12.



The following example assumes that the syringe pump is plugged into port 3 of `Breakout board 1.2 <https://pycontrol.readthedocs.io/en/latest/user-guide/hardware/#breakout-board-12>`_:

1. Download  :download:`_syringepump.py <pyControl_files/_syringepump.py>` and place it in your "devices" directory. 
2. Download :download:`pump_example_task.py <pyControl_files/pump_example_task.py>` and place it you "tasks" directory.
3. Open up pyControl GUI
4. Connect to your board
5. Click the "Config" button and then click "Load framework". This will ensure the _syringepump.py device is on the microcontroller. 
6. From the Task dropdown select the "pump_example_task"
7. Click "Upload"
8. Click "Start"
9. Pressing the user button on the `Breakout board 1.2 <https://pycontrol.readthedocs.io/en/latest/user-guide/hardware/#breakout-board-12>`_ will tell the syring pump to infuse 0.25 mL. 
10. Click "Variables" and adjust the pump volume to 2500. Press the user button and see the difference. You can also try giving it a negative number, causing the motor to spin in the opposite direction.


Manual operation
================
The color display includes 7 inputs: a joystick on the left (4 directions + 1 center button) and 2 additional buttons on the right (A and B). Some of these inputs can be used to manually control the syringe pump. 

"A" button
  Resets the displayed volume to 0.00 mL

"B" button
  Retracts the pump until it reaches the retract limit switch.

Joystick North
  Rotates the motor in the infuse direction.

Joystick South
  Rotates the motor in the retract direction.

Joystick center button
   Press and hold down the button until "..." appears, indicating the pump has entered "homing" mode. It will continuosly rotate the motor until one of the limit switches is pressed. Two options will then appear asking whether the triggered limit switch was the infuse limit switch or the retract limit switch. Answer by pressing the "A" or "B" button. The pump now knows which motor rotation (clockwise or counterclockwise) corresponds to infuse and retract.