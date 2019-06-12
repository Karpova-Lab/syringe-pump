EESchema Schematic File Version 4
LIBS:syringe_board-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Syringe Board"
Date "2019-06-12"
Rev "3.0"
Comp "Andy Lustig"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L asl_symbols:USB_micro_horz_socket_reinforced J4
U 1 1 5CF9BA16
P 10050 3900
F 0 "J4" H 10050 4280 59  0000 C CNN
F 1 "10118194-0001LF" H 10050 4250 50  0001 C CNN
F 2 "asl_footprints:microUSB_horizontal_socket" H 10100 3500 50  0001 C CNN
F 3 "" H 10050 3900 50  0001 C CNN
	1    10050 3900
	1    0    0    1   
$EndComp
$Comp
L asl_symbols:DC-DC_converter U2
U 1 1 5CF9CC3D
P 3700 1900
F 0 "U2" H 3700 2150 50  0001 C CNN
F 1 "ROF-78E3.3-0.5SMD-R" H 4100 1700 50  0001 C CNN
F 2 "asl_footprints:DC_DC_CONVERTER" H 3700 2150 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/ROF-78E3.3-0.5SMD-R/945-1689-1-ND/3593418/?itemSeq=270101613" H 3700 2150 50  0001 C CNN
	1    3700 1900
	1    0    0    1   
$EndComp
$Comp
L asl_symbols:ATMEGA32U4 U3
U 1 1 5CF9D21E
P 8400 3900
F 0 "U3" H 8400 5686 59  0000 C CNN
F 1 "ATMEGA32U4" H 8400 5581 59  0000 C CNN
F 2 "Package_QFP:TQFP-44_10x10mm_P0.8mm" H 8400 3900 50  0001 C CNN
F 3 "" H 8400 3900 50  0001 C CNN
	1    8400 3900
	-1   0    0    -1  
$EndComp
$Comp
L asl_symbols:RJ45 J2
U 1 1 5CFA0150
P 2700 2700
F 0 "J2" H 2371 2704 50  0000 R CNN
F 1 "0855025008" H 2371 2795 50  0000 R CNN
F 2 "asl_footprints:RJ45_SMD" V 2700 2725 50  0001 C CNN
F 3 "~" V 2700 2725 50  0001 C CNN
	1    2700 2700
	1    0    0    1   
$EndComp
$Comp
L asl_symbols:PJ-037A J1
U 1 1 5CFA659C
P 2400 1900
F 0 "J1" H 2170 1950 50  0000 R CNN
F 1 "PJ-037A" H 2170 1859 50  0000 R CNN
F 2 "asl_footprints:DC_Jack" H 2450 1860 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/cui-inc/PJ-037A/CP-037A-ND/1644545" H 2450 1860 50  0001 C CNN
	1    2400 1900
	1    0    0    1   
$EndComp
Wire Wire Line
	3300 2000 3100 2000
Wire Wire Line
	2700 1800 2700 1700
Wire Wire Line
	2700 1700 3100 1700
Text Label 3400 1700 2    50   ~ 0
GND
Text Label 3000 2000 2    50   ~ 0
12VDC
Wire Wire Line
	4100 1950 4250 1950
Text Label 4250 1950 0    50   ~ 0
3.3VDC
$Comp
L asl_symbols:B3FS-1010P S1
U 1 1 5CFB48C1
P 9800 2450
F 0 "S1" H 9800 2765 50  0000 C CNN
F 1 "B3FS-1010P" H 9800 2674 50  0000 C CNN
F 2 "asl_footprints:6mm_tactile_smd" H 9650 2350 50  0001 C CNN
F 3 "https://www.digikey.com/products/en?keywords=sw1440ct" H 9650 2350 50  0001 C CNN
	1    9800 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4300 9300 4300
Wire Wire Line
	9100 4500 9300 4500
Text Label 10350 4400 0    50   ~ 0
GND
Wire Wire Line
	9100 2500 9500 2500
Wire Wire Line
	9500 2500 9500 2400
