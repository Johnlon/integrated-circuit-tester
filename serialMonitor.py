#!/usr/bin/python3
from serial import Serial
import time
import string
import sys
import threading
import time
import platform
from os import _exit
import traceback
import signal

## compat
try:
  import readline
except ImportError:
  import pyreadline as readline

com='5'

print("serial port number [%s] ? " % com)
c = sys.stdin.read(1)
if (c.strip() != ""):
    com = c

if (platform.system() == "Linux"):
    port = '/dev/ttyS' + com 
else:
    port = 'com' + com

print("opening "+ port)

ard = Serial(port,9600,timeout=0.05)

print("opened "+ port)

def keyboardInput():

    try:
        while True:
            line = sys.stdin.readline().strip()
            if (line == "q"):
                break

            # write to arduino
            if len(line) > 0:
                ard.write(line.encode("utf-8"))
                ard.write("\n".encode("utf-8"))
   
        print("QUIT")
        _exit(0)
    except BaseException as x:
        print("ERR READING STDIN\n")
        print(x)
        _exit(1)

def readSerial():
    try:
        msg = ard.readline()
        while (1): 
            resp = msg.decode("utf-8")#.strip()
            if (len(resp) > 0):
                print("%s" % resp, end = '')
                sys.stdout.flush()
            msg = ard.readline()
    except BaseException as x:
        print("ERR ON SERIAL\n")
        print(x)
        _exit(1)
    
def startThreads(ard):

    # thread to read local keyboard input
    input_thread = threading.Thread(target=keyboardInput)
    input_thread.daemon = False
    input_thread.start()

    # thread to read and print data from arduino
    sinput_thread = threading.Thread(target=readSerial)
    sinput_thread.daemon = True
    sinput_thread.start()
    
startThreads(ard)


# Support for CTRL-C needs main thread still running.
# This is actually a crucial step, otherwise all signals sent to your program will be ignored.
# Adding an infinite loop using time.sleep() after the threads have been started will do the trick: 
try:
    while True:
        time.sleep(1) 
except KeyboardInterrupt:
        _exit(1)   
except BaseException as x:
    try:
        print("ERR3 %s" % x)
        ard.close()
        sys.stdin.close()
        _exit(1)   
    except:
        _exit(1)   
