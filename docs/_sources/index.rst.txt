:github_url: https://github.com/Karpova-Lab/syringe-pump

.. Syringe Pump documentation master file, created by
   sphinx-quickstart on Wed Mar  1 17:44:06 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` dir.. include:: isogrk1.txt

.. include:: isogrk1.txt

============
Syringe Pump
============

.. image:: renders/vert.gif

The goal of this project is to provide an easy to assemble, open-source syringe pump that is significantly less expensive than commercial pumps, while maintaining a sufficient level of dispense resolution and repeatability.

This is not the only open source syringe pump that exists. Here are some other projects:

- `Poisedon <https://pachterlab.github.io/poseidon/>`_ by the Pachter Lab
- `Low cost laser cut syringe pump <http://jvoigts.scripts.mit.edu/blog/low-cost-syringe-pump/>`_ by Jakob Voigts
- `3D Printed Syringe Pump Rack <https://hackaday.com/2015/05/29/pump-up-the-volume-with-the-3d-printed-syringe-pump-rack/>`_ by aldricnegrier
- `DIY Syringe Pump <https://hackaday.com/2017/02/26/diy-syringe-pump-saves-big-bucks-for-hackers-lab/>`_ 
- `Open-source syringe pump <http://www.appropedia.org/Open-source_syringe_pump>`_  by Michigan Tech's Open Sustainability Technology Lab
- `Open source syringe pump <http://fab.cba.mit.edu/classes/863.13/people/wildebeest/projects/final/index.html>`_ by Will Patrick
- `SyriGo <http://www.thingiverse.com/thing:1820146>`_ by Ocram

.. The major difference between my take on the DIY syringe pump, and the ones above, is my abstaining from using 3D printed components. 
.. I chose to use lasercut parts because they are more accurate, more precise, stiffer, and more condusive to rapid iteration and/or making large quantities (minutes to lasercut instead of hours to 3d print).
.. https://www.wpiinc.com/var-2300-aladdin-single-syringe-pump


Features
========
- Easy to build

  - ~30 minutes to assemble
  - Assembled with screws and nuts. No glue or thread tapping required
  - Laser cut 1/4" thick acrylic frame

    - Stiff & precise
    - No need for finishing/removing support material as with a 3D printed part

- Infuse and retract capable
- Vertically mounted on `DIN rail <https://en.wikipedia.org/wiki/DIN_rail>`_ 

  - Air bubbles rise to the top and exit at start of infusion
  - Easy to mount multiple pumps side by side

- 2 limit switches prevent the motor from stalling in either direction
- Controller board that combines microcontroller, stepper driver, color display, joystick, and motor/power connections

  - Reprogrammable over USB for complete customization
  - Modern stepper driver rotates motor very quietly
  - Send precise "dispense [X] µL" serial commands to dispense volume or set an infuse rate and provide an high TTL signal for desired duration
  - Can automatically stop experiment when syringe is empty (when infuse limit switch is triggered) 

- Lower cost than comparable commerical pumps (`$750 <http://syringepump.com/NE-1000.php>`_ , `$950 <https://www.wpiinc.com/var-2300-aladdin-single-syringe-pump>`_, `$4600 <https://www.harvardapparatus.com/pumps-liquid-handling/syringe-pumps/infuse-withdraw/standard-infuse-withdraw-phd-22-2000-syringe-pumps.html>`_)

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
  print (u"{:0.1f} \u03bcL volumetric resolution".format(volumeResolution*1000))

.. Empirical results from minimum volume resolution testing:

.. raw:: html

  <style>
      .embed-container {
          position: relative;
          padding-bottom: 56.25%;
          height: 0;
          overflow: hidden;
          max-width: 100%;
      }
      .embed-container iframe,
      .embed-container object,
      .embed-container embed {
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
      }
  </style>
  <div class='embed-container'>
      <iframe src='https://player.vimeo.com/video/306429799?portrait=0' frameborder='0' webkitAllowFullScreen
          mozallowfullscreen allowFullScreen>
      </iframe>
  </div>
  <br></br>

.. image:: frame_assembly/vertical_pumps.jpg
  :align: center
  :width: 100 %


Hardware License
++++++++++++++++
Janelia Open-Source Hardware (Non-commercial)

By downloading, using and/or viewing these designs, documentation and related data and information, and all content in the foregoing (collectively, the “Designs”), you agree to the following:

You may use, copy, modify, display and distribute the Designs for any purpose, excluding any diagnostic, clinical, therapeutic or other medical use.

THE DESIGNS ARE PROTOTYPES AND ARE EXPERIMENTAL IN NATURE AND SHOULD BE USED WITH PRUDENCE AND APPROPRIATE CAUTION, AS NOT ALL OF THE CHARACTERISTICS ARE KNOWN. THE DESIGNS ARE PROVIDED “AS-IS” WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES OF ANY KIND (INCLUDING, BUT NOT LIMITED TO, ANY IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, TITLE, ACCURACY, OR FITNESS FOR A PARTICULAR PURPOSE, AND ANY WARRANTIES ARISING FROM COURSE OF PERFORMANCE, COURSE OF DEALING, COURSE OF CONDUCT, OR USAGE OF TRADE) OR CONDITIONS OF ANY KIND, WHETHER EXPRESS OR IMPLIED OR STATUTORY. NO OPINION, ADVICE OR STATEMENT OF THE HOWARD HUGHES MEDICAL INSTITUTE (“HHMI”) OR ITS TRUSTEES, EMPLOYEES, AGENTS, LICENSORS OR SUPPLIERS, WHETHER MADE WITHIN THE DESIGNS OR OTHERWISE, SHALL CREATE ANY WARRANTY. HHMI MAKES NO WARRANTY THAT THE DESIGNS WILL BE ACCURATE, CURRENT OR RELIABLE. SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OF CERTAIN WARRANTIES OR CONDITIONS, AND AS A CONSEQUENCE SOME OF THE ABOVE DISCLAIMERS MAY NOT APPLY TO YOU. 

HHMI and its trustees, officers, employees, and agents (collectively, the “HHMI Indemnitees”), will be indemnified, defended by counsel acceptable to HHMI, and held harmless by you from and against any claim, liability, cost, expense, damage, deficiency, loss, or obligation, of any kind or nature (including, without limitation, reasonable attorneys' fees and other costs and expenses of defense) (collectively, "Claims"), based upon, arising out of, or otherwise relating to this agreement, including without limitation any cause of action relating to product liability. The previous sentence will not apply to any Claim that is determined with finality by a court of competent jurisdiction to result solely from the gross negligence or willful misconduct of an HHMI Indemnitee. Notwithstanding any other provision of this agreement, your obligation to defend, indemnify and hold harmless the HHMI Indemnitees under this paragraph will not be subject to any limitation or exclusion of liability or damages or otherwise limited in any way.  This provision shall survive any termination or expiration of this agreement.

Any redistribution of the Designs must contain or reference these terms.

Software License
++++++++++++++++
Janelia Open-Source Software

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    
- Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

- Neither the name of HHMI nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.



.. toctree::
   :maxdepth: 2
   :hidden:

   frame.rst
   controller.rst
..   manual.rst
