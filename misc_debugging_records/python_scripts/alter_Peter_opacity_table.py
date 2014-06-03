#============================================================
# Import modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime


#============================================================


# Name of the (input) eostable file to read in:
filename = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/GN93hz'
# Open the input file for reading
infile = open(filename,'r')

# Name of the (output) file to write to:
outfilename = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/altered_GN93hz'
# Open the output file for writing
outfile = open(outfilename,'w')
# 203        format(f4.2,19f7.3)
formatList = ["{0:4.2f}","{0:7.3f}"]

# Do stuff to each line of the file
for line in infile:
     # If the line is blank (aside from return-carriage ascii), skip ahead to the next line
     # Also skip ahead if the line contains any letters, either upper or lower case.
    if (line.isspace()) or re.search('[a-zA-Z]+',line):
        pass
    else:
        words = [ ]
        words.append(line[0:4])
        linesize = size(line.split())
        for i in range(1,linesize+1):
            # Otherwise, split the line up further, and perform all those operations on it.
            # Otherwise, split the line on whitespaces, and parse it.
            words.append(line[7*(i-1)+4 : 7*(i)+4])

            if not words[i].isspace():
                # Find the (value of the) original entry
                originalVal = words[i]
                # Generate a random integer between -9 and +9
                epsilon = 1e-3*randint(-9,9)
                # Add the random integer to the 'last' part of the original value
                newVal = float(originalVal) + epsilon
                # Convert the newVal back into a string with the proper format
                words[i] = formatList[1].format(newVal)
            
        # Join the 'words' back together into a full line
        outline = ''
        for i in range(0,linesize+1):
            outline+=words[i] 
            #        outline+='\n'
        line = outline
     # Finally, prlsint the altered or unaltered line out (to file, later)
    outfile.write(line)
            
# Close the eostable file you've been reading
infile.close()
# Close the file you were writing the outputs to
outfile.close()
print 'Successfully wrote out the altered opacity table'
