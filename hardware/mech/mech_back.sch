EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5EECCECE
P 2200 1650
F 0 "H1" V 2437 1653 50  0000 C CNN
F 1 "PL1" V 2346 1653 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 2200 1650 50  0001 C CNN
F 3 "~" H 2200 1650 50  0001 C CNN
	1    2200 1650
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5EECD0F7
P 2200 2050
F 0 "H2" V 2437 2053 50  0000 C CNN
F 1 "PL2" V 2346 2053 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 2200 2050 50  0001 C CNN
F 3 "~" H 2200 2050 50  0001 C CNN
	1    2200 2050
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5EECD60E
P 2200 2450
F 0 "H3" V 2437 2453 50  0000 C CNN
F 1 "PL3" V 2346 2453 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 2200 2450 50  0001 C CNN
F 3 "~" H 2200 2450 50  0001 C CNN
	1    2200 2450
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5EECDEC4
P 2200 2850
F 0 "H4" V 2437 2853 50  0000 C CNN
F 1 "PL4" V 2346 2853 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 2200 2850 50  0001 C CNN
F 3 "~" H 2200 2850 50  0001 C CNN
	1    2200 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5EED0B9A
P 2400 2950
F 0 "#PWR01" H 2400 2700 50  0001 C CNN
F 1 "GND" H 2405 2777 50  0000 C CNN
F 2 "" H 2400 2950 50  0001 C CNN
F 3 "" H 2400 2950 50  0001 C CNN
	1    2400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1650 2400 1650
Wire Wire Line
	2400 1650 2400 2050
Wire Wire Line
	2300 2050 2400 2050
Connection ~ 2400 2050
Wire Wire Line
	2400 2050 2400 2450
Wire Wire Line
	2300 2450 2400 2450
Connection ~ 2400 2450
Wire Wire Line
	2400 2450 2400 2850
Wire Wire Line
	2300 2850 2400 2850
Connection ~ 2400 2850
Wire Wire Line
	2400 2850 2400 2950
$EndSCHEMATC
