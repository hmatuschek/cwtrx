EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title "QRP CW TRX"
Date "2020-06-24"
Rev "2"
Comp "DM3MAT"
Comment1 "Demodulator"
Comment2 "based on QCX"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:R R20
U 1 1 5E510D0E
P 3800 2450
F 0 "R20" V 3593 2450 50  0000 C CNN
F 1 "100" V 3684 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3730 2450 50  0001 C CNN
F 3 "~" H 3800 2450 50  0001 C CNN
	1    3800 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C30
U 1 1 5E510F43
P 4300 3250
F 0 "C30" V 4048 3250 50  0000 C CNN
F 1 "10n" V 4139 3250 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4338 3100 50  0001 C CNN
F 3 "~" H 4300 3250 50  0001 C CNN
	1    4300 3250
	0    1    1    0   
$EndComp
$Comp
L Amplifier_Operational:TLC272 U6
U 1 1 5E51168D
P 4450 2550
F 0 "U6" H 4450 2917 50  0000 C CNN
F 1 "LM833" H 4450 2826 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 4450 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 4450 2550 50  0001 C CNN
	1    4450 2550
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U6
U 2 1 5E51247D
P 4450 3900
F 0 "U6" H 4450 4267 50  0000 C CNN
F 1 "LM833" H 4450 4176 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 4450 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 4450 3900 50  0001 C CNN
	2    4450 3900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U6
U 3 1 5E512FDF
P 3750 5900
F 0 "U6" H 3708 5946 50  0000 L CNN
F 1 "LM833" H 3708 5855 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 3750 5900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 3750 5900 50  0001 C CNN
	3    3750 5900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R21
U 1 1 5E51B5EE
P 3800 2650
F 0 "R21" V 3593 2650 50  0000 C CNN
F 1 "100" V 3684 2650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3730 2650 50  0001 C CNN
F 3 "~" H 3800 2650 50  0001 C CNN
	1    3800 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R24
U 1 1 5E51B900
P 4600 2900
F 0 "R24" V 4393 2900 50  0000 C CNN
F 1 "10k" V 4484 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4530 2900 50  0001 C CNN
F 3 "~" H 4600 2900 50  0001 C CNN
	1    4600 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	4150 2450 3950 2450
Wire Wire Line
	4150 2650 4050 2650
Wire Wire Line
	4450 2900 4050 2900
Wire Wire Line
	4050 2900 4050 2650
Connection ~ 4050 2650
Wire Wire Line
	4050 2650 3950 2650
Wire Wire Line
	4150 3250 4050 3250
Wire Wire Line
	4050 3250 4050 2900
Connection ~ 4050 2900
Wire Wire Line
	4450 3250 4850 3250
Wire Wire Line
	4850 3250 4850 2900
Wire Wire Line
	4850 2550 4750 2550
Wire Wire Line
	4750 2900 4850 2900
Connection ~ 4850 2900
Wire Wire Line
	4850 2900 4850 2550
$Comp
L Device:R R22
U 1 1 5E529C16
P 3850 3800
F 0 "R22" V 3643 3800 50  0000 C CNN
F 1 "100" V 3734 3800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3780 3800 50  0001 C CNN
F 3 "~" H 3850 3800 50  0001 C CNN
	1    3850 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R23
U 1 1 5E52A495
P 3850 4000
F 0 "R23" V 4057 4000 50  0000 C CNN
F 1 "100" V 3966 4000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 3780 4000 50  0001 C CNN
F 3 "~" H 3850 4000 50  0001 C CNN
	1    3850 4000
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R25
U 1 1 5E52ABDC
P 4600 4300
F 0 "R25" V 4393 4300 50  0000 C CNN
F 1 "10k" V 4484 4300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 4530 4300 50  0001 C CNN
F 3 "~" H 4600 4300 50  0001 C CNN
	1    4600 4300
	0    1    1    0   
$EndComp
$Comp
L Device:C C31
U 1 1 5E52B812
P 4300 4600
F 0 "C31" V 4048 4600 50  0000 C CNN
F 1 "10n" V 4139 4600 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4338 4450 50  0001 C CNN
F 3 "~" H 4300 4600 50  0001 C CNN
	1    4300 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	4000 3800 4150 3800
