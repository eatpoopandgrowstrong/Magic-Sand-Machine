import serial
import serial.tools.list_ports

import time


global ser
        
def ConnectToArduino(COMPortToBeConnectedString,Baudrate, Timeout):
    
        global ser
        ser = serial.Serial(
                
                port = COMPortToBeConnectedString,
                baudrate = Baudrate,
                timeout = Timeout,
                
                
                )
        
        time.sleep(0.01)
        ser.flushInput()
        time.sleep(0.01)
        ser.flushOutput()
        time.sleep(0.01)
        
def CommCheck():
    
    
    ser.write("<Comm Check>".encode())
    
    Data = ReceiveStringWithStartAndEndMarkers()

    if(Data == "Readback"):
    
        print("Successful readback from Arduino")
            
    else:
        
        raise Exception("Python was not able to communicate with Arduino")

        
def ListArduinoConnectedPorts():
    
    ConnectedItems = list(serial.tools.list_ports.comports())
    ArduinoPortsList = []
    
    for port in ConnectedItems:
        
        ArduinoIsConnected = False
        
        if(port[2].startswith("USB VID:PID=2341:0043")):     #Element 3 is the HWID of the device connected
        #if(port[2].find("USB VID:PID=2341:0043")):

            ArduinoIsConnected = True
            
        #if (port[2.])

        if (ArduinoIsConnected == True):
            
            ArduinoPortsList.append(port)

    if ArduinoPortsList:
        
        #return ArduinoPortsList
        print(len(ArduinoPortsList))
        if(len(ArduinoPortsList)>=2):
            print("Error, Multiple Arduino Unos Connected")
            
            raise Exception("Multiple Arduino Unos connected")
        return (ArduinoPortsList[0][0])                 #Element 1 is the COM Port and its number


def WaitForArduino():
    
    #ser.write("<I1000>".encode())
    
    Data = ReceiveStringWithStartAndEndMarkers()
    #print(Data)
    if(Data == "Arduino Is Ready"):
        #print("READY")
        pass
    else:
        raise Exception("READBACK INCOMPLETE")
    
    '''
    Bring problem is that the script is not waiting for arduino to initialise, ofc it will not be able to read or write anything
    
    '''

def ReceiveStringWithStartAndEndMarkers():
    
    global StartMarker, EndMarker
    
    ReceiveInProgress = False
    ReceiveString = ""
    StringIndexCount = 0
    
    while(ser.in_waiting == 0):
        
        #print("Firing")    
        '''
        '''
      #print("LOL")
    #print("The thing is ready " + str(ser.in_waiting))

    x = ser.read().decode("UTF-8")

    if(x == StartMarker):
        ReceiveInProgress = True
        #print("Starting")
        
    while(ReceiveInProgress == True):
     
        '''
        while(ser.in_waiting == 0):
            
            ser.in_waiting
        '''
        x = ser.read().decode("UTF-8")
        #print("x is " + x)
        if(x != StartMarker):
            
            #print(x)
                
            if(x != EndMarker):
                
                #print("Firing")
                ReceiveString = ReceiveString + x
                StringIndexCount += 1
                     
            elif(x == EndMarker):       # Any difference between this and else?
            
                ReceiveInProgress = False
                #print("Terminating")

        '''
        elif(x == StartMarker):
            
            ReceiveInProgress = True
        '''
    
    
    #print("ReceiveString is " + ReceiveString)
    return ReceiveString

    
def DisconnectFromArduino():
    global ser
    ser.close()
    print("Disconnected From Arduino")
    
    
def main():
    global StartMarker, EndMarker
    StartMarker = '<'
    EndMarker = '>'
    
    
    # Port Connection
    
    ArduinoPortsList = ListArduinoConnectedPorts()
    ConnectToArduino(ArduinoPortsList, 115200, 0.01)
    
    Data = ReceiveStringWithStartAndEndMarkers()
    print(Data)
    
    ser.write("<I>".encode())

    Data = ReceiveStringWithStartAndEndMarkers()
    print(Data)
    ser.write("<F07200>".encode())
    
    Data = ReceiveStringWithStartAndEndMarkers()
    print(Data)
    
    ser.close()
    
if (__name__ == "__main__"):

    
    main()
