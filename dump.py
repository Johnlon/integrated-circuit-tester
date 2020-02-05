#!/usr/bin/python
import serial
#import syslog
import time

#The following line is for serial over GPIO
port = 'com6' 

ard = serial.Serial(port,9600,timeout=5)
time.sleep(2) # wait for Arduino

i = 0

while (i < 400):
    # Serial write section

    #time.sleep(1) # I shortened this to match the new value in your Arduino code

    # Serial read section
    msg = ard.readline() #(ard.inWaiting()) # read all characters in buffer
    print(msg.decode("ascii").strip())
    i = i + 1
else:
    print("Exiting")
exit()
