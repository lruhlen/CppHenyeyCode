#============================================================
# Import modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime


#============================================================
# Run the C++ code, and parse and store its outputs into the
# appropriate directory (based on date, version number, etc.)
#============================================================
date = datetime.datetime.today()
month = date.strftime("%b")
day = date.strftime("%d")
year = date.strftime("%Y")
homedir = os.getcwd()
rundir = "/Users/laurel/Desktop/Research/CppHenyeyCode/"
savedirBase = "/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/"+year+"/"+month+"/"+month+"_"+day+"_"+year+"/"
tmp = [0]
versionNum=[0]

# Ask how many iteration loops to run the code for
IterNum = eg.enterbox(msg='How many iteration loops to run?  (default = 1)')
if IterNum == '':
    IterNum = '1'
IterNum = str(int(IterNum) + 1)


if not os.path.exists(savedirBase): # If the save-directory does not already exist, create it
    os.makedirs(savedirBase)
else:  # See how many versions, if any, have already been written here
    filelist = [ ]
    for file in os.listdir(savedirBase):
        if fnmatch.fnmatch(file,'*v[0-9]*'):
            filelist.append(file)
    # See how many versions already exist
    for name in filelist:
        prefix = string.split(name,'v')
        tmp.append(int(prefix[1]))
# Figure out which version number we're writing to file, now
versionNum = str(max(tmp)+1)


# Make the directory for our current version
savedirBase = savedirBase+"v"+versionNum+"/"
os.makedirs(savedirBase)

os.chdir(rundir)
AboutMessage = eg.enterbox(msg='What\'s different about this run?',strip=False)
AboutMessage += '\n'
f= open(savedirBase+"About.txt",'w')
f.write(AboutMessage)
f.close()
os.system("cat "+rundir+"src/AboutThisRun.h >> "+savedirBase+"About.txt")
os.system("grep _name "+rundir+"src/main.cpp >> "+savedirBase+"About.txt")
os.system("grep _var "+rundir+"src/main.cpp >> "+savedirBase+"About.txt")
os.system("n ./bin/main "+savedirBase+month+"_"+day+"_"+year+" "+versionNum +" "+IterNum)

print('Savedir base:\n')
print(savedirBase+month+"_"+day+"_"+year)

# Make directories for each loop iteration, and move the appropriate files into their respective iteration number bins
os.chdir(savedirBase)
for i in range(1,int(IterNum)):
    iterDir = savedirBase+"iter_"+str(i)+"/"
    
    # If the iteration-number-directory does not already exist, create it
    if not os.path.exists(iterDir): 
        os.makedirs(iterDir)

    # Find the files that match the iteration number and move them to correct iter number directory
    os.system("mv *iter_"+str(i)+".txt "+iterDir)
        

# Ask the user if they'd like to plot the results...?

    
os.chdir(homedir)

