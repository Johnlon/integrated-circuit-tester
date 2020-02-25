#!/usr/bin/python3
from serial import Serial
import time
import string
from pathlib import Path
import sys
import threading
import time
import platform
from os import _exit

home = str(Path.home())

## compat
try:
    import readline
except ImportError:
    import pyreadline as readline

def loadDefault():
    try:
        with open(home + "/.ictester") as f:
            content = f.readlines()

        if len(content)>0:
            return content[0].strip()
        else:
            None
    except:
        pass

def saveDefault(comNum):
    with open(home + "/.ictester", "w") as f:
        f.write(comNum)


def selectPort():
    default = loadDefault()

    print("serial port number [%s] ? " % default, end="")
    sys.stdout.flush()

    c = sys.stdin.readline().strip()
    if c.strip() != "":
        com = c
    elif default:
        com=default
    else:
        print("must select port")
        return selectPort()

    saveDefault(com)

    if com.isdigit():
        if (platform.system() == "Linux"):
            port = '/dev/ttyS' + com
        else:
            port = 'com' + com
    else:
        port = com

    print("port is " + port)
    return port

class TesterInterface():

    def _recvResponse(resp):
        print("%s" % resp, end='')

    def __init__(self, serialPort, responseHandler = _recvResponse, *args, **kwargs):

        self.responseHandler = responseHandler
        self.ard = None

        self.port = serialPort

    def open(self):
        print("opening " + self.port)
        self.ard = Serial(self.port, 9600, timeout=0.05)
        print("opened " + self.port)
        self._startThreads()

    def close(self):
        self.ard.close()
        sys.stdin.close()

    def _keyboardInput(self):
        try:
            while True:
                line = sys.stdin.readline().strip()
                if (line == "q"):
                    break

                # write to arduino
                if len(line) > 0:
                    self.writeToTester(line)

            print("QUIT")
            _exit(0)
        except BaseException as x:
            print("ERR READING STDIN\n")
            print(x)
            _exit(1)

    def _readSerial(self):
        try:
            msg = self.ard.readline()
            while (1):
                resp = msg.decode("utf-8")  # .strip()
                if (len(resp) > 0):
                    try:
                        self.responseHandler(resp)
                    except Exception as e:
                        print("ERR in response handler for '%s'" % resp)
                        print("ERR: %s" % type(e) , e)
                        sys.stdout.flush()

                    sys.stdout.flush()
                msg = self.ard.readline()
        except BaseException as x:
            print("ERR ON SERIAL\n")
            print(x)
            _exit(1)

    def _startThreads(self):

        if not self.ard:
            raise Exception("Tester port not open")

        # thread to read local keyboard input
        input_thread = threading.Thread(target=self._keyboardInput)
        input_thread.daemon = False
        input_thread.start()

        # thread to read and print data from arduino
        sinput_thread = threading.Thread(target=self._readSerial)
        sinput_thread.daemon = True
        sinput_thread.start()

    def writeToTester(self, testcase):
        self.ard.write(testcase.encode("utf-8"))
        self.ard.write("\n".encode("utf-8"))



# Support for CTRL-C needs main thread still running.
# This is actually a crucial step, otherwise all signals sent to your program will be ignored.
# Adding an infinite loop using time.sleep() after the threads have been started will do the trick: 
def recvResponse(resp):
    print("%s" % resp, end='')


def main():
    com = selectPort()

    tester = TesterInterface(serialPort=com)

    try:
        tester.open();

        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        _exit(1)
    except BaseException as x:
        try:
            print("ERR3 %s" % x)
            tester.close()
            sys.stdin.close()
            _exit(1)
        except:
            _exit(1)


if __name__ == '__main__':
    main()