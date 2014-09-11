import RPi.GPIO as GPIO
import time
import read_weight

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)

while True:
	
	start = raw_input()

	GPIO.output(17, False)
	time.sleep(0.5)
	GPIO.output(17, True)
	time.sleep(1)

	valid, weight = read_weight.read_weight()

	if valid:
		print weight

GPIO.cleanup()
