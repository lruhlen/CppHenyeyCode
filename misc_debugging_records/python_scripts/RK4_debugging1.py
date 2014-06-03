#============================================================
# Read in potentially useful python modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime, atpy

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

H  = atpy.Table(HelenaFile,type='ascii')
P =  atpy.Table(PeterFile,type='ascii')

#============================================================
# Set up indexing
#============================================================
# To get the column names for each table, enter
# H.columns
# P.columns
# at the python prompt

#============================================================
# Set up some useful variables for later plotting
#============================================================
foo = []
for j in range(size(P.J)):
    thing = min(P.adnab1[j],P.radnab1[j])
    foo.append(thing)
#
HNab = H.tpnab1 * H.P1 / H.T1
PNab = P.tpnab1 *P.P1/P.T1

#============================================================
# Plot stuff
#============================================================
plt.close("all")
plt.clf()

Hname = HelenaFile.split('Research')[-1]
Pname = PeterFile.split('Research')[-1]

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+Hname+"\n"+Pname

plt.xlabel("atmospheric tau cell number")
plt.ylabel("nabla")
plt.grid("on")

plot(foo,color="orange",linewidth=8,label='Naive Peter nabla values')
#plot(RealNab,color="black",linewidth=3,label='Naive Helena nabla values')
plot(P.J,PNab,'--',color="aqua",linewidth=3,label="Actual Peter nabla values")
plot(H.J,HNab,color="black",linewidth=2,label="Actual Helena nabla values")

plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")

#plot(P.tpnab1 * P.P1 / P.T1, color=cm.spring(40),linewidth=3,label='Actual Peter nabla values')
#legend()
#
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
#show()
