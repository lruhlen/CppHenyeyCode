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

File1 ="/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/e_values_for_python.txt"
label1 = 'Peter'

File2 = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
File2 += '/'
filelist = [ ]
for file in os.listdir(File2):
    if fnmatch.fnmatch(file,'*_E_*.txt'):
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
        title = 'E'+str(irow)+str(icol)
        plt.title('Ratio of '+title+' values')
        plot(p[title]/h[title])        
    show()

#plt.figure(1)
#clf()
#plt.subplots_adjust(wspace=0.1,hspace=0.8)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(4,1,1)
#plt.title('E11 values')
#plot(p['j'],p['E11'],color=Color1,label=label1)
#plot(h['j'],h['E11'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('E12 values')
#plot(p['j'],p['E12'],color=Color1,label=label1)
#plot(h['j'],h['E12'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('E13 values')
#plot(p['j'],p['E13'],color=Color1,label=label1)
#plot(h['j'],h['E13'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('E14 values')
#plot(p['j'],p['E14'],color=Color1,label=label1)
#plot(h['j'],h['E14'],color=Color2,label=label2)
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
#plt.title('E21 values')
#plot(p['j'],p['E21'],color=Color1,label=label1)
#plot(h['j'],h['E21'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('E22 values')
#plot(p['j'],p['E22'],color=Color1,label=label1)
#plot(h['j'],h['E22'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('E23 values')
#plot(p['j'],p['E23'],color=Color1,label=label1)
#plot(h['j'],h['E23'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('E24 values')
#plot(p['j'],p['E24'],color=Color1,label=label1)
#plot(h['j'],h['E24'],color=Color2,label=label2)
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
#plt.title('E31 values')
#plot(p['j'],p['E31'],color=Color1,label=label1)
#plot(h['j'],h['E31'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('E32 values')
#plot(p['j'],p['E32'],color=Color1,label=label1)
#plot(h['j'],h['E32'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('E33 values')
#plot(p['j'],p['E33'],color=Color1,label=label1)
#plot(h['j'],h['E33'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('E34 values')
#plot(p['j'],p['E34'],color=Color1,label=label1)
#plot(h['j'],h['E34'],color=Color2,label=label2)
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
#plt.title('E41 values')
#plot(p['j'],p['E41'],color=Color1,label=label1)
#plot(h['j'],h['E41'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('E42 values')
#plot(p['j'],p['E42'],color=Color1,label=label1)
#plot(h['j'],h['E42'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('E43 values')
#plot(p['j'],p['E43'],color=Color1,label=label1)
#plot(h['j'],h['E43'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('E44 values')
#plot(p['j'],p['E44'],color=Color1,label=label1)
#plot(h['j'],h['E44'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
