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

    pinSize = 30
    buttonSize = 30

    height = marginTop + marginBot + (pitchVert * (rows - 1))
    width = 200

    zifPosX = 100
    zifPosY = 0
    options = ["?","0","1","C","L","H","Z","X","S"]

    def __init__(self, parent, *args, **kwargs):
        self.pinList = []
        self.pinListIdx = []
        self.testPattern=StringVar()

        tk.Frame.__init__(self, parent)
        self.initUI()


    def initUI(self):

        self.config(height=Zif.height, width=Zif.width, background="orange", borderwidth=0, highlightthickness=0)

        canvasTop = Canvas(self, height=Zif.height+50, width=Zif.width*2, background="red", borderwidth=0, highlightthickness=0)
        canvasTop.pack(side=LEFT, padx=10, pady=20)

        style = Style()
        style.configure('W.TButton', font = ('courier', 9, ''), background='yellow')

        canvas1 = Canvas(canvasTop, height=Zif.height, width=Zif.socketWidth,  background="yellow", borderwidth=1, highlightthickness=0)
        canvas1.place(x=Zif.zifPosX, y=Zif.zifPosY)
        canvas1.create_rectangle(2, 55, Zif.socketWidth, Zif.height, width=1, outline="black", fill="white");
        canvas1.create_rectangle(20, 20, 40, 80, width=1, outline="black", fill="#EEE");
        canvas1.create_rectangle(18, 5, 42, 30, width=1, outline="black", fill="#EEE");

        (f, self.patternField) = self.entry(canvasTop, font=("courier", 9), text="????????????/????????????", width=Zif.width, height=Zif.pinSize, textvariable=self.testPattern)
        f.place(x=Zif.zifPosX, y=Zif.height+20)

        for pin in range(0, 24):
            (widget,l) = self.label(canvasTop, text=str(pin+1), width=Zif.pinSize, height=Zif.pinSize, style='W.TButton')
            widget.place(x=self.pinPosH(pin), y=self.pinPosV(pin))
            self.pinListIdx.append(0)
            self.pinList.append(l)

            (widget, b) = self.button(canvasTop, text="p"+str(pin+1), width=Zif.pinSize, height=Zif.pinSize, style='W.TButton')
            widget.place(x=self.buttonPosH(pin), y=self.pinPosV(pin))
            b.bind('<Button-1>', functools.partial(self.onClick, button=b, pin=pin))
            b.bind('<Shift-Button-1>', functools.partial(self.onShiftClick, button=b, pin=pin))
            self.repaintButton(b, pin)

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
            return Zif.zifPosX + Zif.socketWidth - Zif.marginSide - Zif.buttonSize

    def buttonPosH(self, pin):
        gap = 20
        if pin < 12:
            return Zif.zifPosX - Zif.buttonSize - gap
        else:
            return Zif.zifPosX + Zif.socketWidth + gap

    def button(self, master, text, height, width, style):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()

        b = Button(f, text=text, style=style)
        b.pack(fill=BOTH, expand=1)
        return (f,b)

    def label(self, master, text, height, width, style):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()

        o = Label(f, text=text, style=style)
        o.pack(fill=BOTH, expand=1)
        return (f,o)

    def entry(self, master, text, height, width, font,textvariable):
        f = Frame(master, height=height, width=width)
        f.pack_propagate(0) # don't shrink
        f.pack()

        o = Entry(f, font=font, textvariable=textvariable, justify=CENTER)
        o.insert(tk.END, text)
        o.pack(fill=BOTH, expand=1)
        return (f,o)


    def onClick(self, event, button, pin):
        print("Single Click, Button-%s pin %d for %s" % (button, pin, event))
        label = self.pinList[pin]
        idx = self.pinListIdx[pin];
        idx = (idx + 1) % len(self.options)
        self.pinListIdx[pin] = idx
        self.repaintButton(button, pin)

    def onShiftClick(self, event, button, pin):
        print("Shift Single Click, Button-%s pin %d for %s" % (button, pin, event))
        label = self.pinList[pin]
        idx = self.pinListIdx[pin];
        idx = (idx - 1) % len(self.options)
        self.pinListIdx[pin] = idx
        self.repaintButton(button, pin)

    def repaintButton(self, button, pin):
        idx = self.pinListIdx[pin];
        code = Zif.options[idx]
        button.configure(text = code)
        self.repaintPattern()

    def repaintPattern(self):
        pattern=""
        for pin in range(0, len(self.pinListIdx)):
            idx = self.pinListIdx[pin];
            code = Zif.options[idx]
            pattern = pattern + code
            if pin == (self.pins/2)-1:
                pattern = pattern + "/"
        self.testPattern.set(pattern)
        # self.testPattern.delete('0','end')
        # self.testPattern.insert(tk.END, pattern)

def main():

    root = Tk()

    root.title("Exploratory Tool")

    ex = Zif(root)
    ex.pack(side=LEFT)#,padx=20, pady=20)


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