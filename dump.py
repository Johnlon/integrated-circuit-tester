#!/usr/bin/python3
import serial

#import syslog
import time

import string
import sys
import threading
import time
#import Queue

#The following line is for serial over GPIO
port = 'com6' 

print("opening "+ port)

ard = serial.Serial(port,9600,timeout=1)

print("opened "+ port)

time.sleep(2) # wait for Arduino

def add_input(buf):
    while True:
        c = sys.stdin.read(1)
        buf.append(c)
        #print("GOT ", c, "<<" , buf)
        


def readSerial():
    msg = ard.readline() #(ard.inWaiting()) # read all characters in buffer
    while (1): #len(msg.rstrip()) > 0):
        resp = msg.decode("utf-8").strip()
        if (len(resp) > 0):
            print("> %s" % resp)
        msg = ard.readline() #(ard.inWaiting()) # read all characters in buffer
    
def foobar(ard):
    buf = []
    input_thread = threading.Thread(target=add_input, args=(buf,))
    input_thread.daemon = True
    input_thread.start()

    sinput_thread = threading.Thread(target=readSerial)
    sinput_thread.daemon = True
    sinput_thread.start()

    last_update = time.time()
    while True:
        
        # if (time.time()-last_update)>01.5:

        #     sys.stdout.write(".")
        #     readSerial()
        #     last_update = time.time()
            
        st = "".join(buf).rstrip()
        #print(">>" , st)
        
        if len(st) > 0:
            #print( "\ninput: [" , st, "]")
            
            ard.write(st.encode("utf-8"))
            ard.write("\n".encode("utf-8"))
            #print( "written")
            
            buf.clear()
foobar(ard)

print( "done")
foobar(ard)

i = 0

while (i < 400):
    # Serial write section

    #time.sleep(1) # I shortened this to match the new value in your Arduino code

    # Serial read section
    msg = ard.readline() #(ard.inWaiting()) # read all characters in buffer
    while (msg != 0):
        print(msg.decode("ascii").strip())
        msg = ard.readline() #(ard.inWaiting()) # read all characters in buffer
    
    
    
    i = i + 1
else:
    print("Exiting")

exit()
