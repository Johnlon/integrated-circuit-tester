import tkinter as tk
from tkinter import *
import functools
import tkinter.ttk as ttk
from tkinter.ttk import *
from tkinter.messagebox import showerror

from serialMonitor import TesterInterface, loadDefault, saveDefault


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

    selectorSize = 25
    selectorHeight = 25
    patternHeight = 30

    testButtonSize = 30

    height = marginTop + marginBot + (pitchVert * (rows - 1))
    width = 200

    zifPosX = 100
    zifPosY = 0
    options = ["?", "0", "1", "V", "G", "C", "L", "H", "Z", "X", "S"]

    surfaceCol = "#F7F7F7"

    def __init__(self, parent, *args, **kwargs):
        self.pinLabels = {}
        self.pinControls = {}
        self.pinCodes = {}
        self.serialMon = None
        self.testPattern = StringVar()
        self.autoTest = BooleanVar()

        tk.Frame.__init__(self, parent)
        self.initUI()

    def initUI(self):

        self.config(height=Zif.height, width=Zif.width, background="white", borderwidth=0, highlightthickness=0)

        canvasTop = Canvas(self, height=Zif.height + 50, width=Zif.width * 2, background="white", borderwidth=1,
                           highlightthickness=0)
        canvasTop.pack(side=LEFT,padx=10, pady=20)

        canvasTop.create_rectangle(Zif.zifPosX + 2, Zif.zifPosY + 55, Zif.zifPosX + Zif.socketWidth,
                                   Zif.zifPosY + Zif.height, width=1, outline="black", fill=Zif.surfaceCol);
        canvasTop.create_rectangle(Zif.zifPosX + 20, Zif.zifPosY + 20, Zif.zifPosX + 40, Zif.zifPosY + 80, width=1,
                                   outline="black", fill="#EEE");
        canvasTop.create_rectangle(Zif.zifPosX + 18, Zif.zifPosY + 5, Zif.zifPosX + 42, Zif.zifPosY + 30, width=1,
                                   outline="black", fill="#EEE");

        self.patternField(canvasTop)
        self.testButton(canvasTop)
        self.autoCheckbox(canvasTop)

        for pin in range(0, self.pins):
            self.label(canvasTop, x=self.labelPosH(pin), y=self.pinPosV(pin), text=str(pin + 1), width=Zif.labelSize,
                       height=Zif.labelSize)

            self.pin(canvasTop, x=self.pinPosH(pin), y=self.pinPosV(pin),
                     width=Zif.pinWidth, height=Zif.pinHeight, pin=pin)

            self.optionMenu(canvasTop, x=self.selectorPosH(pin), y=self.pinPosV(pin),
                            width=Zif.selectorSize, height=Zif.selectorHeight, pin=pin)


        self.comms = TextScrollCombo(self, height=30, width=80)
        self.comms.txt.insert(tk.END, "Serial Log File:\n")

        self.comms.pack(fill=BOTH, expand=1)
        canvasTop.pack(anchor="nw")

        self.pack(fill=BOTH,  expand=1)

        self.repaintPattern()

    def writeLog(self, txt):
        self.comms.txt.insert(tk.END,txt)
        self.comms.txt.see("end")


    def rowOfPin(self, pin):
        if pin < (self.pins / 2):
            return pin
        else:
            return self.pins - pin - 1

    def pinPosV(self, pin):
        return Zif.marginTop + (self.pitchVert * self.rowOfPin(pin))

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

    def testButton(self, master):
        def onClick():
            self.runTest()

        xpos = Zif.zifPosX + Zif.socketWidth + 30
        self.button(master, x=xpos, y=25, text="Test", height=30, width=50, command=onClick, style='W.TButton')

    def autoCheckbox(self, master):
        xpos = Zif.zifPosX + Zif.socketWidth + 30
        cb = tk.Checkbutton(master, text="Auto", height=1, width=3, background="white", variable=self.autoTest)
        cb.place(x=xpos, y=25 + 30)

    def button(self, master, x, y, text, height, width, command, style):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=x, y=y)

        b = Button(f, text=text, style=style, command=command)
        b.pack(fill=BOTH, expand=1)
        return b

    def optionMenu(self, master, x, y, height, width, pin):

        def onClick(code):
            self.repaintPattern()
            if self.autoTest.get():
                self.runTest()

        f = Frame(master, height=height, width=width)
        f.pack_propagate(0)  # don't shrink
        f.pack()
        f.place(x=x, y=y)


        if self.USE_v1_HACK and (pin == 0 or pin == 23):
            o = Label(f, text="-", font=("courier", 9), background=Zif.surfaceCol, borderwidth=0, anchor="center")
            o.pack(fill=BOTH, expand=1)
        else:
            variable = StringVar()
            b = OptionMenu(f, variable, "?", command=onClick, style='W.TButton', *self.options)
            b["menu"].config(bg="white", activebackground="red", selectcolor="green")
            b.pack(fill=BOTH, expand=1)
            self.pinCodes[pin] = variable

    def label(self, master, x, y, text, height, width):
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
        f.place(x=Zif.zifPosX, y=Zif.height + 20)

        o = Entry(f, font=("courier", 9),
                  textvariable=self.testPattern, width=Zif.width,
                  justify=CENTER)
        o.pack(fill=BOTH, expand=1)

        o.configure(style="W.TButton")

        return (f, o)

    def repaintPattern(self):
        pattern = ""

        start = 0
        end = self.pins

        if self.USE_v1_HACK:
            start = 1
            end = 23

        for pin in sorted(self.pinCodes.keys()):
            pinVar = self.pinCodes[pin]
            code = pinVar.get()
            pattern = pattern + code
            if pin == (len(self.pinCodes) / 2):
                pattern = pattern + "/"
        self.testPattern.set(pattern)

    def runTest(self):
        pat = "t:" + self.testPattern.get()
        self.writeLog("%s\n" % pat)
        self.serialMon.writeToTester(pat)

    def paintResult(self, result):
        self.writeLog("%s" % result)
        if result.startswith("ERROR"):
            showerror(title="Error Response", message=result)
        elif result.startswith("PASS"):
            pass
        elif result.startswith("RESULT"):
            resp = result.replace("RESULT : ", "").strip()
            for ipin in range(0, self.pins):
                incode = "-"
                if ipin in self.pinCodes:
                    incode = self.pinCodes[ipin].get()
                code = resp[ipin]
                if code == "-":
                    # not a pin
                    self.pinControls[ipin].configure(background="gray95")
                elif code == "_":
                    # was in input
                    code = incode
                    self.pinControls[ipin].configure(background="white")
                elif code == ".":
                    # was ok
                    code = incode
                    self.pinControls[ipin].configure(background="pale green")
                else: # might be ok cos this could be a "S" or "?"
                    color="yellow"
                    if incode in "HLZ": # was an assertion to not ok
                        color="red"
                    self.pinControls[ipin].configure(background=color)

                self.pinLabels[ipin].set(code)


def main():
    root = Tk()

    root.title("Exploratory Tool")

    ex = Zif(root)
    ex.pack()

    tester = TesterInterface(serialPort="com6")

    ex.serialMon = tester
    tester.responseHandler = ex.paintResult

    tester.open()

    # ex.place(y=60)
    ex.pack()

    # ex.grid(row=0, column=0)
    #
    # rightCanvas = Canvas(root, background="blue",  relief='ridge')
    # rightCanvas.grid(row=0, column=1)

    # root.geometry("600x450+150+150")

    root.mainloop()


if __name__ == '__main__':
    main()