Wire Wire Line
	4150 4000 4050 4000
Wire Wire Line
	4150 4600 4050 4600
Connection ~ 4050 4000
Wire Wire Line
	4050 4000 4000 4000
Wire Wire Line
	4450 4300 4050 4300
Wire Wire Line
	4050 4000 4050 4300
Connection ~ 4050 4300
Wire Wire Line
	4050 4300 4050 4600
Wire Wire Line
	4750 3900 4850 3900
Wire Wire Line
	4850 4600 4450 4600
Wire Wire Line
	4750 4300 4850 4300
Wire Wire Line
	4850 3900 4850 4300
Connection ~ 4850 4300
Wire Wire Line
	4850 4300 4850 4600
$Comp
L Amplifier_Operational:TLC272 U7
U 1 1 5E52F408
P 5850 2550
F 0 "U7" H 5850 2917 50  0000 C CNN
F 1 "LM833" H 5850 2826 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5850 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 5850 2550 50  0001 C CNN
	1    5850 2550
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U7
U 2 1 5E5317D3
P 5850 3900
F 0 "U7" H 5850 4267 50  0000 C CNN
F 1 "LM833" H 5850 4176 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5850 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 5850 3900 50  0001 C CNN
	2    5850 3900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U7
U 3 1 5E535EC0
P 4600 5900
F 0 "U7" H 4558 5946 50  0000 L CNN
F 1 "LM833" H 4558 5855 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 4600 5900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 4600 5900 50  0001 C CNN
	3    4600 5900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U8
U 3 1 5E536F7C
P 5350 5900
F 0 "U8" H 5308 5946 50  0000 L CNN
F 1 "LM833" H 5308 5855 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5350 5900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 5350 5900 50  0001 C CNN
	3    5350 5900
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U8
U 1 1 5E53A340
P 7250 2550
F 0 "U8" H 7250 2917 50  0000 C CNN
F 1 "LM833" H 7250 2826 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 7250 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 7250 2550 50  0001 C CNN
	1    7250 2550
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TLC272 U8
U 2 1 5E53BAA6
P 7250 3900
F 0 "U8" H 7250 4267 50  0000 C CNN
F 1 "LM833" H 7250 4176 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 7250 3900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tlc272.pdf" H 7250 3900 50  0001 C CNN
	2    7250 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R26
U 1 1 5E542CB1
P 5200 2450
F 0 "R26" V 4993 2450 50  0000 C CNN
F 1 "5.1k" V 5084 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5130 2450 50  0001 C CNN
F 3 "~" H 5200 2450 50  0001 C CNN
	1    5200 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C33
U 1 1 5E5555CD
P 5200 1950
F 0 "C33" V 4948 1950 50  0000 C CNN
F 1 "47n" V 5039 1950 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 5238 1800 50  0001 C CNN
F 3 "~" H 5200 1950 50  0001 C CNN
	1    5200 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R R30
U 1 1 5E555CD6
P 6000 2900
F 0 "R30" V 5793 2900 50  0000 C CNN
F 1 "3.3k" V 5884 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5930 2900 50  0001 C CNN
F 3 "~" H 6000 2900 50  0001 C CNN
	1    6000 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	6150 2900 6250 2900
Wire Wire Line
	6250 2550 6150 2550
Wire Wire Line
	5850 2900 5450 2900
Wire Wire Line
	5450 2900 5450 2650
Wire Wire Line
	5450 2650 5550 2650
Wire Wire Line
	5450 2650 5350 2650
Connection ~ 5450 2650
Wire Wire Line
	5350 2450 5450 2450
Wire Wire Line
	5350 1950 5450 1950
Wire Wire Line
	5450 1950 5450 2450
Connection ~ 5450 2450
Wire Wire Line
	5450 2450 5550 2450
Wire Wire Line
	5050 2450 4950 2450
Wire Wire Line
	4950 2450 4950 2550
Wire Wire Line
	4950 2650 5050 2650
Wire Wire Line
	4850 2550 4950 2550
Connection ~ 4850 2550
Connection ~ 4950 2550
Wire Wire Line
	4950 2550 4950 2650
