#============================================================
# Read in potentially useful python modules
#============================================================
import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime, atpy, random

#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================
Color1 = cm.spring(3)
Color2 = cm.spectral(0)
Color3 = cm.Dark2(110)
Color4 = cm.Dark2(35)

#============================================================
#  Change the default plotting parameters
#============================================================
NumColors = 9
cc = [0] * NumColors
for item in range(NumColors):
    cc[item] = 256-( (item+1) * 256 / NumColors)
cc.sort()
    #shuffle(cc)
rcParams['axes.color_cycle'] = list(cm.hsv(cc))
rcParams['lines.linewidth'] = 4
#============================================================
# Read in the raw data
#============================================================
HelenaFile =  eg.fileopenbox(msg='Pick the HELENA file you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
#PeterFile = eg.fileopenbox(msg='Pick the PETER file you want to anaylze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_debugging/')
PeterFile = eg.fileopenbox(msg='Pick the PETER file you want to anaylze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/2013/March/')
#PeterFile = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_first_iter_corrections.txt'

Hname = HelenaFile.split('Research')[-1]
Pname = PeterFile.split('Research')[-1]

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+Hname+"\n"+Pname

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
# Plot stuff
#============================================================
plt.close("all")
plt.clf()
lw=4

HL = "Helena"
PL = "Peter"


plt.figure(1)
plt.title('dP')
plot(H.MassCellNumber,H.dP,linewidth=lw,color=Color1,label=HL)
plot(P.MassCellNumber,P.dP,linewidth=lw,color=Color2,label=PL)
plt.grid(True)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")

plt.figure(2)
plt.title('dr')
plot(H.MassCellNumber,H.dr,linewidth=lw,color=Color1,label=HL)
plot(P.MassCellNumber,P.dr,linewidth=lw,color=Color2,label=PL)
plt.grid(True)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")

plt.figure(3)
plt.title('dL')
plot(H.MassCellNumber,H.dL,linewidth=lw,color=Color1,label=HL)
plot(P.MassCellNumber,P.dL,linewidth=lw,color=Color2,label=PL)
plt.grid(True)
plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
legend(loc="best")

plt.figure(4)
plt.title('dT')
plot(H.MassCellNumber,H.dT,linewidth=lw,color=Color1,label=HL)
plot(P.MassCellNumber,P.dT,linewidth=lw,color=Color2,label=PL)
plt.grid(True)
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


# Tell python to actually *show* me the resulting plots
show()
