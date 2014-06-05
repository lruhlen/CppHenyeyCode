#============================================================
# Read in potentially useful python modules
#============================================================
import re, os, fnmatch, sys, easygui as eg, random as rn
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime, atpy

#============================================================
# Declare constants to help with the calculations
# and plotting
#============================================================

plt.close("all")
plt.clf()

foo=0
KeepGoing = 1
lw = 12

while (KeepGoing == 1):
    #============================================================
    # Read in the raw data
    #============================================================

    PeterFile = eg.fileopenbox(msg='Pick the PETER file you want to anaylze',default='/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/10MjNF_debugging/')
    P =  atpy.Table(PeterFile,type='ascii')

    Pname = PeterFile.split('Research')[-1]
    PL ="/".join(Pname.split('/')[Pname.split('/').index('outputs'):])

    date = datetime.datetime.today()
    date = date.strftime("%b-%d-%Y") 
    name = 'This plot was created on '+date+' from these data files:\n'+Pname
    pltcolor = cm.hsv(foo)

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

    plt.figure(1)
    plt.title('dP')

    plot(P.MassCellNumber,P.dP,linewidth=lw,color=pltcolor,label=PL)
    plt.grid(True)
    #    plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
    legend(loc="best",prop={'size':10})

    plt.figure(2)
    plt.title('dr')
    plt.grid(True)
    plot(P.MassCellNumber,P.dr,linewidth=lw,color=pltcolor,label=PL)
    #   plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
    #    legend(loc="best")

    plt.figure(3)
    plt.title('dL')
    plot(P.MassCellNumber,P.dL,linewidth=lw,color=pltcolor,label=PL)
    plt.grid(True)
    #    plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
    #    legend(loc="best")

    plt.figure(4)
    plt.title('dT')
    plot(P.MassCellNumber,P.dT,linewidth=lw,color=pltcolor,label=PL)
    plt.grid(True)
    #    plt.annotate(name, xy=(0.5, 0.1), xycoords='axes fraction',horizontalalignment='center',fontsize=10)
    #    legend(loc="best")

    # Tell python to actually *show* me the resulting plots
    show()

    foo = mod(foo+rn.randint(21,33),255)
    lw-=3

    KeepGoing = eg.ynbox(msg='Plot another file?',title='',choices=('Yes','No'),image=None)

print 'Done!'
