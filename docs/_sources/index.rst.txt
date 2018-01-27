.. Syringe Pump documentation master file, created by
   sphinx-quickstart on Wed Mar  1 17:44:06 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` dir.. include:: isogrk1.txt

.. include:: isogrk1.txt

============
Syringe Pump
============
 .. raw:: html

   <center>
   <figure>
     <iframe src="https://player.vimeo.com/video/249147119?portrait=0" width="595" height="315" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
   </figure>
   </center>

.. image:: frame_assembly/3d_render.png
  :align: center
  :scale: 100 %

Background
==========
The expansion of the hobbyist 3D printing market has lowered the cost and increased the availability of CNC components due to demand for DIY kits and replacement parts. 
By leveraging these low cost readily available components (stepper motors, lead screws, linear bearings etc.), along with micro-manufacturing services (OSH Park, Ponoko, Shapeways etc.), 
there is no reason that the functionality of a expensive commercial syringe pump can’t be replicated at 1/10th the cost. Therefore, the goal of this project is to make an easy to assemble, open-source syringe pump that is 
an order of magnitude less expensive than commercial pumps, while maintaining a adequate level of reliablity and dispense resolution.

Other Open Source Syringe Pumps:
--------------------------------
- `Open Syringe Pump <https://hackaday.io/post/5681>`_  by naroom
- `Open-source syringe pump <http://www.appropedia.org/Open-source_syringe_pump>`_  by Michigan Tech's Open Sustainability Technology Lab
- `Open source syringe pump <http://fab.cba.mit.edu/classes/863.13/people/wildebeest/projects/final/index.html>`_ by Will Patrick
- `SyriGo <http://www.thingiverse.com/thing:1820146>`_ by Ocram
The major difference between my take on the DIY syringe pump, and the ones above, is my avoidance of 3d printed parts. 
I prefer lasercut parts when possible because they are more precise, stiffer, and more condusive to rapid iteration (minutes to cut instead of hours to 3d print).

Features
========
- Push and pull capable
- Laser cut 1/4" thick acrylic frame

  - Stiff,
  - Precise
  - No need for finishing/removing support material as with a 3D printed part
- Easy to assemble using standard parts (no glue or thread tapping required)
- Controller board that combines microcontroller, stepper driver, and OLED display with pushbuttons
- 2 limit switches prevent the motor from stalling in either direction

Theoretical minimum volume resolution calculated to be **2.65** |mgr|\ L (calculation using Python below)

 .. code:: python

   from math import pi
   from __future__ import print_function

   #Acme rod specs
   pitch = 2 #millimeters
   numStarts = 4
   lead = numStarts*pitch/10.0 #cm

   #Syringe specs
   syringeDiameter = 26 #millimeters
   syringeArea = pi*(syringeDiameter/10.0)**2/4.0 #cm^2

   #Motor specs
   numSteps = 200*8 #200 steps with 1/8 microstepping

   #Result
   resolution = lead*syringeArea/numSteps #mL
   print (u"{:0.3f} \u03bcL resolution".format(resolution*1000))

.. Empirical results from minimum volume resolution testing:

.. raw:: html

  <div style="text-align:center; margin-bottom:24px">
    <a href="https://github.com/Karpova-Lab/syringe-pump" style="background-color: #2980b9;border: none;color: white;padding: 15px 15px;text-align:center;text-decoration: none;display: inline-block;font-size: 18px;border-radius:15px">All files available on Github</a>
  </div>

.. toctree::
   :maxdepth: 2
   :caption: Sections:
   :hidden:

   frame.rst
   controller.rst
..   manual.rst
