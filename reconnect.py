#!/usr/bin/python3
import serial
import time
import queue
import tkinter as tk

def serialLoop(serialPortVar, responseHandler, queue):
    # serialPortVar is a stringVar
    # queue is an instance of Queue class
    ser = None
    current = serialPortVar#.get()

    while True:
        try:
            port = serialPortVar#.get()
            if port != current:
                current=port
                ser.close()
                ser = None
            else:
                if ser is None:
                    responseHandler("Connecting: %s\n" % port)
                    ser = serial.Serial(port, timeout = 0.05)
                    # ser.parity = "O"
                    # ser.bytesize = 8

                    # give arduino a chance to respond
                    time.sleep(2)

                l = ser.readline()
                while len(l) > 0:
                    line = l.decode("utf-8")
                    if line.startswith("READY"):
                        responseHandler("\n")
                    else:
                        responseHandler(line)
                    l = ser.readline()

                # only send one line at a time then process all responses
                if not queue.empty():
                    w = queue.get()
                    responseHandler("SEND: " + w.strip()+ "\n")
                    ser.write(w.encode("utf-8"))
                    ser.write("\n".encode("utf-8"))

                    # wait for some response
                    while ser.in_waiting==0:
                        time.sleep(0.05)

        except BaseException as e:
            if ser is not None:
                responseHandler("Disconnecting: %s\n" % str(e))
                ser.close()
                ser = None
            else:
                responseHandler("No Connection: %s\n" % str(e))
            time.sleep(1)


def resp(a):
    print(a, end='')

q = queue.Queue()
q.put("?")
q.put("1")

port = "com6"
serialLoop(port, resp, q)