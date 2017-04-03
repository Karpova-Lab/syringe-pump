.. Syringe Pump documentation master file, created by
   sphinx-quickstart on Wed Mar  1 17:44:06 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` dir.. include:: isogrk1.txt

.. include:: isogrk1.txt

Welcome to Syringe Pump's documentation!
========================================

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
- Lasercut is better than 3D printed

  - Lower Cost

    - A 3D printer is about $500 upfront cost. Alternatively, one could use a 3D printing service like Shapeways, but it would still be more expensive than lasercutting service like Ponoko.

  - Tighter tolerances
  - No need for finishing/removing support material


- Push and pull capable
- Limit switch prevents withdrawing the syringe too far and causing a big mess
- Easy to Assemble

  - No thread tapping required

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

.. toctree::
   :maxdepth: 2
   :caption: Contents:
   :hidden:

   bom.rst
   assembly.rst
   manual.rst
