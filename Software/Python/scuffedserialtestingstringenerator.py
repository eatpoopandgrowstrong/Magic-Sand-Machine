#   Just a quick script to generate the string to be entered into the Arduino Serial port for debugging/manual testing
# 
# 

XDirection = "+"

XNumberOfSteps = 250

XInterval = 1

YDirection = "+"

YNumberOfSteps = 250

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







print(ArduinoString)
print("Arduino String is " + str (len(ArduinoString)) + " long")