Text HLabel 3550 2450 0    50   Input ~ 0
I+
Text HLabel 3550 2650 0    50   Input ~ 0
I-
Text HLabel 3600 3800 0    50   Input ~ 0
Q+
Text HLabel 3600 4000 0    50   Input ~ 0
Q-
Wire Wire Line
	3600 4000 3700 4000
Wire Wire Line
	3600 3800 3700 3800
Wire Wire Line
	3550 2650 3650 2650
Wire Wire Line
	3550 2450 3650 2450
Text HLabel 8400 3250 2    50   Output ~ 0
NF
$Comp
L power:GND #PWR0145
U 1 1 5E622242
P 4950 2050
F 0 "#PWR0145" H 4950 1800 50  0001 C CNN
F 1 "GND" H 4955 1877 50  0000 C CNN
F 2 "" H 4950 2050 50  0001 C CNN
F 3 "" H 4950 2050 50  0001 C CNN
	1    4950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1950 4950 1950
Wire Wire Line
	4950 1950 4950 2050
$Comp
L Device:R R27
U 1 1 5E5463C7
P 5200 2650
F 0 "R27" V 4993 2650 50  0000 C CNN
F 1 "3.3k" V 5084 2650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5130 2650 50  0001 C CNN
F 3 "~" H 5200 2650 50  0001 C CNN
	1    5200 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R33
U 1 1 5E630C29
P 6600 2650
F 0 "R33" V 6393 2650 50  0000 C CNN
F 1 "3.3k" V 6484 2650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6530 2650 50  0001 C CNN
F 3 "~" H 6600 2650 50  0001 C CNN
	1    6600 2650
	0    1    1    0   
$EndComp
$Comp
L Device:R R32
U 1 1 5E631257
P 6600 2450
F 0 "R32" V 6393 2450 50  0000 C CNN
F 1 "4.3k" V 6484 2450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6530 2450 50  0001 C CNN
F 3 "~" H 6600 2450 50  0001 C CNN
	1    6600 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C36
U 1 1 5E6323A7
P 6600 1950
F 0 "C36" V 6348 1950 50  0000 C CNN
F 1 "470n" V 6439 1950 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 6638 1800 50  0001 C CNN
F 3 "~" H 6600 1950 50  0001 C CNN
	1    6600 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 2450 6350 2450
Connection ~ 6250 2550
Wire Wire Line
	6450 2650 6350 2650
Wire Wire Line
	6750 2450 6850 2450
Wire Wire Line
	6750 2650 6850 2650
$Comp
L Device:R R36
U 1 1 5E683C04
P 7400 2900
F 0 "R36" V 7193 2900 50  0000 C CNN
F 1 "3.3k" V 7284 2900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 7330 2900 50  0001 C CNN
F 3 "~" H 7400 2900 50  0001 C CNN
	1    7400 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 2900 7650 2900
Wire Wire Line
	7650 2900 7650 2550
Wire Wire Line
	7650 2550 7550 2550
Wire Wire Line
	7250 2900 6850 2900
Wire Wire Line
	6850 2900 6850 2650
Connection ~ 6850 2650
Wire Wire Line
	6850 2650 6950 2650
Wire Wire Line
	6750 1950 6850 1950
Wire Wire Line
	6850 1950 6850 2450
Connection ~ 6850 2450
Wire Wire Line
	6850 2450 6950 2450
$Comp
L power:GND #PWR0146
U 1 1 5E68B2C7
P 6350 2050
F 0 "#PWR0146" H 6350 1800 50  0001 C CNN
F 1 "GND" H 6355 1877 50  0000 C CNN
F 2 "" H 6350 2050 50  0001 C CNN
F 3 "" H 6350 2050 50  0001 C CNN
	1    6350 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1950 6350 1950
$Comp
L Device:R R38
U 1 1 5E68D880
P 7900 2550
F 0 "R38" V 7693 2550 50  0000 C CNN
F 1 "1k" V 7784 2550 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 7830 2550 50  0001 C CNN
F 3 "~" H 7900 2550 50  0001 C CNN
	1    7900 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	7750 2550 7650 2550
