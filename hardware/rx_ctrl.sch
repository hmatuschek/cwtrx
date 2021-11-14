EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 6 6
Title "QRP CW TRX"
Date "2020-06-24"
Rev "2"
Comp "DM3MAT"
Comment1 "Controller"
Comment2 "based on QCX"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328-PU U11
U 1 1 5E5F3044
P 3400 3350
F 0 "U11" H 2756 3396 50  0000 R CNN
F 1 "ATmega328-PU" H 2756 3305 50  0000 R CNN
F 2 "Package_DIP:DIP-28_W7.62mm" H 3400 3350 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 3400 3350 50  0001 C CNN
	1    3400 3350
	1    0    0    -1  
$EndComp
Text HLabel 4100 3450 2    50   BiDi ~ 0
SDA
Text HLabel 4100 3550 2    50   Output ~ 0
SCL
Wire Wire Line
	4000 3450 4100 3450
Wire Wire Line
	4000 3550 4100 3550
$Comp
L Device:C C46
U 1 1 5EA4A0C0
P 2700 2400
F 0 "C46" H 2585 2354 50  0000 R CNN
F 1 "100n" H 2585 2445 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 2738 2250 50  0001 C CNN
F 3 "~" H 2700 2400 50  0001 C CNN
	1    2700 2400
	1    0    0    1   
$EndComp
$Comp
L power:+5VD #PWR0121
U 1 1 5EA4B010
P 3400 1550
F 0 "#PWR0121" H 3400 1400 50  0001 C CNN
F 1 "+5VD" H 3415 1723 50  0000 C CNN
F 2 "" H 3400 1550 50  0001 C CNN
F 3 "" H 3400 1550 50  0001 C CNN
	1    3400 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C47
U 1 1 5EA4B66D
P 3750 1650
F 0 "C47" V 3498 1650 50  0000 C CNN
F 1 "100n" V 3589 1650 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 3788 1500 50  0001 C CNN
F 3 "~" H 3750 1650 50  0001 C CNN
	1    3750 1650
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5EA4BDC0
P 2700 2650
F 0 "#PWR0122" H 2700 2400 50  0001 C CNN
F 1 "GND" H 2705 2477 50  0000 C CNN
F 2 "" H 2700 2650 50  0001 C CNN
F 3 "" H 2700 2650 50  0001 C CNN
	1    2700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1650 3500 1650
Wire Wire Line
	3500 1650 3500 1850
Wire Wire Line
	3400 1550 3400 1650
Wire Wire Line
	3400 1650 3500 1650
Connection ~ 3400 1650
Wire Wire Line
	3400 1650 3400 1850
Connection ~ 3500 1650
Wire Wire Line
	2800 2150 2700 2150
Wire Wire Line
	2700 2150 2700 2250
Wire Wire Line
	2700 2550 2700 2650
Text GLabel 4100 3050 2    50   Input ~ 0
Vbat
Wire Wire Line
	4100 3050 4000 3050
$Comp
L Device:R R4
U 1 1 5EA5AFEB
P 2700 7000
F 0 "R4" H 2770 7046 50  0000 L CNN
F 1 "4.7k" H 2770 6955 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 2630 7000 50  0001 C CNN
F 3 "~" H 2700 7000 50  0001 C CNN
	1    2700 7000
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5EA5B595
P 2700 6500
F 0 "R3" H 2770 6546 50  0000 L CNN
F 1 "47k" H 2770 6455 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P15.24mm_Horizontal" V 2630 6500 50  0001 C CNN
F 3 "~" H 2700 6500 50  0001 C CNN
	1    2700 6500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0127
U 1 1 5EA5BBF9
P 2700 7250
F 0 "#PWR0127" H 2700 7000 50  0001 C CNN
F 1 "GND" H 2705 7077 50  0000 C CNN
F 2 "" H 2700 7250 50  0001 C CNN
F 3 "" H 2700 7250 50  0001 C CNN
	1    2700 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6650 2700 6750
Wire Wire Line
	2700 7150 2700 7250
Wire Wire Line
	2700 6350 2700 6250
Text GLabel 2800 6750 2    50   UnSpc ~ 0
Vbat
Wire Wire Line
	2800 6750 2700 6750
Connection ~ 2700 6750
Wire Wire Line
	2700 6750 2700 6850
