'''
This script is intended to pre-process the gcode for that will be read by the Python script
Idea is to remove all the crap comments that are left by the site when downloading
Idea is to just start reading from 

'''
import numpy as np
import matplotlib 
import pandas as pd

def Strip(GcodePath):
    '''
    Pseudocode:
    Open and read file:
    Followed by deleting or stripping all lines that have a comma inside
    '''
    try:
        f = open(GcodePath, "r")          # Read the gcode file from the aforementioned Path
        if(f.readable == False):
            raise Exception("File is not readable")
    except:
        raise Exception("Error Opening Gcode File")

    NewLine = []
    
    for (count, line) in enumerate(f):
        #print(count)
        #print(line)

        if(line.startswith('G')):
            #print("We will keep this")
            ModifiedLine = line.strip("G01 ")
            ModifiedLine = ModifiedLine.strip("\n")
            NewLine.append(ModifiedLine)

    print(NewLine)

    f.close()
    #print(NewLine)
    #print("This is " + NewLine[0])

    return(NewLine)
    '''
    try:
        w = open("write.gcode" , "w")
    except:
        raise Exception("Error Opening File to be written to")
    
    for x in range(len(NewLine)):
        w.write(NewLine[x])
    w.close()
    '''
    
    '''
    If line starts with a ';' delete everything
    If lines does not start with a ';' delete everything up to 'X'
    
    Actually, the stripped gcode does not need to be re-written to a new file, can just be plugged and converted
    into whatever commands are required
    '''

def CalculateDeltas(Gcode, StepPrecision):

    '''
    So in total, there will be n-1 lines of code produced for deltas

    '''
    CleanedXList = []
    CleanedYList = []
    DeltaXList = []
    DeltaYList = []
    for (count,line) in enumerate(Gcode):
        
        '''
        This is a very scuffed way of rounding,
        probably need to do some custom rounding in steps, for example rounding to the step increment
        Such that the division results in whole numbers/int for the number of steps
    
        use some math module?
        '''
        CleanedXList.append(float (line[1:7]))
        CleanedYList.append(float (line[10:16]))
    

    DeltaXList = np.diff(CleanedXList)
    DeltaYList = np.diff(CleanedYList) 

    '''
    After this generate a list of steps required?
    '''      


    return DeltaXList, DeltaYList
       
def ConversionToDeltas(DeltaXList, DeltaYList):

    Radius = 12.15/2

    AlphaP1List = []
    AlphaP2List = []
    for x in range(len(DeltaXList)):
        AlphaP1List.append((DeltaXList[x] + DeltaYList[x])/Radius)
        AlphaP2List.append((DeltaXList[x] - DeltaYList[x])/Radius)

    # Need to figure out the kinematics equation to convert the thing to movement

    
    '''
    I think the 
    '''

    

    # Need to figure out/do calculations on the appropriate 

def ConvertDeltasToSteps(AlphaP1, AlphaP2):

    if(AlphaP1<0):
        XDirection = "-"
    else:
        XDirection = "+"

    if(AlphaP2<0):
        YDirection = "-"
    else:
        YDirection = "+"

    XNumberOfSteps = AlphaP1

    XInterval = 1

    YDirection = "-"

    YNumberOfSteps = AlphaP2

    YInterval = 1


    XNumberOfSteps = str (XNumberOfSteps)
    YNumberOfSteps = str (YNumberOfSteps)
    XInterval = str(XInterval)
    YInterval = str(YInterval)


    if(len(XNumberOfSteps)<7):

        XNumberOfSteps = XNumberOfSteps.zfill(7)
        
    if(len(XInterval)<4):

        XInterval = XInterval.zfill(4)

    if(len(YNumberOfSteps)<7):

        YNumberOfSteps = YNumberOfSteps.zfill(7)
        
    if(len(YInterval)<4):

        YInterval = YInterval.zfill(4)

    ArduinoString = "<M" + XDirection + XNumberOfSteps + XInterval + YDirection + YNumberOfSteps + YInterval + ">"




if __name__ == "__main__":
    GcodePath = "circularpattern.gcode"
    Gcode = Strip(GcodePath)
    DeltaXList, DeltaYList = CalculateDeltas(Gcode, 0.025)
    #ConversionToDeltas(DeltaXList, DeltaYList)
    '''
    
    '''