Connection ~ 7650 2550
$Comp
L Device:R_POT_TRIM RV3
U 1 1 5E69112E
P 8150 3250
F 0 "RV3" H 8081 3296 50  0000 R CNN
F 1 "500" H 8081 3205 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 8150 3250 50  0001 C CNN
F 3 "~" H 8150 3250 50  0001 C CNN
	1    8150 3250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV1
U 1 1 5E6917BE
P 5200 3300
F 0 "RV1" V 4993 3300 50  0000 C CNN
F 1 "50k" V 5084 3300 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 5200 3300 50  0001 C CNN
F 3 "~" H 5200 3300 50  0001 C CNN
	1    5200 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R_POT_TRIM RV2
U 1 1 5E6920EA
P 6600 3300
F 0 "RV2" V 6393 3300 50  0000 C CNN
F 1 "50k" V 6484 3300 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3296W_Vertical" H 6600 3300 50  0001 C CNN
F 3 "~" H 6600 3300 50  0001 C CNN
	1    6600 3300
	0    1    1    0   
$EndComp
$Comp
L Device:R R29
U 1 1 5E6AFC42
P 5200 4000
F 0 "R29" V 4993 4000 50  0000 C CNN
F 1 "3.3k" V 5084 4000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 5130 4000 50  0001 C CNN
F 3 "~" H 5200 4000 50  0001 C CNN
	1    5200 4000
	0    1    1    0   
$EndComp
$Comp
L Device:R R28
U 1 1 5E6B0866
P 5200 3800
F 0 "R28" V 4993 3800 50  0000 C CNN
F 1 "10k" V 5084 3800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5130 3800 50  0001 C CNN
F 3 "~" H 5200 3800 50  0001 C CNN
	1    5200 3800
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 3800 4950 3800
Wire Wire Line
	4950 3800 4950 3900
Wire Wire Line
	4950 4000 5050 4000
Wire Wire Line
	4850 3900 4950 3900
Connection ~ 4850 3900
Connection ~ 4950 3900
Wire Wire Line
	4950 3900 4950 4000
Wire Wire Line
	5050 3300 4950 3300
Wire Wire Line
	4950 3300 4950 3500
Connection ~ 4950 3800
Wire Wire Line
	5200 3450 5200 3500
Wire Wire Line
	5200 3500 4950 3500
Connection ~ 4950 3500
Wire Wire Line
	4950 3500 4950 3800
Wire Wire Line
	5350 3300 5450 3300
Wire Wire Line
	5450 3300 5450 3800
Wire Wire Line
	5450 3800 5550 3800
Wire Wire Line
	5350 3800 5450 3800
Connection ~ 5450 3800
Wire Wire Line
	5350 4000 5450 4000
$Comp
L Device:R R31
U 1 1 5E6CE390
P 6000 4250
F 0 "R31" V 5793 4250 50  0000 C CNN
F 1 "3.3k" V 5884 4250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5930 4250 50  0001 C CNN
F 3 "~" H 6000 4250 50  0001 C CNN
	1    6000 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 4250 5450 4250
Wire Wire Line
	5450 4250 5450 4000
Connection ~ 5450 4000
Wire Wire Line
	5450 4000 5550 4000
$Comp
L Device:C C35
U 1 1 5E6D1119
P 5850 3300
F 0 "C35" V 5598 3300 50  0000 C CNN
F 1 "10n" V 5689 3300 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 5888 3150 50  0001 C CNN
F 3 "~" H 5850 3300 50  0001 C CNN
	1    5850 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0147
U 1 1 5E6D22ED
P 6100 3400
F 0 "#PWR0147" H 6100 3150 50  0001 C CNN
F 1 "GND" H 6105 3227 50  0000 C CNN
F 2 "" H 6100 3400 50  0001 C CNN
F 3 "" H 6100 3400 50  0001 C CNN
	1    6100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3300 5700 3300
Connection ~ 5450 3300
Wire Wire Line
	6000 3300 6100 3300
Wire Wire Line
	6100 3300 6100 3400
Wire Wire Line
	6150 4250 6250 4250
Wire Wire Line
	6250 4250 6250 3900
Wire Wire Line
	6250 3900 6150 3900
$Comp
L Device:R R34
U 1 1 5E6DC19D
P 6600 3800
F 0 "R34" V 6393 3800 50  0000 C CNN
F 1 "7.5k" V 6484 3800 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 6530 3800 50  0001 C CNN
F 3 "~" H 6600 3800 50  0001 C CNN
	1    6600 3800
	0    1    1    0   