Text GLabel 4100 3150 2    50   Input ~ 0
ROT-A
Text GLabel 4100 3250 2    50   Input ~ 0
ROT-B
Text GLabel 4100 3350 2    50   Input ~ 0
ROT-M
Wire Wire Line
	4000 3150 4100 3150
Wire Wire Line
	4000 3250 4100 3250
Wire Wire Line
	4000 3350 4100 3350
Text GLabel 4100 3650 2    50   Input ~ 0
RST
Wire Wire Line
	4100 3650 4000 3650
$Comp
L Connector:AVR-ISP-6 J3
U 1 1 5EA77A20
P 4300 6750
F 0 "J3" H 3971 6846 50  0000 R CNN
F 1 "AVR-ISP-6" H 3971 6755 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" V 4050 6800 50  0001 C CNN
F 3 " ~" H 3025 6200 50  0001 C CNN
	1    4300 6750
	1    0    0    -1  
$EndComp
$Comp
L power:+5VD #PWR0164
U 1 1 5EA7830D
P 4200 6150
F 0 "#PWR0164" H 4200 6000 50  0001 C CNN
F 1 "+5VD" H 4215 6323 50  0000 C CNN
F 2 "" H 4200 6150 50  0001 C CNN
F 3 "" H 4200 6150 50  0001 C CNN
	1    4200 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0165
U 1 1 5EA78A01
P 4200 7250
F 0 "#PWR0165" H 4200 7000 50  0001 C CNN
F 1 "GND" H 4205 7077 50  0000 C CNN
F 2 "" H 4200 7250 50  0001 C CNN
F 3 "" H 4200 7250 50  0001 C CNN
	1    4200 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 6150 4200 6250
Text GLabel 4800 6850 2    50   Input ~ 0
RST
Wire Wire Line
	4800 6850 4700 6850
Text GLabel 4100 2850 2    50   Output ~ 0
KEY
Text GLabel 4100 2250 2    50   Output ~ 0
SIDE
Text GLabel 4100 2150 2    50   Output ~ 0
80M
Text GLabel 4100 4550 2    50   Output ~ 0
40M
Text GLabel 4100 4450 2    50   Output ~ 0
20M
Text GLabel 4100 4350 2    50   Output ~ 0
10M
Wire Wire Line
	4100 2250 4000 2250
Wire Wire Line
	4100 2150 4000 2150
Wire Wire Line
	4200 7150 4200 7250
Text GLabel 4100 3850 2    50   Output ~ 0
LCD_D4
Text GLabel 4100 3950 2    50   Output ~ 0
LCD_D5
Text GLabel 4100 4050 2    50   Output ~ 0
LCD_D6
Text GLabel 4100 4150 2    50   Output ~ 0
LCD_D7
Text GLabel 4100 4250 2    50   Output ~ 0
LCD_EN
Text GLabel 4100 2450 2    50   Input ~ 0
Dit
Text GLabel 4100 2350 2    50   Input ~ 0
Dah
Text GLabel 4100 2750 2    50   Output ~ 0
TX
Wire Wire Line
	4100 3850 4000 3850
Wire Wire Line
	4000 3950 4100 3950
Wire Wire Line
	4100 4050 4000 4050
Wire Wire Line
	4000 4150 4100 4150
Wire Wire Line
	4000 4250 4100 4250
Wire Wire Line
	4000 4550 4100 4550
$Comp
L Device:L_Core_Ferrite L4
U 1 1 5EAA2F8D
P 6150 1300
F 0 "L4" V 6375 1300 50  0000 C CNN
F 1 "100u" V 6284 1300 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 6150 1300 50  0001 C CNN
F 3 "~" H 6150 1300 50  0001 C CNN
	1    6150 1300
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C48
U 1 1 5EAA359D
P 6400 1550
F 0 "C48" H 6285 1504 50  0000 R CNN
F 1 "100n" H 6285 1595 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 6438 1400 50  0001 C CNN
F 3 "~" H 6400 1550 50  0001 C CNN
	1    6400 1550
	1    0    0    1   
$EndComp
Text GLabel 5900 1300 0    50   Input ~ 0
TX
Wire Wire Line
	5900 1300 6000 1300
Wire Wire Line
	6300 1300 6400 1300
Wire Wire Line
	6400 1300 6400 1400
