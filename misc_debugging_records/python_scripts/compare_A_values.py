import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime
#============================================================
file1 = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
filelist = [ ]
for file in os.listdir(file1):
    if fnmatch.fnmatch(file,'*_A_*.txt'):
        filelist.append(file)
file1 = file1+"/"+(str(filelist[0]))

file2 = '/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/n32_1Msun_Amatrix_values.txt'

HA = asciitable.read(file1)
PA = asciitable.read(file2)

Color1 = cm.spectral(0)
Color2 = cm.Dark2(3)
RatioColor = cm.Dark2(110)

#============================================================
# Set up the multiplot layout for this data
#============================================================
plt.close('all')
plt.clf()
matplotlib.rc('xtick', labelsize=10) 
matplotlib.rc('ytick', labelsize=12) 
File1 = file1.split('Desktop')[-1]
File2 = file2.split('Desktop')[-1]
date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
name = 'This plot was created on '+date+' from these data files:\n'+File1+"\n"+File2


i = [1,2,3,4]
for item in i:
    plt.figure(item)
    clf()
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
    Ptitle = 'A'+str(item)
    Htitle = 'col'+str(item)

    plt.title(Ptitle)
    plot(HA[Htitle],'-o',label='Helena',color=Color2,linewidth=4)
    plot(PA[Ptitle],'-o',label='Peter',color=Color1,linewidth=1)
    legend(loc="best")
    plt.annotate(name, xy=(-0.1, -0.25), xycoords='axes fraction',fontsize=10)

    show()