$EndComp
$Comp
L Device:R R35
U 1 1 5E6DD106
P 6600 4000
F 0 "R35" V 6393 4000 50  0000 C CNN
F 1 "3.3k" V 6484 4000 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 6530 4000 50  0001 C CNN
F 3 "~" H 6600 4000 50  0001 C CNN
	1    6600 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 3800 6350 3800
Wire Wire Line
	6350 3800 6350 3900
Wire Wire Line
	6350 4000 6450 4000
Wire Wire Line
	6250 3900 6350 3900
Connection ~ 6250 3900
Connection ~ 6350 3900
Wire Wire Line
	6350 3900 6350 4000
Wire Wire Line
	6750 3800 6850 3800
Wire Wire Line
	6750 3300 6850 3300
Wire Wire Line
	6850 3300 6850 3800
Connection ~ 6850 3800
Wire Wire Line
	6850 3800 6950 3800
Wire Wire Line
	6450 3300 6350 3300
Wire Wire Line
	6350 3300 6350 3550
Connection ~ 6350 3800
Wire Wire Line
	6600 3450 6600 3550
Wire Wire Line
	6600 3550 6350 3550
Connection ~ 6350 3550
Wire Wire Line
	6350 3550 6350 3800
Wire Wire Line
	6750 4000 6850 4000
$Comp
L Device:R R37
U 1 1 5E70F787
P 7400 4250
F 0 "R37" V 7193 4250 50  0000 C CNN
F 1 "3.3k" V 7284 4250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 7330 4250 50  0001 C CNN
F 3 "~" H 7400 4250 50  0001 C CNN
	1    7400 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	7550 4250 7650 4250
Wire Wire Line
	7650 4250 7650 3900
Wire Wire Line
	7650 3900 7550 3900
Wire Wire Line
	7250 4250 6850 4250
Wire Wire Line
	6850 4250 6850 4000
Connection ~ 6850 4000
Wire Wire Line
	6850 4000 6950 4000
$Comp
L Device:C C37
U 1 1 5E7189EF
P 7200 3300
F 0 "C37" V 6948 3300 50  0000 C CNN
F 1 "100n" V 7039 3300 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7238 3150 50  0001 C CNN
F 3 "~" H 7200 3300 50  0001 C CNN
	1    7200 3300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0148
U 1 1 5E7192E7
P 7450 3400
F 0 "#PWR0148" H 7450 3150 50  0001 C CNN
F 1 "GND" H 7455 3227 50  0000 C CNN
F 2 "" H 7450 3400 50  0001 C CNN
F 3 "" H 7450 3400 50  0001 C CNN
	1    7450 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 3300 7450 3300
Wire Wire Line
	7450 3300 7450 3400
Wire Wire Line
	7050 3300 6850 3300
Connection ~ 6850 3300
$Comp
L Device:R R39
U 1 1 5E721507
P 7900 3900
F 0 "R39" V 7693 3900 50  0000 C CNN
F 1 "1k" V 7784 3900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P5.08mm_Vertical" V 7830 3900 50  0001 C CNN
F 3 "~" H 7900 3900 50  0001 C CNN
	1    7900 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 2550 6250 2900
Wire Wire Line
	6350 2050 6350 1950
Wire Wire Line
	6350 2450 6350 2550
Wire Wire Line
	6250 2550 6350 2550
Connection ~ 6350 2550
Wire Wire Line
	6350 2550 6350 2650
Wire Wire Line
	7750 3900 7650 3900
Connection ~ 7650 3900
Wire Wire Line
	8050 2550 8150 2550
Wire Wire Line
	8150 2550 8150 3100
Wire Wire Line
	8050 3900 8150 3900
Wire Wire Line
	8150 3900 8150 3400
Wire Wire Line
	8400 3250 8300 3250
$Comp
L Device:C C29
U 1 1 5EC6FD66
P 4050 5750
F 0 "C29" H 4165 5796 50  0000 L CNN
F 1 "100n" H 4165 5705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4088 5600 50  0001 C CNN
F 3 "~" H 4050 5750 50  0001 C CNN
	1    4050 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C32