$Comp
L power:GND #PWR0166
U 1 1 5EAA75CC
P 6400 1800
F 0 "#PWR0166" H 6400 1550 50  0001 C CNN
F 1 "GND" H 6405 1627 50  0000 C CNN
F 2 "" H 6400 1800 50  0001 C CNN
F 3 "" H 6400 1800 50  0001 C CNN
	1    6400 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1700 6400 1800
Text HLabel 6500 1300 2    50   Output ~ 0
TX5V
Wire Wire Line
	6500 1300 6400 1300
Connection ~ 6400 1300
$Comp
L Device:L_Core_Ferrite L6
U 1 1 5EAADCC4
P 7300 1300
F 0 "L6" V 7525 1300 50  0000 C CNN
F 1 "100u" V 7434 1300 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 7300 1300 50  0001 C CNN
F 3 "~" H 7300 1300 50  0001 C CNN
	1    7300 1300
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C50
U 1 1 5EAADCCE
P 7550 1550
F 0 "C50" H 7435 1504 50  0000 R CNN
F 1 "100n" H 7435 1595 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7588 1400 50  0001 C CNN
F 3 "~" H 7550 1550 50  0001 C CNN
	1    7550 1550
	1    0    0    1   
$EndComp
Text GLabel 7050 1300 0    50   Input ~ 0
KEY
Wire Wire Line
	7050 1300 7150 1300
Wire Wire Line
	7450 1300 7550 1300
Wire Wire Line
	7550 1300 7550 1400
$Comp
L power:GND #PWR0167
U 1 1 5EAADCDC
P 7550 1800
F 0 "#PWR0167" H 7550 1550 50  0001 C CNN
F 1 "GND" H 7555 1627 50  0000 C CNN
F 2 "" H 7550 1800 50  0001 C CNN
F 3 "" H 7550 1800 50  0001 C CNN
	1    7550 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 1700 7550 1800
Text HLabel 7650 1300 2    50   Output ~ 0
Key
Wire Wire Line
	7650 1300 7550 1300
Connection ~ 7550 1300
$Comp
L Device:R R42
U 1 1 5EAB8FAA
P 8400 1300
F 0 "R42" V 8193 1300 50  0000 C CNN
F 1 "1k" V 8284 1300 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 8330 1300 50  0001 C CNN
F 3 "~" H 8400 1300 50  0001 C CNN
	1    8400 1300
	0    1    1    0   
$EndComp
Text GLabel 8150 1300 0    50   Output ~ 0
SIDE
$Comp
L Device:C C52
U 1 1 5EAC1FEE
P 8650 1550
F 0 "C52" H 8535 1504 50  0000 R CNN
F 1 "100n" H 8535 1595 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 8688 1400 50  0001 C CNN
F 3 "~" H 8650 1550 50  0001 C CNN
	1    8650 1550
	1    0    0    1   
$EndComp
Wire Wire Line
	8150 1300 8250 1300
Wire Wire Line
	8550 1300 8650 1300
Wire Wire Line
	8650 1300 8650 1400
$Comp
L power:GND #PWR0168
U 1 1 5EAC640F
P 8650 1800
F 0 "#PWR0168" H 8650 1550 50  0001 C CNN
F 1 "GND" H 8655 1627 50  0000 C CNN
F 2 "" H 8650 1800 50  0001 C CNN
F 3 "" H 8650 1800 50  0001 C CNN
	1    8650 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 1700 8650 1800
Text HLabel 8750 1300 2    50   Output ~ 0
Side
Wire Wire Line
	8750 1300 8650 1300
Connection ~ 8650 1300
Text GLabel 4800 3450 2    50   Output ~ 0
LCD_RS
Text HLabel 4700 3450 0    50   BiDi ~ 0
SDA
Wire Wire Line
	4700 3450 4800 3450
Text HLabel 6500 2250 2    50   Output ~ 0
80m
Text HLabel 7650 2250 2    50   Output ~ 0
40m
Text HLabel 8750 2250 2    50   Output ~ 0
20m
Text HLabel 9900 2250 2    50   Output ~ 0
10m
$Comp
L Device:L_Core_Ferrite L5
U 1 1 5EAD75D4
P 6150 2250
F 0 "L5" V 6375 2250 50  0000 C CNN
F 1 "100u" V 6284 2250 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 6150 2250 50  0001 C CNN
F 3 "~" H 6150 2250 50  0001 C CNN
	1    6150 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C49
