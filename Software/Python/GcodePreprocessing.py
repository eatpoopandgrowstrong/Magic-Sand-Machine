'''
This script is intended to pre-process the gcode for that will be read by the Python script
Idea is to remove all the crap comments that are left by the site when downloading
Idea is to just start reading from 

'''

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
        print(count)
        print(line)
        
        if line.startswith(';'):
            print("DELETE THIS")
        elif(line.startswith('G')):
            print("We will keep this")
            ModifiedLine = line.strip("G01")
            NewLine.append(ModifiedLine)
        elif(line.startswith('')):
            print("There is nothing here")
        

    f.close()
    
    try:
        w = open("write.gcode" , "w")
    except:
        raise Exception("Error Opening File to be written to")
    
    for x in range(len(NewLine)):
        w.write(NewLine[x])
    w.close()

    
    '''
    If line starts with a ';' delete everything
    If lines does not start with a ';' delete everything up to 'X'
    '''


if __name__ == "__main__":
    GcodePath = "initial test gcode.gcode"
    Strip(GcodePath)

    '''
    
    '''