U 1 1 5EC792DC
P 4900 5750
F 0 "C32" H 5015 5796 50  0000 L CNN
F 1 "100n" H 5015 5705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4938 5600 50  0001 C CNN
F 3 "~" H 4900 5750 50  0001 C CNN
	1    4900 5750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C34
U 1 1 5EC7E22B
P 5650 5750
F 0 "C34" H 5765 5796 50  0000 L CNN
F 1 "100n" H 5765 5705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 5688 5600 50  0001 C CNN
F 3 "~" H 5650 5750 50  0001 C CNN
	1    5650 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0149
U 1 1 5ECA3C17
P 3650 5400
F 0 "#PWR0149" H 3650 5250 50  0001 C CNN
F 1 "+12V" H 3665 5573 50  0000 C CNN
F 2 "" H 3650 5400 50  0001 C CNN
F 3 "" H 3650 5400 50  0001 C CNN
	1    3650 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0150
U 1 1 5ECA7426
P 3650 6300
F 0 "#PWR0150" H 3650 6050 50  0001 C CNN
F 1 "GND" H 3655 6127 50  0000 C CNN
F 2 "" H 3650 6300 50  0001 C CNN
F 3 "" H 3650 6300 50  0001 C CNN
	1    3650 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0151
U 1 1 5ECA7C2D
P 4050 6300
F 0 "#PWR0151" H 4050 6050 50  0001 C CNN
F 1 "GND" H 4055 6127 50  0000 C CNN
F 2 "" H 4050 6300 50  0001 C CNN
F 3 "" H 4050 6300 50  0001 C CNN
	1    4050 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0152
U 1 1 5ECA832D
P 4500 6300
F 0 "#PWR0152" H 4500 6050 50  0001 C CNN
F 1 "GND" H 4505 6127 50  0000 C CNN
F 2 "" H 4500 6300 50  0001 C CNN
F 3 "" H 4500 6300 50  0001 C CNN
	1    4500 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0153
U 1 1 5ECA8A57
P 4900 6300
F 0 "#PWR0153" H 4900 6050 50  0001 C CNN
F 1 "GND" H 4905 6127 50  0000 C CNN
F 2 "" H 4900 6300 50  0001 C CNN
F 3 "" H 4900 6300 50  0001 C CNN
	1    4900 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0154
U 1 1 5ECA9284
P 5250 6300
F 0 "#PWR0154" H 5250 6050 50  0001 C CNN
F 1 "GND" H 5255 6127 50  0000 C CNN
F 2 "" H 5250 6300 50  0001 C CNN
F 3 "" H 5250 6300 50  0001 C CNN
	1    5250 6300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0155
U 1 1 5ECA9955
P 5650 6300
F 0 "#PWR0155" H 5650 6050 50  0001 C CNN
F 1 "GND" H 5655 6127 50  0000 C CNN
F 2 "" H 5650 6300 50  0001 C CNN
F 3 "" H 5650 6300 50  0001 C CNN
	1    5650 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 5400 3650 5500
Wire Wire Line
	3650 5500 4050 5500
Wire Wire Line
	5650 5500 5650 5600
Connection ~ 3650 5500
Wire Wire Line
	3650 5500 3650 5600
Wire Wire Line
	5650 5900 5650 6300
Wire Wire Line
	5250 5600 5250 5500
Connection ~ 5250 5500
Wire Wire Line
	5250 5500 5650 5500
Wire Wire Line
	5250 6200 5250 6300
Wire Wire Line
	4900 5900 4900 6300
Wire Wire Line
	4900 5600 4900 5500
Connection ~ 4900 5500
Wire Wire Line
	4900 5500 5250 5500
Wire Wire Line
	4500 5600 4500 5500
Connection ~ 4500 5500
Wire Wire Line
	4500 5500 4900 5500
Wire Wire Line
	4050 5600 4050 5500
Connection ~ 4050 5500
Wire Wire Line
	4050 5500 4500 5500
Wire Wire Line
	4050 5900 4050 6300
Wire Wire Line
	3650 6200 3650 6300
Wire Wire Line
	4500 6200 4500 6300
$EndSCHEMATC
