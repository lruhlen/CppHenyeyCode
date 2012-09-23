import re, os, fnmatch, sys, easygui as eg
from numpy import *
from matplotlib import * 
from pylab import *
import asciitable, string, datetime
#============================================================
# Declare useful physical constants for later
#============================================================
Color1 = cm.Dark2(110)
Color2 = cm.Dark2(3)
RatioColor = cm.Dark2(110)


File1 ="/Users/laurel/Desktop/Research/BodenheimerCode/UnalteredCode/outputs/g_values_for_python.txt"
label1 = 'Peter'

File2 = eg.diropenbox(msg='Pick the run you want to analyze',default='/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/')
File2 += '/'
filelist = [ ]
for file in os.listdir(File2):
    if fnmatch.fnmatch(file,'*_G_*.txt'):
        filelist.append(file)
File2 = File2+str(filelist[0])
label2 = 'Helena'

date = datetime.datetime.today()
date = date.strftime("%b-%d-%Y") 
#============================================================
# Read in the data
#============================================================
p = asciitable.read(File1)
h = asciitable.read(File2)

#============================================================
# Assign names to the data columns
#============================================================
pCell = numpy.array(p['MassCellNumber'][0:])
hCell = numpy.array(h['MassCellNumber'][0:])

pG1 = numpy.array(p['G1'][0:])
hG1 = numpy.array(h['G1'][0:])

pG2 = numpy.array(p['G2'][0:])
hG2 = numpy.array(h['G2'][0:])

pG3 = numpy.array(p['G3'][0:])
hG3 = numpy.array(h['G3'][0:])

pG4 = numpy.array(p['G4'][0:])
hG4 = numpy.array(h['G4'][0:])


#============================================================
# Set up the multiplot layout for this data
#============================================================
plt.close('all')
plt.clf()
#plt.figure(1, figsize=(10, 8))
matplotlib.rc('xtick', labelsize=10) 
matplotlib.rc('ytick', labelsize=10) 
plt.subplots_adjust(wspace=0.3,hspace=0.3)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

# A little something to format the legend properly...
params = {'legend.linewidth': 0.25}
rcParams.update(params)

#============================================================
# Plot the data
#============================================================
plt.figure(1)
plt.subplot(2,2,1)
plot(pCell,hG1/pG1,color=RatioColor,linewidth=2,label='hG1/pG1')
#plot(pCell,pG1,color=Color1,linewidth=2,label='Peter')
plt.ylabel('G1')
legend(loc='best',prop={'size':10})

plt.subplot(2,2,2)
plot(pCell,hG2/pG2,color=RatioColor,linewidth=2,label='hG2/pG2')
#plot(pCell,pG2,color=Color1,linewidth=2,label='Peter')
plt.ylabel('G2')

plt.subplot(2,2,3)
plot(pCell,hG3/pG3,color=RatioColor,linewidth=2,label='hG3/pG3')
#plot(pCell,pG3,color=Color1,linewidth=2,label='Peter')
plt.ylabel('G3')
plt.xlabel('Mass Cell Number')

plt.subplot(2,2,4)
plot(pCell,hG4/pG4,color=RatioColor,linewidth=2,label='hG4/pG4')
#plot(pCell,pG4,color=Color1,linewidth=2,label='Peter')
plt.ylabel('G4')
plt.xlabel('Mass Cell Number')

legend([File1,File2], loc = 'center left', bbox_to_anchor = (-1.5, -0.5),prop={'size':10},title='This plot was created on '+date+' from these data files:')
show()