Connection ~ 9500 2500
Wire Wire Line
	10100 2400 10100 2500
Text Label 10100 2400 0    50   ~ 0
GND
Wire Wire Line
	9100 5400 9100 5300
Wire Wire Line
	9100 5300 9100 5200
Connection ~ 9100 5300
Wire Wire Line
	9100 5100 9100 5200
Connection ~ 9100 5200
Wire Wire Line
	9100 5000 9100 5100
Connection ~ 9100 5100
Text Label 9100 5400 0    50   ~ 0
GND
Wire Wire Line
	10350 3700 10350 3800
Wire Wire Line
	10350 3800 10350 4000
Connection ~ 10350 3800
Wire Wire Line
	10350 4000 10350 4100
Connection ~ 10350 4000
Wire Wire Line
	10350 4400 10350 4100
Connection ~ 10350 4100
Wire Wire Line
	9750 4100 9750 4400
Wire Wire Line
	9600 4400 9750 4400
Connection ~ 9750 4400
Wire Wire Line
	9750 4400 10350 4400
$Comp
L Device:R_Small_US R7
U 1 1 5CFDC0A5
P 9350 3800
F 0 "R7" V 9250 3700 50  0000 C CNN
F 1 "27Ω" V 9250 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9350 3800 50  0001 C CNN
F 3 "~" H 9350 3800 50  0001 C CNN
	1    9350 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R8
U 1 1 5CFDB43E
P 9350 3900
F 0 "R8" V 9450 3750 50  0000 L CNN
F 1 "27Ω" V 9450 4100 50  0000 R CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 9350 3900 50  0001 C CNN
F 3 "~" H 9350 3900 50  0001 C CNN
	1    9350 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	9100 3900 9250 3900
Wire Wire Line
	9100 3800 9250 3800
Wire Wire Line
	9450 3800 9550 3800
Wire Wire Line
	9550 3800 9650 3900
Wire Wire Line
	9650 3900 9750 3900
Wire Wire Line
	9450 3900 9550 3900
Wire Wire Line
	9550 3900 9650 3800
Wire Wire Line
	9650 3800 9750 3800
Wire Wire Line
	9750 3700 9750 3400
Wire Wire Line
	9750 3400 9100 3400
Wire Wire Line
	9100 4700 9100 4800
Wire Wire Line
	9100 4800 9150 4800
Text Label 9150 4800 0    50   ~ 0
3.3VDC
Wire Wire Line
	9100 3600 9400 3600
Wire Wire Line
	9400 3600 9400 2900
Wire Wire Line
	9400 2900 9100 2900
Wire Wire Line
	9100 2600 9100 2700
Wire Wire Line
	9100 2700 9100 2800
Connection ~ 9100 2700
Wire Wire Line
	9100 2900 9100 2800
Connection ~ 9100 2900
Connection ~ 9100 2800
Text Label 9400 2900 0    50   ~ 0
3.3VDC
Text Label 9100 3000 0    50   ~ 0
AREF
Text Label 9250 2500 0    50   ~ 0
RST
Wire Wire Line
	6950 4900 7700 4900
Wire Wire Line
	6950 5000 7700 5000
Wire Wire Line
	6950 5100 7700 5100
Text Label 7600 3400 2    50   ~ 0
RX
Text Label 7600 3500 2    50   ~ 0
TX
$Comp
L Device:R_Small_US R5
U 1 1 5CFF5A05
P 7200 5600
F 0 "R5" V 7100 5500 50  0000 C CNN
F 1 "10KΩ" V 7100 5700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7200 5600 50  0001 C CNN
F 3 "~" H 7200 5600 50  0001 C CNN
	1    7200 5600
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R6
U 1 1 5CFF65E5
P 7200 5700
F 0 "R6" V 7100 5600 50  0000 C CNN
F 1 "10KΩ" V 7100 5800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 7200 5700 50  0001 C CNN
F 3 "~" H 7200 5700 50  0001 C CNN
	1    7200 5700
	0    1    -1   0   
