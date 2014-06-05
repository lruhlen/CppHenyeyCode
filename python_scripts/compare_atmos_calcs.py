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
Hj = 0
Htau = 1
HM = 2
HR = 3
HP = 4
HT = 5

#//    J    dM        M        P        R       dR        T       RHO      TAU      ATG      RAD      TRU    1-beta

Pj = 0
PM = 2
PP = 3
PR = 4
PT = 6
Ptau = 8
#============================================================
# Calculate the dTau values generated at each step by
# each of the 2 codes.
#============================================================
HdTau = numpy.zeros(Hatmos.shape[0]-1)
PdTau = numpy.zeros(Patmos.shape[0]-1)

for cellNum in range(1,Hatmos.shape[0]):
    HdTau[cellNum-1] = Hatmos[cellNum,Htau] - Hatmos[cellNum-1,Htau]

for cellNum in range(1,Patmos.shape[0]):
    PdTau[cellNum-1] = Patmos[cellNum,Ptau] - Patmos[cellNum-1,Ptau]



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
plt.ylabel('Tau (optical depth)')
plt.semilogy(Hatmos[:,Hj],Hatmos[:,Htau],'-',color=Color1,label="Helena",linewidth=4)
plt.semilogy(Patmos[:,Pj],Patmos[:,Ptau],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")


# Plot mass vs. atmos cell number
plt.figure(2)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('dM')
plt.semilogy(Hatmos[:,Hj],Hatmos[:,HM],'-',color=Color1,label="Helena",linewidth=4)
plt.semilogy(Patmos[:,Pj],Patmos[:,1],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")


# Plot radius vs. atmos cell number
plt.figure(3)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('dR')
plt.semilogy(Hatmos[:,Hj],Hatmos[:,HR],'-',color=Color1,label="Helena",linewidth=4)
plt.semilogy(Patmos[:,Pj],Patmos[:,5],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")


# Plot pressure vs. atmos cell number
plt.figure(4)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('Pressure')
plt.semilogy(Hatmos[:,Hj],Hatmos[:,HP],'-',color=Color1,label="Helena",linewidth=4)
plt.semilogy(Patmos[:,Pj],Patmos[:,PP],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")


# Plot temperature vs. atmos cell number
plt.figure(5)
plt.grid(True)
plt.xlabel('Tau cell number')
plt.ylabel('Temperature')
plt.semilogy(Hatmos[:,Hj],Hatmos[:,HT],'-',color=Color1,label="Helena",linewidth=4)
plt.semilogy(Patmos[:,Pj],Patmos[:,PT],'-',color=Color2,label="Peter",linewidth=2)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")



# Tell python to actually *show* me the resulting plots
show()
