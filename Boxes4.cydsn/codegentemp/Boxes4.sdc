# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Matthew Arbesfeld\Documents\PSoC Creator\BoxesUART\Boxes4.cydsn\Boxes4.cyprj
# Date: Sun, 26 Apr 2015 02:25:03 GMT
#set_units -time ns
create_clock -name {Rx_Left_SCBCLK(FFB)} -period 2166.6666666666665 -waveform {0 1083.33333333333} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {Rx_Right_SCBCLK(FFB)} -period 2166.6666666666665 -waveform {0 1083.33333333333} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyHFCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/hfclk}]]
create_generated_clock -name {Rx_Left_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 53 105} -nominal_period 2166.6666666666665 [list]
create_generated_clock -name {Rx_Right_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 53 105} -nominal_period 2166.6666666666665 [list]
create_generated_clock -name {Rx_Back_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 79 157} [list [get_pins {ClockBlock/udb_div_1}]]
create_generated_clock -name {Rx_Front_IntClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 79 157} [list [get_pins {ClockBlock/udb_div_3}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CySYSCLK} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/sysclk}]]
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyLFCLK} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyRouted1} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/dsi_in_0}]]


# Component constraints for C:\Users\Matthew Arbesfeld\Documents\PSoC Creator\BoxesUART\Boxes4.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Matthew Arbesfeld\Documents\PSoC Creator\BoxesUART\Boxes4.cydsn\Boxes4.cyprj
# Date: Sun, 26 Apr 2015 02:24:56 GMT
