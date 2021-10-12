import SerialComm as SC
import tkinter as tk
import ctypes

import importlib

importlib.reload(SC)
'''
Idea is to have 

'''
class Mainwindow:

    def __init__(self,master):
        '''
        Throw all startup and connections here, for now 
        '''
        SC.StartMarker = '<'
        SC.EndMarker = '>'

        root.grid()
        

        self.SpeedVar = tk.IntVar()
        self.SpeedVar.set(1)
        
        self.XAxisFlip = tk.IntVar()
        self.XAxisFlip.set(0)

        self.YAxisFlip = tk.IntVar()
        self.YAxisFlip.set(0)

        self.LeftStatus = 0
        self.RightStatus = 0
        self.UpStatus = 0
        self.DownStatus = 0
        #master.bind("<Up>", self.up_on_press)

        self.DefaultXAxisRadioButton = tk.Radiobutton(

            master,
            text = "Default X Axis",
            variable = self.XAxisFlip,
            value = 0,
            command = lambda: SC.ser.write("<DefaultX>".encode())

        )                

        self.FlipXAxisRadioButton = tk.Radiobutton(

            master,
            text = "Flip X Axis",
            variable = self.XAxisFlip,
            value = 1,
            command = lambda: SC.ser.write("<FlipX>".encode())

        )

        self.DefaultYAxisRadioButton = tk.Radiobutton(

            master,
            text = "Default Y Axis",
            variable = self.YAxisFlip,
            value = 0,
            command = lambda: SC.ser.write("<DefaultY>".encode())

        )

        self.FlipYAxisRadioButton = tk.Radiobutton(

            master,
            text = "Flip Y Axis",
            variable = self.YAxisFlip,
            value = 1,
            command = lambda: SC.ser.write("FlipY".encode())

        )

        self.Speed1RadioButton = tk.Radiobutton(

            master,
            text = "Speed 1",
            variable = self.SpeedVar,
            value = 1,
            #command = lambda: print("1 pressed")
            command = lambda: SC.ser.write("<Fast>".encode())
        )

        self.Speed2RadioButton = tk.Radiobutton(

            master,
            text = "Speed 2",
            variable = self.SpeedVar,
            value = 2,
            #command = lambda: print("2 pressed")
            command = lambda: SC.ser.write("<Slow>".encode())
        )

        self.DefaultXAxisRadioButton.grid(column = 0, row = 0)
        self.FlipXAxisRadioButton.grid(column = 0, row = 1)

        self.DefaultYAxisRadioButton.grid(column = 1, row = 0)
        self.FlipYAxisRadioButton.grid(column = 1, row = 1)


        self.Speed1RadioButton.grid(column = 2, row = 0)
        self.Speed2RadioButton.grid(column = 2, row = 1)

 

        for x in range(4):
           
            root.grid_columnconfigure(x, weight = 1)

        for y in range(2):
          
            root.grid_rowconfigure(y, weight = 1)

        master.bind("<Up>",self.UpOnPress)
        master.bind("<KeyRelease-Up>",self.UpOnRelease)

        master.bind("<Down>",self.DownOnPress)
        master.bind("<KeyRelease-Down>",self.DownOnRelease)

        master.bind("<Left>",self.LeftOnPress)
        master.bind("<KeyRelease-Left>",self.LeftOnRelease)

        master.bind("<Right>",self.RightOnPress)
        master.bind("<KeyRelease-Right>",self.RightOnRelease)


        self.ConnectToArduino()
    
    def ConnectToArduino(self):

        print("Stage 2")
        ArduinoPortsList = SC.ListArduinoConnectedPorts()
        SC.ConnectToArduino(ArduinoPortsList, 115200, 0.01)
        SC.WaitForArduino()
        SC.CommCheck()

        print("Connected to Arduino")

    '''
    Maybe do an if and pass?
    Might be very spammy of serial if the buttons are held down?
    
    Something:

    if(!= ):
        pass
    
    '''
    def UpOnPress(self, event):

        if(self.UpStatus == 0):
            self.UpStatus = 1
            SC.ser.write("<Up>".encode())
            print("Up Pressed")
        

    def UpOnRelease(self, event):

        self.UpStatus = 0
        print("Up Released")
        SC.ser.write("<YStop>".encode())

    def DownOnPress(self, event):
        
        if(self.DownStatus == 0):
            self.DownStatus = 1
            SC.ser.write("<Down>".encode())
            print("Down Pressed")

    def DownOnRelease(self, event):
        
        self.DownStatus = 0
        print("Down Released")
        SC.ser.write("<YStop>".encode())

    def LeftOnPress(self, event):
    
        if(self.LeftStatus == 0):
            self.LeftStatus = 1
            print("Left Pressed")
            SC.ser.write("<Left>".encode())

    def LeftOnRelease(self, event):

        self.LeftStatus = 0
        print("Left Released")
        SC.ser.write("<XStop>".encode())

    def RightOnPress(self, event):

        if(self.RightStatus == 0):
            self.RightStatus = 1
            print("Right Pressed")
            SC.ser.write("<Right>".encode())

    def RightOnRelease(self, event):

        self.RightStatus = 0
        print("Right Released")
        SC.ser.write("<XStop>".encode())
    
if __name__ == "__main__":

    ctypes.windll.shcore.SetProcessDpiAwareness(1)      # For High DPI
    print("Stage 1")
    root = tk.Tk()
    mainwindow = Mainwindow(root)
    root.mainloop()
    
    # If there is 
    
    try:
        SC.DisconnectFromArduino()              # If the Arduino has not been manually disconnected, try ser.close()
    except:                                     # Helps with plugging in and unplugging constantly
        pass