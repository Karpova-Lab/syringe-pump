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
     <iframe src="https://player.vimeo.com/video/306429799?portrait=0" width="595" height="315" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
   </figure>
   </center>

.. image:: frame_assembly/sidebyside.png
  :align: center
  :scale: 100 %

.. .. image:: frame_assembly/3d_render.png
..   :align: center
..   :scale: 100 %

Background
==========
The expansion of the hobbyist 3D printing market has lowered the cost and increased the availability of CNC components due to demand for DIY kits and replacement parts. 
By leveraging these low-cost readily available components (stepper motors, lead screws, linear bearings etc.), along with prototyping services (`OSH Park <https://oshpark.com/>`_, `Big Blue Saw <https://www.bigbluesaw.com/>`_  etc.), 
there is no reason that the functionality of an expensive commercial syringe pump can’t be replicated at 1/10th the cost. 
Therefore, the goal of this project is to make an easy to assemble, open-source syringe pump that is an order of magnitude less expensive than commercial pumps, while maintaining an adequate level of dispense resolution and repeatability.


.. https://www.wpiinc.com/var-2300-aladdin-single-syringe-pump


Alternative Open Source Syringe Pumps
--------------------------------------
I'm not the first to share an open source syringe pump. Here are some examples:

- `3D Printed Syringe Pump Rack <https://hackaday.com/2015/05/29/pump-up-the-volume-with-the-3d-printed-syringe-pump-rack/>`_ by aldricnegrier
- `DIY Syringe Pump <https://hackaday.com/2017/02/26/diy-syringe-pump-saves-big-bucks-for-hackers-lab/>`_ 
- `Open-source syringe pump <http://www.appropedia.org/Open-source_syringe_pump>`_  by Michigan Tech's Open Sustainability Technology Lab
- `Open source syringe pump <http://fab.cba.mit.edu/classes/863.13/people/wildebeest/projects/final/index.html>`_ by Will Patrick
- `SyriGo <http://www.thingiverse.com/thing:1820146>`_ by Ocram

The major difference between my take on the DIY syringe pump, and the ones above, is my abstaining from using 3D printed components. 
I chose to use lasercut parts because they are more accurate, more precise, stiffer, and more condusive to rapid iteration and/or making large quantities (minutes to lasercut instead of hours to 3d print).

Features
========
- Push and pull capable
- Laser cut 1/4" thick acrylic frame

  - Stiff
  - Precise
  - No need for finishing/removing support material as with a 3D printed part
- Easy to assemble using standard parts (no glue or thread tapping required)
- Controller board that combines microcontroller, stepper driver, and color display, joystick, and motor/power connections

  - Reprogrammable over USB for complete customization
  - Modern stepper driver rotates motor with minimal audible noise. 
  - Can be controlled manually, or 
- 2 limit switches prevent the motor from stalling in either direction
- Lower cost than `commercial <http://syringepump.com/NE-1000.php>`_ `alternatives <https://www.harvardapparatus.com/pumps-liquid-handling/syringe-pumps/infuse-withdraw/standard-infuse-withdraw-pump-11-elite-programmable-syringe-pumps.html>`_  

  - Frame ~ $150
  - Electronics ~ $50

The theoretical linear travel resolution is **2.5** |mgr|\ m. Using a 60 mL syringe, this works out to be a volume dispense resolution of **1.4** |mgr|\ L. The calculation is shown below, using Python. You can adjust the numbers and see new results `here <https://repl.it/@alustig3/SyringeResCalc>`_. 

 .. code:: python

  from math import pi

  #Syringe
  innerDiameter = 26.7 #mm
  syringeArea = pi*(innerDiameter/10.0)**2/4.0 #cm^2

  #Lead screw
  pitch = 2 #mm
  numStarts = 4
  lead = numStarts*pitch/10.0 #cm

  #Stepper Driver
  microSteps = 16

  #Motor
  numSteps = 200

  #Result
  linearResolution = lead/(numSteps*microSteps) #cm
  volumeResolution = linearResolution*syringeArea #cm^3 or mL
  print (u"{:0.1f} \u03bcm linear resolution".format(linearResolution*10000))
  print (u"{:0.1f} \u03bcL volume resolution".format(volumeResolution*1000))

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
