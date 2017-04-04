.. Syringe Pump documentation master file, created by
   sphinx-quickstart on Wed Mar  1 17:44:06 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` dir.. include:: isogrk1.txt

.. include:: isogrk1.txt

============
Syringe Pump
============

.. .. raw:: html
..
..   <center>
..   <figure>
..     <iframe src="https://player.vimeo.com/video/196175543?portrait=0" width="595" height="315" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
..   </figure>
..   </center>


Background
==========
Syringe pumps are excessively expensive. By leveraging micro-manufacturing services (OSH Park, Ponoko, Shapeways etc.) and low cost readily available 3D printer components,
there is no reason that the functionality of a $2500 Syringe pump can't be replicated at 1/10th the cost. Therefore, my goal is to make an easy to assemble, open-source syringe pump that
is an order of magnitude less expensive without sacrificing reliablity and resolution.

Other Open Source Syringe Pumps:
--------------------------------
- `Open Syringe Pump <https://hackaday.io/post/5681>`_  by naroom
- `Open-source syringe pump <http://www.appropedia.org/Open-source_syringe_pump>`_  by Michigan Tech's Open Sustainability Technology Lab
- `Open source syringe pump <http://fab.cba.mit.edu/classes/863.13/people/wildebeest/projects/final/index.html>`_ by Will Patrick
- `SyriGo <http://www.thingiverse.com/thing:1820146>`_ by Ocram


Features
========
- Laser cut acrylic frame

  - Most other open source syringe pumps use 3D printed parts. Laser cut acrylic is more rigid and can be produced with superior dimensional accuracy than a 3D printed part. If one decides to make changes to the design, it is much faster to iterate through changes using a lasercutter than if you were to prototype with 3D printed parts. Of course if one doesn't have access to a laser cutter, parts can easily be acquired through services like Ponoko.


- Push and pull capable
- Limit switch prevents withdrawing the syringe too far and causing a big mess

.. raw:: html

  <div style="text-align:center; margin-bottom:24px">
    <a href="https://github.com/Karpova-Lab/syringe-pump" style="background-color: #2980b9;border: none;color: white;padding: 15px 15px;text-align:center;text-decoration: none;display: inline-block;font-size: 18px;border-radius:15px">All files available on Github</a>
  </div>


.. Theoretical minimum volume resolution calculated to be **2.65** |mgr|\ L (calculation using Python below)
..
.. .. code:: python
..
..   from math import pi
..   from __future__ import print_function
..   #Acme rod specs
..   pitch = 2 #millimeters
..   numStarts = 4
..   lead = numStarts*pitch/10.0 #cm
..
..   #Syringe specs
..   syringeDiameter = 26 #millimeters
..   syringeArea = pi*(syringeDiameter/10.0)**2/4.0 #cm^2
..
..   #Motor specs
..   numSteps = 200*8 #200 steps with 1/8 microstepping
..
..   #Result
..   resolution = lead*syringeArea/numSteps #mL
..   print (u"{:0.3f} \u03bcL resolution".format(resolution*1000))

.. Empirical results from minimum volume resolution testing:

.. toctree::
   :maxdepth: 2
   :caption: Sections:
   :hidden:

   bom.rst
   assembly.rst
   manual.rst
