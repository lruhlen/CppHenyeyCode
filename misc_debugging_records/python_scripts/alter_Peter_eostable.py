#============================================================
# Import modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime

#============================================================
# Pseudo-code, from my notes:
# 1. Read the entire file into a python array of some type
# 2. Read in the table values as strings-- all of them.
# 3. Search the table for the strings that signify the start of a new P/X table
# 4. Print that string out unchanged
# 5. Split the following lines on whitespace
# 6. Split the scientific notation entry for rho/cP/etc. on the E(?)
# 7. Split the 'mantissa' (quotes b/c it's a string var, not an actual numerical mantissa from python's p.o.v.) into the first part, and the last two digits
# 8. Convert the string of the last two digits to an integer
# 9. Generate a random integer between -9 and +9  (or maybe b/w -5 and +5?  But start with 9s).
# 10. Add the random integer to those last 2 digits.
# 11. Convert the last two digits back to a string, and re-join that string w/ the first part of the mantissa.
# 12. Rejoin the exponent and the mantissa strings back together.
# 13. (Maybe?  Depending on how the eostable values correspond to the actual cP/rho/etc. values returned by the lookup routine.) Repeat steps 6 thru 12 for the rest of the entries in that line.
# 14. Print the altered line out to file. 
#============================================================

# Name of the (input) eostable file to read in:
filename = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/Original_eostable'
# Open the input file for reading
infile = open(filename,'r')

# Name of the (output) file to write to:
outfilename = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/altered_up_eostable_1e3'
# Open the output file for writing
outfile = open(outfilename,'w')
words = ['','','','','' ]
formatList = ["{0:10.6f}","{0:11.6f}","{0:9.6f}","{0:9.6f}","{0:9.6f}"]

# Do stuff to each line of the file
for line in infile:
     # If the line is blank (aside from return-carriage ascii), skip ahead to the next line
     # If the line signifies the start of a table, just print it out as is, and go on to the next line
    if (line == '\n') or (fnmatch.fnmatch(line,'*T*')):
        pass
    else:
        # Otherwise, split the line up further, and perform all those operations on it.
        # Otherwise, split the line on whitespaces, and parse it.
        words[0] = line[1:10]
        words[1] = line[10:21]
        words[2] = line[21:30]
        words[3] = line[30:39]
        words[4] = line[39:48]
        
        for i in range(1,5):
            # Find the (value of the) original entry
            if i == 1:
                originalVal = words[i]
                # Generate a random integer between -9 and +9
                epsilon = 1e-3*randint(1,9)
                # Add the random integer to the 'last' part of the original value
                newVal = float(originalVal) + epsilon
                # Convert the newVal back into a string with the proper format
                words[i] = formatList[i].format(newVal)
            
        # Join the 'words' back together into a full line
        line =   words[0]+words[1]+words[2]+words[3]+words[4]+'\n'      

     # Finally, print the altered or unaltered line out (to file, later)
    outfile.write(line)
            
# Close the eostable file you've been reading
infile.close()
# Close the file you were writing the outputs to
outfile.close()
