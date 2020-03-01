import tkinter as tk
from tkinter import *
import tkinter.ttk as ttk
from tkinter.ttk import *
from tkinter.messagebox import showerror
import serial
import threading
import time
import queue
import os

if os.name == 'nt':  # sys.platform == 'win32':
    from serial.tools.list_ports_windows import comports
elif os.name == 'posix':
    from serial.tools.list_ports_posix import comports
    #~ elif os.name == 'java':
else:
    raise ImportError("Sorry: no implementation for your platform ('{}') available".format(os.name))

def quit(event):
    print("Double Click, so let's stop")
    import sys;
    sys.exit()


class TextScrollCombo(ttk.Frame):

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        # ensure a consistent GUI size

        # implement stretchability
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)

        # create a Text widget
        self.txt = tk.Text(self)
        self.txt.grid(row=0, column=0, sticky="nsew", padx=2, pady=2)

        # create a Scrollbar and associate it with txt
        scrollb = ttk.Scrollbar(self, command=self.txt.yview)
        scrollb.grid(row=0, column=1, sticky='nsew')
        self.txt['yscrollcommand'] = scrollb.set

class Zif(Frame):
    USE_v1_HACK = True

    socketWidth = 200

    pins = 24

    rows = pins / 2

    pitchVert = 30

    marginSide = 20
    marginTop = 100
    marginBot = 50

    labelSize = 30

    pinHeight = 25
    pinWidth = 50

    selectorSize = 100  # width fine tuned to only show first letter of selection when collapsed
    selectorHeight = 25
    patternHeight = 30

    testButtonSize = 30

    height = marginTop + marginBot + (pitchVert * (rows - 1))
    width = 250

    zifPosX = 150
    zifPosY = 30

    defaultOption = "S  Sample"
    options = ["0  in", "1  in", "V  in", "G  in", "C  in", "L  expected", "H  expected", "Z  expected",
               "X  don't care",
               "?  test", defaultOption]

    surfaceCol = "#EEE"

    def __init__(self, parent, *args, **kwargs):
        self.pinLabels = {}
        self.pinControls = {}
        self.pinCodes = {}
        self.testPattern = StringVar()
        self.autoTest = BooleanVar()
        self.autoTest.set(True)

        self.comPortVar = StringVar()
        self.arduinoInputQueue = queue.Queue()

        tk.Frame.__init__(self, parent)
        self.initUI()
        self.startResponseThread()

    def initUI(self):

        spaceUnderZif = self.zifPosY + 100
        self.config(height=Zif.height + spaceUnderZif, width=Zif.width, background="white", borderwidth=0,
                    highlightthickness=0)

        canvasTop = Canvas(self, height=Zif.height + spaceUnderZif, width=Zif.width * 2, background="white",
                           borderwidth=1,
                           highlightthickness=0)
        canvasTop.pack(side=LEFT, padx=10, pady=20)

        canvasTop.create_rectangle(Zif.zifPosX + 2, Zif.zifPosY + 55, Zif.zifPosX + Zif.socketWidth,
                                   Zif.zifPosY + Zif.height, width=1, outline="black", fill=Zif.surfaceCol);
        canvasTop.create_rectangle(Zif.zifPosX + 20, Zif.zifPosY + 20, Zif.zifPosX + 40, Zif.zifPosY + 80, width=1,
                                   outline="black", fill="#F7F7F7");
        canvasTop.create_rectangle(Zif.zifPosX + 18, Zif.zifPosY + 5, Zif.zifPosX + 42, Zif.zifPosY + 30, width=1,
                                   outline="black", fill="#EEE");

        self.patternField(canvasTop)
        self.portSelector(canvasTop)
        self.testButton(canvasTop)
        self.autoCheckbox(canvasTop)
        self.macros(canvasTop)

        for pin in range(0, self.pins):
            self.pinNumLabel(canvasTop, x=self.labelPosH(pin), y=self.pinPosV(pin), text=str(pin + 1),
                    width=Zif.labelSize, height=Zif.labelSize)

            self.pin(canvasTop, x=self.pinPosH(pin), y=self.pinPosV(pin),
                     width=Zif.pinWidth, height=Zif.pinHeight, pin=pin)

            self.optionMenu(canvasTop, x=self.selectorPosH(pin), y=self.pinPosV(pin),
                    width=Zif.selectorSize, height=Zif.selectorHeight, pin=pin)

        # right hand log pane
        self.comms = TextScrollCombo(self, height=30, width=40)
        self.comms.txt.insert(tk.END, "Serial Log File:\n")
        self.comms.pack(fill=BOTH, expand=1)

        #
        canvasTop.pack(anchor="nw")
        self.pack(fill=BOTH, expand=1)
        self.repaintPattern()

    def startResponseThread(self):

        # thread to read and print data from arduino
        sinput_thread = threading.Thread(target=self.serialLoop)
        sinput_thread.setDaemon(True)
        sinput_thread.start()

    def writeLog(self, txt):
        self.comms.txt.insert(tk.END, txt)
        self.comms.txt.see("end")

    def rowOfPin(self, pin):
        if pin < (self.pins / 2):
            return pin
        else:
            return self.pins - pin - 1

    def pinPosV(self, pin):
        return self.zifPosY + Zif.marginTop + (self.pitchVert * self.rowOfPin(pin))

    def pinPosH(self, pin):
        if pin < (self.pins / 2):
            return Zif.zifPosX + Zif.marginSide
        else:
            return Zif.zifPosX + Zif.socketWidth - Zif.marginSide - Zif.pinWidth

    def labelPosH(self, pin):
        gap = 1
        if pin < (self.pins / 2):
            return Zif.zifPosX + Zif.marginSide + Zif.pinWidth + gap
        else:
            return Zif.zifPosX + Zif.socketWidth - Zif.marginSide - Zif.labelSize - Zif.pinWidth - gap

    def selectorPosH(self, pin):
        gap = 20
        if pin < (self.pins / 2):
            return Zif.zifPosX - Zif.selectorSize - gap
        else:
            return Zif.zifPosX + Zif.socketWidth + gap

    def macros(self, master):

        def macro(text, y, code, fn=self.runTest):
            def onClick():
                if code:
                    for pin in sorted(self.pinCodes.keys()):
                        self.pinCodes[pin].set(code)
                    self.repaintPattern()
                fn()

            width = 60
            xpos = Zif.zifPosX + self.socketWidth + 20

            f = Frame(master, height=20, width=width)
            f.pack_propagate(0)  # don't shrink
            f.pack()
            f.place(x=xpos, y=y)

            b = tk.Button(f, text=text, bg="bisque2", command=onClick)
            b.pack(fill=BOTH, expand=1)

        ypos=0
        macro("All 1", ypos+0, "1")
        macro("All 0", ypos+21, "0")
        macro("All S", ypos+42, "S")
        macro("All Z", ypos+63, "Z")
        macro("Identify", ypos+84, None, fn=self.runIdentify)

    def testButton(self, master):
        def onClick():
            self.runTest()

        width = 60
        xpos = Zif.zifPosX + 80

        f = Frame(master, height=30, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=xpos, y=2)

        b = tk.Button(f, text="Test", bg="bisque2", command=onClick)
        b.pack(fill=BOTH, expand=1)

    def autoCheckbox(self, master):
        xpos = Zif.zifPosX + 150
        cb = tk.Checkbutton(master, text="Auto", height=1, width=3, bg="white", variable=self.autoTest)
        cb.place(x=xpos, y=4)

    def optionMenu(self, master, x, y, height, width, pin):

        f = Frame(master, height=height, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=x, y=y)

        if self.USE_v1_HACK and (pin == 0 or pin == 23):
            o = Label(f, text="-", font=("courier", 9), background=Zif.surfaceCol, borderwidth=0, anchor="center")
            o.pack(fill=BOTH, expand=1)
        else:
            def onClick(code):
                self.repaintPattern()
                if self.autoTest.get():
                    self.runTest()

            variable = StringVar()
            b = OptionMenu(f, variable, Zif.defaultOption, command=onClick, *self.options)
            b["menu"].config(bg="white", font=("courier", 9), activebackground="cornflower blue", selectcolor="green")
            b.pack(fill=BOTH, expand=1)

            self.pinCodes[pin] = variable

    def pinNumLabel(self, master, x, y, text, height, width):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=x, y=y)

        o = Label(f, text=text, font=("courier", 9), background=Zif.surfaceCol, borderwidth=0, anchor="center")
        o.pack(fill=BOTH, expand=1)

    def pin(self, master, x, y, height, width, pin):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=x, y=y)

        pinLabelVariable = StringVar()
        pinLabelVariable.set("")

        o = Label(f, textvariable=pinLabelVariable, font=("courier", 9), background="#DDD", borderwidth=2,
                  relief="solid", anchor="center")
        o.pack(fill=BOTH, expand=1)

        self.pinLabels[pin] = pinLabelVariable
        self.pinControls[pin] = o

    def patternField(self, master):
        f = Frame(master, width=Zif.width, height=Zif.patternHeight)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=Zif.zifPosX, y=self.zifPosY + Zif.height + 20)

        o = Entry(f, font=("courier", 9),
                  textvariable=self.testPattern, width=Zif.width,
                  justify=CENTER)
        o.pack(fill=BOTH, expand=1)

    def getPorts(self):
        iterator = sorted(comports(include_links=False))
        ports=[]
        for n, (port, desc, hwid) in enumerate(iterator, 1):
            ports.append(port)
        return ports

    def portSelector(self, master):

        def onClick(code):
            self.comPortVar.set(code)

        ports = self.getPorts()
        # ports = ["com5", "com6"]
        f = Frame(master, width=Zif.width, height=Zif.patternHeight)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=Zif.zifPosX, y=self.zifPosY + Zif.height + 60)

        ignored = StringVar()
        lastPort = "choose port"

        b = OptionMenu(f, ignored, lastPort, command=onClick, *ports)
        b["menu"].config(bg="white", font=("courier", 9), activebackground="cornflower blue", selectcolor="green")
        b.pack(fill=BOTH, expand=1)

    def repaintPattern(self):
        pattern = ""

        for pin in sorted(self.pinCodes.keys()):
            code = self.pinCodes[pin].get()[0]
            pattern = pattern + code

        half = int(len(pattern)/2)
        split1 = pattern[0:half]
        split2 = pattern[half: len(pattern)]
        cut = split1 + "/" + split2
        self.testPattern.set(cut)

    def runTest(self):
        port = self.comPortVar.get()
        if port == "":
            self.writeLog("Port not open yet\n")
            return

        pat = "t:" + self.testPattern.get()
        self.arduinoInputQueue.put(pat)

    def runIdentify(self):
            port = self.comPortVar.get()
            if port == "":
                self.writeLog("Port not open yet\n")
                return

            self.arduinoInputQueue.put("i")

    def paintResult(self, result):
        self.writeLog("%s" % result)
        if result.startswith("ERROR"):
            showerror(title="Error Response", message=result)
        elif result.startswith("RESULT"):
            resp = result.replace("RESULT : ", "").strip()
            for ipin in range(0, self.pins):
                fg = "black"
                code = resp[ipin]
                incode = "-"
                if ipin in self.pinCodes:
                    incode = self.pinCodes[ipin].get()[0]

                if code == "-":
                    # not a pin
                    self.pinControls[ipin].configure(background="gray95", foreground=fg)
                elif code == "_":
                    # was in input
                    code = incode
                    color = "white"
                    if code == "V":  # was an assertion to not ok
                        fg = "red"
                    elif code == "G":
                        fg = "green"
                    elif code == "C":
                        fg = "blue"
                    elif code == "1":
                        fg = "red"
                    elif code == "0":
                        fg = "green"
                    self.pinControls[ipin].configure(background=color, foreground=fg)
                elif code == ".":
                    # was ok
                    code = incode
                    self.pinControls[ipin].configure(background="pale green", foreground=fg)
                else:
                    # might be ok cos this could be a "S" or "?"
                    color = "yellow"
                    if incode in "HLZ":  # was an assertion to not ok
                        color = "red"
                    self.pinControls[ipin].configure(background=color, foreground=fg)

                self.pinLabels[ipin].set(code)

    def serialLoop(self):

        ser = None
        current = self.comPortVar.get()
        if "" == current:
            self.writeLog("Port not open yet\n")

        while True:
            try:
                port = self.comPortVar.get()
                if port == "":
                    time.sleep(0.1)
                    continue

                if port != current:
                    current = port
                    if ser:
                        ser.close()
                    ser = None
                else:
                    if ser is None:
                        self.writeLog("Connecting: %s\n" % port)
                        ser = serial.Serial(port, timeout=0.05)

                        # give arduino a chance to respond
                        time.sleep(0.1)

                    l = ser.readline()
                    while len(l) > 0:
                        line = l.decode("utf-8")
                        self.paintResult(line)
                        l = ser.readline()

                    # only send one line at a time then process all responses
                    if not self.arduinoInputQueue.empty():
                        w = self.arduinoInputQueue.get()
                        self.writeLog(w.strip() + "\n")
                        ser.write(w.encode("utf-8"))
                        ser.write("\n".encode("utf-8"))

                        # wait for some response
                        while ser.in_waiting == 0:
                            time.sleep(0.05)

            except BaseException as e:
                if ser is not None:
                    self.writeLog("Disconnecting: %s\n" % str(e))
                    ser.close()
                    ser = None
                else:
                    self.writeLog("No Connection: %s\n" % str(e))
                    time.sleep(2)


def main():
    root = Tk()

    root.title("Exploratory Tool")

    ex = Zif(root)
    ex.pack()

    # root.geometry("600x450+150+150")

    root.mainloop()


if __name__ == '__main__':
    main()
