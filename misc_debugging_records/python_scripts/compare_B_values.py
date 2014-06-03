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

File1 ="/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/B_vals_debug_from_Peter_inputs.txt"
label1 = 'From Peter Inputs'

File2 = "/Users/laurel/Desktop/Research/CppHenyeyCode/misc_debugging_records/Sept_13_B_vals_debug_v1.txt"
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
plt.subplots_adjust(wspace=0.3,hspace=0)
plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.2)

# A little something to format the legend properly...
params = {'legend.linewidth': 0.0}
rcParams.update(params)

#============================================================
# Plot the data
#============================================================
row = [1,2,3,4]
col = [1,2,3,4]

for irow in row:
    plt.figure(irow)
    clf()
    plt.suptitle('B matrix values comparisons')
    plt.subplots_adjust(wspace=0.1,hspace=0.8)
    plt.subplots_adjust(left=0.1, right=0.9, top=0.9, bottom=0.25)

    for icol in col:
        
        plt.subplot(4,1,icol)
        htitle = 'col'+str( (irow-1)*4 + icol )
        name = 'Row '+str(irow)+', Col '+str(icol)
        thing = p[htitle]/h[htitle]

        # range padding, to make the annotated plots easier to read
        lower = min(thing) - 0.3*(abs(max(thing)-min(thing)))
        upper = 0.5*(abs(max(thing)-min(thing))) + max(1,max(thing))
        
        pylab.ylim([lower,upper])        
        plot(thing,'-o')
        plot([0,size(thing)],[1,1],'-r',linewidth=2)
        plt.annotate(name, xy=(0.8, 0.7), xycoords='axes fraction')

        print(name+'  Average: '+str(average(numpy.nan_to_num(thing))))
        
        #        show()
    print('\n')
    plt.xlabel('Mass Cell Number')
    legend([File1+'\n'+File2], loc = 'center left', bbox_to_anchor = (0,-1.5),prop={'size':8},title='This plot was created on '+date+' from these data files:')
show()
    