U 1 1 5EAD80E5
P 6400 2500
F 0 "C49" H 6285 2454 50  0000 R CNN
F 1 "100n" H 6285 2545 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 6438 2350 50  0001 C CNN
F 3 "~" H 6400 2500 50  0001 C CNN
	1    6400 2500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0169
U 1 1 5EAD886B
P 6400 2750
F 0 "#PWR0169" H 6400 2500 50  0001 C CNN
F 1 "GND" H 6405 2577 50  0000 C CNN
F 2 "" H 6400 2750 50  0001 C CNN
F 3 "" H 6400 2750 50  0001 C CNN
	1    6400 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L7
U 1 1 5EAD9775
P 7300 2250
F 0 "L7" V 7525 2250 50  0000 C CNN
F 1 "100u" V 7434 2250 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 7300 2250 50  0001 C CNN
F 3 "~" H 7300 2250 50  0001 C CNN
	1    7300 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C51
U 1 1 5EAD977F
P 7550 2500
F 0 "C51" H 7435 2454 50  0000 R CNN
F 1 "100n" H 7435 2545 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 7588 2350 50  0001 C CNN
F 3 "~" H 7550 2500 50  0001 C CNN
	1    7550 2500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0170
U 1 1 5EAD9789
P 7550 2750
F 0 "#PWR0170" H 7550 2500 50  0001 C CNN
F 1 "GND" H 7555 2577 50  0000 C CNN
F 2 "" H 7550 2750 50  0001 C CNN
F 3 "" H 7550 2750 50  0001 C CNN
	1    7550 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L8
U 1 1 5EAE0C0D
P 8400 2250
F 0 "L8" V 8625 2250 50  0000 C CNN
F 1 "100u" V 8534 2250 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 8400 2250 50  0001 C CNN
F 3 "~" H 8400 2250 50  0001 C CNN
	1    8400 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C53
U 1 1 5EAE0C17
P 8650 2500
F 0 "C53" H 8535 2454 50  0000 R CNN
F 1 "100n" H 8535 2545 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 8688 2350 50  0001 C CNN
F 3 "~" H 8650 2500 50  0001 C CNN
	1    8650 2500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0171
U 1 1 5EAE0C21
P 8650 2750
F 0 "#PWR0171" H 8650 2500 50  0001 C CNN
F 1 "GND" H 8655 2577 50  0000 C CNN
F 2 "" H 8650 2750 50  0001 C CNN
F 3 "" H 8650 2750 50  0001 C CNN
	1    8650 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L9
U 1 1 5EAE0C2B
P 9550 2250
F 0 "L9" V 9775 2250 50  0000 C CNN
F 1 "100u" V 9684 2250 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L7.0mm_D3.3mm_P2.54mm_Vertical_Fastron_MICC" H 9550 2250 50  0001 C CNN
F 3 "~" H 9550 2250 50  0001 C CNN
	1    9550 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C54
U 1 1 5EAE0C35
P 9800 2500
F 0 "C54" H 9685 2454 50  0000 R CNN
F 1 "100n" H 9685 2545 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 9838 2350 50  0001 C CNN
F 3 "~" H 9800 2500 50  0001 C CNN
	1    9800 2500
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR0172
U 1 1 5EAE0C3F
P 9800 2750
F 0 "#PWR0172" H 9800 2500 50  0001 C CNN
F 1 "GND" H 9805 2577 50  0000 C CNN
F 2 "" H 9800 2750 50  0001 C CNN
F 3 "" H 9800 2750 50  0001 C CNN
	1    9800 2750
	1    0    0    -1  
$EndComp
Text GLabel 5900 2250 0    50   Output ~ 0
80M
Wire Wire Line
	5900 2250 6000 2250
Wire Wire Line
	6300 2250 6400 2250
Wire Wire Line
	6400 2250 6400 2350
Connection ~ 6400 2250
Wire Wire Line
	6400 2250 6500 2250
Wire Wire Line
	6400 2650 6400 2750
Text GLabel 7050 2250 0    50   Output ~ 0
40M
Wire Wire Line
	7050 2250 7150 2250
Wire Wire Line
	7450 2250 7550 2250
Wire Wire Line
	7550 2250 7550 2350
Connection ~ 7550 2250
Wire Wire Line
	7550 2250 7650 2250
Wire Wire Line
	7550 2650 7550 2750
