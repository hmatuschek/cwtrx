EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 6
Title "QRP CW TRX"
Date "2020-05-15"
Rev "2"
Comp "DM3MAT"
Comment1 "Receiver"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 3250 2450 1400 1100
U 5E45303E
F0 "Mixer" 50
F1 "rx_mixer.sch" 50
F2 "RF" U L 3250 2700 50 
F3 "I+" O R 4650 2700 50 
F4 "Q+" O R 4650 2900 50 
F5 "I-" O R 4650 3100 50 
F6 "Q-" O R 4650 3300 50 
F7 "VFO+I" I L 3250 3100 50 
F8 "VFO+Q" I L 3250 3200 50 
$EndSheet
$Sheet
S 6750 2450 1400 1100
U 5E510879
F0 "Audio" 50
F1 "rx_audio.sch" 50
F2 "NF" I L 6750 2700 50 
F3 "SideTone" I L 6750 3200 50 
F4 "TX5V" I L 6750 3300 50 
F5 "HP" O R 8150 2900 50 
$EndSheet
$Sheet
S 5000 2450 1400 1100
U 5E510ACC
F0 "Demod" 50
F1 "rx_demod.sch" 50
F2 "I+" I L 5000 2700 50 
F3 "I-" I L 5000 3100 50 
F4 "Q+" I L 5000 2900 50 
F5 "Q-" I L 5000 3300 50 
F6 "NF" O R 6400 2700 50 
$EndSheet
$Sheet
S 3250 3950 1400 1100
U 5E59D431
F0 "VFO" 50
F1 "rx_vfo.sch" 50
F2 "VFO+I" I L 3250 4350 50 
F3 "VFO-I" I L 3250 4550 50 
F4 "VFO+Q" I L 3250 4450 50 
F5 "VFO-Q" I L 3250 4650 50 
F6 "SDA" B R 4650 4450 50 
F7 "SCL" I R 4650 4550 50 
F8 "CLK0" O L 3250 4800 50 
F9 "CLK1" O L 3250 4900 50 
F10 "CLK2" O R 4650 4900 50 
$EndSheet
Wire Wire Line
	3250 4350 3150 4350
Wire Wire Line
	3150 4350 3150 3100
Wire Wire Line
	3150 3100 3250 3100
Wire Wire Line
	3050 3200 3250 3200
Wire Wire Line
	4650 2700 5000 2700
Wire Wire Line
	4650 2900 5000 2900
Wire Wire Line
	4650 3100 5000 3100
Wire Wire Line
	4650 3300 5000 3300
Wire Wire Line
	6400 2700 6750 2700
$Comp
L Connector_Generic:Conn_01x02 J1
U 1 1 5ED7AFE6
P 2400 2700
F 0 "J1" H 2318 2917 50  0000 C CNN
F 1 "RX-RF" H 2318 2826 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2400 2700 50  0001 C CNN
F 3 "~" H 2400 2700 50  0001 C CNN
	1    2400 2700
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5ED7DF4D
P 2700 3200
F 0 "#PWR0102" H 2700 2950 50  0001 C CNN
F 1 "GND" H 2705 3027 50  0000 C CNN
F 2 "" H 2700 3200 50  0001 C CNN
F 3 "" H 2700 3200 50  0001 C CNN
	1    2700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 2800 2700 3200
Wire Wire Line
	2600 2800 2700 2800
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5ED8E2FE
P 8650 2900
F 0 "J2" H 8730 2892 50  0000 L CNN
F 1 "HP" H 8730 2801 50  0000 L CNN
F 2 "DM3MAT:Connector_BKL_1x02_P2.54mm_Horizontal" H 8650 2900 50  0001 C CNN
F 3 "~" H 8650 2900 50  0001 C CNN
	1    8650 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5ED8E80B
P 8350 3100
F 0 "#PWR0103" H 8350 2850 50  0001 C CNN
F 1 "GND" H 8355 2927 50  0000 C CNN
F 2 "" H 8350 3100 50  0001 C CNN
F 3 "" H 8350 3100 50  0001 C CNN
	1    8350 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 3000 8350 3000
Wire Wire Line
	8350 3000 8350 3100
Wire Wire Line
	8150 2900 8450 2900