$EndComp
Wire Wire Line
	6950 5600 7100 5600
Wire Wire Line
	6950 5700 7100 5700
Wire Wire Line
	7300 5600 7400 5600
Wire Wire Line
	7400 5600 7400 5700
Wire Wire Line
	7400 5700 7300 5700
Text Label 7400 5650 0    50   ~ 0
GND
$Comp
L Device:LED D1
U 1 1 5CFFDB45
P 5050 5650
F 0 "D1" H 5050 5550 50  0000 C CNN
F 1 "LED" H 5050 5750 50  0000 C CNN
F 2 "LED_SMD:LED_0603_1608Metric" H 5050 5650 50  0001 C CNN
F 3 "~" H 5050 5650 50  0001 C CNN
	1    5050 5650
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small_US R4
U 1 1 5D001160
P 4750 5800
F 0 "R4" V 4650 5800 50  0000 C CNN
F 1 "10KΩ" V 4850 5800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 4750 5800 50  0001 C CNN
F 3 "~" H 4750 5800 50  0001 C CNN
	1    4750 5800
	0    1    1    0   
$EndComp
Wire Wire Line
	4650 5800 4500 5800
Text Label 4500 5800 2    50   ~ 0
GND
Wire Wire Line
	4850 5800 5050 5800
$Comp
L Jumper:SolderJumper_3_Open JP2
U 1 1 5D01D877
P 3700 2900
F 0 "JP2" V 3654 2968 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 3745 2968 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3700 2900 50  0001 C CNN
F 3 "~" H 3700 2900 50  0001 C CNN
	1    3700 2900
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_3_Open JP1
U 1 1 5D01F162
P 3700 2400
F 0 "JP1" V 3654 2468 50  0000 L CNN
F 1 "SolderJumper_3_Open" V 3745 2468 50  0000 L CNN
F 2 "Jumper:SolderJumper-3_P1.3mm_Open_RoundedPad1.0x1.5mm" H 3700 2400 50  0001 C CNN
F 3 "~" H 3700 2400 50  0001 C CNN
	1    3700 2400
	0    1    1    0   
$EndComp
Text Label 3100 2400 0    50   ~ 0
DIO_A
Text Label 3100 2700 0    50   ~ 0
DIO_B
Text Label 3100 2500 0    50   ~ 0
GND
Text Label 3100 3100 0    50   ~ 0
12VDC
Text Label 7600 2500 2    50   ~ 0
MTR_ENABLE
Text Label 7600 2600 2    50   ~ 0
LIMIT1
Text Label 7600 2700 2    50   ~ 0
A2
Text Label 7600 2800 2    50   ~ 0
A3
$Comp
L asl_symbols:feather_wing X1
U 1 1 5D04693D
P 6250 4750
F 0 "X1" H 6250 5865 50  0000 C CNN
F 1 "feather_wing" H 6250 5774 50  0000 C CNN
F 2 "asl_footprints:Feather" H 6250 5750 50  0001 C CNN
F 3 "" H 6450 4300 50  0001 C CNN
	1    6250 4750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5050 5500 5550 5500
Text Label 1850 4750 2    50   ~ 0
MTR_ENABLE
Wire Wire Line
	7700 2500 7600 2500
Wire Wire Line
	7600 2600 7700 2600
Wire Wire Line
	7600 2700 7700 2700
Wire Wire Line
	7600 2800 7700 2800
Wire Wire Line
	1850 4750 1950 4750
Wire Wire Line
	7700 2900 7600 2900
Wire Wire Line
	7700 3000 7600 3000
Text Label 7600 2900 2    50   ~ 0
B
Text Label 7600 3000 2    50   ~ 0
A
Wire Wire Line
	3100 2400 3550 2400
Wire Wire Line
	3100 2700 3550 2700
Wire Wire Line
	3550 2700 3550 2900
Wire Wire Line
	3700 2700 3850 2700
Wire Wire Line
	3700 2200 3850 2200
Wire Wire Line
	3700 3100 3850 3100
