#============================================================
# Read in potentially useful python modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime

#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================
Color1 = cm.Dark2(3)
Color2 = cm.spectral(0)
Color3 = cm.Dark2(110)
Color4 = cm.Dark2(35)

#============================================================
# Read in the raw data
#============================================================
HelenaFile =  eg.fileopenbox(msg='Pick the HELENA file you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/atmos_vals/')
PeterFile = eg.fileopenbox(msg='Pick the PETER file you want to anaylze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/')

Hatmos = numpy.loadtxt(HelenaFile,comments="//")
Hindex = Hatmos[:,0].argsort()
Hatmos = Hatmos[Hindex]

Patmos = numpy.loadtxt(PeterFile, comments="//")
Pindex = Patmos[:,0].argsort()
Patmos = Patmos[Pindex]

#============================================================
# Set up indexing
#============================================================
TauCellNumber = 0
Mtemp = 1
Rtemp = 2



#============================================================
# Plot stuff
#============================================================
plt.close("all")
plt.clf()
File1 = HelenaFile.split('Desktop')[-1]
File2 = PeterFile.split('Desktop')[-1]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+File1+"\n"+File2


# Plot tau vs. atmospheric cell number
plt.figure(1)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('Mtemp values')
plot(Hatmos[:,TauCellNumber],Hatmos[:,Mtemp],'-',color=Color1,label="Helena",linewidth=4)
plot(Patmos[:,TauCellNumber],Patmos[:,Mtemp],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")


# Plot mass vs. atmos cell number
plt.figure(2)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('Rtemp values')
plot(Hatmos[:,TauCellNumber],Hatmos[:,Rtemp],'-',color=Color1,label="Helena",linewidth=4)
plot(Patmos[:,TauCellNumber],Patmos[:,Rtemp],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")




# Tell python to actually *show* me the resulting plots
show()