$Comp
L Connector_Generic:Conn_01x02 J7
U 1 1 5EDECEA1
P 3650 6450
F 0 "J7" V 3850 6450 50  0000 R CNN
F 1 "SW" V 3750 6450 50  0000 R CNN
F 2 "DM3MAT:Connector_BKL_1x02_P2.54mm_Horizontal" H 3650 6450 50  0001 C CNN
F 3 "~" H 3650 6450 50  0001 C CNN
	1    3650 6450
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J6
U 1 1 5EDED32A
P 3350 6750
F 0 "J6" H 3268 6967 50  0000 C CNN
F 1 "Supply" H 3268 6876 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3350 6750 50  0001 C CNN
F 3 "~" H 3350 6750 50  0001 C CNN
	1    3350 6750
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5EDF1635
P 3650 6950
F 0 "#PWR0106" H 3650 6700 50  0001 C CNN
F 1 "GND" H 3655 6777 50  0000 C CNN
F 2 "" H 3650 6950 50  0001 C CNN
F 3 "" H 3650 6950 50  0001 C CNN
	1    3650 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 6750 3650 6750
Wire Wire Line
	3650 6750 3650 6650
Wire Wire Line
	3550 6850 3650 6850
Wire Wire Line
	3650 6850 3650 6950
$Comp
L power:VCC #PWR0107
U 1 1 5EDF5BB5
P 4000 6650
F 0 "#PWR0107" H 4000 6500 50  0001 C CNN
F 1 "VCC" H 4017 6823 50  0000 C CNN
F 2 "" H 4000 6650 50  0001 C CNN
F 3 "" H 4000 6650 50  0001 C CNN
	1    4000 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 6650 3750 6750
Wire Wire Line
	3750 6750 4000 6750
Wire Wire Line
	4000 6750 4000 6650
Text GLabel 3150 4800 0    50   Input ~ 0
TX-OSC
Wire Wire Line
	6500 3200 6750 3200
Wire Wire Line
	6600 3300 6750 3300
Wire Wire Line
	2600 2700 3250 2700
$Comp
L Regulator_Linear:L7805 U10
U 1 1 5EDFD90D
P 5150 6550
F 0 "U10" H 5150 6792 50  0000 C CNN
F 1 "L7805" H 5150 6701 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 5175 6400 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 5150 6500 50  0001 C CNN
	1    5150 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L1
U 1 1 5EDFE632
P 6200 6550
F 0 "L1" V 6425 6550 50  0000 C CNN
F 1 "100u" V 6334 6550 50  0000 C CNN
F 2 "Inductor_THT:L_Axial_L5.3mm_D2.2mm_P7.62mm_Horizontal_Vishay_IM-1" H 6200 6550 50  0001 C CNN
F 3 "~" H 6200 6550 50  0001 C CNN
	1    6200 6550
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C41
U 1 1 5EDFFFDB
P 5550 6800
F 0 "C41" H 5665 6846 50  0000 L CNN
F 1 "100n" H 5665 6755 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 5588 6650 50  0001 C CNN
F 3 "~" H 5550 6800 50  0001 C CNN
	1    5550 6800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C40
U 1 1 5EE003E7
P 4650 6800
F 0 "C40" H 4535 6846 50  0000 R CNN
F 1 "100n" H 4535 6755 50  0000 R CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W2.0mm_P2.50mm" H 4688 6650 50  0001 C CNN
F 3 "~" H 4650 6800 50  0001 C CNN
	1    4650 6800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5EE08456
P 5550 7050
F 0 "#PWR012" H 5550 6800 50  0001 C CNN
F 1 "GND" H 5555 6877 50  0000 C CNN
F 2 "" H 5550 7050 50  0001 C CNN
F 3 "" H 5550 7050 50  0001 C CNN
	1    5550 7050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5EE086E6
P 5150 7050
F 0 "#PWR010" H 5150 6800 50  0001 C CNN
F 1 "GND" H 5155 6877 50  0000 C CNN
F 2 "" H 5150 7050 50  0001 C CNN
F 3 "" H 5150 7050 50  0001 C CNN
	1    5150 7050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5EE089F2
P 4650 7050
F 0 "#PWR09" H 4650 6800 50  0001 C CNN
F 1 "GND" H 4655 6877 50  0000 C CNN
F 2 "" H 4650 7050 50  0001 C CNN
F 3 "" H 4650 7050 50  0001 C CNN
	1    4650 7050
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR08
U 1 1 5EE08F2C
P 4650 6450
F 0 "#PWR08" H 4650 6300 50  0001 C CNN
F 1 "+12V" H 4665 6623 50  0000 C CNN
F 2 "" H 4650 6450 50  0001 C CNN
F 3 "" H 4650 6450 50  0001 C CNN
	1    4650 6450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C42
U 1 1 5EE0AE00
P 5950 6800
F 0 "C42" H 6068 6846 50  0000 L CNN
F 1 "10u" H 6068 6755 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 5988 6650 50  0001 C CNN
F 3 "~" H 5950 6800 50  0001 C CNN
	1    5950 6800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5EE0B8B0
P 5950 7050
F 0 "#PWR013" H 5950 6800 50  0001 C CNN
F 1 "GND" H 5955 6877 50  0000 C CNN
F 2 "" H 5950 7050 50  0001 C CNN
F 3 "" H 5950 7050 50  0001 C CNN
	1    5950 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 6550 5950 6550