Wire Wire Line
	3700 2600 3850 2600
Wire Wire Line
	6950 5300 7000 5300
Wire Wire Line
	6950 5400 7000 5400
Text Label 7000 5300 0    50   ~ 0
RX
Text Label 7000 5400 0    50   ~ 0
TX
Wire Wire Line
	5550 4300 5450 4300
Wire Wire Line
	5550 4400 5450 4400
Wire Wire Line
	5550 4500 5450 4500
Wire Wire Line
	5550 4600 5450 4600
Wire Wire Line
	5550 4200 5450 4200
Wire Wire Line
	5550 4100 5450 4100
Wire Wire Line
	5550 4900 5450 4900
Wire Wire Line
	5550 5000 5450 5000
Wire Wire Line
	5550 5100 5450 5100
Wire Wire Line
	5550 5200 5450 5200
Wire Wire Line
	5550 5300 5450 5300
Wire Wire Line
	5550 5400 5450 5400
Text Label 5450 4300 2    50   ~ 0
A2
Text Label 5450 4400 2    50   ~ 0
A3
Wire Wire Line
	7600 3400 7700 3400
Wire Wire Line
	7600 3500 7700 3500
Wire Wire Line
	6950 4150 7050 4150
Wire Wire Line
	7050 4150 7050 4250
Wire Wire Line
	7050 4250 6950 4250
Wire Wire Line
	6950 4050 7050 4050
Text Label 7050 4250 0    50   ~ 0
GND
Text Label 7050 4050 0    50   ~ 0
3.3VDC
Text Label 5450 4500 2    50   ~ 0
B
Text Label 5450 4600 2    50   ~ 0
A
Text Label 5450 4100 2    50   ~ 0
MTR_ENABLE
Text Label 5450 4200 2    50   ~ 0
LIMIT1
Wire Wire Line
	7700 3900 7650 3900
Text Label 7650 3900 2    50   ~ 0
D5
Text Label 5450 4900 2    50   ~ 0
D5
Text Label 7650 4000 2    50   ~ 0
D6
Wire Wire Line
	7650 4000 7700 4000
Text Label 5450 5000 2    50   ~ 0
D6
Wire Wire Line
	7700 4300 7650 4300
Text Label 7650 4300 2    50   ~ 0
D9
Text Label 5450 5100 2    50   ~ 0
D9
Wire Wire Line
	7700 4400 7650 4400
Text Label 5450 5200 2    50   ~ 0
DIR
Text Label 7650 4400 2    50   ~ 0
DIR
Text Label 5450 5300 2    50   ~ 0
STEP
Wire Wire Line
	7700 4500 7650 4500
Text Label 7650 4500 2    50   ~ 0
STEP
Text Label 5450 5400 2    50   ~ 0
LIMIT2
Wire Wire Line
	7700 4600 7650 4600
Text Label 7650 4600 2    50   ~ 0
LIMIT2
Wire Wire Line
	6950 3950 7050 3950
Text Label 7050 3950 0    50   ~ 0
RST
Wire Wire Line
	6950 4450 7050 4450
Text Label 7050 4450 0    50   ~ 0
AREF
Wire Wire Line
	7700 4700 7600 4700
Text Label 7600 4700 2    50   ~ 0
IND_LED
Text Label 5450 5500 2    50   ~ 0
IND_LED
Wire Wire Line
	7600 3600 7700 3600
Wire Wire Line
	7700 3700 7600 3700
Text Label 7600 3600 2    50   ~ 0
SDA
Text Label 7600 3700 2    50   ~ 0
SCL
Wire Wire Line
	1950 4550 1850 4550
Wire Wire Line
	1950 4650 1850 4650
Text Label 1850 4550 2    50   ~ 0
STEP
Text Label 1850 4650 2    50   ~ 0
DIR
Wire Wire Line
	1950 4300 1850 4300
Wire Wire Line
	1950 4200 1850 4200
Wire Wire Line
	1950 4400 1850 4400
