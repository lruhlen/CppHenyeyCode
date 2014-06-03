import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime
#============================================================
# Declare useful physical constants for later
#============================================================
Color1 = cm.spectral(0)
Color2 = cm.Dark2(3)
RatioColor = cm.Dark2(110)

File1 ="/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/n32_1Msun_Smatrices.txt"
label1 = 'Peter'

File2 = "/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/Sept_12_S_debug_v1.txt"
label2 = 'Helena'

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 

#============================================================
# Read in the data
#============================================================
p = asciitable.read(File1,guess=True)
h = asciitable.read(File2,guess=True)


#============================================================
# Set up the multiplot layout for this data
#============================================================
plt.close('all')
plt.clf()
#plt.figure(1, figsize=(10, 8))
matplotlib.rc('xtick', labelsize=12) 
matplotlib.rc('ytick', labelsize=8) 
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

# A little something to format the legend properly...
params = {'legend.linewidth': 0.25}
rcParams.update(params)

#============================================================
# Plot the data
#============================================================
row = [1,2,3,4]
col = [1,2,3,4]

for irow in row:
    plt.figure(irow)
    clf()
    for icol in col:
        plt.subplots_adjust(wspace=0.1,hspace=0.8)
        plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
        
        plt.subplot(4,1,icol)
        htitle = 'col'+str( (irow-1)*4 + icol )
        ptitle = 'col'+str( (icol-1)*4 +irow )
        plt.title('Ratio of Row '+str(irow)+' Col '+str(icol)+' values')
        plot(p[ptitle]/h[htitle],'-o')        
    show()
    