Wire Wire Line
	4650 6450 4650 6550
Wire Wire Line
	4650 6550 4850 6550
Connection ~ 4650 6550
Wire Wire Line
	4650 6550 4650 6650
Wire Wire Line
	4650 6950 4650 7050
Wire Wire Line
	5150 6850 5150 7050
Wire Wire Line
	5550 6550 5550 6650
Connection ~ 5550 6550
Wire Wire Line
	5550 6550 5450 6550
Wire Wire Line
	5550 6950 5550 7050
Wire Wire Line
	5950 6950 5950 7050
Wire Wire Line
	5950 6550 5950 6650
Connection ~ 5950 6550
Wire Wire Line
	5950 6550 5550 6550
$Comp
L power:+5VA #PWR014
U 1 1 5EE137E3
P 6450 6450
F 0 "#PWR014" H 6450 6300 50  0001 C CNN
F 1 "+5VA" H 6465 6623 50  0000 C CNN
F 2 "" H 6450 6450 50  0001 C CNN
F 3 "" H 6450 6450 50  0001 C CNN
	1    6450 6450
	1    0    0    -1  
$EndComp
$Comp
L power:+5VD #PWR011
U 1 1 5EE13E27
P 5550 6450
F 0 "#PWR011" H 5550 6300 50  0001 C CNN
F 1 "+5VD" H 5565 6623 50  0000 C CNN
F 2 "" H 5550 6450 50  0001 C CNN
F 3 "" H 5550 6450 50  0001 C CNN
	1    5550 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 6450 5550 6550
Wire Wire Line
	6350 6550 6450 6550
Wire Wire Line
	6450 6550 6450 6450
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5EE6F656
P 9750 2750
F 0 "H1" V 9987 2753 50  0000 C CNN
F 1 "GND" V 9896 2753 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9750 2750 50  0001 C CNN
F 3 "~" H 9750 2750 50  0001 C CNN
	1    9750 2750
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5EE7A435
P 9750 3150
F 0 "H2" V 9987 3153 50  0000 C CNN
F 1 "GND" V 9896 3153 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9750 3150 50  0001 C CNN
F 3 "~" H 9750 3150 50  0001 C CNN
	1    9750 3150
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5EE7A833
P 9750 3550
F 0 "H3" V 9987 3553 50  0000 C CNN
F 1 "GND" V 9896 3553 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9750 3550 50  0001 C CNN
F 3 "~" H 9750 3550 50  0001 C CNN
	1    9750 3550
	0    -1   -1   0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5EE7AD6A
P 9750 3950
F 0 "H4" V 9987 3953 50  0000 C CNN
F 1 "GND" V 9896 3953 50  0000 C CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9750 3950 50  0001 C CNN
F 3 "~" H 9750 3950 50  0001 C CNN
	1    9750 3950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5EE7C32D
P 9950 4050
F 0 "#PWR015" H 9950 3800 50  0001 C CNN
F 1 "GND" H 9955 3877 50  0000 C CNN
F 2 "" H 9950 4050 50  0001 C CNN
F 3 "" H 9950 4050 50  0001 C CNN
	1    9950 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 2750 9950 2750
Wire Wire Line
	9950 2750 9950 3150
Wire Wire Line
	9850 3950 9950 3950
Connection ~ 9950 3950
Wire Wire Line
	9950 3950 9950 4050
Wire Wire Line
	9850 3550 9950 3550
Connection ~ 9950 3550
Wire Wire Line
	9950 3550 9950 3950
Wire Wire Line
	9850 3150 9950 3150
Connection ~ 9950 3150
Wire Wire Line
	9950 3150 9950 3550
$Sheet
S 6750 3950 1400 1100
U 5EBC9BB8
F0 "Ctrl" 50
F1 "rx_ctrl.sch" 50
F2 "SDA" B L 6750 4450 50 
F3 "SCL" O L 6750 4550 50 
F4 "TX5V" O R 8150 4150 50 
F5 "Key" O R 8150 4350 50 
F6 "Side" O L 6750 4100 50 
F7 "80m" O R 8150 4950 50 
F8 "40m" O R 8150 4850 50 
F9 "20m" O R 8150 4750 50 
F10 "10m" O R 8150 4650 50 
F11 "TXOC" U R 8150 4250 50 
$EndSheet
Text GLabel 2050 6800 2    50   Input ~ 0
TX-OSC
$Comp
L power:GND #PWR0104
U 1 1 5EBFFCE3
P 1950 6900
F 0 "#PWR0104" H 1950 6650 50  0001 C CNN
F 1 "GND" H 1955 6727 50  0000 C CNN
F 2 "" H 1950 6900 50  0001 C CNN
F 3 "" H 1950 6900 50  0001 C CNN
	1    1950 6900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 6700 1950 6900