Text Label 1850 4400 2    50   ~ 0
MISO
Text Label 1850 4300 2    50   ~ 0
MOSI
Text Label 1850 4200 2    50   ~ 0
SCK
Text Label 7400 4900 2    50   ~ 0
SCK
Text Label 7400 5000 2    50   ~ 0
MOSI
Text Label 7400 5100 2    50   ~ 0
MISO
Wire Wire Line
	1850 5400 1850 5650
Wire Wire Line
	1850 5650 1950 5650
Wire Wire Line
	1850 5400 1950 5400
Wire Wire Line
	1850 5650 1850 5850
Connection ~ 1850 5650
Text Label 1850 5850 0    50   ~ 0
GND
$Comp
L asl_symbols:TMC2130 U1
U 1 1 5D05BA53
P 2450 4850
F 0 "U1" H 2425 6115 50  0000 C CNN
F 1 "TMC2130" H 2425 6024 50  0000 C CNN
F 2 "Package_QFP:TQFP-48-1EP_7x7mm_P0.5mm_EP5x5mm_ThermalVias" H 2300 4650 50  0001 C CNN
F 3 "" H 2300 4650 50  0001 C CNN
	1    2450 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5450 2900 5550
Wire Wire Line
	1850 5850 2450 5850
Wire Wire Line
	2450 5850 2900 5850
Connection ~ 2450 5850
Wire Wire Line
	2900 5850 2900 5650
Wire Wire Line
	2900 5650 2900 5550
Connection ~ 2900 5650
Connection ~ 2900 5550
Wire Wire Line
	2900 3850 2900 3950
Wire Wire Line
	2900 3950 2900 4050
Connection ~ 2900 3950
$Comp
L Device:C_Small C4
U 1 1 5D083C24
P 3400 3850
F 0 "C4" V 3200 3850 50  0000 C CNN
F 1 "100nF" V 3300 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3400 3850 50  0001 C CNN
F 3 "~" H 3400 3850 50  0001 C CNN
	1    3400 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	2900 3850 2950 3850
Connection ~ 2900 3850
$Comp
L Device:C_Small C6
U 1 1 5D115873
P 3750 3850
F 0 "C6" V 3550 3850 50  0000 C CNN
F 1 "100nF" V 3650 3850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3750 3850 50  0001 C CNN
F 3 "~" H 3750 3850 50  0001 C CNN
	1    3750 3850
	0    1    1    0   
$EndComp
Wire Wire Line
	3150 3850 3200 3850
Wire Wire Line
	3200 3850 3200 3550
Wire Wire Line
	3900 3550 3900 3850
Wire Wire Line
	3900 3850 3850 3850
Text Label 3900 3550 0    50   ~ 0
GND
Wire Wire Line
	3300 3950 3300 3850
$Comp
L Device:C_Small C1
U 1 1 5D083227
P 3050 3850
F 0 "C1" V 3250 3800 50  0000 L CNN
F 1 "100nF" V 3150 3750 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3050 3850 50  0001 C CNN
F 3 "~" H 3050 3850 50  0001 C CNN
	1    3050 3850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3300 3950 2900 3950
Wire Wire Line
	3500 3850 3550 3850
Wire Wire Line
	3550 3850 3550 3550
Wire Wire Line
	3550 3550 3900 3550
Wire Wire Line
	3200 3550 3550 3550
Connection ~ 3550 3550
Connection ~ 2900 4050
Wire Wire Line
	3400 4050 3400 3950
Wire Wire Line
	3400 3950 3650 3950
Wire Wire Line
	3650 3850 3650 3950
Wire Wire Line
	3400 4050 2900 4050
$Comp
L Device:C_Small C7
U 1 1 5D1C930B
P 4150 4150
F 0 "C7" V 3950 4150 50  0000 C CNN
F 1 "4.7uF" V 4050 4150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4150 4150 50  0001 C CNN
F 3 "~" H 4150 4150 50  0001 C CNN
	1    4150 4150
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 5D1CABDD
P 3850 4250
F 0 "R3" V 3750 4250 50  0000 C CNN
F 1 "2.2Ω" V 3950 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 3850 4250 50  0001 C CNN
F 3 "~" H 3850 4250 50  0001 C CNN
	1    3850 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 4150 3850 4150
