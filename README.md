uart_rpi_chip
=============

Hooking my bathroom scale to a Raspberry Pi for logging weight. The logged
data is linked to an ID from an RFID reader and sent to a server/database.

The weighing is initialized by the RFID reader.

A simple circuit of 4 load cells (strain gauges) in two wheatstone bridges, 
an instrumentation amplifier and a microcontroller calculates the weight. 
