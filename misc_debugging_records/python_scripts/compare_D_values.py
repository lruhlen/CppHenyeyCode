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

File1 ="/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/d_values_for_python.txt"
label1 = 'Peter'

File2 = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
File2 += '/'
filelist = [ ]
for file in os.listdir(File2):
    if fnmatch.fnmatch(file,'*_D_*.txt'):
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
        title = 'D'+str(irow)+str(icol)
        plt.title('Ratio of '+title+' values')
        plot(p[title]/h[title],'-o')        
    show()
    
#plt.figure(1)
#clf()
#plt.subplots_adjust(wspace=0.1,hspace=0.8)
#plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)
#
#plt.subplot(4,1,1)
#plt.title('D11 values')
#plot(p['j'],p['D11'],color=Color1,label=label1)
#plot(h['j'],h['D11'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('D12 values')
#plot(p['j'],p['D12'],color=Color1,label=label1)
#plot(h['j'],h['D12'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('D13 values')
#plot(p['j'],p['D13'],color=Color1,label=label1)
#plot(h['j'],h['D13'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('D14 values')
#plot(p['j'],p['D14'],color=Color1,label=label1)
#plot(h['j'],h['D14'],color=Color2,label=label2)
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
#plt.title('D21 values')
#plot(p['j'],p['D21'],color=Color1,label=label1)
#plot(h['j'],h['D21'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('D22 values')
#plot(p['j'],p['D22'],color=Color1,label=label1)
#plot(h['j'],h['D22'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('D23 values')
#plot(p['j'],p['D23'],color=Color1,label=label1)
#plot(h['j'],h['D23'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('D24 values')
#plot(p['j'],p['D24'],color=Color1,label=label1)
#plot(h['j'],h['D24'],color=Color2,label=label2)
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
#plt.title('D31 values')
#plot(p['j'],p['D31'],color=Color1,label=label1)
#plot(h['j'],h['D31'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('D32 values')
#plot(p['j'],p['D32'],color=Color1,label=label1)
#plot(h['j'],h['D32'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('D33 values')
#plot(p['j'],p['D33'],color=Color1,label=label1)
#plot(h['j'],h['D33'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('D34 values')
#plot(p['j'],p['D34'],color=Color1,label=label1)
#plot(h['j'],h['D34'],color=Color2,label=label2)
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
#plt.title('D41 values')
#plot(p['j'],p['D41'],color=Color1,label=label1)
#plot(h['j'],h['D41'],color=Color2,label=label2)
##legend()
#
#plt.subplot(4,1,2)
#plt.title('D42 values')
#plot(p['j'],p['D42'],color=Color1,label=label1)
#plot(h['j'],h['D42'],color=Color2,label=label2)
#
#plt.subplot(4,1,3)
#plt.title('D43 values')
#plot(p['j'],p['D43'],color=Color1,label=label1)
#plot(h['j'],h['D43'],color=Color2,label=label2)
#
#plt.subplot(4,1,4)
#plt.title('D44 values')
#plot(p['j'],p['D44'],color=Color1,label=label1)
#plot(h['j'],h['D44'],color=Color2,label=label2)
#plt.xlabel('Mass Cell Number')
#
#
#legend([File1,File2], loc = 'center left', bbox_to_anchor = (0, -1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
#show()