Wire Wire Line
	3850 4350 3700 4350
Wire Wire Line
	3700 4350 3700 4250
Wire Wire Line
	3700 4250 2900 4250
$Comp
L Device:C_Small C8
U 1 1 5D1DB29F
P 4150 4350
F 0 "C8" V 3950 4350 50  0000 C CNN
F 1 "470nF" V 4050 4350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4150 4350 50  0001 C CNN
F 3 "~" H 4150 4350 50  0001 C CNN
	1    4150 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3850 4150 4050 4150
Connection ~ 3850 4150
Wire Wire Line
	4250 4150 4350 4150
Wire Wire Line
	4350 4150 4350 3850
Wire Wire Line
	4350 3850 3900 3850
Connection ~ 3900 3850
Wire Wire Line
	3850 4350 4050 4350
Connection ~ 3850 4350
Wire Wire Line
	4250 4350 4350 4350
Wire Wire Line
	4350 4350 4350 4150
Connection ~ 4350 4150
$Comp
L Device:C_Small C5
U 1 1 5D204D14
P 3450 4350
F 0 "C5" V 3250 4350 50  0000 C CNN
F 1 "100nF" V 3350 4350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3450 4350 50  0001 C CNN
F 3 "~" H 3450 4350 50  0001 C CNN
	1    3450 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2900 4350 3350 4350
Wire Wire Line
	3550 4350 3600 4350
Wire Wire Line
	4350 4600 4350 4350
Connection ~ 4350 4350
$Comp
L Device:C_Small C2
U 1 1 5D217415
P 3050 4500
F 0 "C2" V 2850 4500 50  0000 C CNN
F 1 "22nF" V 2950 4500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3050 4500 50  0001 C CNN
F 3 "~" H 3050 4500 50  0001 C CNN
	1    3050 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 4450 2950 4450
Wire Wire Line
	2950 4450 2950 4400
Wire Wire Line
	2950 4400 3050 4400
Wire Wire Line
	3050 4600 2950 4600
Wire Wire Line
	2950 4600 2950 4550
Wire Wire Line
	2950 4550 2900 4550
Wire Wire Line
	3600 4350 3600 4600
Wire Wire Line
	3600 4600 4350 4600
$Comp
L Device:R_Small_US R1
U 1 1 5D29B52D
P 3100 5400
F 0 "R1" V 3000 5400 50  0000 C CNN
F 1 "0.3Ω" V 3200 5400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3100 5400 50  0001 C CNN
F 3 "~" H 3100 5400 50  0001 C CNN
	1    3100 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R2
U 1 1 5D2ADA9C
P 3450 5300
F 0 "R2" V 3350 5300 50  0000 C CNN
F 1 "0.3Ω" V 3550 5300 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3450 5300 50  0001 C CNN
F 3 "~" H 3450 5300 50  0001 C CNN
	1    3450 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5100 4050 5100
Wire Wire Line
	2900 5000 4050 5000
Wire Wire Line
	2900 4900 4050 4900
Wire Wire Line
	2900 4800 4050 4800
$Comp
L asl_symbols:Screw_Terminal_01x08 J3
U 1 1 5CFC1787
P 4250 5100
F 0 "J3" H 4330 5092 50  0000 L CNN
F 1 "OSTVN08A150" H 4330 5001 50  0000 L CNN
F 2 "asl_footprints:8pos_screw_terminal" H 4250 5100 50  0001 C CNN
F 3 "https://www.digikey.com/product-detail/en/OSTVN08A150/ED10566-ND/1588868/?itemSeq=270117158" H 4250 5100 50  0001 C CNN
	1    4250 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5300 3100 5300
Wire Wire Line
	3100 5500 3450 5500
Wire Wire Line
	3450 5500 3450 5400
