import tkinter as tk
from tkinter import *
import functools
from tkinter.ttk import *


def hello(event, param):
    print("Single Click, Button-l %s" % (param))

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

    def __init__(self, parent, *args, **kwargs):
        tk.Frame.__init__(self, parent)
        self.initUI()

    def initUI(self):

        self.pinList = []

        self.config(height=Zif.height, width=Zif.width, background="orange", borderwidth=0, highlightthickness=0)

        canvasTop = Canvas(self, height=Zif.height+50, width=Zif.width*2, background="red", borderwidth=0, highlightthickness=0)
        canvasTop.pack(side=LEFT, padx=10, pady=20)

        buttonStyle = Style()
        buttonStyle.configure('W.TButton', font = ('calibri', 10, 'bold'), background='yellow')

        labelStyle = Style()
        labelStyle.configure('W.TLabel', font = ('calibri', 10, 'italic'), background='yellow')

        canvas1 = Canvas(canvasTop, height=Zif.height, width=Zif.socketWidth,  background="yellow", borderwidth=1, highlightthickness=0)
        canvas1.place(x=Zif.zifPosX, y=Zif.zifPosY)
        canvas1.create_rectangle(2, 55, Zif.socketWidth, Zif.height, width=1, outline="black", fill="white");
        canvas1.create_rectangle(20, 20, 40, 80, width=1, outline="black", fill="#EEE");
        canvas1.create_rectangle(18, 5, 42, 30, width=1, outline="black", fill="#EEE");

        for pin in range(0, 24):
            (widget,l) = self.label(canvasTop, text=str(pin+1), width=Zif.pinSize, height=Zif.pinSize, style='W.TLabel')
            widget.place(x=self.pinPosH(pin), y=self.pinPosV(pin))
            self.pinList.append(l)

            (widget, b) = self.button(canvasTop, text="p"+str(pin+1), width=Zif.pinSize, height=Zif.pinSize, style='W.TButton')
            widget.place(x=self.buttonPosH(pin), y=self.pinPosV(pin))
            b.bind('<Button-1>', functools.partial(hello, param=pin))
            b.bind('<Double-1>', quit)

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

    #
    # def socketPosH(self, col):
    #     if col == 0:
    #         return Zif.marginSide
    #     else:
    #         return Zif.socketWidth - Zif.marginSide - Zif.buttonSize


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

        b = Label(f, text=text, style='W.TButton')
        b.pack(fill=BOTH, expand=1)
        return (f,b)

def main():

    root = Tk()

    root.title("Exploratory Tool")

    ex = Zif(root)
    ex.pack(side=LEFT,padx=20, pady=20)


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