Wire Wire Line
	8150 2250 8250 2250
Wire Wire Line
	8550 2250 8650 2250
Wire Wire Line
	8650 2350 8650 2250
Connection ~ 8650 2250
Wire Wire Line
	8650 2250 8750 2250
Wire Wire Line
	8650 2650 8650 2750
Text GLabel 8150 2250 0    50   Output ~ 0
20M
Text GLabel 9300 2250 0    50   Output ~ 0
10M
Wire Wire Line
	9300 2250 9400 2250
Wire Wire Line
	9700 2250 9800 2250
Wire Wire Line
	9800 2250 9800 2350
Connection ~ 9800 2250
Wire Wire Line
	9800 2250 9900 2250
Wire Wire Line
	9800 2650 9800 2750
$Comp
L Transistor_BJT:2N3904 Q2
U 1 1 5EB1FD77
P 6600 3450
F 0 "Q2" H 6790 3496 50  0000 L CNN
F 1 "2N3904" H 6790 3405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline_Wide" H 6800 3375 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 6600 3450 50  0001 L CNN
	1    6600 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5EB20541
P 6150 3450
F 0 "R6" V 5943 3450 50  0000 C CNN
F 1 "10k" V 6034 3450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6080 3450 50  0001 C CNN
F 3 "~" H 6150 3450 50  0001 C CNN
	1    6150 3450
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3450 6400 3450
$Comp
L power:GND #GND0101
U 1 1 5EB25577
P 6700 3750
F 0 "#GND0101" H 6700 3500 50  0001 C CNN
F 1 "GND" H 6705 3577 50  0000 C CNN
F 2 "" H 6700 3750 50  0001 C CNN
F 3 "" H 6700 3750 50  0001 C CNN
	1    6700 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 3650 6700 3750
Text HLabel 5900 3450 0    50   Output ~ 0
TX5V
Wire Wire Line
	5900 3450 6000 3450
Wire Wire Line
	7000 3150 6700 3150
Wire Wire Line
	6700 3150 6700 3250
$Comp
L Device:R R5
U 1 1 5EB5CD61
P 5500 6600
F 0 "R5" H 5570 6646 50  0000 L CNN
F 1 "47k" H 5570 6555 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5430 6600 50  0001 C CNN
F 3 "~" H 5500 6600 50  0001 C CNN
	1    5500 6600
	1    0    0    -1  
$EndComp
Text GLabel 5600 6850 2    50   Input ~ 0
RST
$Comp
L power:+5VD #PWR0174
U 1 1 5EB5D2F4
P 5500 6150
F 0 "#PWR0174" H 5500 6000 50  0001 C CNN
F 1 "+5VD" H 5515 6323 50  0000 C CNN
F 2 "" H 5500 6150 50  0001 C CNN
F 3 "" H 5500 6150 50  0001 C CNN
	1    5500 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 6850 5500 6850
Wire Wire Line
	5500 6850 5500 6750
Wire Wire Line
	5500 6450 5500 6150
$Comp
L power:+5VD #PWR0175
U 1 1 5EB6F769
P 6450 4150
F 0 "#PWR0175" H 6450 4000 50  0001 C CNN
F 1 "+5VD" H 6465 4323 50  0000 C CNN
F 2 "" H 6450 4150 50  0001 C CNN
F 3 "" H 6450 4150 50  0001 C CNN
	1    6450 4150
	1    0    0    -1  
$EndComp
Text GLabel 6300 4350 0    50   Output ~ 0
LCD_CR
Text GLabel 6300 4750 0    50   Output ~ 0
LCD_D4
Text GLabel 6300 4850 0    50   Output ~ 0
LCD_D5
Text GLabel 6300 4950 0    50   Output ~ 0
LCD_D6
Text GLabel 6300 5050 0    50   Output ~ 0
LCD_D7
Text GLabel 6300 4650 0    50   Output ~ 0
LCD_RS
Text GLabel 6300 5150 0    50   Output ~ 0
LCD_EN
$Comp
L power:GND #PWR0176
U 1 1 5EB7A663
P 6450 5350
F 0 "#PWR0176" H 6450 5100 50  0001 C CNN
F 1 "GND" H 6455 5177 50  0000 C CNN
F 2 "" H 6450 5350 50  0001 C CNN
F 3 "" H 6450 5350 50  0001 C CNN
	1    6450 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4550 6450 5350
