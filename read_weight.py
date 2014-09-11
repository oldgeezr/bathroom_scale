import uartrpi

def voltage_diff_to_kg(voltage_diff):
	ratio = 10.00/106.00; # Calulated from bucket of water 
	return voltage_diff * ratio;

def read_weight():
	valid = False; # Should be false
	received_messages = 100;	
	voltage_diff = 0.00;

	# Initialize bathroom scale chip
	conn = uartrpi.UART_init();

	while True:
		
		# Read from avr
		voltage_diff = (voltage_diff + uartrpi.UART_receive(conn))/2; 
		received_messages -= 1;
		voltage_diff = uartrpi.UART_receive(conn); 

		# Wait for person to step onto bathroom scale
		# Aka a voltage swing exceeding a defined tolerance
		if voltage_diff > 400:
			break
		elif received_messages == 100:
			# If inactive in 10 sec: Shutdown:
			return valid, voltage_diff;

	valid = True;
	received_messages = 150;	

	# Average voltage diff over 6 seconds
	while received_messages > 0:
		# Read from avr
		voltage_diff = (voltage_diff + uartrpi.UART_receive(conn))/2; 
		print voltage_diff
		received_messages -= 1;
	
	# Convert voltage diff to kg and return
	return (valid, voltage_diff_to_kg(voltage_diff));
