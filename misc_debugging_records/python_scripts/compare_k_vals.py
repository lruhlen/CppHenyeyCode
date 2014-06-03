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

H = numpy.loadtxt(HelenaFile,comments="//")

P = numpy.loadtxt(PeterFile, comments="//")

#============================================================
# Set up indexing
#============================================================
J = 0
dMk1 = 1
dMk2 = 2
dMk3 = 3
dMk4 = 4
dRk1 = 5
dRk2 = 6
dRk3 = 7
dRk4 = 8
dPk1 = 9
dPk2 = 10
dPk3 = 11
dPk4 = 12
dTk1 = 13
dTk2 = 14
dTk3 = 15
dTk4 = 16

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


## Plot temperature vs. atmos cell number
#plt.figure(5)
#plt.grid(True)
#plt.xlabel('Tau cell number')
#plt.ylabel('Temperature')
#plt.semilogy(Hatmos[:,Hj],Hatmos[:,HT],'-',color=Color1,label="Helena",linewidth=4)
#plt.semilogy(Patmos[:,Pj],Patmos[:,PT],'-',color=Color2,label="Peter",linewidth=2)
#plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
#legend(loc="best")



# Tell python to actually *show* me the resulting plots
show()
