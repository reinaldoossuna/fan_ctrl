#!/usr/bin/python
# -*- coding: utf-8 -*-
import logging
import time
import sys
import ASUS.GPIO as GPIO
from control import Control

# Configuration
FAN_PIN     = 238
WAIT_TIME   = 1
PWM_FREQ    = 10

c = Control(configfile="fan_control.config")

# Setup GPIO pin
GPIO.setmode(GPIO.ASUS)
GPIO.setwarnings(False)

GPIO.setup(FAN_PIN, GPIO.OUT)
FAN = GPIO.PWM(FAN_PIN, PWM_FREQ)
FAN.start(c.duty_min)

try:
    while True:
        if c.has_hysterie():
            # Calculate desired FAN speed
            c.get_new_duty()
        FAN.ChangeDutyCycle(c.curr_duty)
        # Wait until next refresh
        time.sleep(WAIT_TIME)

# If a keyboard interrupt occurs, the GPIO is set to 0 and the program exits.
except KeyboardInterrupt:
    if c.is_logging:
        logging.error("STOPED BY KEYBOARD")

    GPIO.cleanup()
    sys.exit()

except Exception as exception:
    if c.is_logging:
        logging.error(str(exception) + "Exception occurred")

    GPIO.cleanup()
    sys.exit()
