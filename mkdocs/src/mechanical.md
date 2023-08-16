# Mechanics
![labeled](mechanical/labeled.png)
![iso photo](mechanical/iso_photo.jpg)
![all parts](mechanical/all_parts.jpg)

## Hardware BOM

| QTY | Description                    | Part Number                                                                                                                                                                 | Supplier      | 
|-----|--------------------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|---------------|
| 4   | M3 x 25mm machine screw        | [92005A130](https://www.mcmaster.com/#92005A130)                                                                                                                            | McMaster-Carr | 
| 6   | M3 x 16mm machine screw        | [92005A126](https://www.mcmaster.com/92005A126/)                                                                                                                            | McMaster-Carr | 
| 16  | M3 x 10mm machine screw        | [92000A120](https://www.mcmaster.com/#92000A120)                                                                                                                            | McMaster-Carr | 
| 15  | M3 thin square nut             | [97259A101](https://www.mcmaster.com/97259A101/)                                                                                                                            | McMaster-Carr | 
| 3   | M3 threaded insert             | [94510A240](https://www.mcmaster.com/#94510A240)                                                                                                                            | McMaster-Carr | 
| 4   | Spring                         | [9657K267](https://www.mcmaster.com/#9657K267)                                                                                                                              | McMaster-Carr | 
| 2   | Flanged sleeve bearing         | [5448T2](https://www.mcmaster.com/#5448T2)                                                                                                                                  | McMaster-Carr | 
| 1   | Knob                           | [6479K78](https://www.mcmaster.com/#6479K78)                                                                                                                                | McMaster-Carr | 
| 1   | 200 x 8mm lead screw           | [3501-0804-0200](https://www.gobilda.com/3501-series-lead-screw-8mm-lead-4-start-200mm-length/)                                                                             | goBILDA       | 
| 1   | 8mm lead screw nut             | [3505-0804-3216](https://www.gobilda.com/3505-series-lead-screw-pattern-nut-8mm-lead-4-start-32mm-od-16mm-length/)                                                          | goBILDA       | 
| 1   | 200 x  8 mm shaft              | [2100-0008-0200](https://www.gobilda.com/2100-series-stainless-steel-round-shaft-8mm-diameter-200mm-length/)                                                                | goBILDA       | 
| 1   | Linear ball bearing            | [1612-0815-0045](https://www.gobilda.com/1612-series-linear-ball-bearing-8mm-id-x-15mm-od-45mm-length-2-pack/)                                                              | goBILDA       | 
| 1   | 5 mm to 8 mm coupler           | [4002-0005-0008](https://www.gobilda.com/4002-series-flexible-clamping-shaft-coupler-5mm-round-bore-to-8mm-round-bore/)                                                     | goBILDA       | 
| 2   | Limit switch                   | [255-5122-ND](https://www.digikey.com/products/en?keywords=255-5122-nd)                                                                                                     | Digi-Key      | 
| 2   | DIN clip                       | [277-2296-ND](https://www.digikey.com/products/en?keywords=277-2296-nd)                                                                                                     | Digi-Key      | 
| 1   | Nema 17 bipolar 60Ncm 200steps | [17HS24-0644S](https://www.omc-stepperonline.com/hybrid-stepper-motor/nema-17-bipolar-18deg-60ncm-85ozin-064a-10v-42x42x60mm-4-wires-17hs24-0644s.html?search=17hs24-0644s) | STEPPERONLINE | 


## Laser cut parts
!!! info "2D cutting services"

	I've gotten good results using laser cutter / waterjet services from [Big Blue Saw](https://www.bigbluesaw.com/), [SendCutSend](https://sendcutsend.com/), and [OSH Cut](https://www.oshcut.com/).

### Base
The base can be cut out of aluminum or acrylic.
Acrylic is a faster and cheaper option if you are using your own laser cutter.
If you are outsourcing the laser cutting anyway, aluminum has the benefit of being stiffer for only a slightly higher cost.

=== "Aluminum" 
	[:material-file-download: base_tapped_holes.dxf](mechanical/cad/base_v79_tapped_holes.dxf)

	- 3/16"(0.1875") aluminum
	- 2.5 mm holes ready for M3x0.5 tap

	![](mechanical/cad/base_aluminum.png)

	Laser cutting/water jetting may offer tapped holes as a service for an added cost. You can also tap the holes yourself using an M3x0.5 tap.

=== "Acrylic" 
	[:material-file-download: base_threaded_inserts.dxf](mechanical/cad/base_v79.dxf)

	- 1/4"(0.25") acrylic
	- 4 mm holes for [flanged M3 threaded inserts](https://www.mcmaster.com/#94510A240) to be added

	![](mechanical/cad/base_acrylic.png)

---

### Clamps

- 1/4"(0.25") acrylic

[:material-file-download: clamps.dxf](mechanical/cad/clamps.dxf)

![](mechanical/cad/clamps.png)

  
## 3D printed parts
These components are printed in Nylon PA 12 using an HP Multi-Jet-Fusion printer. 


### Cradle
[:material-file-download: cradle.step](mechanical/cad/cradle_v118.step)

![](mechanical/cad/cradle_1.png){ width=33% }
![](mechanical/cad/cradle_2.png){ width=33% }

---

### Carriage
[:material-file-download: carriage.step](mechanical/cad/carriage_v81.step)

![](mechanical/cad/carriage_1.png){ width=33% }
![](mechanical/cad/carriage_2.png){ width=33% }

---

### End Support
[:material-file-download: end_support.step](mechanical/cad/end_support_v83.step)

![](mechanical/cad/end_1.png){ width=33% }
![](mechanical/cad/end_2.png){ width=33% }


## Assembly

### Video

<div style="position: relative; padding-bottom: 56.25%; height: 0; overflow: hidden;">
  <iframe src="https://www.youtube.com/embed/mjYri9EQPvc" style="position: absolute; top: 0; left: 0; width: 100%; height: 100%; border:0;" allowfullscreen title="YouTube Video"></iframe>
</div>


### Tools

- Phillips head screwdriver
- M2.5 mm allen key
- 5/64 allen key

### Instructions

#### 1. Assemble cradle

- (2) M3x25mm screws
- (2) springs
- (2) square nuts
- (1) flanged sleeve bearing
- (1) laser cut acrylic clamp
- (1) 3d printed nylon cradle 
	

=== "parts"
	![](mechanical/assembly/cradle_parts.jpg)
=== "assembled"
	![](mechanical/assembly/cradle_assembled.jpg)


#### 2. Mount motor to cradle and attach coupler
- (4) M3x10mm screws
- (1) 5mm to 8mm coupler
- (1) motor with limit switches
- (1) cradle assembly

=== "parts"
	![](mechanical/assembly/motor_parts.jpg)
=== "assembled"
	![](mechanical/assembly/motor_mounted.jpg)

#### 3. Assemble carriage 
- (6) M3x10mm screws
- (2) M3x25mm screws
- (2) springs
- (8) square nuts
- (1) lead nut
- (1) linear bearing
- (1) laser cut acrylic clamp
- (1) 3d printed nylon carriage

=== "parts"
	![](mechanical/assembly/carriage_parts.jpg)
=== "assembled"
	![](mechanical/assembly/carriage_assembled.jpg)

#### 4. Connect carriage to motor
- (1) lead screw
- (1) motor/cradle assembly
- (1) carriage assembly

=== "parts"
	![](mechanical/assembly/lead_screw_parts.jpg)
=== "assembled"
	![](mechanical/assembly/lead_screw_assembled.jpg)

#### 5. Attach baseplate

=== "parts"
	![](mechanical/assembly/baseplate_parts.jpg)
=== "assembled"
	![](mechanical/assembly/baseplate_assembled.jpg)

#### 6. Attach end support
- (1) flanged sleeve bearing
- (1) 3d printed nylon end support
- (2) M3 x 16mm screws
- (2) square nuts

=== "parts"
	![](mechanical/assembly/end_parts.jpg)
=== "assembled"
	![](mechanical/assembly/end_assembled.jpg)

#### 7. Add knob and support shaft
- (1) M3 x 10mm screw
- (1) square nut
- (1) support shaft
- (1) knob

=== "parts"
	![](mechanical/assembly/knob_parts.jpg)
=== "assembled"
	![](mechanical/assembly/knob_assembled.jpg)

#### 8. Add control electronics
- (1) M3 x 10mm screw
- (1) M3 threaded insert
- (1) [Syringe Control Board](electronics.md#pycontrol-syringe-control-board-scb)

=== "parts"
	![](mechanical/assembly/controller_parts.jpg)
=== "assembled"
	![](mechanical/assembly/controller_assembled.jpg)