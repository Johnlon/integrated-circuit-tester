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

def loadLastSerialPortConf():
    try:
        with open(home + "/.ictester") as f:
            content = f.readlines()

        if len(content)>0:
            return content[0].strip()
        else:
            None
    except:
        pass

def saveSerialPortConf(comNum):
    with open(home + "/.ictester", "w") as f:
        f.write(comNum)


def selectPort():
    default = loadLastSerialPortConf()

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

    saveSerialPortConf(com)

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
        sys.stdout.flush()

    def __init__(self, *args, **kwargs):
        self.responseHandler = None
        self.ard = None
        self.serialThreadRunning = False

    def open(self, serialPort, responseHandler = _recvResponse):
        self.responseHandler = responseHandler

        self.responseHandler("opening " + serialPort + "\n")
        if self.ard:
            try:
                self.ard.cancel_read()
                self.ard.close()

            except BaseException as e:
                self.responseHandler(str(e))

            time.sleep(1)

        self.ard = Serial(serialPort, 9600, timeout=1)
        self.ard.parity = "O"
        self.ard.bytesize = 7

        self.responseHandler("opened " + serialPort + "\n")
        self.startResponseThread()

    def close(self):
        self.ard.close()

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
        self.serialThreadRunning = True
        current = self.ard
        while self.ard and self.ard == current:
            msg = None
            try:
                msg = self.ard.readline()
                msg = msg.decode("utf-8")  # .strip()
            except BaseException as e:
                self.responseHandler("ERR: while reading from arduino : %s %s\n" % (type(e), str(e)))
                if msg:
                    self.responseHandler("ERR: read '%s' + \n" % msg)
                break

            if msg and (len(msg) > 0):
                self.responseHandler(msg)

        self.serialThreadRunning = False

    def startKeyboardThread(self):

        if not self.ard:
            raise Exception("Tester port not open")

        # thread to read local keyboard input
        input_thread = threading.Thread(target=self._keyboardInput)
        input_thread.daemon = False
        input_thread.start()

    def startResponseThread(self):

        if not self.ard:
            raise Exception("Tester port not open")

        # thread to read and print data from arduino
        sinput_thread = threading.Thread(target=self._readSerial)
        sinput_thread.daemon = True
        sinput_thread.start()

    def writeToTester(self, testcase):
        try:
            self.ard.write(testcase.encode("utf-8"))
            self.ard.write("\n".encode("utf-8"))
        except BaseException as x:
            self.responseHandler("EXCEPTION : " + str(x))


# Support for CTRL-C needs main thread still running.
# This is actually a crucial step, otherwise all signals sent to your program will be ignored.
# Adding an infinite loop using time.sleep() after the threads have been started will do the trick:
def main():
    com = selectPort()

    tester = TesterInterface()

    try:
        tester.open(serialPort=com)
        tester.startKeyboardThread()

        while True:
            if not tester.serialThreadRunning:
                print("reopening..")
                try:
                    tester.close()
                    tester.open(serialPort=com)
                    tester.startResponseThread()
                except BaseException as e:
                    pass
                    #print("error while reopening", e)

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