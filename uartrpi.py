import serial

# UART initialize
def UART_init():

	# RPi uart, baudrate=9600, no parity, 1 stop bit
	conn = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=1)
	return conn

# Read bytes from avr
def UART_receive(conn):

	# Read input
	bytes = conn.readline()	
	
	# Array: [msB, lsB, '\n']  
	extract = list(bytearray(bytes))
	
	lsB = extract[1]; # lsB int value

	bit = 8
	msB = 0

	# Convert msB to int value
	for i in reversed(bin(extract[0])[2:]):
		if i:
			msB += 2**bit
			bit -= 1

	return  msB + lsB
