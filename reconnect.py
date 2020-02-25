#!/usr/bin/python3
import serial
import time

def serialRead(serialPort):

    ser = None

    while(True):
        try:
            if(ser == None):
                ser = serial.Serial(serialPort, timeout = 2)

                ser.parity = "O"
                ser.bytesize = 7

                print("Reconnecting")

            l = ser.readline()
            while len(l) > 0:
                print(":" + l.decode("utf-8").strip())
                l = ser.readline()
            ser.close()
            ser=None
        except BaseException as e:
            if(not(ser == None)):
                ser.close()
                ser = None
                print("Disconnecting")

            print("No Connection", e)
            time.sleep(2)


serialRead("com6")