Wire Wire Line
	6550 5150 6300 5150
$Comp
L Connector:AudioJack2_Ground_Switch J5
U 1 1 5EB99F4C
P 7650 4950
F 0 "J5" H 7470 4968 50  0000 R CNN
F 1 "Key" H 7470 4877 50  0000 R CNN
F 2 "DM3MAT:Jack_3.5mm_Ledino_KB3SPRS_Horizontal" H 7650 5150 50  0001 C CNN
F 3 "~" H 7650 5150 50  0001 C CNN
	1    7650 4950
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0177
U 1 1 5EB9C52D
P 7650 5350
F 0 "#PWR0177" H 7650 5100 50  0001 C CNN
F 1 "GND" H 7655 5177 50  0000 C CNN
F 2 "" H 7650 5350 50  0001 C CNN
F 3 "" H 7650 5350 50  0001 C CNN
	1    7650 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 5250 7650 5350
Text GLabel 7350 4950 0    50   Input ~ 0
Dit
Wire Wire Line
	7350 4950 7450 4950
Text GLabel 7350 4750 0    50   Input ~ 0
Dah
Wire Wire Line
	7350 4750 7450 4750
Text GLabel 8500 5050 0    50   Output ~ 0
LCD_CR
$Comp
L power:+5VD #PWR0178
U 1 1 5EBE911F
P 8750 4800
F 0 "#PWR0178" H 8750 4650 50  0001 C CNN
F 1 "+5VD" H 8765 4973 50  0000 C CNN
F 2 "" H 8750 4800 50  0001 C CNN
F 3 "" H 8750 4800 50  0001 C CNN
	1    8750 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0179
U 1 1 5EBE97CE
P 8750 5350
F 0 "#PWR0179" H 8750 5100 50  0001 C CNN
F 1 "GND" H 8755 5177 50  0000 C CNN
F 2 "" H 8750 5350 50  0001 C CNN
F 3 "" H 8750 5350 50  0001 C CNN
	1    8750 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT_TRIM RV4
U 1 1 5EBEA4B1
P 8750 5050
F 0 "RV4" H 8680 5096 50  0000 R CNN
F 1 "10k" H 8680 5005 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Runtron_RM-065_Vertical" H 8750 5050 50  0001 C CNN
F 3 "~" H 8750 5050 50  0001 C CNN
	1    8750 5050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8750 5200 8750 5350
Wire Wire Line
	8500 5050 8600 5050
Wire Wire Line
	8750 4800 8750 4900
$Comp
L Connector_Generic:Conn_01x04 J10
U 1 1 5EC3331A
P 9700 5000
F 0 "J10" H 9780 4992 50  0000 L CNN
F 1 "ROT" H 9780 4901 50  0000 L CNN
F 2 "DM3MAT:Connector_BKL_1x04_P2.54mm_Horizontal" H 9700 5000 50  0001 C CNN
F 3 "~" H 9700 5000 50  0001 C CNN
	1    9700 5000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0180
U 1 1 5EC34046
P 9400 5400
F 0 "#PWR0180" H 9400 5150 50  0001 C CNN
F 1 "GND" H 9405 5227 50  0000 C CNN
F 2 "" H 9400 5400 50  0001 C CNN
F 3 "" H 9400 5400 50  0001 C CNN
	1    9400 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 5200 9400 5200
Wire Wire Line
	9400 5200 9400 5400
Text GLabel 9400 5100 0    50   Input ~ 0
ROT-A
Text GLabel 9400 5000 0    50   Input ~ 0
ROT-B
Text GLabel 9400 4900 0    50   Input ~ 0
ROT-M
Wire Wire Line
	9400 4900 9500 4900
Wire Wire Line
	9400 5000 9500 5000
Wire Wire Line
	9400 5100 9500 5100
$Comp
L power:+12V #PWR0111
U 1 1 5EC1BA2D
P 2700 6250
F 0 "#PWR0111" H 2700 6100 50  0001 C CNN
F 1 "+12V" H 2715 6423 50  0000 C CNN
F 2 "" H 2700 6250 50  0001 C CNN
F 3 "" H 2700 6250 50  0001 C CNN
	1    2700 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_Coaxial J13
