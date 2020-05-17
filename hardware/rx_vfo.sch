EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 6
Title "QRP CW TRX"
Date "2020-05-15"
Rev "2"
Comp "DM3MAT"
Comment1 "PLL + I/Q gen"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 74xx:74HC74 U9
U 1 1 5E5AE86A
P 5500 2750
F 0 "U9" H 5500 3231 50  0000 C CNN
F 1 "74HC74" H 5500 3140 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 5500 2750 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 5500 2750 50  0001 C CNN
	1    5500 2750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC74 U9
U 2 1 5E5AEE9A
P 5500 3750
F 0 "U9" H 5500 4231 50  0000 C CNN
F 1 "74HC74" H 5500 4140 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 5500 3750 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 5500 3750 50  0001 C CNN
	2    5500 3750
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC74 U9
U 3 1 5E5AF706
P 7800 3300
F 0 "U9" H 8030 3346 50  0000 L CNN
F 1 "74HC74" H 8030 3255 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 7800 3300 50  0001 C CNN
F 3 "74xx/74hc_hct74.pdf" H 7800 3300 50  0001 C CNN
	3    7800 3300
	1    0    0    -1  
$EndComp
Text HLabel 6250 2650 2    50   Input ~ 0
VFO+I
Text HLabel 6250 2850 2    50   Input ~ 0
VFO-I
Text HLabel 6250 3650 2    50   Input ~ 0
VFO+Q
Text HLabel 6250 3850 2    50   Input ~ 0
VFO-Q
Wire Wire Line
	5800 2650 6000 2650
Wire Wire Line
	5800 2850 6250 2850
Wire Wire Line
	5800 3650 6250 3650
Wire Wire Line
	5800 3850 5900 3850
$Comp
L power:+5VD #PWR0156
U 1 1 5E5B2088
P 4900 2250
F 0 "#PWR0156" H 4900 2100 50  0001 C CNN
F 1 "+5VD" H 4915 2423 50  0000 C CNN
F 2 "" H 4900 2250 50  0001 C CNN
F 3 "" H 4900 2250 50  0001 C CNN
	1    4900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2450 5500 2350
Wire Wire Line
	5500 2350 4900 2350
Wire Wire Line
	4900 2350 4900 2250
Wire Wire Line
	5500 3050 5500 3150
Wire Wire Line
	5500 3150 4900 3150
Wire Wire Line
	4900 3150 4900 2350
Connection ~ 4900 2350
Wire Wire Line
	5500 3450 5500 3150
Connection ~ 5500 3150
Wire Wire Line
	5500 4050 5500 4150
Wire Wire Line
	5500 4150 4900 4150
Wire Wire Line
	4900 4150 4900 3150
Connection ~ 4900 3150
Wire Wire Line
	5200 2750 5000 2750
Wire Wire Line
	5000 2750 5000 3750
Wire Wire Line
	5000 3750 5200 3750
Wire Wire Line
	5200 2650 5100 2650
Wire Wire Line
	5100 2250 5900 2250
Wire Wire Line
	5900 2250 5900 3850
Wire Wire Line
	5100 2250 5100 2650
Connection ~ 5900 3850
Wire Wire Line
	5900 3850 6250 3850
Wire Wire Line
	6000 2650 6000 3300
Wire Wire Line
	6000 3300 5100 3300
Wire Wire Line
	5100 3300 5100 3650
Wire Wire Line
	5100 3650 5200 3650
Connection ~ 6000 2650
Wire Wire Line
	6000 2650 6250 2650
$Comp
L power:+5VD #PWR0157
U 1 1 5E5BA609
P 4750 2150
F 0 "#PWR0157" H 4750 2000 50  0001 C CNN
F 1 "+5VD" H 4765 2323 50  0000 C CNN
F 2 "" H 4750 2150 50  0001 C CNN
F 3 "" H 4750 2150 50  0001 C CNN
	1    4750 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0158
U 1 1 5E5BA940
P 4750 4200
F 0 "#PWR0158" H 4750 3950 50  0001 C CNN
F 1 "GND" H 4755 4027 50  0000 C CNN
F 2 "" H 4750 4200 50  0001 C CNN
F 3 "" H 4750 4200 50  0001 C CNN
	1    4750 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R40
U 1 1 5E5BAFFF
P 4750 2400
F 0 "R40" H 4680 2354 50  0000 R CNN
F 1 "10k" H 4680 2445 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4680 2400 50  0001 C CNN
F 3 "~" H 4750 2400 50  0001 C CNN
	1    4750 2400
	1    0    0    1   
$EndComp
$Comp
L Device:R R41
U 1 1 5E5BB671
P 4750 3700
F 0 "R41" H 4680 3654 50  0000 R CNN
F 1 "10k" H 4680 3745 50  0000 R CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4680 3700 50  0001 C CNN
F 3 "~" H 4750 3700 50  0001 C CNN
	1    4750 3700
	1    0    0    1   
