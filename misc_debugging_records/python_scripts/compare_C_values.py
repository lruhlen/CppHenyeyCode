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

File1 ="/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/c_values_for_python.txt"
label1 = 'Peter'

File2 =  eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
File2 += '/'
filelist = [ ]
for file in os.listdir(File2):
    if fnmatch.fnmatch(file,'*_C_*.txt'):
        filelist.append(file)
File2 = File2+str(filelist[0])
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
        title = 'C'+str(irow)+str(icol)
        plt.title('Ratio of '+title+' values')
        plot(p[title]/h[title])        
    show()

#        
##plot(p['j'],p['C11'],color=Color1,label=label1)
##plot(h['j'],h['C11'],color=Color2,label=label2)
###legend()
#
#plt.subplot(4,1,2)
#plt.title('C12 values')
#plot(p['C11']/h['C11'])
##plot(p['j'],p['C12'],color=Color1,label=label1)
##plot(h['j'],h['C12'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('C13 values')
#plot(p['C11']/h['C11'])
##plot(p['j'],p['C13'],color=Color1,label=label1)
##plot(h['j'],h['C13'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('C14 values')
#plot(p['C11']/h['C11'])
##plot(p['j'],p['C14'],color=Color1,label=label1)
##plot(h['j'],h['C14'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
#
#
########
#plt.figure(2)
#clf()
#plt.subplots_adjust(wspace=0.1,hspace=0.8)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(4,1,1)
#plt.title('C21 values')
#plot(p['j'],p['C21'],color=Color1,label=label1)
#plot(h['j'],h['C21'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('C22 values')
#plot(p['j'],p['C22'],color=Color1,label=label1)
#plot(h['j'],h['C22'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('C23 values')
#plot(p['j'],p['C23'],color=Color1,label=label1)
#plot(h['j'],h['C23'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('C24 values')
#plot(p['j'],p['C24'],color=Color1,label=label1)
#plot(h['j'],h['C24'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
#
##########
#plt.figure(3)
#clf()
#plt.subplots_adjust(wspace=0.1,hspace=0.8)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(4,1,1)
#plt.title('C31 values')
#plot(p['j'],p['C31'],color=Color1,label=label1)
#plot(h['j'],h['C31'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('C32 values')
#plot(p['j'],p['C32'],color=Color1,label=label1)
#plot(h['j'],h['C32'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('C33 values')
#plot(p['j'],p['C33'],color=Color1,label=label1)
#plot(h['j'],h['C33'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('C34 values')
#plot(p['j'],p['C34'],color=Color1,label=label1)
#plot(h['j'],h['C34'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
#
#
##############
#plt.figure(4)
#clf()
#plt.subplots_adjust(wspace=0.1,hspace=0.8)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(4,1,1)
#plt.title('C41 values')
#plot(p['j'],p['C41'],color=Color1,label=label1)
#plot(h['j'],h['C41'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('C42 values')
#plot(p['j'],p['C42'],color=Color1,label=label1)
#plot(h['j'],h['C42'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('C43 values')
#plot(p['j'],p['C43'],color=Color1,label=label1)
#plot(h['j'],h['C43'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('C44 values')
#plot(p['j'],p['C44'],color=Color1,label=label1)
#plot(h['j'],h['C44'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
