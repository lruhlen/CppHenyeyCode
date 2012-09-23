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
os.system("n ./bin/main "+savedirBase+month+"_"+day+"_"+year+" "+versionNum +"&")
os.chdir(homedir)

print('Savedir base:\n')
print(savedirBase+month+"_"+day+"_"+year)