$EndComp
Wire Wire Line
	4750 2750 4750 2550
Wire Wire Line
	4750 2750 4750 3550
Connection ~ 4750 2750
Wire Wire Line
	4750 3850 4750 4200
Wire Wire Line
	4750 2250 4750 2150
$Comp
L Device:C C38
U 1 1 5E5BFBCE
P 4500 2750
F 0 "C38" V 4248 2750 50  0000 C CNN
F 1 "100n" V 4339 2750 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 4538 2600 50  0001 C CNN
F 3 "~" H 4500 2750 50  0001 C CNN
	1    4500 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4650 2750 4750 2750
Wire Wire Line
	4750 2750 5000 2750
Connection ~ 5000 2750
$Comp
L Connector_Generic:Conn_01x07 J9
U 1 1 5E5CA93B
P 3600 3800
F 0 "J9" H 3518 4317 50  0000 C CNN
F 1 "Si5351" H 3518 4226 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x07_P2.54mm_Vertical" H 3600 3800 50  0001 C CNN
F 3 "~" H 3600 3800 50  0001 C CNN
	1    3600 3800
	-1   0    0    -1  
$EndComp
$Comp
L power:+5VD #PWR0159
U 1 1 5E5CD9EB
P 3900 3400
F 0 "#PWR0159" H 3900 3250 50  0001 C CNN
F 1 "+5VD" H 3915 3573 50  0000 C CNN
F 2 "" H 3900 3400 50  0001 C CNN
F 3 "" H 3900 3400 50  0001 C CNN
	1    3900 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0160
U 1 1 5E5CDE5F
P 3900 4200
F 0 "#PWR0160" H 3900 3950 50  0001 C CNN
F 1 "GND" H 3905 4027 50  0000 C CNN
F 2 "" H 3900 4200 50  0001 C CNN
F 3 "" H 3900 4200 50  0001 C CNN
	1    3900 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 3600 3900 3600
Wire Wire Line
	3900 3600 3900 4200
Wire Wire Line
	3800 3500 3900 3500
Wire Wire Line
	3900 3500 3900 3400
Text HLabel 4000 3700 2    50   UnSpc ~ 0
SDA
Text HLabel 4000 3800 2    50   Input ~ 0
SCL
Text HLabel 4000 4100 2    50   Output ~ 0
CLK0
Text HLabel 4000 4000 2    50   Output ~ 0
CLK1
Text HLabel 4250 2750 0    50   Output ~ 0
CLK2
Wire Wire Line
	3800 3700 4000 3700
Wire Wire Line
	4000 3800 3800 3800
Wire Wire Line
	3800 4000 4000 4000
Wire Wire Line
	4250 2750 4350 2750
$Comp
L Device:C C39
U 1 1 5E5E4BB8
P 8500 3350
F 0 "C39" H 8385 3304 50  0000 R CNN
F 1 "100n" H 8385 3395 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 8538 3200 50  0001 C CNN
F 3 "~" H 8500 3350 50  0001 C CNN
	1    8500 3350
	-1   0    0    1   
$EndComp
$Comp
L power:+5VD #PWR0161
U 1 1 5E5E52F7
P 7800 2700
F 0 "#PWR0161" H 7800 2550 50  0001 C CNN
F 1 "+5VD" H 7815 2873 50  0000 C CNN
F 2 "" H 7800 2700 50  0001 C CNN
F 3 "" H 7800 2700 50  0001 C CNN
	1    7800 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0162
U 1 1 5E5E56BC
P 7800 3800
F 0 "#PWR0162" H 7800 3550 50  0001 C CNN
F 1 "GND" H 7805 3627 50  0000 C CNN
F 2 "" H 7800 3800 50  0001 C CNN
F 3 "" H 7800 3800 50  0001 C CNN
	1    7800 3800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0163
U 1 1 5E5E59D0
P 8500 3800
F 0 "#PWR0163" H 8500 3550 50  0001 C CNN
F 1 "GND" H 8505 3627 50  0000 C CNN
F 2 "" H 8500 3800 50  0001 C CNN
F 3 "" H 8500 3800 50  0001 C CNN
	1    8500 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2700 7800 2800
Wire Wire Line
	7800 2800 8500 2800
Wire Wire Line
	8500 2800 8500 3200
Connection ~ 7800 2800
Wire Wire Line
	7800 2800 7800 2900
Wire Wire Line
	8500 3500 8500 3800
Wire Wire Line
	7800 3700 7800 3800
Wire Wire Line
	4000 3900 3800 3900
Wire Wire Line
	3800 4100 4000 4100
Text HLabel 4000 3900 2    50   Output ~ 0
CLK2
$EndSCHEMATC