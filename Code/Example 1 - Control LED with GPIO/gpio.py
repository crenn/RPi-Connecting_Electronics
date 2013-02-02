import time
import RPi.GPIO as GPIO

# Setting library to using BCM GPIO 00..nn numbers GPIO.setmode(GPIO.BCM)
GPIO.setmode(GPIO.BCM)

# Setting the GPIO to an output
GPIO.setup(18, GPIO.OUT)

# Turning the GPIO On and Off 4 times
for x in range(0, 4):
	GPIO.output(18, True)
	time.sleep(1)
	GPIO.output(18, False)
	time.sleep(1)

# Return the GPIO to being an input
GPIO.setup(18, GPIO.IN)