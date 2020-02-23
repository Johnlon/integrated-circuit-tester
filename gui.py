import tkinter as tk
from tkinter import *
import functools
from tkinter.ttk import *


def quit(event):
    print("Double Click, so let's stop")
    import sys; sys.exit()


class Zif(Frame):

    socketWidth = 200

    pins=24
    rows=pins/2

    pitchVert = 30

    marginSide=20
    marginTop=100
    marginBot=50

    labelSize = 30

    pinHeight = 25
    pinWidth = 50

    selectorSize = 50
    selectorHeight = 25
    patternHeight = 30

    testButtonSize = 30

    height = marginTop + marginBot + (pitchVert * (rows - 1))
    width = 200

    zifPosX = 100
    zifPosY = 0
    options = ["?","0","1","V","G","C","L","H","Z","X","S"]

    surfaceCol="#F7F7F7"

    def __init__(self, parent, *args, **kwargs):
        self.pinLabels = []
        self.pinCodes = []
        self.testPattern=StringVar()
        self.autoTest=False

        tk.Frame.__init__(self, parent)
        self.initUI()


    def initUI(self):

        self.config(height=Zif.height, width=Zif.width, background="white", borderwidth=0, highlightthickness=0)

        canvasTop = Canvas(self, height=Zif.height+50, width=Zif.width*2, background="white", borderwidth=0, highlightthickness=0)
        canvasTop.pack(side=LEFT, padx=10, pady=20)

        canvas1 = Canvas(canvasTop, height=Zif.height, width=Zif.socketWidth,  background="white", borderwidth=1, highlightthickness=0)
        canvas1.place(x=Zif.zifPosX, y=Zif.zifPosY)
        canvas1.create_rectangle(2, 55, Zif.socketWidth, Zif.height, width=1, outline="black", fill=Zif.surfaceCol);
        canvas1.create_rectangle(20, 20, 40, 80, width=1, outline="black", fill="#EEE");
        canvas1.create_rectangle(18, 5, 42, 30, width=1, outline="black", fill="#EEE");

        self.patternField(canvasTop)
        self.testButton(canvasTop)

        for pin in range(0, 24):
            self.label(canvasTop, x=self.labelPosH(pin), y=self.pinPosV(pin), text=str(pin+1), width=Zif.labelSize, height=Zif.labelSize)

            pinLabelVariable=StringVar()
            pinLabelVariable.set("")
            self.pinLabels.append(pinLabelVariable)

            self.pin(canvasTop, x=self.pinPosH(pin), y=self.pinPosV(pin), textvariable=pinLabelVariable, width=Zif.pinWidth, height=Zif.pinHeight)
            self.optionMenu(canvasTop, x=self.selectorPosH(pin), y=self.pinPosV(pin), width=Zif.selectorSize, height=Zif.selectorHeight, pin=pin, labelvariable=pinLabelVariable)

        self.repaintPattern()
        canvasTop.pack()
        self.pack()

    def rowOfPin(self, pin):
        if pin < 12:
            return pin
        else:
            return 24 - pin - 1

    def pinPosV(self, pin):
        return Zif.marginTop + (self.pitchVert * self.rowOfPin(pin))

    def pinPosH(self, pin):
        if pin < 12:
            return Zif.zifPosX + Zif.marginSide
        else:
            return Zif.zifPosX + Zif.socketWidth - Zif.marginSide - Zif.pinWidth

    def labelPosH(self, pin):
        gap=1
        if pin < 12:
            return Zif.zifPosX + Zif.marginSide + Zif.pinWidth + gap
        else:
            return Zif.zifPosX + Zif.socketWidth - Zif.marginSide - Zif.labelSize - Zif.pinWidth - gap

    def selectorPosH(self, pin):
        gap = 20
        if pin < 12:
            return Zif.zifPosX - Zif.selectorSize -gap
        else:
            return Zif.zifPosX + Zif.socketWidth + gap


    def testButton(self, master):
        xpos = Zif.zifPosX + Zif.socketWidth + 30
        self.button(master, x=xpos, y=25, text="Test", height=30, width=50, style='W.TButton')

    def button(self, master, x, y, text, height, width, style):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()
        f.place(x=x, y=y)

        b = Button(f, text=text, style=style)
        b.pack(fill=BOTH, expand=1)
        return (f,b)

    def optionMenu(self, master, x,y, height, width, pin, labelvariable):

        variable=StringVar()

        def onClick(code):
            print("pin %d = %s" % (pin, code))
            labelvariable.set(code)
            self.repaintPattern()

        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()
        f.place(x=x,y=y)

        b = OptionMenu(f, variable, "?", command=onClick, *self.options)
        b.pack(fill=BOTH, expand=1)

        self.pinCodes.append(variable)
        return (f,b)

    def label(self, master, x, y, text, height, width):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()
        f.place(x=x, y=y)

        o = Label(f, text=text, font=("courier", 9), background=Zif.surfaceCol, borderwidth=0, anchor="center")
        o.pack(fill=BOTH, expand=1)

    def pin(self, master, x,y,textvariable, height, width):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()
        f.place(x=x,y=y)

        o = Label(f, textvariable=textvariable, font=("courier", 9), background="#DDD", borderwidth=2, relief="solid", anchor="center")
        o.pack(fill=BOTH, expand=1)

    def entry(self, master, text, height, width, font,textvariable):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()

        o = Entry(f, font=font, textvariable=textvariable, justify=CENTER)
        o.insert(tk.END, text)
        o.pack(fill=BOTH, expand=1)
        return (f,o)

    def patternField(self, master):
        f = Frame(master, width=Zif.width, height=Zif.patternHeight)
        f.pack_propagate(0) # don't shrink
        f.pack()
        f.place(x=Zif.zifPosX, y=Zif.height+20)

        o = Entry(f, font=("courier", 9),
                  textvariable=self.testPattern, width=Zif.width,
                  justify=CENTER)
        o.pack(fill=BOTH, expand=1)

        o.configure(style="W.TButton")

        return (f,o)

    def repaintPattern(self):
        pattern=""
        for pin in range(0, 24):
            code = self.pinCodes[pin].get()
            pattern = pattern + code
            if pin == (self.pins/2)-1:
                pattern = pattern + "/"
        self.testPattern.set(pattern)

def main():

    root = Tk()

    root.title("Exploratory Tool")

    ex = Zif(root)
    ex.pack(side=LEFT)


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