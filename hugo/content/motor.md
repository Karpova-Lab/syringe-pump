
# Motor Controller

{{< columns >}} <!-- begin columns block -->
![](render.png)

<---> <!-- magic separator, between columns -->

![](pcb_with_display.jpeg)

{{< /columns >}}

<img src="insertion.gif" style= "width:60%; margin:auto; display:block">
</img>


The syringe pump is designed to be modular so that you can flexibly plug in whichever control board is compatible with your system.

This particular motor controller is designed to interface with [pyControl](https://pycontrol.readthedocs.io/en/latest/)
It receives power from and communicates with pyControl hardware via an RJ45 connection.

The PCB is designed to adhere to the [feather wing specification](https://learn.adafruit.com/adafruit-feather/feather-specification?gclid=Cj0KCQjwsqmEBhDiARIsANV8H3ZFmbJizjrXAZ6NPPpIta56bA8-kGrnnz0L8A4EkraoURAJXrWPU-AaAiQDEALw_wcB)
We use a [Mini color TFT with Joystick](https://www.adafruit.com/product/3321) feather wing. 

The motor controller can receive instructions from pyControl, or respond to user input from the onboard joystick or buttons.

## Printed Circuit Board

<a href="https://oshpark.com/shared_projects/LcC4KhMv"><img src="https://oshpark.com/packs/media/images/badge-5f4e3bf4bf68f72ff88bd92e0089e9cf.png" alt="Order from OSH Park"></img></a>

{{< columns >}}
Schematic:
<a href="schematic.pdf">
  <img src="schematic.jpeg" >
  </img>
</a>
<--->
Layout:
<a href="layout.png">
  <img src="layout.png" >
  </img>
</a>
{{< /columns >}}




## Bill of Materials

{{< button href="ibom.html" >}}View interactive BOM{{< /button >}}

| Qty | Reference          | Description              | Value/MPN                                                                                                                                         | 
|-----|--------------------|--------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------|
| 5   | C1, C5, C6, C7, C8 | 0603 Capacitor           | [100nF](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10F104ZO8NNNC/3886916?s=N4IgTCBcDaIIxgOwDYC0CCsAOdqByAIiALoC%2BQA) | 
| 1   | C2                 | 1206 Capacitor           | [22µF](https://www.digikey.com/en/products/detail/CL31A226MOCLNNC/1276-2728-1-ND/3890814?itemSeq=362659788)                                       | 
| 1   | C3                 | 1206 Capacitor           | [10µF](https://www.digikey.com/en/products/detail/tdk-corporation/CGA5L1X5R1C106M160AC/3950081)                                                   | 
| 1   | C4                 | Electrolytic Capacitor   | [100µF](https://www.digikey.com/en/products/detail/EMZA350ADA101MF80G/565-2559-1-ND/757720?itemSeq=363115427)                                     | 
| 1   | C9                 | 0603 Capacitor           | [2.2µF](https://www.digikey.com/en/products/detail/yageo/CC0603KRX5R8BB225/5195688)                                                               | 
| 1   | C10                | 0603 Capacitor           | [22nF](https://www.digikey.com/en/products/detail/samsung-electro-mechanics/CL10B223KB8WPNC/5961018?s=N4IgTCBcDaIIxgOwDYC0yCsBmALKuIAugL5A)       | 
| 1   | J1                 | RJ45 Jack                | [0855025008](https://www.digikey.com/en/products/detail/molex/0855025008/2404887?s=N4IgTCBcDaIO4FsDMBWALAdgMYBcC0AdgCYgC6AvkA)                    | 
| 1   | J2                 | 16-pin Female Header     | [ESQ-116-12-T-S](https://www.digikey.com/en/products/detail/samtec-inc/ESQ-116-12-T-S/7098325?s=N4IgTCBcDaIKIGUCKBaAjGgbOsKAqKCKAcgCIgC6AvkA)     | 
| 1   | J3                 | 12-pin Female Header     | [ESQ-112-12-T-S](https://www.digikey.com/en/products/detail/samtec-inc/esq-112-12-t-s/7097880)                                                    | 
| 1   | J6                 | 7-pin Right Angle Male   | [PH1RB-07-UA](https://www.digikey.com/en/products/detail/adam-tech/PH1RB-07-UA/9831064?s=N4IgTCBcDa4AwFYDsBaADgCwIwCcBGKcSIAugL5A)                | 
| 1   | J7                 | 7-pin Right Angle Female | [PPTC071LGBN-RC](https://www.digikey.com/en/products/detail/sullins-connector-solutions/PPTC071LGBN-RC/775901?s=N4IgTCBcDaIM4FYAsSDMIC6BfIA)      | 
| 4   | R1, R2, R3, R4     | 0603 Resistor            | [10KΩ](https://www.digikey.com/en/products/detail/yageo/RC0603JR-0710KL/726700?s=N4IgTCBcDaIMwEYEFoEAYDSBxASgYQBVkA5AERAF0BfIA)                   | 
| 2   | R5, R6             | 0805 Resistor            | [0.3Ω](https://www.digikey.com/en/products/detail/panasonic-electronic-components/ERJ-6DQJR30V/6004330?s=N4IgTCBcDaIA4EYCcYAsB2AxgFxAXQF8g)       | 
| 1   | U1                 | 3.3V Linear Regulator    | [AZ1117-3.3](https://www.digikey.com/en/products/detail/AZ1117IH-3.3TRG1/AZ1117IH-3.3TRG1DICT-ND/5699682)                                         | 
| 1   | U2                 | Microcontroller          | [ATSAMD21G](https://www.digikey.com/en/products/detail/microchip-technology/ATSAMD21G18A-AUT/4878867)                                             | 
| 1   | U3                 | EEPROM                   | [AT24C01C-STUM](https://www.digikey.com/en/products/detail/microchip-technology/AT24C01C-STUM-T/3903734)                                          | 
| 1   | U4                 | Motor Driver             | [TMC2209](https://www.digikey.com/en/products/detail/trinamic-motion-control-gmbh/TMC2209-LA-T/10232491?s=N4IgTCBcDaIC4FsDGYwAYCcIC6BfIA)         | 

{{< previous link="/" text="Overview" >}}
{{< next link="frame" text="Frame" >}}