U 1 1 5EC6708D
P 7200 3150
F 0 "J13" H 7300 3125 50  0000 L CNN
F 1 "Conn_Coaxial" H 7300 3034 50  0000 L CNN
F 2 "DM3MAT:RCA_RND_205-00698_Horizontal" H 7200 3150 50  0001 C CNN
F 3 " ~" H 7200 3150 50  0001 C CNN
	1    7200 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5EC7A060
P 7200 3750
F 0 "#PWR016" H 7200 3500 50  0001 C CNN
F 1 "GND" H 7205 3577 50  0000 C CNN
F 2 "" H 7200 3750 50  0001 C CNN
F 3 "" H 7200 3750 50  0001 C CNN
	1    7200 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 3350 7200 3750
$Comp
L Connector_Generic:Conn_01x10 LCD1
U 1 1 5EC99433
P 6750 4650
F 0 "LCD1" H 6830 4642 50  0000 L CNN
F 1 "LCD" H 6830 4551 50  0000 L CNN
F 2 "DM3MAT:Connector_BKL_1x10_P2.54mm_Horizontal" H 6750 4650 50  0001 C CNN
F 3 "~" H 6750 4650 50  0001 C CNN
	1    6750 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 4550 6450 4550
Wire Wire Line
	6550 4250 6450 4250
Wire Wire Line
	6450 4250 6450 4150
$Comp
L Device:R R43
U 1 1 5ECD18DA
P 5850 4450
F 0 "R43" V 5643 4450 50  0000 C CNN
F 1 "220" V 5734 4450 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P2.54mm_Vertical" V 5780 4450 50  0001 C CNN
F 3 "~" H 5850 4450 50  0001 C CNN
	1    5850 4450
	0    1    1    0   
$EndComp
$Comp
L power:+5VD #PWR017
U 1 1 5ECD1F2F
P 5600 4150
F 0 "#PWR017" H 5600 4000 50  0001 C CNN
F 1 "+5VD" H 5615 4323 50  0000 C CNN
F 2 "" H 5600 4150 50  0001 C CNN
F 3 "" H 5600 4150 50  0001 C CNN
	1    5600 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 4450 5600 4450
Wire Wire Line
	5600 4450 5600 4150
Wire Wire Line
	4000 2350 4100 2350
Wire Wire Line
	4000 2450 4100 2450
Wire Wire Line
	4000 2750 4100 2750
Wire Wire Line
	4000 2850 4100 2850
Wire Wire Line
	4000 4350 4100 4350
Wire Wire Line
	4000 4450 4100 4450
Text GLabel 4100 2550 2    50   Input ~ 0
MISO
Text GLabel 4100 2650 2    50   Input ~ 0
SCK
Text GLabel 4800 6650 2    50   Input ~ 0
Dit
Wire Wire Line
	4800 6650 4700 6650
Text GLabel 4800 6750 2    50   Input ~ 0
SCK
Text GLabel 4800 6550 2    50   Input ~ 0
MISO
Wire Wire Line
	4700 6550 4800 6550
Wire Wire Line
	4800 6750 4700 6750
Wire Wire Line
	4000 2550 4100 2550
Wire Wire Line
	4100 2650 4000 2650
Wire Wire Line
	6300 4650 6550 4650
Wire Wire Line
	6550 4750 6300 4750
Wire Wire Line
	6300 4850 6550 4850
Wire Wire Line
	6550 4950 6300 4950
Wire Wire Line
	6300 5050 6550 5050
Wire Wire Line
	6300 4350 6550 4350
Wire Wire Line
	6000 4450 6550 4450
$Comp
L power:GND #PWR0105
U 1 1 5EFDAA8C
P 3400 4950
F 0 "#PWR0105" H 3400 4700 50  0001 C CNN
F 1 "GND" H 3405 4777 50  0000 C CNN
F 2 "" H 3400 4950 50  0001 C CNN
F 3 "" H 3400 4950 50  0001 C CNN
	1    3400 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 5EFDB17A
P 4000 1750
F 0 "#PWR0114" H 4000 1500 50  0001 C CNN
F 1 "GND" H 4005 1577 50  0000 C CNN
F 2 "" H 4000 1750 50  0001 C CNN
F 3 "" H 4000 1750 50  0001 C CNN
	1    4000 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4850 3400 4950
Wire Wire Line
	3900 1650 4000 1650
Wire Wire Line
	4000 1650 4000 1750
$EndSCHEMATC