Text GLabel 8450 4150 2    50   Input ~ 0
TX5V
Text GLabel 8450 4250 2    50   Input ~ 0
TX-OC
Text GLabel 8450 4350 2    50   Input ~ 0
Key
Wire Wire Line
	6750 4100 6500 4100
Wire Wire Line
	6500 3200 6500 4100
Wire Wire Line
	6600 3750 6600 3300
Wire Wire Line
	4650 4450 6750 4450
Wire Wire Line
	4650 4550 6750 4550
Wire Wire Line
	8150 4150 8250 4150
Wire Wire Line
	8250 3750 8250 4150
Wire Wire Line
	6600 3750 8250 3750
Connection ~ 8250 4150
Wire Wire Line
	8250 4150 8450 4150
$Comp
L power:GND #PWR01
U 1 1 5EC56F81
P 8900 5150
F 0 "#PWR01" H 8900 4900 50  0001 C CNN
F 1 "GND" H 8905 4977 50  0000 C CNN
F 2 "" H 8900 5150 50  0001 C CNN
F 3 "" H 8900 5150 50  0001 C CNN
	1    8900 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 4250 8450 4250
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 5EE2366F
P 9200 4550
F 0 "J4" H 9280 4542 50  0000 L CNN
F 1 "ToPA" H 9280 4451 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 9200 4550 50  0001 C CNN
F 3 "~" H 9200 4550 50  0001 C CNN
	1    9200 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4350 8900 4350
Wire Wire Line
	8900 4350 8900 5150
$Comp
L power:+5VD #PWR0112
U 1 1 5EE3486F
P 8900 4150
F 0 "#PWR0112" H 8900 4000 50  0001 C CNN
F 1 "+5VD" H 8915 4323 50  0000 C CNN
F 2 "" H 8900 4150 50  0001 C CNN
F 3 "" H 8900 4150 50  0001 C CNN
	1    8900 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9000 4250 8900 4250
Wire Wire Line
	8900 4250 8900 4150
$Comp
L Connector_Generic:Conn_01x02 J11
U 1 1 5EEF62BC
P 1650 6800
F 0 "J11" H 1568 6475 50  0000 C CNN
F 1 "TxOsc" H 1568 6566 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1650 6800 50  0001 C CNN
F 3 "~" H 1650 6800 50  0001 C CNN
	1    1650 6800
	-1   0    0    1   
$EndComp
Wire Wire Line
	1850 6800 2050 6800
Wire Wire Line
	1850 6700 1950 6700
Wire Wire Line
	3250 4800 3150 4800
Wire Wire Line
	8150 4350 8350 4350
Wire Wire Line
	9000 4450 8250 4450
Wire Wire Line
	8250 4450 8250 4150
Wire Wire Line
	9000 4550 8350 4550
Wire Wire Line
	8350 4550 8350 4350
Connection ~ 8350 4350
Wire Wire Line
	8350 4350 8450 4350
Wire Wire Line
	8150 4650 9000 4650
Wire Wire Line
	8150 4750 9000 4750
Wire Wire Line
	8150 4850 9000 4850
Wire Wire Line
	8150 4950 9000 4950
$Comp
L Device:Jumper_NO_Small JP1
U 1 1 5EBEE065
P 2800 4250
F 0 "JP1" V 2846 4298 50  0000 L CNN
F 1 "LSB" V 2755 4298 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Open_RoundedPad1.0x1.5mm" H 2800 4250 50  0001 C CNN
F 3 "~" H 2800 4250 50  0001 C CNN
	1    2800 4250
	0    1    -1   0   
$EndComp
$Comp
L Device:Jumper_NC_Small JP2
U 1 1 5EBF485F
P 3050 4250
F 0 "JP2" V 3004 4324 50  0000 L CNN
F 1 "USB" V 3095 4324 50  0000 L CNN
F 2 "Jumper:SolderJumper-2_P1.3mm_Bridged_RoundedPad1.0x1.5mm" H 3050 4250 50  0001 C CNN
F 3 "~" H 3050 4250 50  0001 C CNN
	1    3050 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	3050 3200 3050 4050
Wire Wire Line
	2800 4150 2800 4050
Wire Wire Line
	2800 4050 3050 4050
Connection ~ 3050 4050
Wire Wire Line
	3050 4050 3050 4150
Wire Wire Line
	3250 4450 3050 4450
Wire Wire Line
	3050 4450 3050 4350
Wire Wire Line
	3250 4650 2800 4650
Wire Wire Line
	2800 4650 2800 4350
$EndSCHEMATC