Wire Wire Line
	3450 5200 2900 5200
Text Label 3300 5500 3    50   ~ 0
GND
Wire Wire Line
	7700 4800 7600 4800
Text Label 7600 4800 2    50   ~ 0
CS
Wire Wire Line
	1950 4100 1850 4100
Text Label 1850 4100 2    50   ~ 0
CS
Wire Wire Line
	1950 3850 1850 3850
Text Label 1850 3850 2    50   ~ 0
3.3VDC
Wire Wire Line
	4050 5300 3650 5300
Wire Wire Line
	3650 5300 3650 5500
Wire Wire Line
	3650 5500 3450 5500
Connection ~ 3450 5500
Wire Wire Line
	4050 5500 3650 5500
Connection ~ 3650 5500
Wire Wire Line
	4050 5400 4000 5400
Wire Wire Line
	4050 5200 4000 5200
Text Label 4000 5200 2    50   ~ 0
LIMIT1
Text Label 4000 5400 2    50   ~ 0
LIMIT2
$Comp
L Device:CP_Small C3
U 1 1 5D37D1BD
P 3100 1850
F 0 "C3" H 2900 1900 50  0000 L CNN
F 1 "100uF" H 2900 1800 50  0001 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x7.7" H 3100 1850 50  0001 C CNN
F 3 "~" H 3100 1850 50  0001 C CNN
	1    3100 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 1750 3100 1700
Connection ~ 3100 1700
Wire Wire Line
	3100 1700 3700 1700
Wire Wire Line
	3100 1950 3100 2000
Connection ~ 3100 2000
Wire Wire Line
	3100 2000 2700 2000
Text Label 9200 3800 2    50   ~ 0
D+
Text Label 9200 3900 2    50   ~ 0
D-
$Comp
L asl_symbols:Resonator Y1
U 1 1 5D4B4023
P 9400 4400
F 0 "Y1" V 9200 4500 50  0000 C CNN
F 1 "8MHz" V 9200 4300 50  0000 C CNN
F 2 "Crystal:Resonator_SMD_muRata_CSTxExxV-3Pin_3.0x1.1mm" H 9375 4400 50  0001 C CNN
F 3 "~" H 9375 4400 50  0001 C CNN
	1    9400 4400
	0    -1   1    0   
$EndComp
Text Label 3850 3100 0    50   ~ 0
B
Text Label 3850 2700 0    50   ~ 0
TX
Text Label 3850 2600 0    50   ~ 0
A
Text Label 3850 2200 0    50   ~ 0
RX
$Comp
L Mechanical:MountingHole H1
U 1 1 5D009730
P 5350 2550
F 0 "H1" H 5450 2596 50  0000 L CNN
F 1 "MountingHole" H 5450 2505 50  0000 L CNN
F 2 "asl_footprints:standoff nut" H 5350 2550 50  0001 C CNN
F 3 "~" H 5350 2550 50  0001 C CNN
	1    5350 2550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5D0097B7
P 6100 2550
F 0 "H3" H 6200 2596 50  0000 L CNN
F 1 "MountingHole" H 6200 2505 50  0000 L CNN
F 2 "asl_footprints:standoff nut" H 6100 2550 50  0001 C CNN
F 3 "~" H 6100 2550 50  0001 C CNN
	1    6100 2550
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5D01488B
P 5350 2900
F 0 "H2" H 5450 2946 50  0000 L CNN
F 1 "MountingHole" H 5450 2855 50  0000 L CNN
F 2 "asl_footprints:standoff nut" H 5350 2900 50  0001 C CNN
F 3 "~" H 5350 2900 50  0001 C CNN
	1    5350 2900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5D014B39
P 6100 2900
F 0 "H4" H 6200 2946 50  0000 L CNN
F 1 "MountingHole" H 6200 2855 50  0000 L CNN
F 2 "asl_footprints:standoff nut" H 6100 2900 50  0001 C CNN
F 3 "~" H 6100 2900 50  0001 C CNN
	1    6100 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
