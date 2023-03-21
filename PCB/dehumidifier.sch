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
L Connector:Conn_01x02_Male J5
U 1 1 5CFD0AEF
P 5850 5900
F 0 "J5" V 6003 5713 50  0000 R CNN
F 1 "Conn_01x02_Male" V 5912 5713 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 5850 5900 50  0001 C CNN
F 3 "~" H 5850 5900 50  0001 C CNN
	1    5850 5900
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D1
U 1 1 5CFD0CBF
P 5950 5250
F 0 "D1" V 5904 5329 50  0000 L CNN
F 1 "D" V 5995 5329 50  0000 L CNN
F 2 "Diode_THT:D_5W_P12.70mm_Horizontal" H 5950 5250 50  0001 C CNN
F 3 "~" H 5950 5250 50  0001 C CNN
	1    5950 5250
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5CFD0D95
P 6350 5250
F 0 "R2" H 6420 5296 50  0000 L CNN
F 1 "330R" H 6420 5205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6280 5250 50  0001 C CNN
F 3 "~" H 6350 5250 50  0001 C CNN
	1    6350 5250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5CFD0E22
P 5350 5100
F 0 "R1" V 5143 5100 50  0000 C CNN
F 1 "1.2K" V 5234 5100 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 5280 5100 50  0001 C CNN
F 3 "~" H 5350 5100 50  0001 C CNN
	1    5350 5100
	0    1    1    0   
$EndComp
$Comp
L Device:C C4
U 1 1 5CFD0ED2
P 5350 5450
F 0 "C4" V 5098 5450 50  0000 C CNN
F 1 "2.0uF" V 5189 5450 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 5388 5300 50  0001 C CNN
F 3 "~" H 5350 5450 50  0001 C CNN
	1    5350 5450
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5CFD1031
P 6950 3700
F 0 "R4" V 6743 3700 50  0000 C CNN
F 1 "1K" V 6834 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6880 3700 50  0001 C CNN
F 3 "~" H 6950 3700 50  0001 C CNN
	1    6950 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 5700 5950 5400
Wire Wire Line
	5950 5400 6350 5400
Connection ~ 5950 5400
Wire Wire Line
	6350 5100 5950 5100
Wire Wire Line
	5950 5100 5500 5100
Connection ~ 5950 5100
Wire Wire Line
	5950 5400 5500 5450
Wire Wire Line
	5200 5450 5200 5100
$Comp
L power:GND #PWR015
U 1 1 5CFD22C8
P 5200 5100
F 0 "#PWR015" H 5200 4850 50  0001 C CNN
F 1 "GND" V 5205 4972 50  0000 R CNN
F 2 "" H 5200 5100 50  0001 C CNN
F 3 "" H 5200 5100 50  0001 C CNN
	1    5200 5100
	0    1    1    0   
$EndComp
Connection ~ 5200 5100
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 61B485EE
P 1700 3600
F 0 "J2" H 1808 3781 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1808 3690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1700 3600 50  0001 C CNN
F 3 "~" H 1700 3600 50  0001 C CNN
	1    1700 3600
	1    0    0    -1  
$EndComp
Text Notes 1500 3750 0    50   ~ 0
5V\nGND
$Comp
L power:PWR_FLAG #FLG01
U 1 1 61B4B01A
P 1900 3600
F 0 "#FLG01" H 1900 3675 50  0001 C CNN
F 1 "PWR_FLAG" V 1900 3728 50  0000 L CNN
F 2 "" H 1900 3600 50  0001 C CNN
F 3 "~" H 1900 3600 50  0001 C CNN
	1    1900 3600
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 61B4C559
P 1900 3700
F 0 "#FLG02" H 1900 3775 50  0001 C CNN
F 1 "PWR_FLAG" V 1900 3828 50  0000 L CNN
F 2 "" H 1900 3700 50  0001 C CNN
F 3 "~" H 1900 3700 50  0001 C CNN
	1    1900 3700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61B4CD6C
P 1900 3700
F 0 "#PWR02" H 1900 3450 50  0001 C CNN
F 1 "GND" V 1905 3572 50  0000 R CNN
F 2 "" H 1900 3700 50  0001 C CNN
F 3 "" H 1900 3700 50  0001 C CNN
	1    1900 3700
	0    -1   -1   0   
$EndComp
Connection ~ 1900 3700
$Comp
L power:+5V #PWR01
U 1 1 61B4EC2F
P 1900 3600
F 0 "#PWR01" H 1900 3450 50  0001 C CNN
F 1 "+5V" V 1915 3728 50  0000 L CNN
F 2 "" H 1900 3600 50  0001 C CNN
F 3 "" H 1900 3600 50  0001 C CNN
	1    1900 3600
	0    1    1    0   
$EndComp
Connection ~ 1900 3600
Text Notes 2150 4650 0    50   ~ 0
SensorHi\nSensorLo\nPump
Text Notes 2400 2100 0    63   ~ 0
Pump relay
Wire Wire Line
	4100 2850 3350 2850
$Comp
L power:GND #PWR012
U 1 1 5CFD2AF2
P 4100 2450
F 0 "#PWR012" H 4100 2200 50  0001 C CNN
F 1 "GND" H 4105 2277 50  0000 C CNN
F 2 "" H 4100 2450 50  0001 C CNN
F 3 "" H 4100 2450 50  0001 C CNN
	1    4100 2450
	-1   0    0    1   
$EndComp
Wire Wire Line
	6800 3700 3800 2650
