#!/usr/bin/env python
# -*- coding: utf-8 -*-

import serial
import uartrpi

# Initialize UART connection
conn = uartrpi.UART_init()

while(1):
	# Print 
	msg = uartrpi.UART_receive(conn)
	print msg

conn.close()