$Comp
L Transistor_BJT:BC337 Q1
U 1 1 5CFD1101
P 4000 2650
F 0 "Q1" H 4191 2696 50  0000 L CNN
F 1 "BC337" H 4191 2605 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 4200 2575 50  0001 L CIN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bc337.pdf" H 4000 2650 50  0001 L CNN
	1    4000 2650
	1    0    0    -1  
$EndComp
$Comp
L Relay:SANYOU_SRD_Form_C K1
U 1 1 5CFD0818
P 3050 2650
F 0 "K1" V 3617 2650 50  0000 C CNN
F 1 "SANYOU_SRD_Form_C" V 3526 2650 50  0000 C CNN
F 2 "Relay_THT:Relay_SPDT_SANYOU_SRD_Series_Form_C" H 3500 2600 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 3050 2650 50  0001 C CNN
	1    3050 2650
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 61B6ED4A
P 2500 4550
F 0 "J3" H 2608 4831 50  0000 C CNN
F 1 "Conn_01x03_Male" H 2608 4740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2500 4550 50  0001 C CNN
F 3 "~" H 2500 4550 50  0001 C CNN
	1    2500 4550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 61B7A2BC
P 2750 2850
F 0 "#PWR03" H 2750 2700 50  0001 C CNN
F 1 "+5V" V 2765 2978 50  0000 L CNN
F 2 "" H 2750 2850 50  0001 C CNN
F 3 "" H 2750 2850 50  0001 C CNN
	1    2750 2850
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7100 3700 2700 4650
$Comp
L power:+5V #PWR05
U 1 1 61B7F398
P 5950 5700
F 0 "#PWR05" H 5950 5550 50  0001 C CNN
F 1 "+5V" V 5965 5828 50  0000 L CNN
F 2 "" H 5950 5700 50  0001 C CNN
F 3 "" H 5950 5700 50  0001 C CNN
	1    5950 5700
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 61B88B95
P 5850 6950
F 0 "J4" V 6003 6763 50  0000 R CNN
F 1 "Conn_01x02_Male" V 5912 6763 50  0000 R CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 5850 6950 50  0001 C CNN
F 3 "~" H 5850 6950 50  0001 C CNN
	1    5850 6950
	0    -1   -1   0   
$EndComp
$Comp
L Device:D D2
U 1 1 61B88D69
P 5950 6300
F 0 "D2" V 5904 6379 50  0000 L CNN
F 1 "D" V 5995 6379 50  0000 L CNN
F 2 "Diode_THT:D_5W_P12.70mm_Horizontal" H 5950 6300 50  0001 C CNN
F 3 "~" H 5950 6300 50  0001 C CNN
	1    5950 6300
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 61B88D73
P 6350 6300
F 0 "R5" H 6420 6346 50  0000 L CNN
F 1 "330R" H 6420 6255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 6280 6300 50  0001 C CNN
F 3 "~" H 6350 6300 50  0001 C CNN
	1    6350 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 61B88D7D
P 5350 6150
F 0 "R3" V 5143 6150 50  0000 C CNN
F 1 "1.2K" V 5234 6150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0309_L9.0mm_D3.2mm_P12.70mm_Horizontal" V 5280 6150 50  0001 C CNN
F 3 "~" H 5350 6150 50  0001 C CNN
	1    5350 6150
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 61B88D87
P 5350 6500
F 0 "C1" V 5098 6500 50  0000 C CNN
F 1 "2.0uF" V 5189 6500 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 5388 6350 50  0001 C CNN
F 3 "~" H 5350 6500 50  0001 C CNN
	1    5350 6500
	0    1    1    0   
$EndComp
Wire Wire Line
	5850 6750 5950 6450
Wire Wire Line
	5950 6450 6350 6450
Connection ~ 5950 6450
Wire Wire Line
	6350 6150 5950 6150
Wire Wire Line
	5950 6150 5500 6150
Connection ~ 5950 6150
Wire Wire Line
	5950 6450 5500 6500
Wire Wire Line
	5200 6500 5200 6150
$Comp
L power:GND #PWR04
U 1 1 61B88D99
P 5200 6150
F 0 "#PWR04" H 5200 5900 50  0001 C CNN
F 1 "GND" V 5205 6022 50  0000 R CNN
F 2 "" H 5200 6150 50  0001 C CNN
F 3 "" H 5200 6150 50  0001 C CNN
	1    5200 6150
	0    1    1    0   
$EndComp
Connection ~ 5200 6150
$Comp
L power:+5V #PWR06
U 1 1 61B88DA4
P 5950 6750
F 0 "#PWR06" H 5950 6600 50  0001 C CNN
F 1 "+5V" V 5965 6878 50  0000 L CNN
F 2 "" H 5950 6750 50  0001 C CNN
F 3 "" H 5950 6750 50  0001 C CNN
	1    5950 6750
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 5100 2700 4450
Wire Wire Line
	5950 6150 2700 4550
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 61B4E099
P 1400 1800
F 0 "J6" H 1508 1981 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1508 1890 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1400 1800 50  0001 C CNN
F 3 "~" H 1400 1800 50  0001 C CNN
	1    1400 1800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 61B4E8F3
P 1250 2150
F 0 "J1" H 1358 2331 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1358 2240 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1250 2150 50  0001 C CNN
F 3 "~" H 1250 2150 50  0001 C CNN
	1    1250 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2150 1600 1800
Wire Wire Line
	1450 2250 3350 2450
Wire Wire Line
	2750 2350 1600 1900
NoConn ~ 2750 2550
NoConn ~ 4850 6100
NoConn ~ 5950 6300
$EndSCHEMATC